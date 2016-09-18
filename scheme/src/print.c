
/**
 * @file print.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:12:17 2012
 * @brief Printing stuff for SFS.
 *
 * Printing stuff for SFS.
 */

#include "print.h"

#include <stdio.h>

void sfs_print_atom( object o ) {
	
	/*switch(o->type){
	
		case SFS_NUMBER:
			switch(o->this.number.numtype){
		
			case NUM_INTEGER:
			printf("%d",o->this.num.this.integer);
			break;
	
			case NUM_REAL:
			printf("%lf",o->this.num.this.real);
			break;

			default:
			break;
			}

		case SFS_CHARACTER:
		printf("%c",o->this.character);
		break;

		case SFS_STRING:
		printf("%s",o->this.string);
		break;

		case SFS_SYMBOL:
		printf("%s",o->this.symbol);
		break;

		case SFS_NIL:
		printf("()");
		break;

		case SFS_BOOLEAN:
		if(o->this.boolean == VRAI){
		
			printf("#t");
		}
		else{

			printf("#f");
		}

		default:
		break;
	}*/
	
    return;
}

void sfs_print_pair( object o ) {

    return sfs_print( o );
}

void sfs_print( object o ) {

    if ( SFS_PAIR == o->type ) {
        sfs_print_pair( o );
    }
    else {
        sfs_print_atom( o );
    }

}
