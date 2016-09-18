
/**
 * @file read.h
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 18:30:11 2012
 * @brief Read routine for SFS.
 *
 * Read routine for SFS.
 */

#ifndef _READ_H_
#define _READ_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#include "object.h"

enum {S_OK, S_KO, S_END};
int isspecial(char c);
uint   sfs_get_sexpr( string input, FILE *fp );
/*here permet de se positionner au niveau de la S_expr cad montre à quel niveau en est la lecture*/
object sfs_read( char *input, uint *here );
object sfs_read_atom( char *input, uint *here );
object sfs_read_pair( char *stream, uint *i );


#ifdef __cplusplus
}
#endif

#endif /* _READ_H_ */
