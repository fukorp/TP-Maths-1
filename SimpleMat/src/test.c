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

/*

gcc -Wall -std=c99 -pedantic -g src/test.c -o bin/test lib/simplemat.a
gcc src/test.c -o test.exe -Iinclude -Llib -lsimplemat -lm

*/

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#include "../include/simplemat.h"








int main(void)
{
  s_mat* m;
  s_mat* a;
  s_mat* b;
  s_mat* c;
  s_mat* r;



  printf("Création d'une matrice de taille 4x4\n");
  m=s_mat_new(4,4);
  printf("La matrice possède %d lignes et %d colonnes\n",m->num_rows,m->num_cols);



  printf("Libération de la mémoire occupée\n");


  s_mat_free(m);




  printf("Création d'une matrice carrée de taille 7x7\n");
  m=s_mat_carree(7);
  afficher_mat(m);
  s_mat_free(m);

  printf("Création de la matrice identité'5x5\n");
  m=s_mat_id(5);
  afficher_mat(m);
  s_mat_free(m);

  printf("Création de la matrice [[1,3][2,7]]\n");
  double valeurs[7]= {1.0,3.0,2.0,7.0,8.0,9.0,10};
  m=s_mat_coef(2,2,valeurs,7);
  printf("Le coefficient de la %d ème ligne et la %d ème colonne vaut:%f \n",1,2,m->data[0][1]);
  afficher_mat(m);
  s_mat_free(m);




  printf("Création d'une matrice d'entiers aléatoires entre -5 et 8\n");
  m=mat_alea_entier(3,4,-5,8);
  afficher_mat(m);
  printf("Échange de la ligne 1 avec la ligne 3\n");
  echange_deux_lignes(m,0,2);
  afficher_mat(m);


  printf("Libération de la mémoire occupée\n");
  s_mat_free(m);

  printf("Création d'une matrice de nombres aléatoires entre -12 et 12\n");
  m=mat_alea(7,4,-12,12);
  afficher_mat(m);
  printf("Libération de la mémoire occupée\n");
  s_mat_free(m);

  printf("Création de la matrice A=[[1,3,5][2,7,0]]\n");
  double valeurss[7] = {1.0, 3.0, 0.0, 2.0, 7.0, 9.0, 10};
  a=s_mat_coef(2,3,valeurss,5);
  afficher_mat(a);
  printf("Création de la matrice B=[[4,-5,5][-2,-4,9]]\n");
  double valeursss[9] = {4.0, -5.0, 5.0, -2.0, -4.0, 9.0, 10, 11 ,-1};
  b=s_mat_coef(2,3,valeursss,6);
  afficher_mat(b);
  printf("Création de la matrice C\n");
   c=s_mat_coef(3,2,valeursss,6);
  afficher_mat(c);

  printf("3A:\n");
  r=mat_mul_ext(a,3.0);
  afficher_mat(r);
  s_mat_free(r);

  printf("A+B:\n");
  r=mat_add(a,b);
  afficher_mat(r);
  s_mat_free(r);


  printf("A-B:\n");
  r=mat_minus(a,b);
  afficher_mat(r);
  s_mat_free(r);

  printf("Opposé de A\n");
  r=mat_oppose(a);
  afficher_mat(r);
  s_mat_free(r);

  printf("B*C\n");
  r=mat_mul(b,c);
  afficher_mat(r);


  s_mat_free(a);
  s_mat_free(b);
  s_mat_free(c);

  printf("A\n");
  a=s_mat_coef(2,3,valeurss,5);
  afficher_mat(a);
  b=s_mat_coef(3,3,valeursss,9);
  printf("B\n");
  afficher_mat(b);
  c=s_mat_coef(2,2,valeursss,4);

  printf("C\n");
  afficher_mat(c);

  printf("A=A*B\n");
  mat_mul_droite(a,b);
  printf("A\n");
  afficher_mat(a);
  printf("A=C*A\n");
  mat_mul_gauche(c,a);
  printf("A\n");



  afficher_mat(a);
  s_mat_free(a);
  s_mat_free(b);
  s_mat_free(c);


  s_mat_free(r);

  printf("E(5,2,3)\n");
  r=s_mat_e(5,2,3);
  afficher_mat(r);
  s_mat_free(r);

  printf("L(7,2,3,-3.5)\n");
  r=s_mat_l(7,2,3,-3.5);
  afficher_mat(r);
  s_mat_free(r);

  printf("H(5,4,-2)\n");
  r=s_mat_h(5,2,-2.7);
  afficher_mat(r);
  s_mat_free(r);

  printf("Tests\n");
  a=s_mat_coef(2,3,valeurss,5);
  b=s_mat_coef(2,2,valeurss,5);
  printf("A=\n");
  afficher_mat(a);

  printf("B=\n");
  afficher_mat(b);

  if(est_carree(a))
    {
      printf("La matrice A est carrée\n");

    }
  else
    {
        printf("La matrice A n'est pas carrée\n");
        printf("La transposée de A est\n");
        c=transpose(a);
        afficher_mat(c);
        s_mat_free(c);

    }

  if(est_carree(b))
    {
      printf("La matrice B est carrée\n");
      printf("La trace de B vaut %f\n",trace(b));
    }
  else
    {
        printf("La matrice B n'est pas carrée\n");
    }



  if(est_egal(a,a))
    {
      printf("La matrice A est égale à elle même\n");
    }

  if(!est_egal(a,b))
    {
      printf("La matrice A n'est pas  égale à B\n");
    }

  c=s_mat_id(2);

  if(est_egal(b,c))
    {
      printf("La matrice B est égale à l'identité\n");

    }
  else
    {
      printf("La matrice B n'est pas  égale à l'identité\n");

    }

   if(est_id(b))
    {
      printf("La matrice B est égale à l'identité\n");

    }
  else
    {
      printf("La matrice B n'est pas  égale à l'identité\n");

    }


   s_mat_free(a);
   s_mat_free(b);
   s_mat_free(c);

   a=s_mat_coef(2,3,valeurss,5);
   b=mat_minus(a,a);
   printf("A=\n");
   afficher_mat(a);
   printf("B=\n");
   afficher_mat(b);

   if(est_nulle(b))
    {
      printf("La matrice B est nulle\n");

    }
  else
    {
      printf("La matrice B n'est pas  nulle\n");

    }
    if(est_nulle(a))
    {
      printf("La matrice A est nulle\n");

    }
  else
    {
      printf("La matrice A n'est pas  nulle\n");

    }

   s_mat_free(a);
   s_mat_free(b);
  return 0;

  }
