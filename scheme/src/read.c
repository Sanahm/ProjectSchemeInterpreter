
/**
 * @file read.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 18:31:05 2012
 * @brief Read routine for SFS.
 *
 * Read routine for SFS.
 */
#include <limits.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "read.h"

int isspecial(char c) {
    return (c==':'|| (c>='<' && c <='@')||(c>= '-' && c<='/')|| c=='*'|| c=='+'|| c=='&'|| c=='%'||c=='$'|| c=='!'|| c=='~'|| c=='^'|| c=='_');
}

void flip( uint *i ) {

    if ( *i == FALSE ) {
        *i = TRUE;
    }
    else {
        *i = FALSE;
    }
}

/*
 * @fn char* first_usefull_char(char* line)
 *
 * @brief retourne un pointeur sur le premier caractere utile dans line
 * ou NULL si line ne contient que des espaces et des commentaires
 */
char* first_usefull_char(char* line) {

    int i=0;
    if (line == NULL) {
        return NULL;
    }
    i = 0;
    /* on saute les espaces */
    while(line[i] != '\0' && isspace(line[i])) {
        i++;
    }
    /* si fin de ligne => ligne inutile */
    if(line[i] == '\0') {
        return NULL;
    }
    /* si premier caractere non espace est ';' => ligne inutile */
    if(line[i] == ';') {
        return NULL;
    }
    return line + i; /* ligne utile */
}

/**
 * @fn uint  sfs_get_sexpr( char *input, FILE *fp )
 *
 * @brief extrait la prochaine S-Expression dans le flux fp et la stocke dans input
 * (meme si elle est repartie sur plusieurs lignes)
 * @param fp (FILE *) flux d'entree (ouvert en ecriture, mode texte)
 * @param input (char *) chaine allouee de taille BIGSTRING, dans laquelle la S-Expression sera stockée
 *
 * @return S_OK si une S-Expression apparemment valide a ete trouvee
 * @return S_KO si on n'a pas trouve de S-Expression valide
 * @return S_END si fin de fichier atteinte sans avoir lu de caractere utile.
 *
 * sfs_get_sexpr commence par lire une ligne dans fp,
 * puis compte le nombre de parentheses ouvrantes et fermantes sur la ligne.
 * Les parentheses dans des chaines et les caracteres Scheme #\( et #\)
 * ne sont pas comptes.
 *
 * Si le compte devient zéro et que
 *        - la ligne est fini, la fonction retourne S_OK
 * 				- la ligne n'est pas fini la fonction retourne S_KO
 *
 * S'il y a plus de parentheses fermantes qu'ouvrantes,
 * la fonction retourne S_KO.
 * Les commentaires et espaces qui figurent a la fin de chaque ligne
 * sont remplacés par un espace.
 * Les espaces qui figurent a la fin de la S-Expression (y compris '\n')
 * sont supprimés.
 *
 * Attention : cette fonction refuse les S-Expression multiple sur une seule ligne. Ainsi :
 *    a b c
 *    (qqchose) (autrechose)
 *    (qqchose) 78
 * seront considereees comme des erreurs
 * et la fonction retournera S_KO
 *
 * @pre fp doit etre prealablement ouvert en lecture
 * @pre input doit etre prealablement alloue en memoire, de taille BIGSTRING
 */

typedef enum {
    NOTHING,        /* rien n'a ete trouve encore.. */
    STRING_ATOME,   /* la premiere trouvee dans la ligne semble etre un atome */
    BASIC_ATOME,    /* la premiere trouvee dans la ligne semble etre d'une chaine */
    S_EXPR_PARENTHESIS, /* la premiere trouvee dans la ligne semble etre une expression parenthesee */
    FINISHED        /* on a trouve une S-Expr bien formee */
} EXPRESSION_TYPE_T;

