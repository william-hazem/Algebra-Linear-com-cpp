#ifndef LINEARALGEBRA_H
#define LINEARALGEBRA_H

#include "Matrix.h"

/*
	template<typename type>
		double max(Mat<type> A)
		{
			if(A.get_i() == 0)
				return 0;
			if(A.get_i() > 1 && A.get_j() > 1)
				throw "No is a colunm matrix or a row matrix";
			type max_value = A.get()[0][0];
			
			// For row matrix
			if(A.get_i() == 1 && A.get_j() > 1 )
			
				for(nat j = 1; j < A.get_j(); j++)
					if(max_value < A.get()[0][j])
						max_value = A.get_i()[0][j];
			// For colunm matrix			
			else
				for(nat i = 1; i < A.get_i(); i++)
					if(max_value < A.get()[i][0])
						max_value = A.get_i()[i][0];
		}
*/

namespace Lalg
{
	/*	Constructs	*/
	template<typename type>
	type abs(type);
	
	template<>
	char abs<char>(char x );
	
	template<typename type>
	type max(Mat<type>);
	
	template<typename type>
	type max(vector<type>);
	
	template<typename type>
	type max_abs(Mat<type>);
	/*	Code Here	*/

	template<typename type>
	type abs(type x)
	{
		return x < 0 ? x*-1 : x;
	}
	
	/*	Especialização da função template abs */
	template<>
	char abs<char>(char x)
	{
		cout << "Hello" << endl;
	}
	
	template<typename type>
	type max(Mat<type> A)
	{
		if(A.is_colunm())
			A.transpose();
		else
			if(!A.is_row())
				throw "No is a colunm matrix or a row matrix";
		if(A.is_null())
			throw "No elements in array";	
		return max(A[0]);
	}
	
	template<typename type>
	type max(vector<type> V)
	{
		type m = V[0];
		if(V.size() == 0)
			throw "No elements";
		if(V.size() > 1)
			for(nat i = 1; i < V.size() ; i ++)
				if(V[i] > m)
					m = V[i];
		return m;
	}
	
	template<typename type>
	type max_abs(vector<type> A)
	{
		
	}
	
	/*max está definida apenas para matrizes colunas ou matrizes linhas*/

	
	float max_abs(vector<vector<float>> V)
	{
		int m = abs(V[0][0]);
		if(V.size() == 0)
			throw "No elements";
		if(V.size() > 1)
			for(nat i = 1; i < V.size() ; i ++)
				if(abs(V[i][0]) > m)
					m = abs(V[i][0]);
		return m;
	}
	
	/* return 0 when the posto is 1 - is a problem - resolving... and testing...*/
	/* work for not square matrix - testing....*/
	nat posto(Mat<float> A)
	{
		if(A.get_i() == A.get_j())
		{
			A.print();
			if(A.det() != 0)
				return A.get_i();
			
			for(nat i = 0; i < A.get_i(); i ++)
				for(nat j = 0; j < A.get_j(); j++)
				{
					auto sub_A = A.sub_matrix(i,j);
					if(sub_A.det() != 0)
						return sub_A.get_i();
				}
		}
		else
		{
			nat p = 0, ci = A.get_i(), cj = A.get_j();
			Mat<float> sub_aux;
			
			for(nat k = 0; k < A.get_j(); k++ )
			{
				if(A.get_i() > A.get_j())
					sub_aux = A.sub_matrix(k,A.get_j()+1);
				else
					sub_aux = A.sub_matrix(A.get_i()+1, k);
				if(posto(sub_aux) != 0)
					return sub_aux.get_i();
			}
		}
	}
	
	template<typename type>
	Mat<double> Gauss_Seidel(Mat<type> A, Mat<type> y, nat limit_n)
	{
		//if( A.get_i() != A.get_j() && !(y.is_colunm()) ) 
			//throw "Invalid matrizes";
		
		Mat<double> X (A.get_i(), 1, 0);
		auto x = X.get(), x0 =x;
		
		for(nat l = 0; l < limit_n; l++)
		{
			for(nat i = 0; i < A.get_i(); i++)
			{
				double h = 0;
				for(nat j = 0; j < A.get_j(); j++)
					if(i != j)
						h += A.get()[i][j] * x0[j][0];
				x0[i][0] = (y.get()[i][0]-h) / A.get()[i][i];
			}
			x = x0;
		}
		return {&x};	
	}
}

#endif /*Linear Algebra*/
/*
int main() {
	int x = Linalg.abs(-1);
	cout << x;
	vector<int> V = {1,2,3,4,5,4,0};
	int y = Linalg.max(V);
	cout << y;
	
	Mat<int> M(3,1,2);
	M.transpose();
	//M.print();
	
	return 0;
}
*/
