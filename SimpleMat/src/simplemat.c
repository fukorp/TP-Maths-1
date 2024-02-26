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

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <time.h>

#include <stdbool.h>
#include "../include/sm_util.h"


#define ORG_OUTPUT 1

#define INVALID_ROWS "Le nombre de ligne ne peut être nul"
#define INVALID_COLS "Le nombre de colonne ne peut être nul"
#define INVALID_DIM "La dimension ne peut être nulle"
#define INVALID_DIM_ADD "Les dimensions des deux matrices doivent être identiques pour en faire la somme"
#define INVALID_DIM_MUL "Le nombre de colonnes de la première matrice doit être égal au nombre de ligne de la seconde pour effectuer le produit de deux matrices"
#define INVALID_DIM_MUL_D "La matrice de droite n'est pas carrée"
#define INVALID_DIM_MUL_G "La matrice de gauche n'est pas carrée"
#define INVALID_LIGNE "L'indice de ligne doit être strictement positif et inférieur à la taille de la matrice"
#define INVALID_COLONNE "L'indice  colonne doit être strictement positif et inférieur à la taille de la matrice"
#define INVALID_INVERSION "Pour les matrices d'interversion  ou de type L(n,i,j,a) les indices doivent être différents"
#define INVALID_CARREE "La matrice doit être carrée"



typedef struct simplemat_s {
  unsigned int num_rows;
  unsigned int num_cols;
  double **data;
} s_mat;


/** Constructeurs
 *    Allocation de la mémoire d'une matrice
*/
s_mat *s_mat_new(unsigned int num_rows, unsigned int num_cols) {
  if (num_rows == 0) {
    LOG_ERROR(INVALID_ROWS);
    exit(EXIT_FAILURE);
  }
  if (num_cols == 0) {
    LOG_ERROR(INVALID_COLS);
    exit(EXIT_FAILURE);

  }

  /// allocation d'un pointeur vers un s_mat
  s_mat *m = calloc(1, sizeof(*m));
  ALLOC_CHECK(m);

  m->num_rows = num_rows;
  m->num_cols = num_cols;

  /// Allocation d'un tableau de pointeurs
  m->data = calloc(m->num_rows, sizeof(*m->data));
  ALLOC_CHECK(m->data);

  /// Allocation de n*m double

  double *lignes = calloc(m->num_rows*m->num_cols,sizeof(double));
  ALLOC_CHECK(lignes);

  for(unsigned int i = 0; i < m->num_rows; ++i) {
    m->data[i] = &lignes[i*m->num_cols];
  }
  return m;
}


/**
 * Copie d'une matrice
 *
 *
 */
s_mat *s_mat_copie(s_mat *matrice)
{
  s_mat*  copie;
  copie=s_mat_new(matrice->num_rows, matrice->num_cols);
  for(unsigned int i=0;i<matrice->num_rows;i++)
    {
        for(unsigned int j=0;j<matrice->num_cols;j++)
          {
            copie->data[i][j]=matrice->data[i][j];

          }

    }
  return copie;

}


/**  Matrice carrée */

s_mat *s_mat_carree(unsigned int n) {
  if (n == 0) {
    LOG_ERROR(INVALID_DIM);
    exit(EXIT_FAILURE);

  }


  return s_mat_new(n,n);


}




/** Matrice identité */
s_mat *s_mat_id(unsigned int n) {
  if (n == 0) {
    LOG_ERROR(INVALID_DIM);
    exit(EXIT_FAILURE);
  }
  s_mat* m;
  m=s_mat_new(n,n);
  for(unsigned int i=0;i<n;i++)
    {
      m->data[i][i]=1;

    }

  return m;


}




/* Matrices d'opérations élémentaires sur les lignes
*/


/** Homothétie */
s_mat *s_mat_h(unsigned int n, unsigned int i, double a)
{
    if( i > n )
      {
        LOG_ERROR(INVALID_LIGNE);

        exit(EXIT_FAILURE);
      }

    s_mat* m;
    m=s_mat_id(n);
    m->data[i-1][i-1]=a;
    return m;

}


