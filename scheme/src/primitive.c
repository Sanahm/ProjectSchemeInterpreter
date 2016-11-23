#include "primitive.h"
#include "object.h"
#include "env.h"
#include "read.h"
#include<limits.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>


/*primitive: arithmétique entière*/
object plus_t( object list ){
	/* on prend en paramètre une liste d'object dont il faut faire la somme */
    object objres,obj = NULL;int i =1;num n;
    n.numtype = NUM_INTEGER;
    n.this.integer = 0;
    objres = make_number(n);
    obj = list;
	while( obj != nil ){
        objres = operation(objres,car(obj),"+");
        if(objres == NULL ){
        	REPORT_MSG(";ERROR: +: Wrong type in arg%d ",i);
        	sfs_print(stderr,car(obj)); fprintf( stderr,"\n");
    		return objres;
    	}
    	if(objres->type == SFS_SYMBOL && !strcasecmp(objres->this.symbol,"nan")) break;
        obj = cdr(obj);
        i++;
    }
    return objres;
}

object minus_t( object list ){
	/* on prend en paramètre une liste d'object dont il faut faire la soustraction */
    object objres,obj = NULL;int i =1;num n;
    n.numtype = NUM_INTEGER;
    n.this.integer = 0;
    objres = make_number(n);
    if(list == nil) {
	    REPORT_MSG(";ERROR: -: Wrong number of args given\n; expected at least one arg\n");
    	return NULL;
    }
    /*if(cdr(list) == nil){*/
    	
    obj = list;
	while( obj != nil ){
        if(i == 1 && cdr(list) != nil) objres = operation(objres,car(obj),"+");
        else objres = operation(objres,car(obj),"-");
        if(objres == NULL ){
        	REPORT_MSG(";ERROR: -: Wrong type in arg%d ",i);
        	sfs_print(stderr,car(obj)); fprintf( stderr,"\n");
    		return objres;
    	}
    	if(objres->type == SFS_SYMBOL && !strcasecmp(objres->this.symbol,"nan")) break;
        obj = cdr(obj);
        i++;
    }
    return objres;
}

object mult_t( object list ){
	/* on prend en paramètre une liste d'object dont il faut faire la multiplication */
    object objres,obj = NULL;int i =1;num n;
    n.numtype = NUM_INTEGER;
    n.this.integer = 1;
    objres = make_number(n);
    obj = list;
	while( obj != nil ){
        objres = operation(objres,car(obj),"*");
        if(objres == NULL ){
        	REPORT_MSG(";ERROR: *: Wrong type in arg%d ",i);
        	sfs_print(stderr,car(obj)); fprintf( stderr,"\n");
    		return objres;
    	}
    	if(objres->type == SFS_SYMBOL && !strcasecmp(objres->this.symbol,"nan")) break;
        obj = cdr(obj);
        i++;
    }
    return objres;
}

object division_t( object list ){
	/* on prend en paramètre une liste d'object dont il faut faire la division */
    object objres,obj = NULL;int i =1;num n;
    n.numtype = NUM_INTEGER;
    n.this.integer = 1;
    objres = make_number(n);
    if(list == nil) {
	    REPORT_MSG(";ERROR: /: Wrong number of args given\n; expected at least one arg\n");
    	return NULL;
    }
    obj = list;
	if(cdr(obj) == nil){
		objres = operation(objres,car(obj),"/");
        if(objres == NULL ){
        	REPORT_MSG(";ERROR: /: Wrong type in arg%d ",i);
        	sfs_print(stderr,car(obj)); fprintf( stderr,"\n");
    		return objres;
    	}
    	return objres;
    }
    i++;
    objres = car(list);
    obj = cdr(obj);
	while( obj != nil ){
        objres = operation(objres,car(obj),"/");
        if(objres == NULL ){
        	REPORT_MSG(";ERROR: /: Wrong type in arg%d ",i);
        	sfs_print(stderr,car(obj)); fprintf( stderr,"\n");
    		return objres;
    	}
    	if(objres->type == SFS_SYMBOL && !strcasecmp(objres->this.symbol,"nan")) break;
        obj = cdr(obj);
        i++;
    }
    return objres;
}

