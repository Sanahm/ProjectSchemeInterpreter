
/**
 * @file primitve.h
 * @author SANA Mohamed, Emile Bertrand <Mohamed.Sana@phelma.grenoble-inp.fr>>
 * @date Fri Oct 29 00:04:46 2016
 * @brief Primitive definition for SFS.
 *
 * Primitive definition for SFS.
 */

#ifndef _PRIMITIVE_H_
#define _PRIMITIVE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "object.h"

object plus_t( object list );
object minus_t( object list );
object mult_t( object list );
object division_t( object list);
object quotient_t( object list );
object remainder_t( object list );
object inf_t( object list);
object infe_t( object list);
object sup_t( object list);
object supe_t( object list);
object ctoi_t( object list );
object itoc_t( object list );
object symbtostr_t( object list );
object strtosymb_t( object list );
object strtonum_t( object list );
object numtostr_t( object list );
object eqv_t( object list );
object isboolean_t( object  list);
object isinteger_t( object list);
object isreal_t(object list);
object isnull_t(object list);
object issymbol_t(object list);
object ischar_t(object list);
object isstring_t(object list);
object ispair_t(object list);

#endif