/** Inversion de deux lignes */
s_mat *s_mat_e(unsigned int n, unsigned int i, unsigned j)
{
    if( i > n || j> n)
      {
        LOG_ERROR(INVALID_LIGNE);

            exit(EXIT_FAILURE);
      }

    if( i == j)
      {
          LOG_ERROR(INVALID_INVERSION);
              exit(EXIT_FAILURE);


      }
    s_mat* m;
    m=s_mat_id(n);
    m->data[i-1][i-1]=0;
    m->data[j-1][j-1]=0;
    m->data[j-1][i-1]=1;
    m->data[i-1][j-1]=1;


    return m;


}


s_mat *s_mat_l(unsigned int n, unsigned int i ,unsigned int j, double a)
{


   if( i > n || i<=0)
      {
        LOG_ERROR(INVALID_LIGNE);
      exit(EXIT_FAILURE);
      }
 if( j > n || j<=0)
      {
        LOG_ERROR(INVALID_COLONNE);
      exit(EXIT_FAILURE);
      }

    if( i == j )
      {
          LOG_ERROR(INVALID_INVERSION);
                exit(EXIT_FAILURE);


      }

    s_mat* m;
    m=s_mat_id(n);
    m->data[i-1][j-1]=a;
    return m;

}


/** Matrice coefficients donnés */
s_mat *s_mat_coef(unsigned int n,unsigned int m, double  valeurs[], unsigned int nbVal)
{
  unsigned int i=0;
  unsigned int q=0;
  unsigned int r=0;
  s_mat* matrice;
  nbVal=nbVal>n*m?n*m:nbVal;

  matrice=s_mat_new(n,m);
  while(i<nbVal)
    {
      // index de la ligne //
      q=i/m;
      //index de la colonne //
      r=i%m;

      matrice->data[q][r]=valeurs[i];
      i++;

    }
  return matrice;

}



/* Matrice aléatoires */


   /**
    * Matrice aléatoires d'entier
     */
s_mat *mat_alea_entier(unsigned int n,unsigned int m, int min , int max)
{
  srand(time(0));
  s_mat* matrice;
  matrice=s_mat_new(n,m);
  for(unsigned int i=0;i<n;i++)
    {

      for(unsigned int j=0;j<m;j++)
        {
          /* pas terrible la distribution n'est certainement pas uniforme */
         matrice->data[i][j]= min +(int)(rand() / (double)RAND_MAX * (1+max-min));
        }
    }

  return matrice;

}


 /**
  * Matrice aléatoires de flottants
  */
s_mat *mat_alea(unsigned int n,unsigned int m, int min , int max)
{
  srand(time(0));
  s_mat* matrice;
  matrice=s_mat_new(n,m);
  for(unsigned int i=0;i<n;i++)
    {

      for(unsigned int j=0;j<m;j++)
        {
          matrice->data[i][j]= min +((float)rand() / (float)RAND_MAX * (1+max-min));
        }
    }

  return matrice;

}



/**
 *  Libère la mémoire occupée par une matrice
 */
void s_mat_free(s_mat *matrix) {
  free(matrix->data[0]);
  free(matrix->data);
  free(matrix);
}



/**
 *   Affiche une matrice à l'écran
 */
void afficher_mat(s_mat *matrix)
{
 #if ORG_OUTPUT
  for(unsigned int i = 0; i < matrix->num_rows;i++)
    {

      for(unsigned int j=0;j < matrix->num_cols;j++)
        {
          printf("%-2.7f ",matrix->data[i][j]);
        }
      printf("\n");

    }
 #else
  printf("[\n");
  for(unsigned int i = 0; i < matrix->num_rows;i++)
    {
      printf(" [");
      for(unsigned int j=0;j < matrix->num_cols;j++)
        {
          printf("%-1.5f ",matrix->data[i][j]);
          if(j<matrix->num_cols-1) printf(",");

        }
       if(i<matrix->num_rows-1)  printf("],\n");
       else printf("]\n");
    }
   printf("]\n");
#endif
}