object quotient_t( object list ){
	/* on prend en paramètre une liste d'object dont il faut faire la division entière*/
	num n; object obj;
    if(list == nil || cdr(list) == nil || cdr(cdr(list)) != nil) {
	    REPORT_MSG(";ERROR: quotient: Wrong number of args given\n; expected only 2 args\n");
    	return NULL;
    }
	obj = car(list);
    if( obj->type != SFS_NUMBER || (obj->type == SFS_NUMBER && obj->this.number.numtype != NUM_INTEGER)){    
    	REPORT_MSG(";ERROR: quotient: Wrong type in arg1 ");   
    	sfs_print(stderr,obj); fprintf( stderr,"\n");
		return NULL; 
	}
	obj = car(cdr(list));
	if( obj->type != SFS_NUMBER || (obj->type == SFS_NUMBER && obj->this.number.numtype != NUM_INTEGER) ){
    	REPORT_MSG(";ERROR: quotient: Wrong type in arg2 ");   
    	sfs_print(stderr,obj); fprintf( stderr,"\n");
		return NULL; 
	}
	if( obj->this.number.numtype == NUM_INTEGER && obj->this.number.this.integer == 0 ){
    	REPORT_MSG(";ERROR: quotient: numerical overflow ");   
    	sfs_print(stderr,obj); fprintf( stderr,"\n");
		return NULL; 
	}
    n.numtype = NUM_INTEGER;
    n.this.integer = ((object)car(list))->this.number.this.integer/obj->this.number.this.integer;
    return make_number(n);
}

object interaction_env_t( object list ){
	if(list!=nil ){
		REPORT_MSG(";ERROR: interaction-environment: Do not take any arg\n");
		return NULL;
	}
	print_env(environment);
	return make_symbol("Reading environment complete");
}

	
object remainder_t( object list ){
	/* on prend en paramètre une liste d'object dont il faut faire la division entière*/
	num n; object obj;
    if(list == nil || cdr(list) == nil || cdr(cdr(list)) != nil) {
	    REPORT_MSG(";ERROR: remainder: Wrong number of args given\n; expected only 2 args\n");
    	return NULL;
    }
	obj = car(list);
    if( obj->type != SFS_NUMBER || (obj->type == SFS_NUMBER && obj->this.number.numtype != NUM_INTEGER)){    
    	REPORT_MSG(";ERROR: remainder: Wrong type in arg1 ");   
    	sfs_print(stderr,obj); fprintf( stderr,"\n");
		return NULL; 
	}
	obj = car(cdr(list));
	if( obj->type != SFS_NUMBER || (obj->type == SFS_NUMBER && obj->this.number.numtype != NUM_INTEGER) ){
    	REPORT_MSG(";ERROR: remainder: Wrong type in arg2 ");   
    	sfs_print(stderr,obj); fprintf( stderr,"\n");
		return NULL; 
	}
	if( obj->this.number.numtype == NUM_INTEGER && obj->this.number.this.integer == 0 ){
    	REPORT_MSG(";ERROR: remainder: numerical overflow ");   
    	sfs_print(stderr,obj); fprintf( stderr,"\n");
		return NULL; 
	}
    n.numtype = NUM_INTEGER;
    n.this.integer = ((object)car(list))->this.number.this.integer%obj->this.number.this.integer;
    return make_number(n);
}
/******************************calculs trigonométriques********************************/
object trigo_t( object list, double (*pfunct)(double),char*name ){ /* symbol to string(symbtostr): retourne le caractere ascii*/
	object obj;num n;
    if(list == nil || cdr(list) != nil) {
	    REPORT_MSG(";ERROR: %s: Wrong number of args given\n; expected one arg\n",name);
    	return NULL;
    }
	obj = car(list);
    if( obj->type != SFS_NUMBER && obj->type != SFS_SYMBOL || (obj->type == SFS_SYMBOL && !strcasecmp(obj->this.symbol,"nan") )){
    	REPORT_MSG(";ERROR: %s: Wrong type in arg1 ",name);   
    	sfs_print(stderr,obj); sprintf(stderr,"\n");
		return NULL; 
	}
	n.numtype = NUM_REAL;
	if(obj->this.number.numtype == NUM_REAL){
		n.this.real = pfunct(obj->this.number.this.real);
		return make_number(n);
	}
	else if(obj->this.number.numtype == NUM_INTEGER){
		n.this.real = pfunct(obj->this.number.this.integer);
		return make_number(n);
	}
	else{
		if(!strcasecmp(obj->this.symbol,"+inf")) n.this.real =  pfunct(LONG_MAX);
		if(!strcasecmp(obj->this.symbol,"-inf")) n.this.real =  pfunct(LONG_MIN);
		return make_number(n);
	}
}
object cos_t( object list ){
	return trigo_t(list,cos,"cos");
}
object sin_t( object list ){
	return trigo_t(list,sin,"sin");
}
object tan_t( object list ){
	return trigo_t(list,tan,"tan");
}
object cosh_t( object list ){
	return trigo_t(list,cosh,"cosh");
}
object sinh_t( object list ){
	return trigo_t(list,sinh,"sinh");
}
object tanh_t( object list ){
	return trigo_t(list,tanh,"tanh");
}
object acos_t( object list ){
	return trigo_t(list,acos,"acos");
}
object asin_t( object list ){
	return trigo_t(list,asin,"asin");
}
object atan_t( object list ){
	return trigo_t(list,atan,"atan");
}
object exp_t( object list ){
	return trigo_t(list,exp,"exp");
}
object log_t( object list ){
	return trigo_t(list,log,"log");
}
object log10_t( object list ){
	return trigo_t(list,log10,"log10");
}
object ceiling_t( object list ){
	return trigo_t(list,ceil,"ceiling");
}
object floor_t( object list ){
	return trigo_t(list,floor,"floor");
}
object abs_t( object list ){
	return trigo_t(list,fabs,"abs");
}
object sqrt_t( object list ){
	return trigo_t(list,sqrt,"sqrt");
}
object round_t( object list ){
	
