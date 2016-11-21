
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

void sfs_print_atom(FILE *p, object o ) {
	
    switch(o->type) {

    case SFS_NUMBER:
        switch(o->this.number.numtype) {

        case NUM_INTEGER:
            /*if(o->this.number.this.integer == LONG_MAX) fprintf(p,"+inf");
            else if(o->this.number.this.integer == LONG_MIN)  fprintf(p,"-inf");
            else*/ fprintf(p,"%lli",o->this.number.this.integer);
            break;

        case NUM_REAL:
         	fprintf( p,"%.15G",o->this.number.this.real); /*%.16G = on affiche au maximum 16 chiffres significatifs*/
            break;

        default:
            break;
        }
        break;

    case SFS_CHARACTER:
        if(o->this.character == '\n') fprintf( p,"#\\newline");
        else if(o->this.character == ' ') fprintf( p,"#\\space");
        else fprintf( p,"#\\%c",o->this.character);
        break;

    case SFS_STRING:
        fprintf( p,"\"%s\"",o->this.string);
        break;

    case SFS_SYMBOL:
        fprintf(p,"%s",o->this.symbol);
        break;

    case SFS_NIL:
        fprintf( p,"()");
        break;

    case SFS_BOOLEAN:
        if(o->this.boolean == VRAI) {

            fprintf( p,"#t");
        }
        else {

            fprintf( p,"#f");
        }

    default:
        break;
    }

    return;
}

void sfs_print_pair(FILE *p, object o) {

    if((o->this.pair.car)->type == SFS_PAIR) fprintf( p,"(");
    sfs_printf(p,o->this.pair.car);
	
    if((o->this.pair.cdr)->type != SFS_NIL) {
        fprintf( p," ");
	if((o->this.pair.cdr)->type != SFS_PAIR) fprintf( p,". ");
        sfs_printf(p,o->this.pair.cdr);
	if((o->this.pair.cdr)->type != SFS_PAIR) fprintf( p,")");
    }
	
    else fprintf( p,")");
}

void sfs_printf(FILE *p, object o ) {

    if ( SFS_PAIR == o->type ) {
        sfs_print_pair(p, o );
    }
    else {
        sfs_print_atom(p, o );
    }

}
void sfs_print(FILE *p, object o ) {

    if( o->type == SFS_PAIR ) {
        fprintf( p,"(");

        sfs_printf(p,o);

    }
    else sfs_printf(p,o);
}