/* Structure d'espace vectoriel */

/** Multiplication par un scalaire */
s_mat *mat_mul_ext(s_mat* matrice , double scalaire)
{
  s_mat* output;
  unsigned int n=matrice->num_rows;
  unsigned int m=matrice->num_cols;
  output=s_mat_new(n,m);
  for(unsigned int i=0;i<n;i++)
    {
      for(unsigned int j=0;j<m;j++)
        {
          output->data[i][j]= scalaire*matrice->data[i][j];

        }
    }

  return output;

}


/** Addition de deux matrices
 */
s_mat *mat_add(s_mat* A , s_mat* B)
{
 unsigned int n=A->num_rows;
 unsigned int m=A->num_cols;

  if(n != B->num_rows || m != B->num_cols)
    {
       LOG_ERROR(INVALID_DIM_ADD);
       exit(EXIT_FAILURE);

    }
  s_mat* output;

  output=s_mat_new(n,m);
  for(unsigned int i=0;i<n;i++)
    {
      for(unsigned int j=0;j<m;j++)
        {
          output->data[i][j]= A->data[i][j]+B->data[i][j];

        }
    }

  return output;

}

/**
 * Soustration de deux matrices
 */
s_mat *mat_minus(s_mat* A , s_mat* B)
{
  unsigned int n=A->num_rows;
  unsigned int m=A->num_cols;

  if(n != B->num_rows || m != B->num_cols)
    {
       LOG_ERROR(INVALID_DIM_ADD);
    exit(EXIT_FAILURE);
    }
  s_mat* output;

  output=s_mat_new(n,m);
  for(unsigned int i=0;i<n;i++)
    {
      for(unsigned int j=0;j<m;j++)
        {
          output->data[i][j]= A->data[i][j]-B->data[i][j];

        }
    }

  return output;
}

/**
 * Opposé d'une matrice
 */
s_mat *mat_oppose(s_mat* matrice)
{
  s_mat* output;
  unsigned int n=matrice->num_rows;
  unsigned int m=matrice->num_cols;
  output=s_mat_new(n,m);
  for(unsigned int i=0;i<n;i++)
    {
      for(unsigned int j=0;j<m;j++)
        {
          output->data[i][j]= (-1.0)*matrice->data[i][j];

        }
    }

  return output;
}

/* Structure d'algèbre */




/**
 * Multiplication de deux matrices
 * Renvoie une matrice produit de A et de B
 */
s_mat *mat_mul(s_mat* A , s_mat* B)
{
 unsigned int n=A->num_cols;
 unsigned int m=B->num_rows;
 double somme=0;

  if(n != m)
    {
       LOG_ERROR(INVALID_DIM_MUL);
           exit(EXIT_FAILURE);

    }
  s_mat* output;


  output=s_mat_new(A->num_rows,B->num_cols);
  for(unsigned int i=0;i<A->num_rows;i++)
    {
      for(unsigned int j=0;j<B->num_cols;j++)
        {
          somme=0;
          for(unsigned int k=0;k<n;k++) somme=somme+A->data[i][k]*B->data[k][j];
          output->data[i][j]= somme;
        }
    }

  return output;
}


/**
 * Multiplication de deux matrices
 * multiplie la matrice B à gauche par la matrice carrée A
 * B<-A*B
 */
void mat_mul_gauche(s_mat* A , s_mat* B)
{
 unsigned int n=A->num_cols;
 unsigned int m=B->num_rows;
 double somme=0;

  if(n != m)
    {
       LOG_ERROR(INVALID_DIM_MUL);
       exit(EXIT_FAILURE);
    }

  if(n != A->num_rows)
    {
      LOG_ERROR(INVALID_DIM_MUL_G);
      exit(EXIT_FAILURE);
    }
  s_mat* BB;

  BB=s_mat_copie(B);
  for(unsigned int i=0;i<A->num_rows;i++)
    {
      for(unsigned int j=0;j<B->num_cols;j++)
        {
          somme=0;
          for(unsigned int k=0;k<n;k++) somme=somme+A->data[i][k]*BB->data[k][j];
          B->data[i][j]= somme;
        }
    }

  s_mat_free(BB);
  return;

}


