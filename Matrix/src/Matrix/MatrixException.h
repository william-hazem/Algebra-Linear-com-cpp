#pragma once

#include <exception>

class MatrixException : public std::exception
{
public:
	MatrixException(const char* m);
};

class MathDefinition : public MatrixException
{
public:
	MathDefinition(const char* msg);
};