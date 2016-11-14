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
        	REPORT_MSG(";ERROR: +: Wrong type to apply in arg%d ",i);
        	sfs_print(car(obj)); printf("\n");
    		return objres;
    	}
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
    obj = list;
	while( obj != nil ){
        if(i == 1) objres = operation(objres,car(obj),"+");
        else objres = operation(objres,car(obj),"-");
        if(objres == NULL ){
        	REPORT_MSG(";ERROR: -: Wrong type to apply in arg%d ",i);
        	sfs_print(car(obj)); printf("\n");
    		return objres;
    	}
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
        	REPORT_MSG(";ERROR: *: Wrong type to apply in arg%d ",i);
        	sfs_print(car(obj)); printf("\n");
    		return objres;
    	}
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
        	REPORT_MSG(";ERROR: /: Wrong type to apply in arg%d ",i);
        	sfs_print(car(obj)); printf("\n");
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
        	REPORT_MSG(";ERROR: /: Wrong type to apply in arg%d ",i);
        	sfs_print(car(obj)); printf("\n");
    		return objres;
    	}
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
    	REPORT_MSG(";ERROR: quotient: Wrong type to apply in arg1 ");   
    	sfs_print(obj); printf("\n");
		return NULL; 
	}
	obj = car(cdr(list));
	if( obj->type != SFS_NUMBER || (obj->type == SFS_NUMBER && obj->this.number.numtype != NUM_INTEGER) ){
    	REPORT_MSG(";ERROR: quotient: Wrong type to apply in arg2 ");   
    	sfs_print(obj); printf("\n");
		return NULL; 
	}
	if( obj->this.number.numtype == NUM_INTEGER && obj->this.number.this.integer == 0 ){
    	REPORT_MSG(";ERROR: quotient: numerical overflow ");   
    	sfs_print(obj); printf("\n");
		return NULL; 
	}
    n.numtype = NUM_INTEGER;
    n.this.integer = ((object)car(list))->this.number.this.integer/obj->this.number.this.integer;
    return make_number(n);
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
    	REPORT_MSG(";ERROR: remainder: Wrong type to apply in arg1 ");   
    	sfs_print(obj); printf("\n");
		return NULL; 
	}
	obj = car(cdr(list));
	if( obj->type != SFS_NUMBER || (obj->type == SFS_NUMBER && obj->this.number.numtype != NUM_INTEGER) ){
    	REPORT_MSG(";ERROR: remainder: Wrong type to apply in arg2 ");   
    	sfs_print(obj); printf("\n");
		return NULL; 
	}
	if( obj->this.number.numtype == NUM_INTEGER && obj->this.number.this.integer == 0 ){
    	REPORT_MSG(";ERROR: remainder: numerical overflow ");   
    	sfs_print(obj); printf("\n");
		return NULL; 
	}
    n.numtype = NUM_INTEGER;
    n.this.integer = ((object)car(list))->this.number.this.integer/obj->this.number.this.integer;
    return make_number(n);
}

object inf_t( object list){
	/* on prend en paramètre une liste d'object dont il faut faire la somme */
    object objres,obj = NULL;int i =1;
    if(list == nil) return VRAI;   
    objres = car(list);
    if( objres->type != SFS_NUMBER ){
    	REPORT_MSG(";ERROR: <: Wrong type to apply in arg%d ",i);
    	sfs_print(objres); printf("\n");
		return NULL;
	}
	i++;
    obj = cdr(list);
	while( obj != nil && objres != FAUX ){
        objres = operation(car(list),car(obj),"<");
        if(objres == FAUX) return FAUX;
        if(objres == NULL ){
        	REPORT_MSG(";ERROR: <: Wrong type to apply in arg%d ",i);
        	sfs_print(car(obj)); printf("\n");
    		return objres;
    	}
        obj = cdr(obj);
        i++;
    }
    return VRAI;
}

object infe_t( object list){
	/* on prend en paramètre une liste d'object dont il faut faire la somme */
    object objres,obj = NULL;int i =1;
    if(list == nil) return VRAI;  
    objres = car(list);
    if( objres->type != SFS_NUMBER ){
    	REPORT_MSG(";ERROR: <=: Wrong type to apply in arg%d ",i);
    	sfs_print(objres); printf("\n");
		return NULL;
	}
	i++;
    obj = cdr(list);
	while( obj != nil && objres != FAUX ){
        objres = operation(car(list),car(obj),"<=");
        if(objres == FAUX) return FAUX;
        if(objres == NULL ){
        	REPORT_MSG(";ERROR: <=: Wrong type to apply in arg%d ",i);
        	sfs_print(car(obj)); printf("\n");
    		return objres;
    	}
        obj = cdr(obj);
        i++;
    }
    return VRAI;
}

object sup_t( object list){
	/* on prend en paramètre une liste d'object dont il faut faire la somme */
    object objres,obj = NULL;int i =1;
    if(list == nil) return VRAI;  
    objres = car(list);
    if( objres->type != SFS_NUMBER ){
    	REPORT_MSG(";ERROR: >: Wrong type to apply in arg%d ",i);
    	sfs_print(objres); printf("\n");
		return NULL;
	}
	i++;
    obj = cdr(list);
	while( obj != nil && objres != FAUX ){
        objres = operation(car(list),car(obj),">");
        if(objres == FAUX) return FAUX;
        if(objres == NULL ){
        	REPORT_MSG(";ERROR: >: Wrong type to apply in arg%d ",i);
        	sfs_print(car(obj)); printf("\n");
    		return objres;
    	}
        obj = cdr(obj);
        i++;
    }
    return VRAI;
}