	if(((object) car(list))->type != SFS_NUMBER) return trigo_t(list,floor,"round");
	if(((object) car(list))->this.number.numtype == NUM_INTEGER) return trigo_t(list,floor,"round");
	else{
		if((((object) car(list))->this.number.this.real - floor(((object) car(list))->this.number.this.real)) < 0.5) return trigo_t(list,floor,"round");
		else return trigo_t(list,ceil,"round");
}
}
int pgcd( long int a, long int b){ /* plus grand commun diviseur*/
	int r = a%b;
	if(r == 0) return fabs(b);
	return pgcd(b,r);
}
int ppcm(  long int a, long int b) {
	if (a == 0 || b == 0) return 0;
	return (a*b)/pgcd(a,b);
}

object pgcdpcm_t( object list,int u, int (*pfunct)(int,int),char*name ){
	num n; object obj;
	n.numtype = NUM_INTEGER; n.this.integer =  u;
    if(list == nil) return make_number(n);
    if(cdr(list) == nil || cdr(cdr(list)) != nil) {
	    REPORT_MSG(";ERROR: %s: Wrong number of args given\n; expected only 2 args\n",name);
    	return NULL;
    }
	obj = car(list);
    if( obj->type != SFS_NUMBER || (obj->type == SFS_NUMBER && obj->this.number.numtype != NUM_INTEGER)){    
    	REPORT_MSG(";ERROR: %s: Wrong type in arg1 ",name);  
    	sfs_print(stderr,obj); fprintf( stderr,"\n");
		return NULL; 
	}
	obj = car(cdr(list));
	if( obj->type != SFS_NUMBER || (obj->type == SFS_NUMBER && obj->this.number.numtype != NUM_INTEGER) ){
		REPORT_MSG(";ERROR: %s: Wrong type in arg2 ",name); 
    	sfs_print(stderr,obj); fprintf( stderr,"\n");
		return NULL; 
	}
    n.this.integer = pfunct(((object)car(list))->this.number.this.integer,obj->this.number.this.integer);
    return make_number(n);
}
/*yes yes yes j'ai gagné des lignes youpiiii*/
object pgcd_t(object list){
	pgcdpcm_t(list,0,pgcd,"gcd");
}
object ppcm_t(object list){
	pgcdpcm_t(list,1,ppcm,"lcm");
}

