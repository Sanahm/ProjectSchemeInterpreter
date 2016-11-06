
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

#endif