object supe_t( object list){
	/* on prend en paramètre une liste d'object dont il faut faire la somme */
    object objres,obj = NULL;int i =1;
    if(list == nil) return VRAI;  
    objres = car(list);
    if( objres->type != SFS_NUMBER ){
    	REPORT_MSG(";ERROR: >=: Wrong type to apply in arg%d ",i);
    	sfs_print(objres); printf("\n");
		return NULL;
	}
	i++;
    obj = cdr(list);
	while( obj != nil && objres != FAUX ){
        objres = operation(car(list),car(obj),">=");
        if(objres == FAUX) return FAUX;
        if(objres == NULL ){
        	REPORT_MSG(";ERROR: >=: Wrong type to apply in arg%d ",i);
        	sfs_print(car(obj)); printf("\n");
    		return objres;
    	}
        obj = cdr(obj);
        i++;
    }
    return VRAI;
}

object ctoi_t( object list ){ /* char to int(ctoi): retourne le caractere ascii*/
	/* on prend en paramètre une liste d'object dont il faut faire la division entière*/
	num n; object obj;
    if(list == nil || cdr(list) != nil) {
	    REPORT_MSG(";ERROR: char->integer: Wrong number of args given\n; expected one arg\n");
    	return NULL;
    }
	obj = car(list);
    if( obj->type != SFS_CHARACTER ){    
    	REPORT_MSG(";ERROR: char->integer: Wrong type to apply in arg1 ");   
    	sfs_print(obj); printf("\n");
		return NULL; 
	}
	n.numtype = NUM_INTEGER;
	n.this.integer = obj->this.character;
	return make_number(n);    
}

object itoc_t( object list ){ /* int to char(itoc): retourne le caractere ascii*/
	/* on prend en paramètre une liste d'object dont il faut faire la division entière*/
	object obj;
    if(list == nil || cdr(list) != nil) {
	    REPORT_MSG(";ERROR: integer->char: Wrong number of args given\n; expected one arg\n");
    	return NULL;
    }
	obj = car(list);
    if( obj->type != SFS_NUMBER || (obj->type == SFS_NUMBER && obj->this.number.numtype != NUM_INTEGER) ){    
    	REPORT_MSG(";ERROR: integer->char: Wrong type to apply in arg1 ");   
    	sfs_print(obj); printf("\n");
		return NULL; 
	}
    if( (obj->this.number.this.integer < 32) || (obj->this.number.this.integer > 127) ){    
    	REPORT_MSG(";ERROR: integer->char: Argument out of range ");   
    	sfs_print(obj); printf("\n");
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
    	sfs_print(obj); printf("\n");
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
    	sfs_print(obj); printf("\n");
		return NULL; 
	}
	obj->type = SFS_SYMBOL;
	return obj;
}



object strtonum_t( object list ){
	num n; object obj1,obj2; char * endptr,*str; uint here = 0;
    if(list == nil || (cdr(list) != nil && cdr(cdr(list)) != nil) ) {
	    REPORT_MSG(";ERROR: string->number: Wrong number of args given\n; expected form (string->number str base*) default base is 10\n");
    	return NULL;
    }
	obj1 = car(list);
    if( obj1->type != SFS_STRING ){    
    	REPORT_MSG(";ERROR: string->number: Wrong type to apply in arg1 ");   
    	sfs_print(obj1); printf("\n");
		return NULL; 
	}
	obj2 = car(cdr(list));
	if(obj2){
		if( obj2->type != SFS_NUMBER || (obj2->type == SFS_NUMBER && obj2->this.number.numtype != NUM_INTEGER) ){
			REPORT_MSG(";ERROR: string->number: Wrong type to apply in ");   
			sfs_print(obj2); printf("\n");
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
	/* on prend en paramètre une liste d'object dont il faut faire la division entière*/
	object obj1,obj2; int res = 0;int taille = 0;num n; char* str,*strs;int i =0;
    if(list == nil || (cdr(list) != nil && cdr(cdr(list)) != nil) ) {
	    REPORT_MSG(";ERROR: number->string: Wrong number of args given\n; expected form (string->number num base*) default base is 10\n");
    	return NULL;
    }
	obj1 = car(list);
    if( obj1->type != SFS_NUMBER){    
    	REPORT_MSG(";ERROR: number->string: Wrong type to apply in arg1 ");   
    	sfs_print(obj1); printf("\n");
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
		sfs_print(obj2); printf("\n");
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
		i = taille -1;
		while( res != 0 ){
			if(res%obj2->this.number.this.integer < 10){
				sprintf(str,"%d",res%obj2->this.number.this.integer);
				strs[i] = str[0];
			}
			else strs[i] = 87+res;
			res = res/obj2->this.number.this.integer;
			i--;
		}
		return make_string(strs);
	}
	if(sprintf(str,"%.16G",obj1->this.number.this.real));
	return make_string(str);

}

object eqv_t( object list ){
	/* on prend en paramètre une liste d'object dont il faut faire la division entière*/
	object obj,obj1,obj2;
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
			if( strcasecmp(obj1->this.character,obj2->this.character) ) return FAUX;
		}
		if( obj1->type == SFS_BOOLEAN){
			if( obj1->this.boolean != obj2->this.boolean ) return FAUX;
		}
		obj = cdr(obj);
	}
	return VRAI;
}


						
		
