#pragma once

/*
#ifndef LIAL_MATRIX && LIAL_FRACTION
#	define LIAL_MATRIX
#	define LIAL_FRACTION
#endif
*/
#define LIAL_MATRIX
#ifdef LIAL_MATRIX
#	include "Matrix.h"
#endif // ONLY_MATRIX

/*
#ifndef LIAL_FRACTION
#	include "Fraction.h"
#endif // ONLY_FRACTION
*/

#include "LIALExtraUtilities.h"

/** 
 * TO DO 
 **
 * -[ ] Optional Build Logger 
 * -[ ] Better Exceptions and Warnings
 * -[ ] Documentation
 *
 */
