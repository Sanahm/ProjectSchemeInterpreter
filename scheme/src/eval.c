
/**
 * @file eval.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:11:30 2012
 * @brief Evaluation stuff for SFS.
 *
 * Evaluation stuff for SFS.
 */

#include "eval.h"
#include "env.h"
#include <string.h>
#include <strings.h>
#include <primitive.h>
#include "calcul.h"



object sfs_eval( object o, object environment ) {
    object list,objres,procedure,objc = NULL, obj = o , env_incr = environment;
    static int i = 1;
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
        if(!objres || !strcmp(".",obj->this.symbol)/* pour le point*/) {
        	add_object_to_list(&STACK,obj);           
            REPORT_MSG(";ERROR: unbound variable: %s\n; no previous definition.\n",obj->this.symbol);
            if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
            else REPORT_MSG("; in scope environment.\n");
            if(STACK != nil ) {
                inverse_list(&STACK);
                print_stack(STACK);
            }
            init_stack();
            return NULL;
        }
        if( objres->type == SFS_PRIMITIVE && (STACK == nil || i)) {
            REPORT_MSG("#<primitive-procedure %s>\n",obj->this.symbol);
            return make_symbol("#<procedure>");
        }
        if( objres->type == SFS_COMPOUND && (STACK == nil || i)) {
            REPORT_MSG("#<CLOSURE %s ",obj->this.symbol);
            sfs_print(stderr,objres->this.compound.parms);
            fprintf(stderr,"%c",32);
            if(cdr(objres->this.compound.body) != nil) sfs_print(stderr,objres->this.compound.body);
            else sfs_print(stderr,car(objres->this.compound.body));
            REPORT_MSG(">\n");
            return make_symbol("#<procedure>");
        }