uint  sfs_get_sexpr( char *input, FILE *fp ) {
    int       parlevel = 0 , gui = 0;
    uint      in_string = FALSE;
    uint      s = 0;
    char      k[BIGSTRING];
    char      *ret = NULL;
    char      *chunk = NULL;
    uint      i = 0;
    string    sfs_prompt;

    EXPRESSION_TYPE_T typeOfExpressionFound = NOTHING;

    parlevel = 0;
    memset( input, '\0', BIGSTRING );

    do {
        ret = NULL;
        chunk = NULL;

        /* si en mode interactif*/
        if ( stdin == fp ) {
            uint nspaces = 2*parlevel;

            init_string( sfs_prompt );

            /* le prompt indique le niveau de parenthese
               et decale la prochaine entrée en fonction
               de ce niveau (un peu à la python)*/
            sprintf( sfs_prompt, "SFS:%u > ", parlevel );

            for ( i= 0; i< nspaces; i++ ) {
                sfs_prompt[strlen(sfs_prompt)] = ' ';
            }

            /* si sur plusieurs lignes, le \n équivaut à un espace*/
            if (nspaces>0) {
                input[strlen(input)+1] = '\0';
                input[strlen(input)] = ' ';
            }

            /*saisie de la prochaine ligne à ajouter dans l'input*/
            chunk = readline( sfs_prompt );
        }
        /*si en mode fichier*/
        else {
            chunk=k;
            memset( chunk, '\0', BIGSTRING );
            ret = fgets( chunk, BIGSTRING, fp );

            if ( NULL == ret ) {
                /* fin de fichier...*/
                if ( parlevel != 0 ) {
                    WARNING_MSG( "Parse error: missing ')'" );
                    return S_KO;
                }
                return S_END;
            }

            if (strlen(chunk) == BIGSTRING-1
                    && chunk[BIGSTRING-1] != '\n'
                    && !feof(fp)) {
                WARNING_MSG( "Too long line for this interpreter!" );
                return S_KO;
            }
        }

        /* si la ligne est inutile
        	=> on va directement à la prochaine iteration */
        if (first_usefull_char(chunk) == NULL) {
            continue;
        }


        s = strlen( chunk );

        if ( s > 0 ) {
            if (strlen(input) + s > BIGSTRING-1 ) {
                WARNING_MSG( "Too long a S-expression for this interpreter!" );
                return S_KO;
            }

            for ( i = 0; i< strlen(chunk); i++ ) {
                /* si la fin de la ligne chunk est inutile,
                   on ajoute un espace dans input et on sort de la boucle*/
                if ( in_string == FALSE && first_usefull_char(chunk + i) == NULL ) {
                    chunk[i]='\0';
                    input[strlen(input)] = ' ';
                    break;
                }


                switch(chunk[i]) {
                case '(':
                    if (in_string == FALSE
                            && ! ( i>1 && chunk[i-1] == '\\' && chunk[i-2] == '#' ) ) {
                        parlevel++;
                        typeOfExpressionFound = S_EXPR_PARENTHESIS;
                    }
                    break;
                case ')':
                    if ( in_string == FALSE
                            && ! ( i>1 && chunk[i-1] == '\\' && chunk[i-2] == '#' ) ) {
                        parlevel--;
                        if (parlevel == 0 ) {
                            typeOfExpressionFound = FINISHED;
                        }
                        if ( parlevel < 0 ) {
                            WARNING_MSG( "Parse error : cannot start with ')'" );
                            return S_KO;
                        }
                    }
                    break;

                case '"':
                    if ( i<2 || chunk[i-1] != '\\') {
                        if ( in_string == FALSE ) {
                            if(typeOfExpressionFound == BASIC_ATOME) {
                                if( chunk[i-1] == '\'' || gui) {
                                    typeOfExpressionFound = STRING_ATOME;
                                    in_string = TRUE;
                                    break;
                                }
                                WARNING_MSG("Parse error: invalid string after atom : '%s'", chunk+i);
                                return S_KO;
                            }
                            in_string = TRUE;
                            if(typeOfExpressionFound != S_EXPR_PARENTHESIS) {
                                typeOfExpressionFound = STRING_ATOME;
                            }
                        }
                        else {
                            in_string = FALSE;
                            if(typeOfExpressionFound == STRING_ATOME) {
                                typeOfExpressionFound = FINISHED;
                            }
                        }
                    }
                    break;
                default:
                    if(in_string == FALSE) {
                        if(chunk[i] == '\'') gui = 1;
                        if(isspace(chunk[i]) && !gui) {
                            if(typeOfExpressionFound == BASIC_ATOME) {
                                typeOfExpressionFound = FINISHED;
                            }
                        } else if(typeOfExpressionFound != S_EXPR_PARENTHESIS) {
                            typeOfExpressionFound = BASIC_ATOME;
                        }
                    }
                    break;
                }


                if(typeOfExpressionFound == FINISHED) {
                    char *first_useful = first_usefull_char(chunk + i + 1);
                    if( first_useful != NULL) {
                        if(*first_useful == ')' ) {
                            WARNING_MSG( "Parse error: too many closing parenthesis')'" );
                        }
                        else {
                            WARNING_MSG("Parse error: invalid trailing chars after S-Expr : '%s'", chunk+i);
                        }
                        return S_KO;
                    }
                }

                /* recopie char par char*/
                input[strlen(input)] = chunk[i];
            }
            if(in_string == TRUE) {
                WARNING_MSG( "Parse error: non terminated string on line %s", chunk );
                return S_KO;
            }
        }


        if ( parlevel > 0 && fp != stdin ) {
            if ( feof( fp ) ) {
                WARNING_MSG( "Parse error: missing ')'" );
                return S_KO;
            }

            if (input[strlen(input)-1] == '\n') input[strlen(input)-1] = ' ';
        }
    } while ( parlevel > 0 );

    /* Suppression des espaces restant a la fin de l'expression, notamment le dernier '\n' */
    while (isspace(input[strlen(input)-1])) input[strlen(input)-1] = '\0';

    if(stdin == fp) {
        add_history( input );
    }
    return S_OK;
}


