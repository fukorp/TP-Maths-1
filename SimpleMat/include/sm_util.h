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
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#define DEBUG_TRUE 1

// couleur pour le terminal
#define ROUGE "\033[0;31m"
#define RESET "\033[0m"
#define VERT "\033[0;32m"
#define VIOLET "\033[0;35m"

#define LOG_ERROR(fmt)   error_log(stderr, __FILE__, __LINE__, ROUGE fmt RESET);


#define ALLOC_CHECK(ptr)  if (!(ptr)) { fprintf(stderr, "%s:%d pointeur nul: %s n", __FILE__, __LINE__, (#ptr));  exit(EXIT_FAILURE);     }


void error_log(FILE *stream, const char *file_name,
  unsigned int line, const char *format);

void my_log(FILE* stream,const char *file_name, unsigned int line, const char *format);


_Bool egalD(double a, double b, double epsilon);


double max(double num1, double num2);
double min(double num1, double num2);
