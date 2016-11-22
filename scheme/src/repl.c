
/**
 * @file repl.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 18:13:02 2012
 * @brief Main REPL for SFS.
 *
 * Main REPL for SFS.
 */



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <math.h>


#include "object.h"
#include "read.h"
#include "eval.h"
#include "print.h"
#include "env.h"
#include "primitive.h"
# define M_PI		3.14159265358979323846	/* pi */
/* mode d'interaction avec l'interpreteur (exemple)*/
typedef enum {INTERACTIF,SCRIPT} inter_mode;


void usage_error( char *command ) {

    fprintf( stderr, "Usage: %s [file.scm]\n   If no file is given, executes in Shell mode.\n", command );
}


object nil;
object VRAI;
object FAUX;
object environment;
object STACK;

void init_interpreter ( void ) {
	num pi;
	pi.numtype = NUM_REAL; pi.this.real = M_PI;
    nil      = make_nil();
    VRAI     = make_bool();
    FAUX     = make_bool();
	STACK    = nil;
    environment = make_env();
    /*definition du top level*/
    add_symbol_to_env( environment,make_symbol("quote"),make_symbol("quote") );
    add_symbol_to_env( environment,make_symbol("define"),make_symbol("define") );
    add_symbol_to_env( environment,make_symbol("set!"),make_symbol("set!") );
    add_symbol_to_env( environment,make_symbol("begin"),make_symbol("begin") );
    add_symbol_to_env( environment,make_symbol("if"),make_symbol("if") );
    add_symbol_to_env( environment,make_symbol("and"),make_symbol("and") );
    add_symbol_to_env( environment,make_symbol("or"),make_symbol("or") );
    add_symbol_to_env( environment,make_symbol("+inf"),make_symbol("+inf") );
    add_symbol_to_env( environment,make_symbol("-inf"),make_symbol("-inf") );
    add_symbol_to_env( environment,make_symbol("pi"),make_number(pi) );
    add_symbol_to_env( environment,make_symbol("+"), make_primitive(plus_t) );
    add_symbol_to_env( environment,make_symbol("-"), make_primitive(minus_t) );
    add_symbol_to_env( environment,make_symbol("*"), make_primitive(mult_t) );
    add_symbol_to_env( environment,make_symbol("/"), make_primitive(division_t) );
    add_symbol_to_env( environment,make_symbol("quotient"), make_primitive(quotient_t) );
    add_symbol_to_env( environment,make_symbol("remainder"), make_primitive(remainder_t) );
    /* calcul trigono et hyperbol et fonctions diverses*/
    add_symbol_to_env( environment,make_symbol("cos"), make_primitive(cos_t) );
    add_symbol_to_env( environment,make_symbol("sin"), make_primitive(sin_t) );
    add_symbol_to_env( environment,make_symbol("tan"), make_primitive(tan_t) );
    add_symbol_to_env( environment,make_symbol("cosh"), make_primitive(cosh_t) );
    add_symbol_to_env( environment,make_symbol("sinh"), make_primitive(sinh_t) );
    add_symbol_to_env( environment,make_symbol("tanh"), make_primitive(tanh_t) );
    add_symbol_to_env( environment,make_symbol("acos"), make_primitive(acos_t) );
    add_symbol_to_env( environment,make_symbol("asin"), make_primitive(asin_t) );
    add_symbol_to_env( environment,make_symbol("atan"), make_primitive(atan_t) );
    add_symbol_to_env( environment,make_symbol("ceiling"), make_primitive(ceiling_t) ); /*entier le plus proche par les valeurs supérieures*/
    add_symbol_to_env( environment,make_symbol("floor"), make_primitive(floor_t) ); /*entier le plus proche par les valeurs inférieures*/
    add_symbol_to_env( environment,make_symbol("exp"), make_primitive(exp_t) );
    add_symbol_to_env( environment,make_symbol("log"), make_primitive(log_t) );
    add_symbol_to_env( environment,make_symbol("log10"), make_primitive(log10_t) );
    add_symbol_to_env( environment,make_symbol("sqrt"), make_primitive(sqrt_t) );
    add_symbol_to_env( environment,make_symbol("round"), make_primitive(round_t) );
    add_symbol_to_env( environment,make_symbol("abs"), make_primitive(abs_t) );
    add_symbol_to_env( environment,make_symbol("gcd"), make_primitive(pgcd_t) );
    add_symbol_to_env( environment,make_symbol("lcm"), make_primitive(ppcm_t) );
    
    
    add_symbol_to_env( environment,make_symbol("<"), make_primitive(inf_t) );
    add_symbol_to_env( environment,make_symbol("<="), make_primitive(infe_t) );
    add_symbol_to_env( environment,make_symbol(">"), make_primitive(sup_t) );
    add_symbol_to_env( environment,make_symbol(">="), make_primitive(supe_t) );
    add_symbol_to_env( environment,make_symbol("char->integer"), make_primitive(ctoi_t) );
    add_symbol_to_env( environment,make_symbol("integer->char"), make_primitive(itoc_t) );
    add_symbol_to_env( environment,make_symbol("symbol->string"), make_primitive(symbtostr_t) );
    add_symbol_to_env( environment,make_symbol("string->symbol"), make_primitive(strtosymb_t) );
    add_symbol_to_env( environment,make_symbol("string->number"), make_primitive(strtonum_t) );
    add_symbol_to_env( environment,make_symbol("number->string"), make_primitive(numtostr_t) );
    add_symbol_to_env( environment,make_symbol("eqv?"), make_primitive(eqv_t) );
    add_symbol_to_env( environment,make_symbol("eq?"), make_primitive(eq_t) );
    add_symbol_to_env( environment,make_symbol("equal?"), make_primitive(equal_t) );
    add_symbol_to_env( environment,make_symbol("boolean?"), make_primitive(isboolean_t) );
    add_symbol_to_env( environment,make_symbol("integer?"), make_primitive(isinteger_t) );
    add_symbol_to_env( environment,make_symbol("real?"), make_primitive(isreal_t) );
    add_symbol_to_env( environment,make_symbol("null?"), make_primitive(isnull_t) );
    add_symbol_to_env( environment,make_symbol("symbol?"), make_primitive(issymbol_t) );
    add_symbol_to_env( environment,make_symbol("char?"), make_primitive(ischar_t) );
    add_symbol_to_env( environment,make_symbol("string?"), make_primitive(isstring_t) );
    add_symbol_to_env( environment,make_symbol("pair?"), make_primitive(ispair_t) );
    add_symbol_to_env( environment,make_symbol("cons"), make_primitive(cons_t) );
    add_symbol_to_env( environment,make_symbol("car"), make_primitive(car_t) );
    add_symbol_to_env( environment,make_symbol("cdr"), make_primitive(cdr_t) );
    add_symbol_to_env( environment,make_symbol("set-car!"), make_primitive(set_car_t) );
    add_symbol_to_env( environment,make_symbol("set-cdr!"), make_primitive(set_cdr_t) );
    add_symbol_to_env( environment,make_symbol("list"), make_primitive(list_t) );
    add_symbol_to_env( environment,make_symbol("list?"), make_primitive(islist_t) );
    add_symbol_to_env( environment,make_symbol("eval"), make_primitive(eval_t) );
    add_symbol_to_env( environment,make_symbol("interaction-environment"), make_primitive(interaction_env_t) );



    /*toutes ces formes doivent être disponible au lancement de scheme, dans l'interpreteur*/
}

