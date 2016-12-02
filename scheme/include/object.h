
/**
 * @file object.h
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 17:49:46 2012
 * @brief Object definition for SFS.
 *
 * Object definition for SFS.
 */

#ifndef _OBJECT_H_
#define _OBJECT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "number.h"

typedef struct object_t {

    uint type;

    union {

        num              number;
        char             character;
        string           string;
        string           symbol;

        struct pair_t {
            struct object_t *car;
            struct object_t *cdr;
        }                pair;

        struct object_t *special;
        struct object_t *nil; /*nil <--> empty_list*/
        struct object_t *boolean;
        struct object_t ** tab;
		struct { struct object_t * (*function)(struct object_t *);} primitive; /*function est un pointeur sur fonction qui prend en paramètre un argument de type object et qui retourne un objet de type object*/
		struct {struct object_t *parms;
				struct object_t *body;
				struct object_t *envt; } compound;
			
    } this;

} *object;


object make_object( uint type );
object make_nil( void );
object make_bool( void );
object make_number( num nbre );
object make_character( char c );
object make_pair( void );
object make_boolean( char c);
object make_symbol( string symb );
object make_string( string str );
object make_env(void);
object make_primitive( object* myfunction );
object make_lambda(object parms, object body, object env);

#define SFS_NUMBER       0x00
#define SFS_CHARACTER    0x01
#define SFS_STRING       0x02
#define SFS_PAIR         0x03
#define SFS_NIL          0x04
#define SFS_BOOLEAN      0x05
#define SFS_SYMBOL       0x06
#define SFS_PRIMITIVE    0x07
#define SFS_COMPOUND	 0x08
#define SFS_TAB          0x20

extern object nil;
extern object VRAI;
extern object FAUX;
extern object TopLevel;
extern object STACK;
#ifdef __cplusplus
}
#endif

#endif /* _OBJECT_H_ */
