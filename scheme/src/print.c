
/**
 * @file print.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:12:17 2012
 * @brief Printing stuff for SFS.
 *
 * Printing stuff for SFS.
 */
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "print.h"

#include <stdio.h>

void sfs_print_atom( object o ) {
	
	switch(o->type){
	
		case SFS_NUMBER:
			switch(o->this.number.numtype){
		
				case NUM_INTEGER:
					if(o->this.number.this.integer == LONG_MAX) printf("+inf");
					else if(o->this.number.this.integer == LONG_MIN) printf("-inf");					
					else printf("%lli",o->this.number.this.integer);
					break;
		
				case NUM_REAL:
					if(o->this.number.this.real >= LONG_MAX) printf("+inf");
					else if(o->this.number.this.real <= LONG_MIN) printf("-inf");					
					else printf("%lf",o->this.number.this.real);
					break;

				default:
					break;
			}
		break;

		case SFS_CHARACTER:
			if(o->this.character == '\n') printf("#\\newline");
			else if(o->this.character == ' ') printf("#\\space");
			else printf("#\\%c",o->this.character);
			break;

		case SFS_STRING:
			printf("\"%s\"",o->this.string);
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
	}
 
    return;
}

void sfs_print_pair( object o) {
	if((o->this.pair.car)->type == SFS_PAIR) printf("(");
	sfs_printf(o->this.pair.car);
	if((o->this.pair.cdr)->type != SFS_NIL){
		printf(" ");
		sfs_printf(o->this.pair.cdr);
	}
	else printf(")");
}

void sfs_printf( object o ) {
    if ( SFS_PAIR == o->type ) {
        sfs_print_pair( o );
    }
    else {
        sfs_print_atom( o );
    }

}
void sfs_print( object o ) {
	if( o->type == SFS_PAIR ){
		printf("(");
	
		sfs_printf(o);

	}
	else sfs_printf(o);
}