object sfs_read( char *input, uint *here ) { /*here permet de se positionner au niveau de la S_expr cad montre à quel niveau en est la lecture*/

    while( isspace(input[*here]) && *here < strlen(input)) (*here)++;
    if ( input[*here] == '(' ) {
        (*here)++;
        while( isspace(input[*here]) && *here < strlen(input) ) (*here)++;
        if ( input[(*here)] == ')' ) {
            (*here)++;
            return nil;
        }
        else {
            return sfs_read_pair( input, here );
        }
    }
    else {
        return sfs_read_atom( input, here );
    }
}

object sfs_read_atom( char *input, uint *here ) {

    object atom = NULL;
    string str,strs;
    char*endptr;
    int herec = *here; /*une copie du here*/
    int j = 0,i = 0,h = 0;
    num u;
    /*Est ce une chaine de charactere?*/
    if( input[*here] == '"') {
        (*here)++;
        while( *here < strlen(input) && input[*here] != '"' ) {
            if(input[*here] =='\\' && input[*here+1] =='"') {
                str[i] = '\\';
                str[i+1] = '"';
                *here += 2;
                i += 2;
                continue;
            }
            str[i] = input[*here];
            i++;
            (*here)++;
        }
        if( input[*here] == '"' && ((isspace(input[*here+1]) || input[*here+1]== ')' || input[*here+1]=='(' || *here == strlen(input)-1) || input[*here+1] == '"') ) {
            str[i] = '\0';
            atom = make_string(str);
            (*here)++; /* on passe au caractere suivant avant de retourner*/
            return atom;
        }
        return atom;
    }
    /*Est ce un nombre ou un symbole +/-?*/
    /*etant donne qu'un entier relatif commence par le symb +/- on fait d'une pierre 2 coups
    on commence par tester si on a le symb +/- puis si derriere c'est un entier alors on lit un entier relatif sinon si c'est un espace on lit un symb
    dans les autres cas on retourne une erreur*/
    if( input[*here] =='+' || input[*here] =='-' || input[*here] =='.' || isdigit(input[*here]) ) {
        str[0] = input[*here];
        (*here)++;
        i++;
        if( *here <= strlen(input) && (isspace(input[*here])||input[*here]==')' || input[*here]=='(' || *here == strlen(input)) && !isdigit(input[*here-1]) ) {
            /* ca veut dire qu'on lit un symbole +/-*/
            str[1]='\0';
            atom = make_symbol(str); /*teste si +/- est un symbol ou pas  ;; str[0] = input[*here-1]*/
            return atom;
        }
        /*sinon on prend tous les digits apres le signe*/
        while( *here < strlen(input) && isdigit(input[*here]) ) { /*on prend tous les digits*/
            str[i] = input[*here];
            (*here)++;
            i++;
        }
        /*Est ce un nombre reel a virgule?*/
        if ( str[0] == '.' || input[*here] == '.' || input[*here] == 'e' || input[*here] == 'E' || input[*here] == '#' ) { /*on est en train de lire un float*/
            if(*here < strlen(input) && str[0] != '.' ) { /*voir ça m'a fait souffrir*/
                str[i] = input[*here];
                (*here)++;
                i++;
            }
            while( *here < strlen(input) && (isdigit(input[*here]) || input[*here] == '#' || input[*here] == 'e'|| input[*here] == 'E' || input[*here] == '.')) { /*on prend tous les digits*/
                if( input[*here] == 'e' || input[*here] == 'E' ) j = i;
                if(input[*here] =='.') h = i;
                str[i] = input[*here];
                (*here)++;
                i++;
            }
            str[i] = '\0';
            if(!j) i = strlen(str)-1;
            else i = j-1;
            while(i > 0 && str[i] =='#') { /*"15.2##" => 15.200*/
                str[i] = '0';
                i--;
            }
            if(h) i = h-1;
            while(i > 0 && str[i] =='#') { /*"15##.2" => 1500.200*/
                str[i] = '0';
                i--;
            }

            if( *here >= strlen(input) || isspace(input[*here]) || input[*here]==')'|| input[*here]=='(') {
                u.numtype = NUM_REAL;/*et on lit un reel*/
                u.this.real = strtod(str,&endptr);
                if(!(endptr[0] != '\0' || (u.this.real == 0 && endptr == str))) {
                    atom = make_number(u);
                    return atom;
                }
            }
            *here = herec;
            i=0;
            strcpy(str,""); /*on réinitialise et on laisse continuer*/
            goto read_symbol;
        }
        /*on est en train de lire un rationnel*/
        if ( input[*here] == '/' ) {
            str[i] = '\0';
            (*here)++;
            i = 0;
            while( *here < strlen(input) && isdigit(input[*here]) ) { /*on prend tous les digits*/
                strs[i] = input[*here];
                (*here)++;
                i++;
            }
            if( isspace(input[*here]) || input[*here]==')'|| input[*here]=='(' || *here == strlen(input)) {
                strs[i] = '\0';
                u.numtype = NUM_REAL;/*et on lit un reel*/
                u.this.real = strtod(str,NULL)/strtod(strs,&endptr);
                if(!(endptr[0] != '\0' || (strtod(strs,&endptr) == 0 && endptr == strs))) {
                    atom = make_number(u);
                    return atom;
                }
            }
            *here = herec;
            i=0;
            strcpy(str,""); /*on réinitialise et on laisse continuer*/
            goto read_symbol;
        }
        /*sinon c'est tout simplement un entier*/
        if( isspace(input[*here]) || input[*here]==')'|| input[*here]=='('||*here == strlen(input) || input[*here]=='\"') {
            str[i] = '\0';
            u.numtype = NUM_INTEGER;
            u.this.integer = strtol(str,NULL,10);
            if(u.this.integer == LONG_MAX) atom = make_symbol("+inf");
            else if(u.this.integer == LONG_MIN)  atom=  make_symbol("-inf");
            else atom = make_number(u);
            return atom;
        }
        *here = herec;
        i =0;
        strcpy(str,""); /*on réinitialise et on laisse continuer*/
        goto read_symbol;
    }

