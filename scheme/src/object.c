
/**
 * @file object.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 18:02:57 2012
 * @brief Object definitions for SFS.
 *
 * Object definitions for SFS.
 */

#include "object.h"
#include "mem.h"


object make_object( uint type ) {

    object t = sfs_malloc( sizeof( *t ) );

    t->type = type;

    return t;
}

object make_nil( void ) {

    object t = make_object( SFS_NIL );

    t->this.special = t;

    return t;
}

object make_bool( void ) {

    object t = make_object( SFS_BOOLEAN );

    t->this.special = t;

    return t;
}

object make_boolean(char c) {

    object t = make_object( SFS_BOOLEAN );
    if(c == 't') {
        t->this.boolean = VRAI;
    }
    if(c == 'f') {
        t->this.boolean = FAUX;
    }
    return t;
}

object make_number( num nbre ) {

    object t = make_object( SFS_NUMBER );

    if(t) {
        t->this.number = nbre;
    }
    return t;
}

object make_string( string str ) {

    object t = make_object( SFS_STRING );

    if(t!=NULL) {
        if(strcpy(t->this.string,str)==NULL) {
            return NULL;
        }
    }
    return t;
}

object make_symbol( string symb ) {

    object t = make_object( SFS_SYMBOL );

    if(t) {
        if(strcpy(t->this.symbol,symb)==NULL) {
            return NULL;
        }
    }
    return t;
}

object make_character( char c ) {

    object t = make_object( SFS_CHARACTER );

    if(t) {
        t->this.character = c;
    }

    return t;
}

object make_pair( void ) {

    object t = make_object( SFS_PAIR );

    if(((t->this.pair).car = sfs_malloc(sizeof(*((t->this.pair).car)))) == NULL
            ||((t->this.pair).cdr = sfs_malloc(sizeof(*((t->this.pair).cdr)))) == NULL) t = NULL ;

    return t;
}








