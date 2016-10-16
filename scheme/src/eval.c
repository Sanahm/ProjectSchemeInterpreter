
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


int isand(char*str) {
    if(!strcasecmp("and",str)) return 1;
    return 0;
}

int isor(char*str) {
    if(!strcasecmp("or",str)) return 1;
    return 0;
}
int isif(char*str) {
    if(!strcasecmp("if",str)) return 1;
    return 0;
}
int isquote(char*str) {
    if(!strcasecmp("quote",str)) return 1;
    return 0;
}
int isbegin(char*str) {
    if(!strcasecmp("begin",str)) return 1;
    return 0;
}
int isdefine(char*str) {
    if(!strcasecmp("define",str)) return 1;
    return 0;
}
int isset(char*str) {
    if(!strcasecmp("set!",str)) return 1;
    return 0;
}
int isplus(char*str) {
    if(!strcasecmp("+",str)) return 1;
    return 0;
}
int ismoins(char*str) {
    if(!strcasecmp("-",str)) return 1;
    return 0;
}
int ismult(char*str) {
    if(!strcasecmp("*",str)) return 1;
    return 0;
}
int isdiv(char*str) {
    if(!strcasecmp("/",str)) return 1;
    return 0;
}
int isinf(char*str) {
    if(!strcasecmp("<",str)) return 1;
    return 0;
}
int isinfe(char*str) {
    if(!strcasecmp("<=",str)) return 1;
    return 0;
}
int issup(char*str) {
    if(!strcasecmp(">",str)) return 1;
    return 0;
}
int issupe(char*str) {
    if(!strcasecmp(">=",str)) return 1;
    return 0;
}


