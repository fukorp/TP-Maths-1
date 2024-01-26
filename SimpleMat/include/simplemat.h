
/*
    simplemat une librairie de calculs matriciels à visée pédagogique
    Copyright 2021 Vincent Ledda
    Contact : vincent.ledda@centralelille.fr

    This file is part of simplemat

    simplemat is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    simplemat is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with simplemat; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

#include "sm_util.h"
#define INVALID_ROWS "Le nombre de ligne ne peut être nul"
#define INVALID_COLS "Le nombre de colonne ne peut être nul"
#define INVALID_DIM "La dimension ne peut être nulle"
#define INVALID_SYS_DIM "Les matrices doivent avoir le même nombre de lignes"
#define INVALID_DIM_ADD "Les dimensions des deux matrices doivent être identiques pour en faire la somme"
#define INVALID_DIM_MUL "Le nombre de colonnes de la première matrice doit être égal au nombre de ligne de la seconde pour effectuer le produit de deux matrices"
#define INVALID_LIGNE "L'indice de ligne doit être strictement positif et inférieur à la taille de la matrice"
#define INVALID_COLONNE "L'indice  colonne doit être strictement positif et inférieur à la taille de la matrice"

#define INVALID_INVERSION "Pour les matrices d'interversion  ou de type L(n,i,j,a) les indices doivent être différents"
#define INVALID_CARREE "La matrice doit être carrée"
#define INVALID_INV "La matrice n'est pas inversible"
#define INVALID_DIM_MUL_D "La matrice de droite n'est pas carrée"
#define INVALID_INDEX "indexes invalides"
#define INVALID_DIM_MUL_G "La matrice de gauche n'est pas carrée"
/* Structures */



typedef struct simplemat_s {
  unsigned int num_rows;
  unsigned int num_cols;
  double **data;
} s_mat;


/* Création des matrices */

/* constructeur
Allocation de la mémoire d'une matrice
*/
s_mat *s_mat_new( unsigned int num_row, unsigned int num_cols);

/** Crée une matrice carrée */

s_mat *s_mat_carree( unsigned int n);
/** Copie une matrice */

s_mat *s_mat_copie(s_mat *matrice);


/** Crée une matrice identité */
s_mat *s_mat_id(unsigned int n);


/** Matrice coefficients donnés */
s_mat *s_mat_coef(unsigned int n,unsigned int m, double  valeurs[], unsigned int nbVal);


/** Matrice aléatoires */
s_mat *mat_alea_entier(unsigned int n,unsigned int m, int min , int max);
s_mat *mat_alea(unsigned int n,unsigned int m, int min , int max);


/* opérations élémentaires sur les lignes */

s_mat *s_mat_e(unsigned int n, unsigned int i, unsigned j);
s_mat *s_mat_h(unsigned int n, unsigned int i, double a);
s_mat *s_mat_l(unsigned int n, unsigned int i ,unsigned int j, double a);



/** Structure d'espace vectoriel

       */

s_mat *mat_add(s_mat* A , s_mat* B);
s_mat *mat_minus(s_mat* A , s_mat* B);
s_mat *mat_mul_ext(s_mat* matrice , double scalaire);
s_mat *mat_oppose(s_mat* matrice);


/** Structure d'algèbre */
s_mat *mat_mul(s_mat* A , s_mat* B);

void mat_mul_droite(s_mat* A , s_mat* B);

void mat_mul_gauche(s_mat* A , s_mat* B);



/* Libère la mémoire occupée par une matrice */
void s_mat_free(s_mat *mat);

/* Misc */

double trace(s_mat* A);
s_mat *transpose(s_mat* A);
void echange_deux_lignes(s_mat* A, unsigned int i, unsigned int j);



/* Question */

_Bool est_carree(s_mat* matrice);
_Bool est_egal(s_mat* A,s_mat* B);
_Bool est_id(s_mat* A);
_Bool est_nulle(s_mat* A);


/* Affichage */

void afficher_mat(s_mat *matrix);
/** Échange deux lignes
 */