/******************************************************************************************/
object cmp_t( object list, char*op){
	/* on prend en paramètre une liste d'object dont il faut faire la somme */
    object objres,obj = NULL;int i =1;
    if(list == nil) return VRAI;   
    objres = car(list);
    if( objres->type != SFS_NUMBER && objres->type != SFS_SYMBOL ){
    	REPORT_MSG(";ERROR: %s: Wrong type to apply in arg%d ",op,i);
    	sfs_print(stderr,objres); fprintf( stderr,"\n");
		return NULL;
	}
	i++;
    obj = cdr(list);
	while( obj != nil && objres != FAUX ){
        objres = operation(car(list),car(obj),op);
        if(objres == FAUX) return FAUX;
        if(objres == NULL){
        	REPORT_MSG(";ERROR: %s: Wrong type to apply in arg%d ",op,i);
        	sfs_print(stderr,car(obj)); fprintf( stderr,"\n");
    		return objres;
    	}
        obj = cdr(obj);
        i++;
    }
    return VRAI;
}

object inf_t( object list){
	return cmp_t(list,"<");
}

object infe_t( object list){
	return cmp_t(list,"<=");
}

object sup_t( object list){
	return cmp_t(list,">");
}

object supe_t( object list){
	return cmp_t(list,">=");
}

object ctoi_t( object list ){ /* char to int(ctoi): retourne le caractere ascii*/

	num n; object obj;
    if(list == nil || cdr(list) != nil) {
	    REPORT_MSG(";ERROR: char->integer: Wrong number of args given\n; expected one arg\n");
    	return NULL;
    }
	obj = car(list);
    if( obj->type != SFS_CHARACTER ){    
    	REPORT_MSG(";ERROR: char->integer: Wrong type to apply in arg1 ");   
    	sfs_print(stderr,obj); fprintf( stderr,"\n");
		return NULL; 
	}
	n.numtype = NUM_INTEGER;
	n.this.integer = obj->this.character;
	return make_number(n);    
}

object itoc_t( object list ){ /* int to char(itoc): retourne le caractere ascii*/

	object obj;
    if(list == nil || cdr(list) != nil) {
	    REPORT_MSG(";ERROR: integer->char: Wrong number of args given\n; expected one arg\n");
    	return NULL;
    }
	obj = car(list);
    if( obj->type != SFS_NUMBER || (obj->type == SFS_NUMBER && obj->this.number.numtype != NUM_INTEGER) ){    
    	REPORT_MSG(";ERROR: integer->char: Wrong type to apply in arg1 ");   
    	sfs_print(stderr,obj); fprintf( stderr,"\n");
		return NULL; 
	}
    if( (obj->this.number.this.integer < 32) || (obj->this.number.this.integer > 127) ){    
    	REPORT_MSG(";ERROR: integer->char: Argument out of range [32 127] ");   
    	sfs_print(stderr,obj); fprintf( stderr,"\n");
		return NULL; 
	}
	return make_character(obj->this.number.this.integer);
 
}

object symbtostr_t( object list ){ /* symbol to string(symbtostr): retourne le caractere ascii*/
	object obj;
    if(list == nil || cdr(list) != nil) {
	    REPORT_MSG(";ERROR: symbol->string: Wrong number of args given\n; expected one arg\n");
    	return NULL;
    }
	obj = car(list);
    if( obj->type != SFS_SYMBOL ){
    	REPORT_MSG(";ERROR: symbol->string: Wrong type to apply in arg1 ");   
    	sfs_print(stderr,obj); fprintf( stderr,"\n");
		return NULL; 
	}
	obj->type = SFS_STRING;
	return obj;
}

object strtosymb_t( object list ){ /* symbol to string(symbtostr): retourne le caractere ascii*/
	object obj;
    if(list == nil || cdr(list) != nil) {
	    REPORT_MSG(";ERROR: symbol->string: Wrong number of args given\n; expected one arg\n");
    	return NULL;
    }
	obj = car(list);
    if( obj->type != SFS_STRING ){
    	REPORT_MSG(";ERROR: symbol->string: Wrong type to apply in arg1 ");   
    	sfs_print(stderr,obj); fprintf( stderr,"\n");
		return NULL; 
	}
	obj->type = SFS_SYMBOL;
	return obj;
}