object car(object o) {
    if( o == NULL ) return NULL;
    if( o->type == SFS_PAIR ) return o->this.pair.car;
    return NULL;
}
object cdr(object o) {
    if( o == NULL ) return NULL;
    if( o->type == SFS_PAIR ) return o->this.pair.cdr;
    return NULL;
}
object operation( object obj1,object obj2, char op ) {
    num n;
    if(obj1 == NULL || obj2 == NULL) return NULL;
    switch(op) {
    case '+':
        if(obj1->type == SFS_SYMBOL && (!strcasecmp(obj1->this.symbol,"+inf") || !strcasecmp(obj1->this.symbol,"-inf")) ) return obj1;
        if(obj2->type == SFS_SYMBOL && (!strcasecmp(obj2->this.symbol,"+inf") || !strcasecmp(obj2->this.symbol,"-inf")) ) return obj2;
        if( obj1->this.number.numtype == NUM_REAL && obj2->this.number.numtype == NUM_REAL) {
            n.numtype = NUM_REAL;
            n.this.real = obj1->this.number.this.real + obj2->this.number.this.real;
            return make_number(n);
        }
        if( obj1->this.number.numtype == NUM_REAL && obj2->this.number.numtype == NUM_INTEGER) {
            n.numtype = NUM_REAL;
            n.this.real = obj1->this.number.this.real + (double)obj2->this.number.this.integer;
            return make_number(n);
        }
        if( obj1->this.number.numtype == NUM_INTEGER && obj2->this.number.numtype == NUM_REAL) {
            n.numtype = NUM_REAL;
            n.this.real = (double)obj1->this.number.this.integer + obj2->this.number.this.real;
            return make_number(n);
        }
        if( obj1->this.number.numtype == NUM_INTEGER && obj2->this.number.numtype == NUM_INTEGER ) {
            n.numtype = NUM_INTEGER;
            n.this.integer = obj1->this.number.this.integer + obj2->this.number.this.integer;
            return make_number(n);
        }
    case '-':
        if(obj1->type == SFS_SYMBOL && (!strcasecmp(obj1->this.symbol,"+inf") || !strcasecmp(obj1->this.symbol,"-inf")) ) return obj1;
        if(obj2->type == SFS_SYMBOL && (!strcasecmp(obj2->this.symbol,"+inf") || !strcasecmp(obj2->this.symbol,"-inf")) ) return obj2;
        if( obj1->this.number.numtype == NUM_REAL && obj2->this.number.numtype == NUM_REAL) {
            n.numtype = NUM_REAL;
            n.this.real = obj1->this.number.this.real - obj2->this.number.this.real;
            return make_number(n);
        }
        if( obj1->this.number.numtype == NUM_REAL && obj2->this.number.numtype == NUM_INTEGER) {
            n.numtype = NUM_REAL;
            n.this.real = obj1->this.number.this.real - (double)obj2->this.number.this.integer;
            return make_number(n);
        }
        if( obj1->this.number.numtype == NUM_INTEGER && obj2->this.number.numtype == NUM_REAL) {
            n.numtype = NUM_REAL;
            n.this.real = (double)obj1->this.number.this.integer - obj2->this.number.this.real;
            return make_number(n);
        }
        if( obj1->this.number.numtype == NUM_INTEGER && obj2->this.number.numtype == NUM_INTEGER ) {
            n.numtype = NUM_INTEGER;
            n.this.integer = obj1->this.number.this.integer - obj2->this.number.this.integer;
            return make_number(n);
        }
    case '*':
        if( obj1->this.number.numtype == NUM_REAL && obj2->this.number.numtype == NUM_REAL) {
            n.numtype = NUM_REAL;
            n.this.real = obj1->this.number.this.real * obj2->this.number.this.real;
            return make_number(n);
        }
        if( obj1->this.number.numtype == NUM_REAL && obj2->this.number.numtype == NUM_INTEGER) {
            n.numtype = NUM_REAL;
            n.this.real = obj1->this.number.this.real * (double)obj2->this.number.this.integer;
            return make_number(n);
        }
        if( obj1->this.number.numtype == NUM_INTEGER && obj2->this.number.numtype == NUM_REAL) {
            n.numtype = NUM_REAL;
            n.this.real = (double)obj1->this.number.this.integer * obj2->this.number.this.real;
            return make_number(n);
        }
        if( obj1->this.number.numtype == NUM_INTEGER && obj2->this.number.numtype == NUM_INTEGER ) {
            n.numtype = NUM_INTEGER;
            n.this.integer = obj1->this.number.this.integer * obj2->this.number.this.integer;
            return make_number(n);
        }
    case '/':
        if(obj2->type == SFS_SYMBOL && (!strcasecmp(obj2->this.symbol,"+inf") || !strcasecmp(obj2->this.symbol,"-inf")) ) {
            if(obj1->type != SFS_SYMBOL) {
                n.numtype = NUM_REAL;
                n.this.real = 0;
                return make_number(n);
            }
        }
        if( obj1->this.number.numtype == NUM_REAL && (obj2->this.number.numtype == NUM_REAL && obj2->this.number.this.real != 0)) {
            n.numtype = NUM_REAL;
            n.this.real = obj1->this.number.this.real / obj2->this.number.this.real;
            return make_number(n);
        }
        if( obj1->this.number.numtype == NUM_REAL && (obj2->this.number.numtype == NUM_INTEGER && obj2->this.number.this.integer != 0)) {
            n.numtype = NUM_REAL;
            n.this.real = obj1->this.number.this.real / (double)obj2->this.number.this.integer;
            return make_number(n);
        }
        if( obj1->this.number.numtype == NUM_INTEGER && (obj2->this.number.numtype == NUM_REAL && obj2->this.number.this.real !=0 )) {
            n.numtype = NUM_REAL;
            n.this.real = (double)obj1->this.number.this.integer / obj2->this.number.this.real;
            return make_number(n);
        }
        if( obj1->this.number.numtype == NUM_INTEGER && (obj2->this.number.numtype == NUM_INTEGER && obj2->this.number.this.integer !=0 )) {
            n.numtype = NUM_REAL;
            n.this.real = (double)obj1->this.number.this.integer / (double)obj2->this.number.this.integer;
            return make_number(n);
        }
        if((obj2->this.number.numtype == NUM_INTEGER && obj2->this.number.this.integer == 0) || (obj2->this.number.numtype == NUM_REAL && obj2->this.number.this.real == 0)) {
            if((obj1->this.number.numtype == NUM_INTEGER && obj1->this.number.this.integer > 0) || (obj1->this.number.numtype == NUM_REAL && obj1->this.number.this.real > 0))
                return make_symbol("+inf");
            if((obj1->this.number.numtype == NUM_INTEGER && obj1->this.number.this.integer < 0) || (obj1->this.number.numtype == NUM_REAL && obj1->this.number.this.real < 0))
                return make_symbol("-inf");
        }

    case '<':
        if( obj1->this.number.numtype == NUM_REAL && obj2->this.number.numtype == NUM_REAL) {
            if( obj1->this.number.this.real < obj2->this.number.this.real ) return VRAI;
            return FAUX;
        }
        if( obj1->this.number.numtype == NUM_REAL && obj2->this.number.numtype == NUM_INTEGER) {
            if( obj1->this.number.this.real < (double)obj2->this.number.this.integer ) return VRAI;
            return FAUX;
        }
        if( obj1->this.number.numtype == NUM_INTEGER && obj2->this.number.numtype == NUM_REAL) {
            if( (double)obj1->this.number.this.integer < obj2->this.number.this.real ) return VRAI;
            return FAUX;
        }
        if( obj1->this.number.numtype == NUM_INTEGER && obj2->this.number.numtype == NUM_INTEGER ) {
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
        if( obj1->this.number.numtype == NUM_REAL && obj2->this.number.numtype == NUM_REAL) {
            if( obj1->this.number.this.real > obj2->this.number.this.real ) return VRAI;
            return FAUX;
        }
        if( obj1->this.number.numtype == NUM_REAL && obj2->this.number.numtype == NUM_INTEGER) {
            if( obj1->this.number.this.real > (double)obj2->this.number.this.integer ) return VRAI;
            return FAUX;
        }
        if( obj1->this.number.numtype == NUM_INTEGER && obj2->this.number.numtype == NUM_REAL) {
            if( (double)obj1->this.number.this.integer > obj2->this.number.this.real ) return VRAI;
            return FAUX;
        }
        if( obj1->this.number.numtype == NUM_INTEGER && obj2->this.number.numtype == NUM_INTEGER ) {
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
    object objres = NULL, obj = o , env_incr=environment;
begin:
    switch(obj->type) {
    case SFS_NUMBER:
        return obj;
    case SFS_CHARACTER:
        return obj;
    case SFS_STRING:
        return obj;
    case SFS_SYMBOL:
        return get_symbol_value(environment,o);
    case SFS_NIL:
        return obj;
    case SFS_BOOLEAN:
        return obj;
    case SFS_PAIR:
        if(car(obj)->type == SFS_SYMBOL) {
            if(isplus(car(obj)->this.symbol)) {
                objres = sfs_eval(car(cdr(obj)));
                obj = cdr(cdr(obj));
                while( obj != nil) {
                    objres = operation(objres,sfs_eval(car(obj)),'+');
                    obj = cdr(obj);
                }
                return objres;
            }
            if(ismoins(car(obj)->this.symbol)) {
                objres = sfs_eval(car(cdr(obj)));
                obj = cdr(cdr(obj));
                while( obj != nil) {
                    objres = operation(objres,sfs_eval(car(obj)),'-');
                    obj = cdr(obj);
                }
                return objres;
            }
            if(ismult(car(obj)->this.symbol)) {
                objres = sfs_eval(car(cdr(obj)));
                obj = cdr(cdr(obj));
                while( obj != nil) {
                    objres = operation(objres,sfs_eval(car(obj)),'*');
                    obj = cdr(obj);
                }
                return objres;
            }
            if(isdiv(car(obj)->this.symbol)) {
                objres = sfs_eval(car(cdr(obj)));
                obj = cdr(cdr(obj));
                while( obj != nil) {
                    objres = operation(objres,sfs_eval(car(obj)),'/');
                    if(objres->type == SFS_SYMBOL && (!strcasecmp(objres->this.symbol,"+inf") || !strcasecmp(objres->this.symbol,"-inf")) ) break;
                    obj = cdr(obj);
                }
                return objres;
            }
            if(isand(car(obj)->this.symbol)) {
                obj = cdr(obj);
                while(obj != nil) {
                    if( sfs_eval(car(obj)) == FAUX ) return FAUX;
                    obj = cdr(obj);
                }
                return VRAI;
            }
            if(isor(car(obj)->this.symbol)) {
                obj = cdr(obj);
                while(obj != nil) {
                    if( sfs_eval(car(obj)) == FAUX ) {
                        obj = cdr(obj);
                        continue;
                    }
                    return VRAI;
                }
                return FAUX;
            }
            if(isinf(car(obj)->this.symbol)) {
                return operation(sfs_eval(car(cdr(obj))) , sfs_eval(car(cdr(cdr(obj)))), '<');
            }
            if(issup(car(obj)->this.symbol)) {
                return operation(sfs_eval(car(cdr(obj))) , sfs_eval(car(cdr(cdr(obj)))), '>');
            }
            if(isif(car(obj)->this.symbol)) {
                obj = cdr(obj);
                if( sfs_eval(car(obj)) == VRAI ) {
                    if( car(cdr(obj)) != nil ) {
                        obj = car(cdr(obj));
                        goto begin;
                    }
                    return;
                }

                if( sfs_eval(car(obj)) == FAUX ) {
                    if( car(cdr(cdr(obj))) != nil ) {
                        obj = car(cdr(cdr(obj)));
                        goto begin;
                    } else return FAUX;
                    return;
                }
            }
            if(isbegin(car(obj)->this.symbol)) {
                objres = sfs_eval(car(cdr(obj)));
                obj = cdr(cdr(obj));
                while( obj != nil) {
                    objres = sfs_eval(car(obj));
                    obj = cdr(obj);
                }
                return objres;
            }
            if(isquote(car(obj)->this.symbol)) {
                return cdr(obj);
            }
		
            if(isdefine(car(obj)->this.symbol)) {
                obj = cdr(obj);
		
                if(obj->type == SFS_PAIR && car(obj)->type == SFS_SYMBOL && cdr(obj)->type == SFS_PAIR && cdr(cdr(obj)) == nil) /*formulation du define correcte*/
                {
                    if( is_symbol_in_env( environment, car(obj) ) != nil) {
                        return set_symbol_value_in_env( environment, car(obj), sfs_eval(car(cdr(obj))));
                    }
                    else {
                        return add_symbol_to_env( environment, car(obj), sfs_eval(car(cdr(obj))) );
                    }
                }
                else {
                    WARNING_MSG("Not a correct define syntaxe --- Aborts");
                    return nil;
                }
            }
            if(isset(car(obj)->this.symbol)) {
                obj = cdr(obj);
                if(obj->type == SFS_PAIR && car(obj)->type == SFS_SYMBOL && cdr(obj)->type == SFS_PAIR && cdr(cdr(obj)) == nil) /*formulation du set correcte*/
                {
                    while( is_symbol_in_env( env_incr, car(obj) ) == nil && cdr(env_incr) != nil )
                    {
                        env_incr=cdr(env_incr);
                    }
                    if(set_symbol_value_in_env( env_incr, car(obj), sfs_eval(car(cdr(obj)))) == nil) {
                        WARNING_MSG("The symbol %s can't be set (he doesn't exist) --- Aborts",car(obj)->this.symbol);
                        return nil;
                    }
                    return set_symbol_value_in_env( env_incr, car(obj), sfs_eval(car(cdr(obj))));
                }
                else {
                    WARNING_MSG("Not a correct set! syntaxe --- Aborts");
                    return nil;
                }
            }
            else { /*le car d'un debut d'arbre ne peut pas etre une paire*/
                WARNING_MSG("Invalid S-expression for evaluation --- Aborts");
		return obj;
            }

        default:
            break;
        }


        return objres;
    }

}