    /*lire les symboles:
    un symb peut etre un define, quote, a ,b ,A, fnj, !vf, etc*/
read_symbol:
    if(isalpha(input[*here]) || isspecial(input[*here]) || isdigit(input[*here])) { /* isspecial() définie plus haut, retourne 1 si (! % etc)*/
        str[0] = input[*here];
        (*here)++;
        i++;
        while((isalpha(input[*here]) || isdigit(input[*here]) || isspecial(input[*here])) && *here < strlen(input)) { /* ca c'est un symbol :$irud, %jdf*/
            str[i] = input[*here];
            (*here)++;
            i++;
        }
        if(isspace(input[*here]) || input[*here]==')' || input[*here]=='(' || *here == strlen(input)) {
            str[i] = '\0';
            atom = make_symbol(str);
            return atom;
        }
        REPORT_MSG(";ERROR: unsupported: strange character detected '%c'\n",input[*here]);
        return atom;

    }

    /*lire les booleans + newline et space et character*/
    if(input[*here] == '#') {
        /*2 cas se presentent*/
        (*here)++;
        if(input[*here] == '\\') {
            (*here)++;
            if( isspace(input[*here+1]) || input[*here+1] == ')' || input[*here]=='(' || *here == strlen(input)-1 ) {
                atom = make_character(input[*here]);
                (*here)++;
                return atom;
            }
            /*soit on lit newline ou space*/
            while( isalpha(input[*here]) && *here < strlen(input) ) { /*on recupère la chaine*/
                str[i] = input[*here];
                (*here)++;
                i++;
            }
            if( isspace(input[*here]) || input[*here] == ')' || input[*here]=='(' || *here == strlen(input)) {
                str[i] = '\0';
                if(!strcmp(str,"newline")) atom = make_character('\n'); /*allez cest bon */
                if(!strcmp(str,"nl")) atom = make_character('\n'); /*on fait les 2 on est fort*/
                if(!strcmp(str,"space")) atom = make_character(' ');
                return atom;
            }
            return atom;
        }
        if( (input[*here] == 't' || input[*here] == 'f') && (isspace(input[*here+1]) || input[*here+1]==')' || input[*here]=='(' || *here == strlen(input)-1) ) {
            atom = make_boolean(input[*here]);
            (*here)++; /* on passe au caractere suivant avant de retourner*/
            return atom;
        }
    }