object strtonum_t( object list ){
	num n; object obj1,obj2; char * endptr,*str; uint here = 0;int i = 0;
    if(list == nil || (cdr(list) != nil && cdr(cdr(list)) != nil) ) {
	    REPORT_MSG(";ERROR: string->number: Wrong number of args given\n; expected form (string->number str base*) default base is 10\n");
    	return NULL;
    }
	obj1 = car(list);
    if( obj1->type != SFS_STRING ){    
    	REPORT_MSG(";ERROR: string->number: Wrong type to apply in arg1 ");   
    	sfs_print(stderr,obj1); fprintf( stderr,"\n");
		return NULL; 
	}
	obj2 = car(cdr(list));
	if(obj2){
		if( obj2->type != SFS_NUMBER || (obj2->type == SFS_NUMBER && obj2->this.number.numtype != NUM_INTEGER) ){
			REPORT_MSG(";ERROR: string->number: Wrong type to apply in ");   
			sfs_print(stderr,obj2); fprintf( stderr,"\n");
			return NULL; 
		}
		if( obj2->this.number.this.integer != 2 && obj2->this.number.this.integer != 8 && obj2->this.number.this.integer != 10 && obj2->this.number.this.integer != 16){
			return FAUX; 
		}
		n.numtype = NUM_INTEGER;
		endptr = NULL;
		str = obj1->this.string;
		n.this.integer = strtol(str,&endptr,obj2->this.number.this.integer);
		if(endptr[0] != '\0' || (endptr == str && n.this.integer == 0)){
			return FAUX;
		}
		
		return make_number(n);
	}
	str = obj1->this.string;
	i = strlen(str)-1;
	obj2= sfs_read(str,&here);
	if(!obj2 || obj2->type != SFS_NUMBER ) return FAUX;
	return obj2;
	
}

object numtostr_t( object list ){

	object obj1,obj2; int res = 0;int taille = 0;num n; char* str,*strs;int i =0;
    if(list == nil || (cdr(list) != nil && cdr(cdr(list)) != nil) ) {
	    REPORT_MSG(";ERROR: number->string: Wrong number of args given\n; expected form (string->number num base*) default base is 10\n");
    	return NULL;
    }
	obj1 = car(list);
	if( obj1->type == SFS_SYMBOL && (!strcasecmp(obj1->this.symbol,"+inf") || !strcasecmp(obj1->this.symbol,"-inf") || !strcasecmp(obj1->this.symbol,"nan")) ) return obj1;
    if( obj1->type != SFS_NUMBER){    
    	REPORT_MSG(";ERROR: number->string: Wrong type to apply in arg1 ");   
    	sfs_print(stderr,obj1); fprintf( stderr,"\n");
		return NULL; 
	}
	obj2 = car(cdr(list));
	if(!obj2){
		n.numtype = NUM_INTEGER; /*par défaut la base c'est 10*/
		n.this.integer = 10;
		obj2 = make_number(n);
	}
	if( obj2->type != SFS_NUMBER || (obj2->type == SFS_NUMBER && obj2->this.number.numtype != NUM_INTEGER) ){
		REPORT_MSG(";ERROR: number->string: Wrong type to apply in ");   
		sfs_print(stderr,obj2); fprintf( stderr,"\n");
		return NULL; 
	}
	if( obj2->this.number.this.integer != 2 && obj2->this.number.this.integer != 8 && obj2->this.number.this.integer != 10 && obj2->this.number.this.integer != 16){
		return FAUX; 
	}
	if( obj1->this.number.numtype == NUM_INTEGER ){
		res = obj1->this.number.this.integer;
		taille = log(obj1->this.number.this.integer)/log(obj2->this.number.this.integer)+1; /*nombre de bits utilisés pour coder res*/
		str = calloc(taille,sizeof(*str));
		strs = calloc(taille,sizeof(*strs));
		strs[taille] = '\0';
		i = taille -1;
		while( res != 0 ){
			if(res%obj2->this.number.this.integer < 10){
				sprintf( str,"%d",res%obj2->this.number.this.integer);
				strs[i] = str[0];
			}
			else strs[i] = 87+res%obj2->this.number.this.integer;
			res = res/obj2->this.number.this.integer;
			i--;
		}
		return make_string(strs);
	}
	if(sprintf( str,"%.15G",obj1->this.number.this.real));
	return make_string(str);

}