        if(  ( objres->type == SFS_SYMBOL && !strcasecmp(obj->this.symbol,objres->this.symbol) && objres == car(is_symbol_in_all_env(environment,obj)) )) { /*quand on tape par exemple SFS:0> (if #t define)*/
            if( !strcasecmp("+inf",objres->this.symbol) || !strcasecmp("-inf",objres->this.symbol) ) return objres;
            else if( STACK != nil && objres->type != SFS_PRIMITIVE) {
            	add_object_to_list(&STACK,obj);
                REPORT_MSG(";ERROR: Use of keyword as variable %s\n; in expression: ",obj->this.symbol);
                sfs_print(stderr,car(STACK));
                fprintf( stderr,"\n");
                if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
                else REPORT_MSG("; in scope environment.\n");
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

    case SFS_COMPOUND:
        return obj;

    case SFS_PRIMITIVE:
        return obj;

    case SFS_PAIR:
        if(car(obj)->type == SFS_SYMBOL) {

            if(islambda(car(obj)->this.symbol)) {

               	add_object_to_list(&STACK,obj);
            	objc = obj;
            	objres = get_symbol_value(environment,car(obj));
            	if( (objres->type == SFS_SYMBOL) && !strcasecmp(car(obj)->this.symbol,objres->this.symbol) ){  
		        	objres = cdr(obj);
		        	if( objres == nil || cdr(objres) == nil){ /*(lambda) ou (lambda x)*/          		
		        		REPORT_MSG(";ERROR: lambda: bad body ");
		        		error:
		        		sfs_print(stderr,objres); fprintf( stderr,"\n");
		        		REPORT_MSG("; in expression: ");sfs_print(stderr,objc); fprintf( stderr,"\n");
				    	if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
						else REPORT_MSG("; in scope environment.\n");
						if(STACK != nil ){
							inverse_list(&STACK);
							print_stack(STACK);
						}
						init_stack();
						return NULL;
					}
					objres = car(objres);
					if( objres->type != SFS_SYMBOL ){
						if (objres->type == SFS_PAIR || objres->type == SFS_NIL ){
							while( objres != nil ){ /*ici je verifie que les param sont bien de type symbol sinon j'arrete tout*/
								if(car(objres)->type != SFS_SYMBOL && car(objres)->type != SFS_PAIR){ /*si cest une paire la prochaine il rentrera dans la paire*/
									REPORT_MSG(";ERROR: lambda: bad formals ");
									goto error; /*le goto cest pour aller print le reste du msg: trop de paresse en moi :)!!*/
								}
								objres = cdr(objres);
							}
						}
						else{
							REPORT_MSG(";ERROR: lambda: bad formals ");
							goto error;
						}
					}
		        	object parms = car(cdr(obj));
		        	object body = cdr(cdr(obj));
					if(i){
						REPORT_MSG("#<CLOSURE <anon> ");
						sfs_print(stderr,parms); fprintf(stderr,"%c",32);
						if(cdr(body) != nil ) sfs_print(stderr,body);
						else sfs_print(stderr,car(body));
						REPORT_MSG(">\n");
						return make_symbol("#<procedure>");
					}
					i = 1;
					return make_lambda(parms,body,environment);
                                    
            	}
			    else{
			   		REPORT_MSG(";ERROR: Wrong type to apply\n; lambda: has been redifined.\n; in expression: ");
		        	sfs_print(stderr,objc); fprintf( stderr,"\n");
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

            if(islet(car(obj)->this.symbol)) {
                objc = obj;
                object objres1 = car(cdr(obj)),objres2=NULL, objres3=NULL;

                add_object_to_list(&STACK,obj);
                objres = get_symbol_value(environment,car(obj));
                if( (objres->type == SFS_SYMBOL) && !strcasecmp(car(obj)->this.symbol,objres->this.symbol) ) {
		    if(objres1==NULL){
			REPORT_MSG(";ERROR:  let: bad formal\n;in expression: ");
                        sfs_print(stderr,objc);
                        fprintf( stderr,"\n");
                        if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
                        else REPORT_MSG("; in scope environment.\n");
                        if(STACK != nil ) {
                            inverse_list(&STACK);
                            print_stack(STACK);
                        }
                        init_stack();
                        return NULL;
                    }
                    if(objres1->type != SFS_PAIR && objres1 != nil ) {
                        REPORT_MSG(";ERROR:  let: bad bindings ");
                        sfs_print(stderr,car(cdr(objc)));
                        REPORT_MSG("\n;in expression: ");
                        sfs_print(stderr,objc);
                        fprintf( stderr,"\n");
                        if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
                        else REPORT_MSG("; in scope environment.\n");
                        if(STACK != nil ) {
                            inverse_list(&STACK);
                            print_stack(STACK);
                        }
                        init_stack();
                        return NULL;
                    }
			obj=cdr(cdr(obj));
			objres=make_pair();
			objres3=objres;
			objres2 = objres;
                    objres->this.pair.car=make_pair();
                    objres=car(objres);
                    objres->this.pair.car=make_symbol("lambda");
                    objres->this.pair.cdr=make_pair();
                    objres=cdr(objres);
                    objres->this.pair.cdr=obj;

                    if(objres1 == nil) {
                        objres->this.pair.car=nil;

                    }
                    else {
                        objres->this.pair.car=make_pair();
                        objres=car(objres);
                        while(objres1 != nil) {

                            if( car(car(objres1)) == NULL ||  car(objres1)->type != SFS_PAIR || car(car(objres1))->type != SFS_SYMBOL || cdr(cdr(car(objres1))) != nil ) {
                                REPORT_MSG(";ERROR:  let: bad bindings ");
                                sfs_print(stderr,car(objres1));
                                REPORT_MSG("\n;in expression: ");
                                sfs_print(stderr,objc);
                                fprintf( stderr,"\n");
                                if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
                                else REPORT_MSG("; in scope environment.\n");
                                if(STACK != nil ) {
                                    inverse_list(&STACK);
                                    print_stack(STACK);
                                }
                                init_stack();
                                return NULL;
                            }

                            objres->this.pair.car=car(car(objres1));
                            objres2->this.pair.cdr=make_pair();
                            objres2=cdr(objres2);
                            objres2->this.pair.car=car(cdr(car(objres1)));
                            objres1=cdr(objres1);
                            if(objres1 != nil) {
                                objres->this.pair.cdr=make_pair();
                                objres=cdr(objres);
                            }

                        }
                        objres->this.pair.cdr=nil;







                    }
			                        objres2->this.pair.cdr=nil;

                        return sfs_eval(objres3,environment);
                }
                else {
                    REPORT_MSG(";ERROR: Wrong type to apply\n; let: has been redifined.\n; in expression: ");
                    sfs_print(stderr,objc);
                    fprintf( stderr,"\n");
                    if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
                    else REPORT_MSG("; in scope environment.\n");
                    if(STACK != nil ) {
                        inverse_list(&STACK);
                        print_stack(STACK);
                    }
                    init_stack();
                    return NULL;
                }
            }
		if(isletetoi(car(obj)->this.symbol)) {
                objc = obj;
                object objres1 = car(cdr(obj)),objres2=cdr(objres1), objres3=cdr(cdr(obj));

                add_object_to_list(&STACK,obj);
                objres = get_symbol_value(environment,car(obj));
                if( (objres->type == SFS_SYMBOL) && !strcasecmp(car(obj)->this.symbol,objres->this.symbol) ) {
		    if(objres1==NULL){
			REPORT_MSG(";ERROR:  let*: bad formal\n;in expression: ");
                        sfs_print(stderr,objc);
                        fprintf( stderr,"\n");
                        if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
                        else REPORT_MSG("; in scope environment.\n");
                        if(STACK != nil ) {
                            inverse_list(&STACK);
                            print_stack(STACK);
                        }
                        init_stack();
                        return NULL;
                    }
                    if(objres1->type != SFS_PAIR && objres1 != nil ) {
                        REPORT_MSG(";ERROR:  let*: bad bindings ");
                        sfs_print(stderr,car(cdr(objc)));
                        REPORT_MSG("\n;in expression: ");
                        sfs_print(stderr,objc);
                        fprintf( stderr,"\n");
                        if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
                        else REPORT_MSG("; in scope environment.\n");
                        if(STACK != nil ) {
                            inverse_list(&STACK);
                            print_stack(STACK);
                        }
                        init_stack();
                        return NULL;
                    }
			obj->this.pair.car=make_symbol("let");
			if(objres1 == nil || cdr(objres1) == nil){
				
				return sfs_eval(obj,environment);
			}
			obj=cdr(obj);
			obj->this.pair.cdr=make_pair();
			obj=cdr(obj);
			obj->this.pair.cdr=nil;
			obj->this.pair.car=make_pair();
			obj=car(obj);
			if(cdr(cdr(objres1)) == nil) obj->this.pair.car = make_symbol("let");
			else obj->this.pair.car = make_symbol("let*");
			objres1->this.pair.cdr = nil;
			obj->this.pair.cdr=make_pair();
			obj=cdr(obj);
			obj->this.pair.cdr=objres3;
			obj->this.pair.car=objres2;
			
			return sfs_eval(objc,environment);
                }
                else {
                    REPORT_MSG(";ERROR: Wrong type to apply\n; let*: has been redifined.\n; in expression: ");
                    sfs_print(stderr,objc);
                    fprintf( stderr,"\n");
                    if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
                    else REPORT_MSG("; in scope environment.\n");
                    if(STACK != nil ) {
                        inverse_list(&STACK);
                        print_stack(STACK);
                    }
                    init_stack();
                    return NULL;
                }
            }
            if(isand(car(obj)->this.symbol)) {
                objc = obj;
                add_object_to_list(&STACK,obj);
                objres = get_symbol_value(environment,car(obj));
                if( (objres->type == SFS_SYMBOL) && !strcasecmp(car(obj)->this.symbol,objres->this.symbol) ) {
                    objres = VRAI;
                    while(cdr(obj) != nil) {
                        obj = cdr(obj);
                        objres = get_symbol_value(environment, car(obj));
                        if(objres && (objres->type == SFS_PRIMITIVE || objres->type == SFS_COMPOUND) && cdr(obj) != nil ) i = 0;
                        objres = sfs_eval(car(obj),environment);
                        i = 1;
                        if( objres == NULL ) {
                            return NULL;
                        }
                        if( objres == FAUX ) return FAUX;
                    }
                    return objres;
                }
                else {
                    REPORT_MSG(";ERROR: Wrong type to apply\n; or: has been redifined.\n; in expression: ");
                    sfs_print(stderr,objc);
                    fprintf( stderr,"\n");
                    if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
                    else REPORT_MSG("; in scope environment.\n");
                    if(STACK != nil ) {
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
                if( (objres->type == SFS_SYMBOL) && !strcasecmp(car(obj)->this.symbol,objres->this.symbol) ) {
                    obj = cdr(obj);
                    while(obj != nil) {
                        objres = sfs_eval(car(obj),environment);
                        if( objres == NULL ) {
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
                else {
                    REPORT_MSG(";ERROR: Wrong type to apply\n; or: has been redifined.\n; in expression: ");
                    sfs_print(stderr,objc);
                    fprintf( stderr,"\n");
                    if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
                    else REPORT_MSG("; in scope environment.\n");
                    if(STACK != nil ) {
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
                if( (objres->type == SFS_SYMBOL) && !strcasecmp(car(obj)->this.symbol,objres->this.symbol) ) { /*ca c'est la definition d'une bonne fonction if*/
                    obj = cdr(obj);
                    if(obj == nil || obj == NULL) {
                        REPORT_MSG(";ERROR: if: missing predicat.\n; in expression : ");
                        sfs_print(stderr,objc);
                        fprintf( stderr,"\n");
                        REPORT_MSG("; expected form : (if predicat consequence alternative).\n");
                        if(STACK != nil ) {
                            inverse_list(&STACK);
                            print_stack(STACK);
                        }
                        return NULL;
                    }
                    if(i) {
                        i = 0; /*(if (lambda (n) (+ 1 n)) 2)*/
                        objres = sfs_eval(car(obj),environment);/*le predicat*/
                        i = 1;
                    }
                    else objres = sfs_eval(car(obj),environment);
                    if(objres == NULL) return NULL;
                    if( objres != FAUX ) {
                        if( car(cdr(obj)) != NULL /*&& car(cdr(obj)) != nil */) {/*consequence?*/
                            obj = car(cdr(obj));
                            /*objres = get_symbol_value(environment, obj);
                            /*if(objres && (objres->type == SFS_PRIMITIVE || objres->type == SFS_COMPOUND) && i) i = 1;*/
                            goto begin;
                        }
                        REPORT_MSG(";ERROR: if: missing consequence.\n; in expression : ");
                        sfs_print(stderr,objc);
                        fprintf( stderr,"\n");
                        REPORT_MSG("; expected form : (if predicat consequence alternative).\n");
                        if(STACK != nil ) {
                            inverse_list(&STACK);
                            print_stack(STACK);
                        }
                        init_stack();
                        return NULL;
                    }

                    else {
                        if( car(cdr(cdr(obj))) != nil && car(cdr(cdr(obj))) != NULL ) { /*on teste pour savoir si y'a l'alternative ou pas*/
                            obj = car(cdr(cdr(obj)));
                            /*objres = get_symbol_value(obj,environment);
                            if(objres && obj->type == SFS_SYMBOL && objres->type == SFS_SYMBOL && !strcasecmp(obj->this.symbol,objres->this.symbol) ) { /*(if #f 1 define) ne doit pas passer*/
                                /*REPORT_MSG(";ERROR: Wrong type to apply\n; in expression: ");
                                sfs_print(stderr,objc);
                                fprintf( stderr,"\n");
                                if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
                                else REPORT_MSG("; in scope environment.\n");
                                if(STACK != nil ) {
                                    inverse_list(&STACK);
                                    print_stack(STACK);
                                }
                                init_stack();
                                return NULL;
                            }*/
                            /*objres = get_symbol_value(environment, obj);
                            if(objres && objres->type == SFS_PRIMITIVE && i) i = 1;*/
                            goto begin;
                        } else return FAUX;
                    }
                }
                else { /*ca veut dire que le if a été redéfini*/
                    REPORT_MSG(";ERROR: Wrong type to apply\n; if: has been redifined.\n; in expression: ");
                    sfs_print(stderr,objc);
                    fprintf( stderr,"\n");
                    if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
                    else REPORT_MSG("; in scope environment.\n");
                    if(STACK != nil ) {
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
                if( (objres->type == SFS_SYMBOL) && !strcasecmp(car(obj)->this.symbol,objres->this.symbol) ) {
                    objres = obj;
                    if( cdr(obj) == nil || cdr(obj) == NULL ) {
                        REPORT_MSG("#<unspecified>\n");
                        return NULL;
                    }
                    obj = cdr(obj);
                    while( obj != nil && objres!=NULL) {
                        objres = get_symbol_value(environment, car(obj));
                        if(car(car(obj)) && car(car(obj))->type == SFS_SYMBOL && islambda(car(car(obj))->this.symbol) && i) i = 0;
                        if(objres && (objres->type == SFS_PRIMITIVE || objres->type == SFS_COMPOUND) && cdr(obj)!=nil) i = 0;
                        objres = sfs_eval(car(obj),environment);
                        i =1;
                        obj = cdr(obj);
                    }
                    return objres;
                }
                else {
                    REPORT_MSG(";ERROR: Wrong type to apply\n; begin: has been redifined.\n; in expression: ");
                    sfs_print(stderr,objc);
                    fprintf( stderr,"\n");
                    if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
                    else REPORT_MSG("; in scope environment.\n");
                    if(STACK != nil ) {
                        inverse_list(&STACK);
                        print_stack(STACK);
                    }
                    init_stack();
                    return NULL;
                }
            }
            if(isquote(car(obj)->this.symbol)) {
                objc = obj;
                objres = get_symbol_value(environment,car(obj));
                add_object_to_list(&STACK,objc);
                if( (objres->type == SFS_SYMBOL) && !strcasecmp(car(obj)->this.symbol,objres->this.symbol) ) {
                    if( cdr(obj) == nil ) {
                        REPORT_MSG(";ERROR: quote: missing or extra expression ");
                        sfs_print(stderr,obj);
                        fprintf( stderr,"\n");
                        REPORT_MSG("; in expression: ");
                        sfs_print(stderr,obj);
                        fprintf( stderr,"\n");
                        if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
                        else REPORT_MSG("; in scope environment\n");
                        if(STACK != nil ) {
                            inverse_list(&STACK);
                            print_stack(STACK);
                        }
                        init_stack();
                        return NULL;
                    }
                    /* pour le point*/
                    /*objres=car(cdr(obj));
                    if(objres->type == SFS_PAIR){
                    	while(cdr(objres) != nil  && strcmp(".",car(cdr(objres))->this.symbol) ){
                    		objres=cdr(objres);

                    	}


                    }
                    if(cdr(objres) != nil && objres->type == SFS_PAIR && car(cdr(objres)) != NULL && car(cdr(objres))->type == SFS_SYMBOL && !strcmp(".",car(cdr(objres))->this.symbol) ){/* pour le point*/
                    /*add_object_to_list(&STACK,objres);
                    if(cdr(cdr(cdr(objres))) == nil)	objres->this.pair.cdr = car(cdr(cdr(objres)));
                    else{
                    	REPORT_MSG(";ERROR: list: missing paren ");
                    		sfs_print(stderr,objc); fprintf( stderr,"\n");
                    		REPORT_MSG("; in expression: ");
                    		sfs_print(stderr,objc); fprintf( stderr,"\n");
                    		if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
                    		else REPORT_MSG("; in scope environment\n");
                    		if(STACK != nil ){
                    			inverse_list(&STACK);
                    			print_stack(STACK);
                    		}
                    		init_stack();
                    		return NULL;
                    }
                    }*/
					if(cdr(cdr(obj)) != nil) {
                        REPORT_MSG(";ERROR: define: missing or extra expression ");
                        sfs_print(stderr,objc);
                        fprintf( stderr,"\n");
                        REPORT_MSG("; in expression: ");
                        sfs_print(stderr,objc);
                        fprintf( stderr,"\n");
                        if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
                        else REPORT_MSG("; in scope environment\n");
                        if(STACK != nil ) {
                            inverse_list(&STACK);
                            print_stack(STACK);
                        }
                        init_stack();
                        return NULL;
                    }
                    return car(cdr(obj));
                }
                else {                    
                    REPORT_MSG(";ERROR: Wrong type to apply\n; quote: has been redifined.\n; in expression: ");
                    sfs_print(stderr,objc);
                    fprintf( stderr,"\n");
                    if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
                    else REPORT_MSG("; in scope environment.\n");
                    if(STACK != nil ) {
                        inverse_list(&STACK);
                        print_stack(STACK);
                    }
                    init_stack();
                    return NULL;
                }
            }

            if(isdefine(car(obj)->this.symbol)) {
                objc= obj;
                objres = get_symbol_value(environment,car(obj));
                add_object_to_list(&STACK,objc);
                if( (objres->type == SFS_SYMBOL) && !strcasecmp(car(obj)->this.symbol,objres->this.symbol) ) {
                    obj = cdr(obj);
                    /*if(	obj->type == SFS_PAIR && car(obj)->type == SFS_PAIR) {
                        REPORT_MSG(";ERROR: define: bad formals\n; in expression : ");
                        sfs_print(stderr,car(obj));
                        fprintf( stderr,"\n");
                        if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
                        else REPORT_MSG("; in scope environment.\n");
                        if(STACK != nil ) {
                            inverse_list(&STACK);
                            print_stack(STACK);
                        }
                        init_stack();
                        return NULL;
                    }*/

                    if(obj->type == SFS_PAIR && car(obj)->type == SFS_SYMBOL && cdr(obj)->type == SFS_PAIR && cdr(cdr(obj)) == nil) /*formulation du define correcte*/
                    {
                        if(!strcmp(".",car(obj)->this.symbol)) { /* pour le point */
                            REPORT_MSG(";ERROR: define: \".\" cannot be set ");
                            sfs_print(stderr,objc);
                            fprintf( stderr,"\n");
                            REPORT_MSG("; in expression: ");
                            sfs_print(stderr,objc);
                            fprintf( stderr,"\n");
                            if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
                            else REPORT_MSG("; in scope environment\n");
                            if(STACK != nil ) {
                                inverse_list(&STACK);
                                print_stack(STACK);
                            }
                            init_stack();
                            return NULL;
                        }

                        objres = get_symbol_value(environment, car(cdr(obj)));
                        if(car(car(cdr(obj))) && car(car(cdr(obj)))->type == SFS_SYMBOL && (islambda(car(car(cdr(obj)))->this.symbol)|| !strcasecmp("interaction-environment",car(car(cdr(obj)))->this.symbol))) i = 0;
                        if(objres && (objres->type == SFS_PRIMITIVE || objres->type == SFS_COMPOUND )) i = 0;
                        objres = sfs_eval(car(cdr(obj)),environment);/*if(!objres) return FAUX;*/
                        i =1;
                        if(objres != NULL) {
                            if( is_symbol_in_env( environment, car(obj) ) != nil) {
                                objc = get_symbol_value(environment,car(obj));
                                if( !strcasecmp(car(obj)->this.symbol,objc->this.symbol) || objc->type == SFS_PRIMITIVE ) {
                                    REPORT_MSG(";WARNING: redefining built-in syntax %s\n", car(obj)->this.symbol );
                                }
                                set_symbol_value_in_env( environment, car(obj), objres );
                                return null;
                            }
                            else {
                                add_symbol_to_env( environment, car(obj), objres );
                                return null;
                            }
                        }
                        return NULL;

                    }
                    else if(obj->type == SFS_PAIR && car(obj)->type == SFS_PAIR && cdr(obj)->type == SFS_PAIR ) /*formulation du define correcte*/
                    {
                        object objres2=NULL;

                        objres=cdr(car(obj));
                        objres2=cdr(obj);
                        obj->this.pair.car = car(car(obj));
                        obj->this.pair.cdr=make_pair();
                        obj=cdr(obj);
                        obj->this.pair.car=make_pair();
                        obj->this.pair.cdr=nil;
                        obj=car(obj);
                        obj->this.pair.car=make_symbol("lambda");
                        obj->this.pair.cdr=make_pair();
                        obj=cdr(obj);
                        obj->this.pair.car=objres;
                        obj->this.pair.cdr=objres2;


                        return sfs_eval(objc,environment);
                    }
                    else {
                        REPORT_MSG(";ERROR: define: missing or extra expression ");
                        sfs_print(stderr,objc);
                        fprintf( stderr,"\n");
                        REPORT_MSG("; in expression: ");
                        sfs_print(stderr,objc);
                        fprintf( stderr,"\n");
                        if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
                        else REPORT_MSG("; in scope environment\n");
                        if(STACK != nil ) {
                            inverse_list(&STACK);
                            print_stack(STACK);
                        }
                        init_stack();
                        return NULL;
                    }
                }
                else {                    
                    REPORT_MSG(";ERROR: Wrong type to apply\n; define: has been redifined.\n; in expression: ");
                    sfs_print(stderr,objc);
                    fprintf( stderr,"\n");
                    if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
                    else REPORT_MSG("; in scope environment.\n");
                    if(STACK != nil ) {
                        inverse_list(&STACK);
                        print_stack(STACK);
                    }
                    init_stack();
                    return NULL;
                }
            }

            if(isset(car(obj)->this.symbol)) {
                objc= obj;
                objres = get_symbol_value(environment,car(obj));
                add_object_to_list(&STACK,objc);
                if( (objres->type == SFS_SYMBOL) && !strcasecmp(car(obj)->this.symbol,objres->this.symbol) ) {
                    obj = cdr(obj);
                    if(	obj->type == SFS_PAIR && car(obj)->type == SFS_PAIR) {                       
                        REPORT_MSG(";ERROR: set!: bad formals\n; in expression : ");
                        sfs_print(stderr,car(obj));
                        fprintf( stderr,"\n");
                        if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
                        else REPORT_MSG("; in scope environment.\n");
                        if(STACK != nil ) {
                            inverse_list(&STACK);
                            print_stack(STACK);
                        }
                        init_stack();
                        return NULL;
                    }

                    if(obj->type == SFS_PAIR && car(obj)->type == SFS_SYMBOL && cdr(obj)->type == SFS_PAIR && cdr(cdr(obj)) == nil) /*formulation du set correcte*/
                    {
                        if(!strcmp(".",car(obj)->this.symbol)) { /* pour le point */
                            REPORT_MSG(";ERROR: set!: \".\" cannot be set ");
                            sfs_print(stderr,objc);
                            fprintf( stderr,"\n");
                            REPORT_MSG("; in expression: ");
                            sfs_print(stderr,objc);
                            fprintf( stderr,"\n");
                            if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
                            else REPORT_MSG("; in scope environment\n");
                            if(STACK != nil ) {
                                inverse_list(&STACK);
                                print_stack(STACK);
                            }
                            init_stack();
                            return NULL;
                        }
                        while( env_incr != nil && (object) is_symbol_in_env( env_incr, car(obj) ) == nil )
                        {
                            env_incr=cdr(env_incr);
                        }
                        if(env_incr == nil) {
                            REPORT_MSG(";ERROR: unbound variable: %s\n ; no previous definition.\n",car(obj)->this.symbol);
                            if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
                            else REPORT_MSG("; in scope environment\n");
                            if(STACK != nil ) {
                                inverse_list(&STACK);
                                print_stack(STACK);
                            }
                            init_stack();
                            return NULL;
                        }
                        objres = sfs_eval(car(obj),environment);
                        if(!objres) return NULL;
                        objres = sfs_eval(car(cdr(obj)),environment);
                        if(objres == nil || objres == NULL) return NULL;
                        objres = set_symbol_value_in_env( env_incr, car(obj), objres);

                        /*return car(objres);*/
                        return null;
                    }
                    else {
                        REPORT_MSG(";ERROR: set!: missing or extra expression ");
                        sfs_print(stderr,objc);
                        fprintf( stderr,"\n");
                        REPORT_MSG("; in expression: ");
                        sfs_print(stderr,objc);
                        fprintf( stderr,"\n");
                        if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
                        else REPORT_MSG("; in scope environment\n");
                        if(STACK != nil ) {
                            inverse_list(&STACK);
                            print_stack(STACK);
                        }
                        init_stack();
                        return NULL;
                    }
                }
                else {
                    REPORT_MSG(";ERROR: Wrong type to apply\n; set!: has been redifined.\n; in expression: ");
                    sfs_print(stderr,objc);
                    fprintf( stderr,"\n");
                    if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
                    else REPORT_MSG("; in scope environment.\n");
                    if(STACK != nil ) {
                        inverse_list(&STACK);
                        print_stack(STACK);
                    }
                    init_stack();
                    return NULL;
                }
            }


            primi:
		    /*les primitives*/
			add_object_to_list(&STACK,obj);
		    objc = obj;  		    
		    if(i){ i = 0;
		    	procedure = sfs_eval(car(objc),environment);i = 1;
		    } else procedure = sfs_eval(car(objc),environment);
		    if(!procedure) return NULL;
	     
		    if(procedure->type == SFS_COMPOUND) {
		    	object comp = nil; list = nil;
		    			    	
		    	add_object_to_list(&comp,make_symbol("begin"));/*(begin ...*/
		    	object parms = procedure->this.compound.parms;

				obj = cdr(objc);
				while(obj != nil){
					objres = make_pair();
					if(!objres) return NULL;
					objres->this.pair.car = make_symbol("quote");
					objres->this.pair.cdr = make_pair();
					if(!objres->this.pair.cdr) return NULL;
					objres->this.pair.cdr->this.pair.cdr = nil;
					if(car(obj)->type == SFS_SYMBOL){  /*ca c'est mis pour ce genre de cas (+ sin 4)*/
						objres->this.pair.cdr->this.pair.car = get_symbol_value(environment,car(obj));
						if(objres->this.pair.cdr->this.pair.car && objres->this.pair.cdr->this.pair.car->type == SFS_COMPOUND) i = 0;
						if(!objres->this.pair.cdr->this.pair.car) return sfs_eval(car(obj),environment);
						if(objres->this.pair.cdr->this.pair.car->type == SFS_PRIMITIVE) {
							add_object_to_list(&list,objres);
							obj = cdr(obj);
							continue;
						}
					}
					if(car(car(obj)) && car(car(obj))->type == SFS_SYMBOL && islambda(car(car(obj))->this.symbol)) i = 0; /* a cause de ça (map (lambda (n) (expt n n)) '(1 2 3 4 5))*/
					objres->this.pair.cdr->this.pair.car = sfs_eval(car(obj),environment);
					if(!objres->this.pair.cdr->this.pair.car) return NULL;
					add_object_to_list(&list,objres);
					obj = cdr(obj);
				}
				inverse_list(&list); /*il faut réinverser la liste pour qu'elle devienne comme avant*/
		    	
	    		if((parms->type == SFS_PAIR || parms->type == SFS_NIL) && sizeof_list(list) != sizeof_list(parms)){
					REPORT_MSG(";ERROR: lambda: Wrong number of args given\n; in expression: ");
			    	sfs_print(stderr,objc); fprintf( stderr,"\n");
			    	if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
					else REPORT_MSG("; in scope environment.\n");
					if(STACK != nil ){
						inverse_list(&STACK);
						print_stack(STACK);
					}
					init_stack();
					return NULL;
	    		}
		    	while(parms != nil && parms != NULL){
		    		object symb = make_pair();
		    		if(!symb){
			    		REPORT_MSG(";ERROR: memory: unable to allocate memory! try rebooting\n"); return NULL;
		    		}
		    		symb->this.pair.car = make_symbol("define"); /*(define ...*/
		    		symb->this.pair.cdr = make_pair();
		    		if(!symb->this.pair.cdr){
			    		REPORT_MSG(";ERROR: memory: unable to allocate memory! try rebooting\n"); return NULL;
		    		}
		    		if( parms->type == SFS_PAIR ) symb->this.pair.cdr->this.pair.car = car(parms);/*(define symb ..*/
		    		else symb->this.pair.cdr->this.pair.car = parms;
		    		symb->this.pair.cdr->this.pair.cdr = make_pair();
		    		if(!symb->this.pair.cdr->this.pair.cdr){
			    		REPORT_MSG(";ERROR: memory: unable to allocate memory! try rebooting\n"); return NULL;
		    		}
		    		if( parms->type == SFS_PAIR ) symb->this.pair.cdr->this.pair.cdr->this.pair.car = car(list);/*(define symb value .*/
		    		else {
		    			symb->this.pair.cdr->this.pair.cdr->this.pair.car = make_pair();
		    			if(!symb->this.pair.cdr->this.pair.cdr->this.pair.car){
		    				REPORT_MSG(";ERROR: memory: unable to allocate memory! try rebooting\n"); return NULL;
		    			}
		    			symb->this.pair.cdr->this.pair.cdr->this.pair.car->this.pair.car = make_symbol("quote");
		    			symb->this.pair.cdr->this.pair.cdr->this.pair.car->this.pair.cdr = make_pair();
		    			if(!symb->this.pair.cdr->this.pair.cdr->this.pair.car->this.pair.cdr){
		    				REPORT_MSG(";ERROR: memory: unable to allocate memory! try rebooting\n"); return NULL;
		    			}
		    			symb->this.pair.cdr->this.pair.cdr->this.pair.car->this.pair.cdr->this.pair.car = list;
		    			symb->this.pair.cdr->this.pair.cdr->this.pair.car->this.pair.cdr->this.pair.cdr = nil;
		    		}
		    		symb->this.pair.cdr->this.pair.cdr->this.pair.cdr = nil;		/*(define symb value )*/
		    		add_object_to_list(&comp,symb);/*sfs_print(stderr,comp); fprintf(stderr,"\n");*/
		    		parms = cdr(parms);
		    		list = cdr(list);
		    	}
		    	object body = procedure->this.compound.body;
		    	while(body != nil){
		    		add_object_to_list(&comp,car(body));
		    		if(car(body)->type == SFS_SYMBOL && islambda(car(body))) i = 0;
		    		body = cdr(body);
		    	}
	    			    			    	
		    	inverse_list(&comp);/*(begin (define symb1 val1) (define symb2 val2) ... body)*/
		    	/*if(procedure->this.compound.envt != TopLevel)*/ extend_env = procedure->this.compound.envt;
		    	if(!add_new_env(&extend_env)){
		    		REPORT_MSG(";ERROR: memory: unable to allocate memory! try rebooting\n"); return NULL;
		    	}
		    	init_stack();
		    	/*if(procedure->this.compound.envt != TopLevel)*/ procedure->this.compound.envt = extend_env;    	
		    	objres = sfs_eval(comp,extend_env);/*extend env a été rajouté parce que dans certaine primives
		    	font appel à sfs_eval et on donc besoin de savoir dans quel environment courant on est*/
		    	
		    	extend_env = cdr(extend_env); /*on réinitilaise*/    	
		    	return objres;		    			    	
		    		    
		    }
		    
		    else if(procedure->type != SFS_PRIMITIVE) {
	       		REPORT_MSG(";ERROR: Wrong type to apply ");
            	sfs_print(stderr,procedure); fprintf( stderr,"\n");
	       		REPORT_MSG("; in expression: ");
            	sfs_print(stderr,objc); fprintf( stderr,"\n");            	
            	if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
				else REPORT_MSG("; in scope environment.\n");
				if(STACK != nil ){
					inverse_list(&STACK);
					print_stack(STACK);
				}
				init_stack();
				return NULL;
			}
			else {
				list = nil;
				obj = cdr(obj);
				while(obj != nil){
					if(car(obj)->type == SFS_SYMBOL){ /* ca c'est mis pour ce genre de cas (+ sin 4)*/
						objres = get_symbol_value(environment,car(obj));
						if(objres && objres->type == SFS_COMPOUND) i = 0;
						if(!objres) return sfs_eval(car(obj),environment);
						if(objres->type == SFS_PRIMITIVE) {
							add_object_to_list(&list,objres);
							obj = cdr(obj);
							continue;
						}
					}
					if(car(car(obj)) && car(car(obj))->type == SFS_SYMBOL && islambda(car(car(obj))->this.symbol)) i = 0; /* a cause de ça (map (lambda (n) (expt n n)) '(1 2 3 4 5))*/
					objres = sfs_eval(car(obj),environment);
					if(!objres) return objres; /*qui est NULL*/
					add_object_to_list(&list,objres);
					obj = cdr(obj);
				}
				inverse_list(&list); /*il faut réinverser la liste pour qu'elle devienne comme avant*/
				/*i = 0;*/
				objres = procedure->this.primitive.function(list);
				if(!objres || objres == EXCEPT){
					REPORT_MSG("; in expression: ");sfs_print(stderr,objc);fprintf( stderr,"\n");
		        	if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
					else REPORT_MSG("; in scope environment.\n");
					if(STACK != nil ){
						inverse_list(&STACK);
						print_stack(STACK);
					}
					init_stack();
					if(objres == EXCEPT) return NULL;
				}
				if( objres == extend_env){
					return objres;
				}
				if(objres != NULL && objres->type == SFS_PRIMITIVE) return sfs_eval(objres,environment);
				return objres;
			}
       }
       
	   if(car(obj)->type == SFS_PAIR){
	   		i = 0;
	   		goto primi;
	   }
	   else if(car(obj)->type == SFS_COMPOUND){
	   		i = 0;
	   		goto primi;
	   }
	   else if(car(obj)->type == SFS_PRIMITIVE){
	   		i = 0;
	   		goto primi;
	   }
       else { /*le car d'un debut d'arbre ne peut pas autre chose qu'un symbol ou une paire*/
	    	add_object_to_list(&STACK,car(obj));
       		REPORT_MSG(";ERROR: Wrong type to apply ");
        	sfs_print(stderr,car(obj)); fprintf( stderr,"\n");
       		REPORT_MSG("; in expression: ");
        	sfs_print(stderr,obj); fprintf( stderr,"\n");            	
        	if(cdr(environment) == nil) REPORT_MSG("; in top level environment.\n");
			else REPORT_MSG("; in scope environment.\n");
			if(STACK != nil ){
				inverse_list(&STACK);
				print_stack(STACK);
			}
			init_stack();
			return NULL;
       }

       default:
           break;
    }


    return NULL;

}












