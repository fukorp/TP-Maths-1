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
#include <stdarg.h>
#include <stdbool.h>
#include "../include/sm_util.h"
#include <float.h>
#include <math.h>




void error_log(  FILE* stream,  const char *file_name,  unsigned int line,  const char *format)
{

  fprintf(stream, "[%s:%d] [ERREUR] %s\n", file_name, (int)line, format);
  return;


}


/**
 * maximum
 */
double max(double num1, double num2)
{
    return (num1 > num2 ) ? num1 : num2;
}

/**
 *  minimum
 */
double min(double num1, double num2)
{
    return (num1 > num2 ) ? num2 : num1;
}


/**
 * Renvoie vrai si deux doubles sont égaux à epsilon près
 */
_Bool egalD(double a, double b, double epsilon) {
		double absA = fabs(a);
		double absB = fabs(b);
		double diff = fabs(a - b);

		if (a == b) {
                  // raccourci gère les valeurs infinies
                  return true;
                }
                else if (a == 0 || b == 0 || (absA + absB < DBL_MIN))
                  {
			// a ou  b sont proches de 0
			return diff < (epsilon);
		} else {
                  // Sinon erreur relative
			return diff / min((absA + absB), DBL_MAX) < epsilon;
		}
	}