int main ( int argc, char *argv[] ) {

    char     input[BIGSTRING];
    uint     here = 0;
    object   output = NULL;
    object   sexpr = NULL;
    inter_mode mode;
    FILE *   fp = NULL; /* le flux dans lequel les commande seront lues : stdin (mode shell) ou un fichier */

    /* exemples d'utilisation des macros du fichier notify.h */
    /* WARNING_MSG : sera toujours affiche */
    WARNING_MSG("Un message WARNING_MSG !");

    /* macro INFO_MSG : uniquement si compil avec -DVERBOSE. Cf Makefile*/
    INFO_MSG("Un message INFO_MSG : Debut du programme %s", argv[0]);

    /* macro DEBUG_MSG : uniquement si compil avec -DDEBUG (ie : compil avec make debug). Cf Makefile */
    DEBUG_MSG("Un message DEBUG_MSG !");

    /* La ligne suivante provoquerait l'affichage du message
       puis la sortie du programme avec un code erreur non nul (EXIT_FAILURE) */
    /* ERROR_MSG("Erreur. Arret du programme"); */

    if ( argc > 2 ) {
        usage_error( argv[0] );
        exit( EXIT_FAILURE );
    }
    if(argc == 2 && strcmp(argv[1], "-h") == 0) {
        usage_error( argv[0] );
        exit( EXIT_SUCCESS );
    }

    init_interpreter();
	
    /*par defaut : mode shell interactif */
    fp = stdin;
    mode = INTERACTIF;
    if(argc == 2) {
        /* mode fichier de commandes */
        fp = fopen( argv[1], "r" );
        if ( fp == NULL ) {
            perror( "fopen" );
            exit( EXIT_FAILURE );
        }
        mode = SCRIPT;
    }


    while ( 1 ) {
        input[0]='\0';
        here = 0;
        output = NULL;
        sexpr = NULL;
        uint Sexpr_err;

        Sexpr_err = sfs_get_sexpr( input, fp );

        if ( S_OK != Sexpr_err) {
            /* si fichier alors on sort*/
            if (mode == SCRIPT) {
                fclose( fp );
                if (Sexpr_err==S_END) {
                    /* Cas fin de fichier script */
                    exit(EXIT_SUCCESS);
                }
                /* Cas S-Expression mal formee dans le fichier script */
                ERROR_MSG("Malformed S-expression --- Aborts");
            }
            /*sinon on rend la main à l'utilisateur*/
            continue;
        }

        if ( 0 == strlen( input ) ) {
            continue;
        }

        /* Pour le step 0 on se contente d'afficher */
        /* la S-Expression lue */
        /* puis d'en lire une autre */
        /* METTRE EN COMMENTAIRE LES DEUX LIGNES SUIVANTES */
        /* POUR PASSER A L'INCREMENT 1 */
        /*printf("%s\n", input );*/
        /*continue;*/

        here  = 0;
        sexpr = sfs_read( input, &here );

        if ( NULL == sexpr ) {
            /* si fichier alors on sort*/
            if (mode == SCRIPT) {
                fclose( fp );
                /*macro ERROR_MSG : message d'erreur puis fin de programme ! */
                ERROR_MSG("Invalid S-expression --- Aborts");
            }
            WARNING_MSG("Invalid S-expression --- Aborts");/*c'est moi qui ai ajoute ca*/
            /*sinon on rend la main à l'utilisateur*/
            continue ;
        }
		init_stack();
        output = sfs_eval( sexpr );
        if( NULL == output) {
            /* si fichier alors on sort */
            if (mode == SCRIPT) {
                fclose( fp );
                /*macro ERROR_MSG : message d'erreur puis fin de programme ! */
                ERROR_MSG("Error while evaluating input --- Aborts");
            }
            /*REPORT_MSG("Invalid S-expression --- Aborts.\n");/*c'est moi qui ai ajoute ca*/
            /*sinon on rend la main à l'utilisateur*/
            continue ;
        }

        printf( "==> " );
        /*sfs_print(stdout,sexpr);*/
        sfs_print(stdout, output );
        printf( "\n" );
    }

    if (mode == SCRIPT) {
        fclose( fp );
    }
    exit( EXIT_SUCCESS );
}
