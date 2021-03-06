/**
 * @file env.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Oct 11 15:04:46 2016
 * @brief fonction de gestion de l'environnement.
 *
 * fonction de gestion de l'environnement.
 */
#include "env.h"
#include<string.h>
#include<strings.h>
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include"eval.h"
#include"calcul.h"
#define A 31 /*utilisé seulement dans la fonction de hachage*/


object research_symbol_in_obj( object o, object symb ) {
    object obj = o;
    if(obj && obj->type != SFS_PAIR) return nil;
    while( obj != nil && obj != NULL ) {
        if( !strcasecmp(car(car(obj))->this.symbol,symb->this.symbol) ) return car(obj);
        obj = cdr(obj);
    }
    return nil;
}


object is_symbol_in_env( object env, object symb ) {
    return research_symbol_in_obj(car(env)->this.tab[hachage(symb->this.symbol,car(env)->type)],symb);
}

object is_symbol_in_all_env( object env, object symb ) {
    object obj;
    if(env == nil || env == NULL) return nil;
    obj = is_symbol_in_env( env,symb );
    if( obj != nil ) return obj;
    return is_symbol_in_all_env( cdr(env),symb );
}

object get_symbol_value( object env, object symb) {
    return cdr(is_symbol_in_all_env(env,symb));
}

int hachage(char*mot,int dim_tab_hach) {
    int h;
    int i;
    int taillemot=strlen(mot);
    h=tolower(mot[taillemot-1]);
    for(i=taillemot-2; i>=0; i--) {
        h=h*A+tolower(mot[i]);
    }
    return abs(h)%dim_tab_hach;
}

object add_symbol_to_env( object env, object symb, object value ) {
    object obj = make_pair();
    if(obj) {
        obj->this.pair.car = make_pair();
        obj->this.pair.car->this.pair.car = symb;
        obj->this.pair.car->this.pair.cdr = value;
        obj->this.pair.cdr = car(env)->this.tab[hachage(symb->this.symbol,car(env)->type)];
        car(env)->this.tab[hachage(symb->this.symbol,car(env)->type)]= obj;
        return obj->this.pair.car;
    }
    return nil;
}
object set_symbol_value_in_env( object env, object symb, object value) { /*renvoyer un objet plutot qu'un int*/

    if(!is_symbol_in_env( env,symb )) return nil;
    if(value != NULL) {
        is_symbol_in_env( env,symb )->this.pair.cdr = value;
        return is_symbol_in_env( env,symb );
    }
    return NULL;
}

int add_new_env(object* env) {
    object obj = make_env();
    if(obj) {

        obj->this.pair.cdr = *env;
        *env = obj;
        return 1;
    }
    return 0;
    /*si c'est null il faut faire un warning*/
}

void add_object_to_list(object* list,object obj) {
    object objc = make_pair();
    if(obj) {
        objc->this.pair.car = obj;
        objc->this.pair.cdr = *list;
        *list = objc;
    }
}
void inverse_list(object*list) {
    object obj,objres = nil;
    obj = *list;
    while(obj != nil) {
        add_object_to_list(&objres,car(obj));
        obj = cdr(obj);
    }
    *list = objres;
}

int sizeof_list(object list){
	object obj = list; int i = 0;
	if(list->type != SFS_PAIR && list->type != SFS_NIL) return 1;
	while(obj != nil ){
		i++;
		obj = cdr(obj);
	}
	return i;
}	

void print_env( object env ){
	object objres,obj2,obj1 = env;int i;
	if(env == nil || env == NULL){
		
		return ;
	}
	fprintf(stderr,"**************begin***************\n");
	for( i = 0; i< SFS_TAB; i++ ){
		obj2 = car(obj1)->this.tab[i];
		while(obj2 != nil && obj2 != NULL){
			if(!strcasecmp(".",car(car(obj2))->this.symbol)){
				obj2 = cdr(obj2);
				continue;
			}
			REPORT_MSG(">>> %s ------------------- ",car(car(obj2))->this.symbol);
			init_stack();
			objres = sfs_eval(car(car(obj2)),extend_env);
			if(objres && !(objres->type == SFS_SYMBOL && !strcasecmp(objres->this.symbol,"#<procedure>"))) REPORT_MSG("<#@ internal constant>\n");
			fprintf(stderr,"\n");
			obj2 = cdr(obj2);
		}
	}
	if(cdr(obj1) != nil )fprintf(stderr,"*************scope environment************\n");
	print_env( cdr(obj1) );
}




void print_stack(object stack) {
    object obj = stack;
    int i = 1;
    REPORT_MSG(";STACK TRACE\n");
    while(obj != nil ) {
        REPORT_MSG("%d; ",i);
        sfs_print(stderr,car(obj));
        fprintf(stderr,"\n");
        obj = cdr(obj);
        i++;
    }
}

void init_stack(void) {
    STACK 	= nil;
}






