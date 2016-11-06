
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
#include "calcul.h"



object sfs_eval( object o ) {
    object list,objres,objc = NULL, obj = o , env_incr = environment;
begin:
    switch(obj->type) {
    
    case SFS_NUMBER:
        return obj;
        
    case SFS_CHARACTER:		
        return obj;
        
    case SFS_STRING:
        return obj;
        
    case SFS_SYMBOL:
    	objc = obj;
    	objres = get_symbol_value(environment,obj);
    	if(!objres){
			add_object_to_list(&STACK,obj);
    		REPORT_MSG(";ERROR: unbound variable: %s\n; no previous definition.\n",obj->this.symbol);
    		if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
    		else REPORT_MSG("; in scope environment.\n");
			if(STACK != nil ){
				inverse_list(&STACK);
				print_stack(STACK);
			}  
			init_stack();
			return NULL;		
    	}
    	
        if( objres->type == SFS_SYMBOL && !strcasecmp(obj->this.symbol,objres->this.symbol) ){ /*quand on tape par exemple SFS:0> (if #t define)*/
        	if( STACK != nil ){
			   	REPORT_MSG(";ERROR: Use of keyword as variable %s\n; in expression: ",obj->this.symbol);
				sfs_print(car(STACK)); printf("\n");
				if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
				else REPORT_MSG("; in scope environment.\n");
				add_object_to_list(&STACK,obj);			
				inverse_list(&STACK);
				print_stack(STACK);
			}
			else REPORT_MSG("(#@keyword . #<primitive-macro! #<primitive-procedure %s>>)\n",obj->this.symbol);
			init_stack();
			return NULL;  
		}
        return objres;
        
    case SFS_NIL:
        return obj;
        
    case SFS_BOOLEAN:
        return obj;
        
    case SFS_PAIR:
        if(car(obj)->type == SFS_SYMBOL) {
                    
            if(isand(car(obj)->this.symbol)) {
                objc = obj;
				add_object_to_list(&STACK,obj);
				objres = get_symbol_value(environment,car(obj));
            	if( (objres->type == SFS_SYMBOL) && !strcasecmp(car(obj)->this.symbol,objres->this.symbol) ){            
            		objres = VRAI;
		            while(cdr(obj) != nil) {
		            	obj = cdr(obj);
		            	objres = sfs_eval(car(obj));
		            	if( objres == NULL ){ 
		            		return NULL;
		            	}
		                if( objres == FAUX ) return FAUX;
		            }
		            return objres;
		        }
		        else{
		       		REPORT_MSG(";ERROR: Wrong type to apply\n; or: has been redifined.\n; in expression: ");
                	sfs_print(objc); printf("\n");
                	if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
					else REPORT_MSG("; in scope environment.\n");
					if(STACK != nil ){
						inverse_list(&STACK);
						print_stack(STACK);
					}
					init_stack();
					return NULL;		        
		        }		        		        
            }
            
            if(isor(car(obj)->this.symbol)) {
                objc = obj;
				add_object_to_list(&STACK,obj);
				objres = get_symbol_value(environment,car(obj));
            	if( (objres->type == SFS_SYMBOL) && !strcasecmp(car(obj)->this.symbol,objres->this.symbol) ){ 
            		obj = cdr(obj);                
		            while(obj != nil) {
		            	objres = sfs_eval(car(obj));
		            	if( objres == NULL ){
		            		return NULL;
		            	}                
		                if( objres == FAUX ) {
		                    obj = cdr(obj);
		                    continue;
		                }		                	
		                return objres;
		            }
		            return FAUX;
		        }
		        else{
		       		REPORT_MSG(";ERROR: Wrong type to apply\n; or: has been redifined.\n; in expression: ");
                	sfs_print(objc); printf("\n");
                	if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
					else REPORT_MSG("; in scope environment.\n");
					if(STACK != nil ){
						inverse_list(&STACK);
						print_stack(STACK);
					}
					init_stack();
					return NULL;		        
		        }
            }
            
            if(isif(car(obj)->this.symbol)) {
            	objc = obj;
				add_object_to_list(&STACK,obj);
				objres = get_symbol_value(environment,car(obj));
            	if( (objres->type == SFS_SYMBOL) && !strcasecmp(car(obj)->this.symbol,objres->this.symbol) ){  /*ca c'est la definition d'une bonne fonction if*/
		            obj = cdr(obj);
		            if(obj == nil || obj == NULL){
		                REPORT_MSG(";ERROR: if: missing predicat.\n; in expression : "); 
		                sfs_print(objc); printf("\n");
		                REPORT_MSG("; expected form : (if predicat consequence alternative).\n");
		                if(STACK != nil ){           
							inverse_list(&STACK);
							print_stack(STACK);
						}
		            	return NULL;
		            }
					objres = sfs_eval(car(obj));/*le predicat*/
					if(objres == NULL) return NULL;
		            if( objres != FAUX ) {
		                if( car(cdr(obj)) != NULL && car(cdr(obj)) != nil ) {/*consequence?*/
		                    obj = car(cdr(obj));
		                    goto begin;
		                }
		                REPORT_MSG(";ERROR: if: missing consequence.\n; in expression : "); 
		                sfs_print(objc); printf("\n");   
		                REPORT_MSG("; expected form : (if predicat consequence alternative).\n");       
						if(STACK != nil ){
							inverse_list(&STACK);
							print_stack(STACK);
						}
						init_stack();
		            	return NULL;
		            }

		            else{
		                if( car(cdr(cdr(obj))) != nil && car(cdr(cdr(obj))) != NULL ) { /*on teste pour savoir si y'a la conséquence ou pas*/
		                    obj = car(cdr(cdr(obj)));objres = sfs_eval(obj);
		                    if( obj->type == SFS_SYMBOL && objres->type == SFS_SYMBOL && !strcasecmp(obj->this.symbol,objres->this.symbol) ){
							   	REPORT_MSG(";ERROR: Wrong type to apply\n; in expression: ");
						    	sfs_print(objc); printf("\n");
						    	if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
								else REPORT_MSG("; in scope environment.\n");
								if(STACK != nil ){
									inverse_list(&STACK);
									print_stack(STACK);
								}
								init_stack();
								return NULL;
							}		                    
		                    goto begin;
		                } else return FAUX;
		            }
		        }
		       	else{/*ca veut dire que le if a été redéfini*/
		       		REPORT_MSG(";ERROR: Wrong type to apply\n; if: has been redifined.\n; in expression: ");
                	sfs_print(objc); printf("\n");
                	if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
					else REPORT_MSG("; in scope environment.\n");
					if(STACK != nil ){
						inverse_list(&STACK);
						print_stack(STACK);
					}
					init_stack();
					return NULL;
				}
		       		
            }
            
            if(isbegin(car(obj)->this.symbol)) {
            	objc = obj;
				add_object_to_list(&STACK,obj);
				objres = get_symbol_value(environment,car(obj));
            	if( (objres->type == SFS_SYMBOL) && !strcasecmp(car(obj)->this.symbol,objres->this.symbol) ){ 
		            objres = obj;
		            if( cdr(obj) == nil || cdr(obj) == NULL ){
		            	REPORT_MSG("#<unspecified>\n");
		            	return NULL;
		            }
		            objres = sfs_eval(car(cdr(obj))); 
		            obj = cdr(cdr(obj));
		            while( obj != nil && objres!=NULL) {
		                objres = sfs_eval(car(obj));
		                obj = cdr(obj);
		            }
		            return objres;
		        }
		        else{
		       		REPORT_MSG(";ERROR: Wrong type to apply\n; begin: has been redifined.\n; in expression: ");
                	sfs_print(objc); printf("\n");
                	if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
					else REPORT_MSG("; in scope environment.\n");
					if(STACK != nil ){
						inverse_list(&STACK);
						print_stack(STACK);
					}
					init_stack();
					return NULL;
		        }
            }
            if(isquote(car(obj)->this.symbol)) {
            	objc = obj;
				add_object_to_list(&STACK,obj);
				objres = get_symbol_value(environment,car(obj));
            	if( (objres->type == SFS_SYMBOL) && !strcasecmp(car(obj)->this.symbol,objres->this.symbol) ){            
		        	if( cdr(obj) == nil ){
		        		REPORT_MSG(";ERROR: quote: missing or extra expression ");
		        		sfs_print(obj); printf("\n");
		        		REPORT_MSG("; in expression: ");
		        		sfs_print(obj); printf("\n");
						if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
						else REPORT_MSG("; in scope environment\n");
						if(STACK != nil ){
							inverse_list(&STACK);
							print_stack(STACK);
						}
						init_stack();
					}
		            return car(cdr(obj));
		        }
		        else{
		       		REPORT_MSG(";ERROR: Wrong type to apply\n; quote: has been redifined.\n; in expression: ");
                	sfs_print(objc); printf("\n");
                	if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
					else REPORT_MSG("; in scope environment.\n");
					if(STACK != nil ){
						inverse_list(&STACK);
						print_stack(STACK);
					}
					init_stack();
					return NULL;
		        }		       
            }
		
            if(isdefine(car(obj)->this.symbol)) {
            	objc= obj;
				add_object_to_list(&STACK,obj);
				objres = get_symbol_value(environment,car(obj));
            	if( (objres->type == SFS_SYMBOL) && !strcasecmp(car(obj)->this.symbol,objres->this.symbol) ){           
		            obj = cdr(obj);
					if(	obj->type == SFS_PAIR && car(obj)->type == SFS_PAIR){
		            	REPORT_MSG(";ERROR: define: bad formals\n; in expression : ");
		            	sfs_print(car(obj)); printf("\n");
		            	if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
						else REPORT_MSG("; in scope environment.\n");
						if(STACK != nil ){
							inverse_list(&STACK);
							print_stack(STACK);
						}
						init_stack();
						return NULL;
		   			}

		            if(obj->type == SFS_PAIR && car(obj)->type == SFS_SYMBOL && cdr(obj)->type == SFS_PAIR && cdr(cdr(obj)) == nil) /*formulation du define correcte*/
		            {
						objres = sfs_eval(car(cdr(obj)));
						if(objres != NULL && objres !=nil){
				            if( is_symbol_in_env( environment, car(obj) ) != nil) {	
				            	objc = get_symbol_value(environment,car(obj));
				          		if( !strcasecmp(car(obj)->this.symbol,objc->this.symbol) ){
				          			REPORT_MSG(";WARNING: redefining built-in syntax\n", car(obj)->this.symbol );
				          		}	        
				                return car(set_symbol_value_in_env( environment, car(obj), objres ));
				            }
				            else {
				                return car(add_symbol_to_env( environment, car(obj), objres ));
				            }
				        }
				        return NULL;
			
		            }
		            else {
		        		REPORT_MSG(";ERROR: define: missing or extra expression ");
		        		sfs_print(objc); printf("\n");
		        		REPORT_MSG("; in expression: ");
		        		sfs_print(objc); printf("\n");
						if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
						else REPORT_MSG("; in scope environment\n");
						if(STACK != nil ){
							inverse_list(&STACK);
							print_stack(STACK);
						}
						init_stack();
		                return NULL;
		            }
		        }
		        else{
		       		REPORT_MSG(";ERROR: Wrong type to apply\n; define: has been redifined.\n; in expression: ");
                	sfs_print(objc); printf("\n");
                	if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
					else REPORT_MSG("; in scope environment.\n");
					if(STACK != nil ){
						inverse_list(&STACK);
						print_stack(STACK);
					}
					init_stack();
					return NULL;
		        }	
            }
            
            if(isset(car(obj)->this.symbol)) {
            	objc= obj;
				add_object_to_list(&STACK,obj);
				objres = get_symbol_value(environment,car(obj));
            	if( (objres->type == SFS_SYMBOL) && !strcasecmp(car(obj)->this.symbol,objres->this.symbol) ){            
                	obj = cdr(obj);
					if(	obj->type == SFS_PAIR && car(obj)->type == SFS_PAIR){
			            REPORT_MSG(";ERROR: set!: bad formals\n; in expression : ");
		            	sfs_print(car(obj)); printf("\n");
		            	if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
						else REPORT_MSG("; in scope environment.\n");
						if(STACK != nil ){
							inverse_list(&STACK);
							print_stack(STACK);
						}
						init_stack();
						return NULL;
		   			}
				
		            if(obj->type == SFS_PAIR && car(obj)->type == SFS_SYMBOL && cdr(obj)->type == SFS_PAIR && cdr(cdr(obj)) == nil) /*formulation du set correcte*/
		            {
		                while( env_incr != nil && (object) is_symbol_in_env( env_incr, car(obj) ) == nil )
		                {
		                    env_incr=cdr(env_incr);
		                }
						if(env_incr == nil) {
							REPORT_MSG(";ERROR: unbound variable: %s\n ; no previous definition.\n",car(obj)->this.symbol);
							if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
							else REPORT_MSG("; in scope environment\n");      
							if(STACK != nil ){
								inverse_list(&STACK);
								print_stack(STACK);
							}
							init_stack();
				            return NULL;
		                }
		                objres = sfs_eval(car(obj));
						if(!objres) return NULL;
						objres = sfs_eval(car(cdr(obj)));
						if(objres == nil || objres == NULL) return NULL;
						objres = set_symbol_value_in_env( env_incr, car(obj), objres);

		                return car(objres);
		            }
		            else {
		                REPORT_MSG(";ERROR: set!: missing or extra expression ");
						sfs_print(objc); printf("\n");
						REPORT_MSG("; in expression: ");
						sfs_print(objc); printf("\n");
						if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
						else REPORT_MSG("; in scope environment\n");
						if(STACK != nil ){
							inverse_list(&STACK);
							print_stack(STACK);
						}
						init_stack();
		                return NULL;
		            }
		         }
		        else{
		       		REPORT_MSG(";ERROR: Wrong type to apply\n; set!: has been redifined.\n; in expression: ");
                	sfs_print(objc); printf("\n");
                	if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
					else REPORT_MSG("; in scope environment.\n");
					if(STACK != nil ){
						inverse_list(&STACK);
						print_stack(STACK);
					}
					init_stack();
					return NULL;
		        }
		        
           }
		    /*les primitives*/
			add_object_to_list(&STACK,obj);
		    objc = obj; list = nil;
		    obj = cdr(obj);
		    while(obj != nil){
		    	objres = sfs_eval(car(obj));
		    	if(!objres) return objres; /*qui est NULL*/
		    	add_object_to_list(&list,objres);
		    	obj = cdr(obj);
		    }
		    inverse_list(&list); /*il faut réinverser la liste pour qu'elle devienne comme avant*/
		    objres = sfs_eval(car(objc));
		    if(!objres) return objres;
		    objres = objres->this.primitive.function(list);
		    if(!objres){
		    	REPORT_MSG("; in expression: ");sfs_print(objc);printf("\n");
            	if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
				else REPORT_MSG("; in scope environment.\n");
				if(STACK != nil ){
					inverse_list(&STACK);
					print_stack(STACK);
				}
				init_stack();
			}
			return objres;
       }
       
	   if(car(obj)->type == SFS_PAIR){
	   		objres = sfs_eval(car(obj));
	   		if( objres == NULL || objres == nil) return NULL;
	   		obj->this.pair.car = objres;
			return sfs_eval(obj);
	   }
       else { /*le car d'un debut d'arbre ne peut pas autre chose qu'un symbol ou une paire*/
            WARNING_MSG("Invalid S-expression for evaluation --- Aborts");
			return NULL;
       }

       default:
           break;
    }


        return objres;
    

}