object equal_t( object list ){

	object obj,obj1,obj2; object t = nil;
    if(list == nil || cdr(list) == nil) return VRAI;
    
	obj1 = car(list); obj = cdr(list);
	while( obj != nil ){
		obj2 = car(obj);
		if( obj1->type != obj2->type) return FAUX;
		 
		if( obj1->type == SFS_NUMBER ){
			if( obj1->this.number.numtype != obj1->this.number.numtype ) return FAUX; 
			if( obj1->this.number.numtype == NUM_INTEGER && (obj1->this.number.this.integer != obj2->this.number.this.integer)) return FAUX;
			if( obj1->this.number.numtype == NUM_REAL && (obj1->this.number.this.real != obj2->this.number.this.real)) return FAUX;
		}
		if( obj1->type == SFS_CHARACTER ){
			if( obj1->this.character != obj2->this.character ) return FAUX;
		}
		if( obj1->type == SFS_SYMBOL ){
			if( strcasecmp(obj1->this.symbol,obj2->this.symbol) ) return FAUX;
		}
		if( obj1->type == SFS_STRING ){
			if( strcasecmp(obj1->this.string,obj2->this.string) ) return FAUX;
		}
		if( obj1->type == SFS_BOOLEAN ){
			if( obj1->this.boolean != obj2->this.boolean ) return FAUX;
		}
		if( obj1->type == SFS_PAIR ){
			while(obj1 != nil && obj1 != NULL && obj2 != nil && obj2 != NULL){
				add_object_to_list(&t,car(obj2));
				add_object_to_list(&t,car(obj1));
				if(t){
					if(equal_t(t) == FAUX) return FAUX;
					t = nil; /* on réinitialise*/
				}
				obj1 = cdr(obj1);
				obj2 = cdr(obj2);
			}
			if((obj1 == nil && obj2 != nil) || (obj2 == nil && obj1 != nil)) return FAUX;
			if((obj1 == NULL && obj2 != NULL) || (obj2 == NULL && obj1 != NULL)) return FAUX;
			
		}
		obj1 = car(list);		
		obj = cdr(obj);
	}
	return VRAI;
}

object eqv_t( object list ){
	/* on prend en paramètre une liste d'object dont il faut faire la division entière*/
	object obj,obj1,obj2; object t = nil;
    if(list == nil || cdr(list) == nil) return VRAI;
    
	obj1 = car(list); obj = cdr(list);
	while( obj != nil ){
		obj2 = car(obj);
		if( obj1->type != obj2->type) return FAUX;
		 
		if( obj1->type == SFS_NUMBER ){
			if( obj1->this.number.numtype != obj1->this.number.numtype ) return FAUX; 
			if( obj1->this.number.numtype == NUM_INTEGER && (obj1->this.number.this.integer != obj2->this.number.this.integer)) return FAUX;
			if( obj1->this.number.numtype == NUM_REAL && (obj1->this.number.this.real != obj2->this.number.this.real)) return FAUX;
		}
		if( obj1->type == SFS_CHARACTER ){
			if( obj1->this.character != obj2->this.character ) return FAUX;
		}
		if( obj1->type == SFS_SYMBOL ){
			if( strcasecmp(obj1->this.symbol,obj2->this.symbol) ) return FAUX;
		}
		if( obj1->type == SFS_STRING ){
			if(&obj1 != &obj2) return make_symbol("#<unspecified>");
			if( strcasecmp(obj1->this.string,obj2->this.string) ) return FAUX;
		}
		if( obj1->type == SFS_BOOLEAN ){
			if( obj1->this.boolean != obj2->this.boolean ) return FAUX;
		}
		if( obj1->type == SFS_PAIR ){
			if(&obj1 != &obj2) return make_symbol("#<unspecified>");
			while(obj1 != nil && obj1 != NULL && obj2 != nil && obj2 != NULL){
				if(car(obj1) != car(obj2)) return make_symbol("#<unspecified>");
				add_object_to_list(&t,car(obj2));
				add_object_to_list(&t,car(obj1));
				if(t){
					if(equal_t(t) == FAUX) return FAUX;
					t = nil; /* on réinitialise*/
				}
				obj1 = cdr(obj1);
				obj2 = cdr(obj2);
			}
			if((obj1 == nil && obj2 != nil) || (obj2 == nil && obj1 != nil)) return FAUX;
			if((obj1 == NULL && obj2 != NULL) || (obj2 == NULL && obj1 != NULL)) return FAUX;
			
		}
		obj1 = car(list);		
		obj = cdr(obj);
	}
	return VRAI;
}