/**
 * Multiplication de deux matrices
 * multiplie la matrice A par une matrice carrée B
 * A<-A*B
 */
void mat_mul_droite(s_mat* A , s_mat* B)
{
 unsigned int n=A->num_cols;
 unsigned int m=B->num_rows;
 double somme=0;

  if(n != m)
    {
       LOG_ERROR(INVALID_DIM_MUL);
       exit(EXIT_FAILURE);
    }
  if(m != B->num_cols)
    {
      LOG_ERROR(INVALID_DIM_MUL_D);
      exit(EXIT_FAILURE);
    }
  s_mat* AA;

  AA=s_mat_copie(A);
  for(unsigned int i=0;i<A->num_rows;i++)
    {
      for(unsigned int j=0;j<B->num_cols;j++)
        {
          somme=0;
          for(unsigned int k=0;k<n;k++) somme=somme+AA->data[i][k]*B->data[k][j];
          A->data[i][j]= somme;
        }
    }
  s_mat_free(AA);

  return;

}






/* Questions */
/**
 * La matrice est-elle carrée?
 */
  _Bool est_carree(s_mat* matrice)
  {
    return matrice->num_cols==matrice->num_rows? true: false;

  }











/**
 * Deux matrices sont-elles égales?
 */
_Bool est_egal(s_mat* A,s_mat* B)
  {
    _Bool drapeau=false;
    if(A->num_cols == B->num_cols && A->num_rows == B-> num_rows)
      {
        drapeau = true;

        for(unsigned int i=0; i< A->num_rows;i++  )
          {

            for(unsigned int j=0; j< A->num_cols;j++  )
              {
                if (!egalD(A->data[i][j], B->data[i][j],10000*DBL_EPSILON))
                  {
		    //printf("différents!: %3.15f et %3.15f \n",A->data[i][j], B->data[i][j]);

                    drapeau =false;
                    break;

                  }

              }
          }
      }

    return drapeau;

  }


/** Renvoie vrai si la matrice est nulle */
_Bool est_nulle(s_mat* A)
{
  _Bool drapeau=true;
  for(unsigned int i=0; i< A->num_rows;i++  )
    {

      for(unsigned int j=0; j< A->num_cols;j++  )
        {
          if (!egalD(A->data[i][i], 0,DBL_EPSILON))
            {
              drapeau =false;
              break;

                  }

              }
          }


    return drapeau;

  }

/** Renvoie vrai si la matrice est la matrice identité */
_Bool est_id(s_mat* A)
{
  _Bool drapeau=true;
  for(unsigned int i=0; i< A->num_rows;i++  )
    {

      if (!egalD(A->data[i][i], 1,DBL_EPSILON))
            {
              drapeau =false;
              break;
            }
    }


    return drapeau;

}

/* Misc */

/** Renvoie la trace d'une matrice */
double trace(s_mat* A)
{
  double sommme=0;
  if(!est_carree(A))
    {
       LOG_ERROR(INVALID_CARREE);
             exit(EXIT_FAILURE);

    }
  else
    {


      for(unsigned int i=0;i< A->num_cols;i++)
        {
          sommme =sommme+A->data[i][i];

        }
    }

      return sommme;

}




/** Renvoie la transposée d'une matrice */
s_mat *transpose(s_mat* A)
{
  s_mat* t;
  t=s_mat_new(A->num_cols,A->num_rows);
  for(unsigned int i=0;i<A->num_rows;i++)
    {
      for(unsigned int j=0;j<A->num_cols;j++)
        {
          t->data[j][i]=A->data[i][j];

    }


}
  return t;

}
/** Échange deux lignes
 */
void echange_deux_lignes(s_mat* A, unsigned int i, unsigned int j)
{
  double tmp;
  for(unsigned int k=0; k < A->num_cols; k++)
    {
      tmp=A->data[j][k];
      A->data[j][k]=A->data[i][k];
      A->data[i][k]=tmp;

    }

}
