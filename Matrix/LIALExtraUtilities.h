#pragma once

#include "Matrix.h"

namespace LIAL
{
	/*
		Initialize a matrix by adress or pointer.
	*/
	template<typename _type>
	bool createMatrix(LIAL::Matrix<_type>* matrix, size_t i, size_t j)
	{

		if (matrix == NULL)
		{
			*matrix = LIAL::Matrix<real>(i, j);
		}
		else
		{
			if (matrix->isEmpty() == false)
			{
				return false;
			}
			try
			{
				*matrix = LIAL::Matrix<real>(i, j);
			}
			catch (std::bad_alloc& bad_alloc)
			{
				throw bad_alloc;
			}

		}

		return true;
	} //!createMatrix

	
} //!LIAL