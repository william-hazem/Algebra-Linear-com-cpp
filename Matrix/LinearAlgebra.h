#pragma once

#include "Matrix.h"

typedef real Type;

namespace LIAL
{
	bool isSameDimension(const LIAL::Matrix<Type>& A, const LIAL::Matrix<Type>& B)
	{
		return A.isSameDimension(B);
	}

	/*
		Create an amplifier matrix,
		A * x = y
	*/
	template<typename _type>
	LIAL::Matrix<_type>* amp(const Matrix<_type>& A, const Matrix<_type>& y)
	{

		if (A.get_i() != y.get_i())
			return 0; //Null Pointer
		size_t _i = A.get_i(), _j = A.get_j() + y.get_j(), Aj = A.get_j();
		LIAL::Matrix<_type> R(_i, _j);
		for (size_t i = 0; i < _i; i++)
		{
			for (size_t j = 0; j < _j; j++)
			{
				if (j < Aj)
				{
					R[i][j] = A[i][j];
				}
				else
				{
					R[i][j] = y[i][j];
				}
			}
		}
		return 0;
	}


	template<typename _T>
	void escalonar(LIAL::Matrix<_T> matrix)
	{

	}



} //LIAL