object eq_t( object list ){
	
	object obj,obj1,obj2; object t = nil;
    if(list == nil || cdr(list) == nil) return VRAI;
    
	obj1 = car(list); obj = cdr(list);
	while( obj != nil ){
		obj2 = car(obj);
		if( obj1->type != obj2->type) return FAUX;
		 
		if( obj1->type == SFS_NUMBER ){
			if(&obj1 != &obj2) return make_symbol("#<unspecified>");
			if( obj1->this.number.numtype != obj1->this.number.numtype ) return FAUX; 
			if( obj1->this.number.numtype == NUM_INTEGER && (obj1->this.number.this.integer != obj2->this.number.this.integer)) return FAUX;
			if( obj1->this.number.numtype == NUM_REAL && (obj1->this.number.this.real != obj2->this.number.this.real)) return FAUX;
		}
		if( obj1->type == SFS_CHARACTER ){
			if( obj1->this.character != obj2->this.character ) return FAUX;
		}
		if( obj1->type == SFS_SYMBOL ){
			if( strcasecmp(obj1->this.symbol,obj2->this.symbol) ) return FAUX;
		}
		if( obj1->type == SFS_STRING ){
			if(&obj1 != &obj2) return make_symbol("#<unspecified>");
			if( strcasecmp(obj1->this.string,obj2->this.string) ) return FAUX;
		}
		if( obj1->type == SFS_BOOLEAN ){
			if( obj1->this.boolean != obj2->this.boolean ) return FAUX;
		}
		if( obj1->type == SFS_PAIR ){
			if(&obj1 != &obj2) return make_symbol("#<unspecified>");
			while(obj1 != nil && obj1 != NULL && obj2 != nil && obj2 != NULL){
				if(car(obj1) != car(obj2)) return make_symbol("#<unspecified>");
				add_object_to_list(&t,car(obj2));
				add_object_to_list(&t,car(obj1));
				if(t){
					if(equal_t(t) == FAUX) return FAUX;
					t = nil; /* on réinitialise*/
				}
				obj1 = cdr(obj1);
				obj2 = cdr(obj2);
			}
			if((obj1 == nil && obj2 != nil) || (obj2 == nil && obj1 != nil)) return FAUX;
			if((obj1 == NULL && obj2 != NULL) || (obj2 == NULL && obj1 != NULL)) return FAUX;
			
		}
		obj1 = car(list);		
		obj = cdr(obj);
	}
	return VRAI;
}

object isboolean_t( object  list){
	object obj=car(list);
	if(cdr(list) != nil){
		REPORT_MSG(";ERROR: boolean?: Wrong number of args given\n; expected only one arg\n");
    		return NULL;
    	}
	if(obj->type == SFS_BOOLEAN) return VRAI;
	return FAUX;
}

