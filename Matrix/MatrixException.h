#pragma once

#include <exception>

class MatrixException
{
protected:
	const char* msg;

public:
	MatrixException(const char* m = "none") : msg(m) {};
	virtual ~MatrixException() {};

	virtual const char* what() const = 0;
	virtual const char* type() const = 0;
};

class MathDefinition : public MatrixException
{
public:
	MathDefinition(const char* msg) : MatrixException(msg) {};
	~MathDefinition() {};

	const char* type() const
	{
		return "MathDefinition Exception";
	}

	const char* what() const
	{
		return msg;
	}
};