
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
object interaction_env_t( object list );
/*trigo*/
object trigo_t( object list, double (*pfunct)(double),char*name );
object cos_t( object list );
object sin_t( object list );
object tan_t( object list );
object cosh_t( object list );
object sinh_t( object list );
object tanh_t( object list );
object acos_t( object list );
object asin_t( object list );
object atan_t( object list );
object exp_t( object list );
object log_t( object list );
object log10_t( object list );
object ceiling_t( object list );
object floor_t( object list );
object abs_t( object list );
object sqrt_t( object list );
object round_t( object list );
int pgcd( long int a, long int b);
int ppcm( long int a, long int b);
object pgcdpcm_t( object list,int u, int (*pfunct)(int,int),char*name );
object pgcd_t( object list );
object ppcm_t(object list);




/************************/
/*comparaison*/
object cmp_t( object list, char*op);
object inf_t( object list);
object infe_t( object list);
object sup_t( object list);
object supe_t( object list);
/************************/
/*conversion de type*/
object ctoi_t( object list );
object itoc_t( object list );
object symbtostr_t( object list );
object strtosymb_t( object list );
object strtonum_t( object list );
object numtostr_t( object list );
/***********************/
object eqv_t( object list );
object eq_t( object list );
object equal_t( object list );
object isboolean_t( object  list);
object isinteger_t( object list);
object isreal_t(object list);
object isnull_t(object list);
object issymbol_t(object list);
object ischar_t(object list);
object isstring_t(object list);
object make_string_t(object list);
/*object expt_t( object list );*/
object ispair_t(object list);
object cons_t( object list);
object car_t( object list);
object cdr_t( object list);
object set_car_t( object list);
object set_cdr_t( object list);
object list_t( object list);
object islist_t( object list );
object eval_t( object list );
object not_t(object list);
object reverse_t(object list);
object length_t(object list);
object append_t(object list);
object map_t( object list);
object procedure_t( object list );
object apply_t( object list);
#endif

