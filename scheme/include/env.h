/**
 * @file env.h
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Oct 11 15:04:46 2016
 * @brief fonction de gestion de l'environnement.
 *
 * fonction de gestion de l'environnement.
 */


#ifndef _ENV_H_
#define _ENV_H_

#include "object.h"

object research_symbol_in_obj( object o, object symb );/*recherche symbole dans une case de la table de hachage*/
object is_symbol_in_env( object env, object symb );
object is_symbol_in_all_env( object env, object symb );
object get_symbol_value( object env, object symb);
int hachage(char*mot,int dim_tab_hach);
object add_symbol_to_env( object env, object symb, object value );
object set_symbol_value_in_env( object env, object symb, object value);
void add_new_env(object* env);
void add_object_to_list(object* list,object obj);
void inverse_list(object*list);
void print_stack(object stack);
int sizeof_stack(object stack);
void init_stack(void);

#endif
