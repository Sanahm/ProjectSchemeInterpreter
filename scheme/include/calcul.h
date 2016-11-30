
/**
 * @file calcul.h
 * @author SANA Mohamed <Mohamed.Sana@phelma.grenoble-inp.fr>
 * @date Fri Oct 30 00:20 2016
 * @brief Evaluation stuff for SFS.
 *
 * Evaluation stuff for SFS.
 */

#ifndef _CALCUL_H_
#define _CALCUL_H_

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
int islet(char*str);
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
object operation( object obj1,object obj2, char*op );

#ifdef __cplusplus
}
#endif

#endif








