
/**
 * @file eval.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:11:30 2012
 * @brief Evaluation stuff for SFS.
 *
 * Evaluation stuff for SFS.
 */

#include "eval.h"
#include <string.h>
#include <strings.h>


int isand(char*str){
	if(!strcasecmp("and",str)) return 1;
	return 0;
}

int isor(char*str){
	if(!strcasecmp("or",str)) return 1;
	return 0;
}
int isif(char*str){
	if(!strcasecmp("if",str)) return 1;
	return 0;
}
int isquote(char*str){
	if(!strcasecmp("quote",str)) return 1;
	return 0;
}
<<<<<<< HEAD
int isbegin(char*str){
	if(!strcasecmp("begin",str)) return 1;
	return 0;
}
=======
>>>>>>> 6abfdeef7b7dba83c4d6fe3095b6c45f83410695
int isdefine(char*str){
	if(!strcasecmp("define",str)) return 1;
	return 0;
}
int isset(char*str){
	if(!strcasecmp("set",str)) return 1;
	return 0;
}
int isplus(char*str){
	if(!strcasecmp("+",str)) return 1;
	return 0;
}
int ismoins(char*str){
	if(!strcasecmp("-",str)) return 1;
	return 0;
}
int ismult(char*str){
	if(!strcasecmp("*",str)) return 1;
	return 0;
}
int isdiv(char*str){
	if(!strcasecmp("/",str)) return 1;
	return 0;
}
int isinf(char*str){
	if(!strcasecmp("<",str)) return 1;
	return 0;
}
int isinfe(char*str){
	if(!strcasecmp("<=",str)) return 1;
	return 0;
}
int issup(char*str){
	if(!strcasecmp(">",str)) return 1;
	return 0;
}
int issupe(char*str){
	if(!strcasecmp(">=",str)) return 1;
	return 0;
}

	
object car(object o){
	if( o == NULL ) return NULL;
	if( o->type == SFS_PAIR ) return o->this.pair.car;
	return NULL;
}
object cdr(object o){
	if( o == NULL ) return NULL;
	if( o->type == SFS_PAIR ) return o->this.pair.cdr;
	return NULL;
}
object operation( object obj1,object obj2, char op ){
     num n;
     if(obj1 == NULL || obj2 == NULL) return NULL;
<<<<<<< HEAD
     switch(op) {
	    case '+':
		if(obj1->type == SFS_SYMBOL && (!strcasecmp(obj1->this.symbol,"+inf") || !strcasecmp(obj1->this.symbol,"-inf")) ) return obj1;
		if(obj2->type == SFS_SYMBOL && (!strcasecmp(obj2->this.symbol,"+inf") || !strcasecmp(obj2->this.symbol,"-inf")) ) return obj2;
=======
     if(obj1->type != SFS_NUMBER && obj2->type != SFS_NUMBER) return NULL;
     switch(op) {
	    case '+':
>>>>>>> 6abfdeef7b7dba83c4d6fe3095b6c45f83410695
		if( obj1->this.number.numtype == NUM_REAL && obj2->this.number.numtype == NUM_REAL){
			n.numtype = NUM_REAL;
			n.this.real = obj1->this.number.this.real + obj2->this.number.this.real;
			return make_number(n);
		}
		if( obj1->this.number.numtype == NUM_REAL && obj2->this.number.numtype == NUM_INTEGER){
			n.numtype = NUM_REAL;
			n.this.real = obj1->this.number.this.real + (double)obj2->this.number.this.integer;
			return make_number(n);
		}
		if( obj1->this.number.numtype == NUM_INTEGER && obj2->this.number.numtype == NUM_REAL){
			n.numtype = NUM_REAL;
			n.this.real = (double)obj1->this.number.this.integer + obj2->this.number.this.real;
			return make_number(n);
		}
		if( obj1->this.number.numtype == NUM_INTEGER && obj2->this.number.numtype == NUM_INTEGER ){
			n.numtype = NUM_INTEGER;
			n.this.integer = obj1->this.number.this.integer + obj2->this.number.this.integer;
			return make_number(n);
		}
	   case '-':
<<<<<<< HEAD
		if(obj1->type == SFS_SYMBOL && (!strcasecmp(obj1->this.symbol,"+inf") || !strcasecmp(obj1->this.symbol,"-inf")) ) return obj1;
		if(obj2->type == SFS_SYMBOL && (!strcasecmp(obj2->this.symbol,"+inf") || !strcasecmp(obj2->this.symbol,"-inf")) ) return obj2;
=======
>>>>>>> 6abfdeef7b7dba83c4d6fe3095b6c45f83410695
		if( obj1->this.number.numtype == NUM_REAL && obj2->this.number.numtype == NUM_REAL){
			n.numtype = NUM_REAL;
			n.this.real = obj1->this.number.this.real - obj2->this.number.this.real;
			return make_number(n);
		}
		if( obj1->this.number.numtype == NUM_REAL && obj2->this.number.numtype == NUM_INTEGER){
			n.numtype = NUM_REAL;
			n.this.real = obj1->this.number.this.real - (double)obj2->this.number.this.integer;
			return make_number(n);
		}
		if( obj1->this.number.numtype == NUM_INTEGER && obj2->this.number.numtype == NUM_REAL){
			n.numtype = NUM_REAL;
			n.this.real = (double)obj1->this.number.this.integer - obj2->this.number.this.real;
			return make_number(n);
		}
		if( obj1->this.number.numtype == NUM_INTEGER && obj2->this.number.numtype == NUM_INTEGER ){
			n.numtype = NUM_INTEGER;
			n.this.integer = obj1->this.number.this.integer - obj2->this.number.this.integer;
			return make_number(n);
		}
	   case '*':
		if( obj1->this.number.numtype == NUM_REAL && obj2->this.number.numtype == NUM_REAL){
			n.numtype = NUM_REAL;
			n.this.real = obj1->this.number.this.real * obj2->this.number.this.real;
			return make_number(n);
		}
		if( obj1->this.number.numtype == NUM_REAL && obj2->this.number.numtype == NUM_INTEGER){
			n.numtype = NUM_REAL;
			n.this.real = obj1->this.number.this.real * (double)obj2->this.number.this.integer;
			return make_number(n);
		}
		if( obj1->this.number.numtype == NUM_INTEGER && obj2->this.number.numtype == NUM_REAL){
			n.numtype = NUM_REAL;
			n.this.real = (double)obj1->this.number.this.integer * obj2->this.number.this.real;
			return make_number(n);
		}
		if( obj1->this.number.numtype == NUM_INTEGER && obj2->this.number.numtype == NUM_INTEGER ){
			n.numtype = NUM_INTEGER;
			n.this.integer = obj1->this.number.this.integer * obj2->this.number.this.integer;
			return make_number(n);
		}
	   case '/':
<<<<<<< HEAD
		if(obj2->type == SFS_SYMBOL && (!strcasecmp(obj2->this.symbol,"+inf") || !strcasecmp(obj2->this.symbol,"-inf")) ){
			if(obj1->type != SFS_SYMBOL){
				n.numtype = NUM_REAL;
				n.this.real = 0;
				return make_number(n);
			}
		}
		if( obj1->this.number.numtype == NUM_REAL && (obj2->this.number.numtype == NUM_REAL && obj2->this.number.this.real != 0)){
=======
		if( obj1->this.number.numtype == NUM_REAL && obj2->this.number.numtype == NUM_REAL && obj2->this.number.this.real!=0){
>>>>>>> 6abfdeef7b7dba83c4d6fe3095b6c45f83410695
			n.numtype = NUM_REAL;
			n.this.real = obj1->this.number.this.real / obj2->this.number.this.real;
			return make_number(n);
		}
<<<<<<< HEAD
		if( obj1->this.number.numtype == NUM_REAL && (obj2->this.number.numtype == NUM_INTEGER && obj2->this.number.this.integer != 0)){
=======
		if( obj1->this.number.numtype == NUM_REAL && obj2->this.number.numtype == NUM_INTEGER && obj2->this.number.this.integer!=0){
>>>>>>> 6abfdeef7b7dba83c4d6fe3095b6c45f83410695
			n.numtype = NUM_REAL;
			n.this.real = obj1->this.number.this.real / (double)obj2->this.number.this.integer;
			return make_number(n);
		}
<<<<<<< HEAD
		if( obj1->this.number.numtype == NUM_INTEGER && (obj2->this.number.numtype == NUM_REAL && obj2->this.number.this.real !=0 )){
=======
		if( obj1->this.number.numtype == NUM_INTEGER && obj2->this.number.numtype == NUM_REAL && obj2->this.number.this.real!=0){
>>>>>>> 6abfdeef7b7dba83c4d6fe3095b6c45f83410695
			n.numtype = NUM_REAL;
			n.this.real = (double)obj1->this.number.this.integer / obj2->this.number.this.real;
			return make_number(n);
		}
<<<<<<< HEAD
		if( obj1->this.number.numtype == NUM_INTEGER && (obj2->this.number.numtype == NUM_INTEGER && obj2->this.number.this.integer !=0 )){
			n.numtype = NUM_REAL;
			n.this.real = (double)obj1->this.number.this.integer / (double)obj2->this.number.this.integer;
			return make_number(n);
		}
		if((obj2->this.number.numtype == NUM_INTEGER && obj2->this.number.this.integer == 0) || (obj2->this.number.numtype == NUM_REAL && obj2->this.number.this.real == 0)){
			if((obj1->this.number.numtype == NUM_INTEGER && obj1->this.number.this.integer > 0) || (obj1->this.number.numtype == NUM_REAL && obj1->this.number.this.real > 0))
				return make_symbol("+inf");
			if((obj1->this.number.numtype == NUM_INTEGER && obj1->this.number.this.integer < 0) || (obj1->this.number.numtype == NUM_REAL && obj1->this.number.this.real < 0))
				return make_symbol("-inf");
		}

=======
		if( obj1->this.number.numtype == NUM_INTEGER && obj2->this.number.numtype == NUM_INTEGER && obj2->this.number.this.integer!=0){
			n.numtype = NUM_INTEGER;
			n.this.integer = obj1->this.number.this.integer / obj2->this.number.this.integer;
			return make_number(n);
		}
>>>>>>> 6abfdeef7b7dba83c4d6fe3095b6c45f83410695
	   case '<':
		if( obj1->this.number.numtype == NUM_REAL && obj2->this.number.numtype == NUM_REAL){
			if( obj1->this.number.this.real < obj2->this.number.this.real ) return VRAI;
			return FAUX;
		}
		if( obj1->this.number.numtype == NUM_REAL && obj2->this.number.numtype == NUM_INTEGER){
			if( obj1->this.number.this.real < (double)obj2->this.number.this.integer ) return VRAI;
			return FAUX;
		}
		if( obj1->this.number.numtype == NUM_INTEGER && obj2->this.number.numtype == NUM_REAL){
			if( (double)obj1->this.number.this.integer < obj2->this.number.this.real ) return VRAI;
			return FAUX;
		}
		if( obj1->this.number.numtype == NUM_INTEGER && obj2->this.number.numtype == NUM_INTEGER ){
			if( obj1->this.number.this.integer < obj2->this.number.this.integer ) return VRAI;
			return FAUX;
		}
	   /*case "<=":
		if( obj1->this.number.numtype == NUM_REAL && obj2->this.number.numtype == NUM_REAL){
			if( obj1->this.number.this.real <= obj2->this.number.this.real ) return VRAI;
			return FAUX;
		}
		if( obj1->this.number.numtype == NUM_REAL && obj2->this.number.numtype == NUM_INTEGER){
			if( obj1->this.number.this.real <= (double)obj2->this.number.this.integer ) return VRAI;
			return FAUX;
		}
		if( obj1->this.number.numtype == NUM_INTEGER && obj2->this.number.numtype == NUM_REAL){
			if( (double)obj1->this.number.this.integer <= obj2->this.number.this.real ) return VRAI;
			return FAUX;
		}
		if( obj1->this.number.numtype == NUM_INTEGER && obj2->this.number.numtype == NUM_INTEGER ){
			if( obj1->this.number.this.integer <= obj2->this.number.this.integer ) return VRAI;
			return FAUX;
		}*/
	   case '>':
		if( obj1->this.number.numtype == NUM_REAL && obj2->this.number.numtype == NUM_REAL){
			if( obj1->this.number.this.real > obj2->this.number.this.real ) return VRAI;
			return FAUX;
		}
		if( obj1->this.number.numtype == NUM_REAL && obj2->this.number.numtype == NUM_INTEGER){
			if( obj1->this.number.this.real > (double)obj2->this.number.this.integer ) return VRAI;
			return FAUX;
		}
		if( obj1->this.number.numtype == NUM_INTEGER && obj2->this.number.numtype == NUM_REAL){
			if( (double)obj1->this.number.this.integer > obj2->this.number.this.real ) return VRAI;
			return FAUX;
		}
		if( obj1->this.number.numtype == NUM_INTEGER && obj2->this.number.numtype == NUM_INTEGER ){
			if( obj1->this.number.this.integer > obj2->this.number.this.integer ) return VRAI;
			return FAUX;
		}
	   /*case ">=":
		if( obj1->this.number.numtype == NUM_REAL && obj2->this.number.numtype == NUM_REAL){
			if( obj1->this.number.this.real >= obj2->this.number.this.real ) return VRAI;
			return FAUX;
		}
		if( obj1->this.number.numtype == NUM_REAL && obj2->this.number.numtype == NUM_INTEGER){
			if( obj1->this.number.this.real >= (double)obj2->this.number.this.integer ) return VRAI;
			return FAUX;
		}
		if( obj1->this.number.numtype == NUM_INTEGER && obj2->this.number.numtype == NUM_REAL){
			if( (double)obj1->this.number.this.integer >= obj2->this.number.this.real ) return VRAI;
			return FAUX;
		}
		if( obj1->this.number.numtype == NUM_INTEGER && obj2->this.number.numtype == NUM_INTEGER ){
			if( obj1->this.number.this.integer >= obj2->this.number.this.integer ) return VRAI;
			return FAUX;
		}*/
        default:
        	break;
      }
      return NULL;
}	

object sfs_eval( object o ) {
<<<<<<< HEAD
    object objres = NULL, obj = o;
    begin:
    switch(obj->type) {
	    case SFS_NUMBER:
		return obj;
	    case SFS_CHARACTER:
		return obj;
	    case SFS_STRING:
	 	return obj;
	    case SFS_SYMBOL:
		return obj;
	    case SFS_NIL:
		return obj;
	    case SFS_BOOLEAN:
		return obj;
	    case SFS_PAIR:
		if(car(obj)->type == SFS_SYMBOL){
			if(isplus(car(obj)->this.symbol)){
				objres = sfs_eval(car(cdr(obj)));
				obj = cdr(cdr(obj));
=======
    object objres, obj = NULL;
    switch(o->type) {
	    case SFS_NUMBER:
		return make_number(o->this.number);
	    case SFS_CHARACTER:
		return make_character(o->this.character);
	    case SFS_STRING:
	 	return make_string(o->this.string);
	    case SFS_SYMBOL:
		return make_symbol(o->this.symbol);
	    case SFS_NIL:
		return make_nil();
	    case SFS_BOOLEAN:
		return o;
	    case SFS_PAIR:
		if(car(o)->type == SFS_SYMBOL){
			if(isplus(car(o)->this.symbol)){
				objres = sfs_eval(car(cdr(o)));
				obj = cdr(cdr(o));
>>>>>>> 6abfdeef7b7dba83c4d6fe3095b6c45f83410695
				while( obj != nil){
					objres = operation(objres,sfs_eval(car(obj)),'+');
					obj = cdr(obj);
				}
				return objres;
			}
<<<<<<< HEAD
			if(ismoins(car(obj)->this.symbol)){
				objres = sfs_eval(car(cdr(obj)));
				obj = cdr(cdr(obj));
=======
			if(ismoins(car(o)->this.symbol)){
				objres = sfs_eval(car(cdr(o)));
				obj = cdr(cdr(o));
>>>>>>> 6abfdeef7b7dba83c4d6fe3095b6c45f83410695
				while( obj != nil){
					objres = operation(objres,sfs_eval(car(obj)),'-');
					obj = cdr(obj);
				}
				return objres;
			}
<<<<<<< HEAD
			if(ismult(car(obj)->this.symbol)){
				objres = sfs_eval(car(cdr(obj)));
				obj = cdr(cdr(obj));
=======
			if(ismult(car(o)->this.symbol)){
				objres = sfs_eval(car(cdr(o)));
				obj = cdr(cdr(o));
>>>>>>> 6abfdeef7b7dba83c4d6fe3095b6c45f83410695
				while( obj != nil){
					objres = operation(objres,sfs_eval(car(obj)),'*');
					obj = cdr(obj);
				}
				return objres;
			}
<<<<<<< HEAD
			if(isdiv(car(obj)->this.symbol)){
				objres = sfs_eval(car(cdr(obj)));
				obj = cdr(cdr(obj));
				while( obj != nil){
					objres = operation(objres,sfs_eval(car(obj)),'/');
					if(objres->type == SFS_SYMBOL && (!strcasecmp(objres->this.symbol,"+inf") || !strcasecmp(objres->this.symbol,"-inf")) ) break;
=======
			if(isdiv(car(o)->this.symbol)){
				objres = sfs_eval(car(cdr(o)));
				obj = cdr(cdr(o));
				while( obj != nil){
					objres = operation(objres,sfs_eval(car(obj)),'/');
>>>>>>> 6abfdeef7b7dba83c4d6fe3095b6c45f83410695
					obj = cdr(obj);
				}
				return objres;
			}
<<<<<<< HEAD
			if(isand(car(obj)->this.symbol)){
				obj = cdr(obj);
				while(obj != nil){
					if( sfs_eval(car(obj)) == FAUX ) return FAUX;
=======
			if(isand(car(o)->this.symbol)){
				obj = cdr(o);
				while(obj != nil){
					if( car(obj)->type == SFS_BOOLEAN && car(obj)->this.boolean == FAUX ) return FAUX;
>>>>>>> 6abfdeef7b7dba83c4d6fe3095b6c45f83410695
					obj = cdr(obj);
				}
				return VRAI;
			}
<<<<<<< HEAD
			if(isor(car(obj)->this.symbol)){
				obj = cdr(obj);
				while(obj != nil){
					if( sfs_eval(car(obj)) == FAUX ){
=======
			if(isor(car(o)->this.symbol)){
				obj = cdr(o);
				while(obj != nil){
					if( car(obj)->type == SFS_BOOLEAN && car(obj)->this.boolean == FAUX ){
>>>>>>> 6abfdeef7b7dba83c4d6fe3095b6c45f83410695
						obj = cdr(obj);
						continue;
					}
					return VRAI;
				}
				return FAUX;
			}
<<<<<<< HEAD
			if(isinf(car(obj)->this.symbol)){
				return operation(sfs_eval(car(cdr(obj))) , sfs_eval(car(cdr(cdr(obj)))), '<');
			}
			if(issup(car(obj)->this.symbol)){
				return operation(sfs_eval(car(cdr(obj))) , sfs_eval(car(cdr(cdr(obj)))), '>');
			}
			if(isif(car(obj)->this.symbol)){
				obj = cdr(obj);
				if( sfs_eval(car(obj)) == VRAI ){
					if( car(cdr(obj)) != nil ) {
						obj = car(cdr(obj));
						goto begin;
					}
					return;
				}
				
				if( sfs_eval(car(obj)) == FAUX ){
					if( car(cdr(cdr(obj))) != nil ){
						obj = car(cdr(cdr(obj)));
						goto begin;
					}else return FAUX;
					return;					
				}
			}
			if(isbegin(car(obj)->this.symbol)){
				objres = sfs_eval(car(cdr(obj)));
				obj = cdr(cdr(obj));
				while( obj != nil){
					objres = sfs_eval(car(obj));
					obj = cdr(obj);
				}
				return objres;
			}
								  
=======
			if(isinf(car(o)->this.symbol)){
				return operation(sfs_eval(car(cdr(o))) , sfs_eval(car(cdr(cdr(o)))), '<');
			}
			if(issup(car(o)->this.symbol)){
				return operation(sfs_eval(car(cdr(o))) , sfs_eval(car(cdr(cdr(o)))), '>');
			}
			if(isif(car(o)->this.symbol)){
				obj = cdr(o);
				begin:
				if( sfs_eval(car(obj)) == VRAI ){
					obj = cdr(obj);
					if( obj != nil ) goto begin;
					return;
				}
				if( sfs_eval(car(obj)) == FAUX ){
					obj = cdr(cdr(obj));
					if( cdr(cdr(cdr(o))) == nil ) return FAUX;
					if( obj != nil ) goto begin;
					return;					
				}
				return sfs_eval(car(obj));
			}				  
>>>>>>> 6abfdeef7b7dba83c4d6fe3095b6c45f83410695
		}

    default:
        break;
    }
    
		
<<<<<<< HEAD
    return objres;
=======
    return obj;
>>>>>>> 6abfdeef7b7dba83c4d6fe3095b6c45f83410695
}
















