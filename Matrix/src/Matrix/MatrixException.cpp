#include "MatrixException.h"

MatrixException::MatrixException(const char* msg) :
    std::exception(msg)
{
    /**/
}

MathDefinition::MathDefinition(const char* msg) :
   MatrixException(msg)
{
    /**/
}