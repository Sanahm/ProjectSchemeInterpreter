
/**
 * @file eval.h
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:10:38 2012
 * @brief Evaluation stuff for SFS.
 *
 * Evaluation stuff for SFS.
 */

#ifndef _EVAL_H_
#define _EVAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "number.h"
#include "object.h"

int isand(char*str);
int isor(char*str);
int isif(char*str);
int isquote(char*str);
int isdefine(char*str);
int isset(char*str);
int isplus(char*str);
int ismoins(char*str);
int ismult(char*str);
int isdiv(char*str);
int isinf(char*str);
int isinfe(char*str);
int issup(char*str);
int issupe(char*str);
object car(object o);
object cdr(object o);
object operation( object obj1,object obj2, char op );
object sfs_eval( object o);

#ifdef __cplusplus
}
#endif

#endif /* _EVAL_H_ */
