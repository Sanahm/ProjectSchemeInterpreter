#include "primitive.h"
#include "object.h"
#include "env.h"

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
    if(list == nil) return objres;
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
	if( obj->type == SFS_NUMBER && obj->this.number.numtype == NUM_INTEGER && obj->this.number.this.integer == 0 ){
    	REPORT_MSG(";ERROR: quotient: numerical overflow ");   
    	sfs_print(obj); printf("\n");
		return NULL; 
	}
    n.numtype = NUM_INTEGER;
    n.this.integer = ((object)car(list))->this.number.this.integer/obj->this.number.this.integer;
    return make_number(n);
}
	


















						
		
