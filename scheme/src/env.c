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
#include<math.h>
#define A 31 /*utilisé seulement dans la fonction de hachage (dangereux si A réutilisé)*/


object research_symbol_in_obj( object o, object symb ) {
    object obj = o;
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

    if( car(env) == nil) return nil;
    if( is_symbol_in_env( env, symb) ) return is_symbol_in_env( env, symb);
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
    is_symbol_in_env( env,symb )->this.pair.cdr = value;
    return is_symbol_in_env( env,symb );
}

void add_new_env(object* env) {
    object obj = make_env();
    if(obj) {
        
        obj->this.pair.cdr = *env;
        *env = obj;
    }
    /*si c'est null il faut faire un warning*/
}