object isinteger_t( object list){
	object obj=car(list);
	if(cdr(list) != nil){
		REPORT_MSG(";ERROR: integer?: Wrong number of args given\n; expected only one arg\n");
    		return NULL;
    	}
	if(obj->type == SFS_NUMBER && obj->this.number.numtype == NUM_INTEGER) return VRAI;
	return FAUX;
}
object isreal_t(object list){
	object obj=car(list);
	if(cdr(list) != nil){
		REPORT_MSG(";ERROR: real?: Wrong number of args given\n; expected only one arg\n");
    		return NULL;
    	}
	if(obj->type == SFS_NUMBER && obj->this.number.numtype == NUM_REAL) return VRAI;
	return FAUX;
}
object isnull_t(object list){
	object obj=car(list);
	if(cdr(list) != nil){
		REPORT_MSG(";ERROR: null?: Wrong number of args given\n; expected only one arg\n");
    		return NULL;
    	}
	if(obj == nil) return VRAI;
	return FAUX;
}
object issymbol_t(object list){
	object obj=car(list);
	if(cdr(list) != nil){
		REPORT_MSG(";ERROR: symbol?: Wrong number of args given\n; expected only one arg\n");
    		return NULL;
    	}
	if(obj->type == SFS_SYMBOL) return VRAI;
	return FAUX;
}
object ischar_t(object list){
	object obj=car(list);
	if(cdr(list) != nil){
		REPORT_MSG(";ERROR: char?: Wrong number of args given\n; expected only one arg\n");
    		return NULL;
    	}
	if(obj->type == SFS_CHARACTER) return VRAI;
	return FAUX;
}
object isstring_t(object list){
	object obj=car(list);
	if(cdr(list) != nil){
		REPORT_MSG(";ERROR: string?: Wrong number of args given\n; expected only one arg\n");
    		return NULL;
    	}
	if(obj->type == SFS_STRING) return VRAI;
	return FAUX;
}
object ispair_t(object list){
	object obj=car(list);
	if(cdr(list) != nil){
		REPORT_MSG(";ERROR: pair?: Wrong number of args given\n; expected only one arg\n");
    		return NULL;
    	}
	if(obj->type == SFS_PAIR) return VRAI;
	return FAUX;
}

object cons_t( object list){
	object obj;
	if(list == nil || cdr(list) == nil || cdr(cdr(list)) != nil){
	    REPORT_MSG(";ERROR: cons: Wrong number of args given\n; expected only two args\n");
    		return NULL;
    }
	obj=make_pair();
	obj->this.pair.car=car(list);
	obj->this.pair.cdr=car(cdr(list));
	return obj;
}
	
object car_t( object list){
	
	if(cdr(list) != nil){
	    REPORT_MSG(";ERROR: car: Wrong number of args given\n; expected only one arg\n");
    		return NULL;
    }
	if(((object) car(list))->type != SFS_PAIR){
		REPORT_MSG(";ERROR: car: Wrong type of args given\n; expected a pair\n");
    		return NULL;
    }
	return car(car(list)); 
}
object cdr_t( object list){
if(cdr(list) != nil){
	    REPORT_MSG(";ERROR: cdr: Wrong number of args given\n; expected only one arg\n");
    		return NULL;
    }
if(((object) car(list))->type != SFS_PAIR){
		REPORT_MSG(";ERROR: cdr: Wrong type of args given\n; expected a pair\n");
    		return NULL;
    }
	return cdr(car(list)); 
}
object set_car_t( object list){
if(list == nil || cdr(list) == nil || cdr(cdr(list)) != nil){
	    REPORT_MSG(";ERROR: set-car!: Wrong number of args given\n; expected only two args\n");
    		return NULL;
    }
if(((object) car(list))->type != SFS_PAIR){
		REPORT_MSG(";ERROR: set-car!: Wrong type of args given\n; expected a pair for the first arg\n");
    		return NULL;
    }
	
	((object) car(list))->this.pair.car=car(cdr(list));
	return make_symbol("#<unspecified>");


}
object set_cdr_t( object list){
if(list == nil || cdr(list) == nil || cdr(cdr(list)) != nil){
	    REPORT_MSG(";ERROR: set-cdr!: Wrong number of args given\n; expected only two args\n");
    		return NULL;
    }
if(((object) car(list))->type != SFS_PAIR){
		REPORT_MSG(";ERROR: set-cdr!: Wrong type of args given\n; expected a pair for the first arg\n");
    		return NULL;
    }

	((object) car(list))->this.pair.cdr=car(cdr(list));
	return make_symbol("#<unspecified>");

}
object list_t( object list){
	
	return list;
}
object islist_t( object list ){
	object obj=car(list);
	if(cdr(list) != nil){
	    REPORT_MSG(";ERROR: list?: Wrong number of args given\n; expected only one arg\n");
    		return NULL;
    }

	while(cdr(obj) != NULL){
		obj=cdr(obj);
		
}
	if(obj == nil) return VRAI;
	return FAUX;
}

object eval_t( object list){

	if(cdr(list) != nil){
	    REPORT_MSG(";ERROR: list?: Wrong number of args given\n; expected only one arg\n");
    		return NULL;
    }
	return sfs_eval(car(list));
}
