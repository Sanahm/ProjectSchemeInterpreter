#include <string.h>
#include <strings.h>
#include "calcul.h"


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

object operation( object obj1,object obj2, char*op ) {
    num n;
    if(obj1 == NULL || obj2 == NULL) return NULL;
    switch(op[0]) {
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
            if(obj1->type == SFS_NUMBER) {
                n.numtype = NUM_REAL;
                n.this.real = 0;       /* 0/inf =0*/
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
            return make_symbol("nan");
        }

    case '<':
    	switch(op[1]){
    		 case '=':
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
				}
			default:
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
			}

    case '>':
    	switch(op[1]){
   			case '=':
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
				}
			default:
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
			}

    default:
        break;
    }
    return NULL;
}