    if(input[*here] == '\'') {
        int cpt = 0, par=0, gui = 1;
        string strs = "( quote ";
        uint j = 0;
        (*here)++;
        i=0;

        cpt=1;
        while( isspace(input[*here]) && *here < strlen(input)) {
            (*here)++;
            j++;
        }
        while(*here < strlen(input) && cpt!=0 ) {
            if( input[*here] == '\"' ) {
                if (input[*here-j-1] == '\'') gui = 1;
                if (input[*here-1] != '\\') gui--;
            }
            if( input[*here]=='(' && input[*here-j-1]=='\'' && par==0) {
                par=1;
                cpt--;
            }
            if(par && input[*here-1] !='\\') {
                if(input[*here]==')') cpt--;
                if(input[*here]=='(') cpt++;

            }
            else {
                if(input[*here]==')' || input[*here]=='(' || (isspace(input[*here]) && gui == 1)) {

                    break;
                }
            }
            str[i] = input[*here];
            (*here)++;
            if(input[*here-1] =='\'') {
                while( isspace(input[*here]) && *here < strlen(input)) {
                    (*here)++;
                    j++;
                }
            }
            i++;
        }

        str[i] = ')';
        str[i+1] = '\0';
        strcat(strs,str);
        j = 0;
        return sfs_read(strs, &j);;
    }

    return atom;
}

object sfs_read_pair( char *stream, uint *i ) {

    object pr = make_pair();
    if(stream[*i] < 0) return NULL;
    while(isspace(stream[*i]) && *i < strlen(stream)) (*i)++; /*pour gerer les espaces*/
    pr->this.pair.car = sfs_read(stream,i);
    if( pr->this.pair.car == NULL ) return NULL;
    while(isspace(stream[*i]) && *i < strlen(stream)) (*i)++; /*pour gerer les espaces*/
    if( stream[*i] != ')') pr->this.pair.cdr = sfs_read_pair(stream,i);
    else {
        pr->this.pair.cdr = nil;
        (*i)++;
    }
    if( pr->this.pair.cdr == NULL) return NULL;
    return pr;
}

