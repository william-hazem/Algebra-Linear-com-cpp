#ifndef MATRIX_H
#define MATRIX_H

#include <clocale>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;

/* 99  is c in decimal */
/* 114 is r in decimal */
#define COL 99
#define ROW 114

/* natural type */
typedef unsigned int nat;

template<typename type>
class Mat
{
private:
	vector<vector<type> > matrix;
	
	void init(vector<vector<type>> *matrix, nat i, nat j, type init_value)
	{
		vector<type> row (j,init_value);
		for(nat ci = 0; ci < i; ci++)
			matrix->push_back(row);
	}
	
	void init(nat i, nat j, type init_value) {
		vector<type> row (j,init_value);
		for(nat ci = 0; ci < i; ci++)
			matrix.push_back(row);
	}
	
	void init(initializer_list<type> A)
	{
		this->matrix.push_back(A);
	}
	
	void init(initializer_list<initializer_list<type>> A)
	{
		for(auto it_i : A)
			this->matrix.push_back(it_i);
	}
	
public:
	
	/* empty construct */
	Mat() {}
	
	/* Initialized list for two dimensions */
	Mat(initializer_list<std::initializer_list<type>> A)
	{
		init(A);
	}
	
	/* Initialized list for a colunm matrix or row matrix */
	Mat(initializer_list<type> A, char matrix_type = 'c')
	{
		cout << matrix_type << endl;
		init(A);
		if(matrix_type == 'c')
			this->transpose();
		else 
			if(matrix_type != 'r')
				throw "No defined";
	}
	
	/* Reference construct of a vector<vector<TYPE>>*/
	Mat(vector<vector<type> > *matrix) 
	{
		this->matrix = *matrix;
	}
	
	/* Reference construct for a column matrix */
	Mat(vector<type> matrix) 
	{
		this->init(matrix.size(), 1, 0);
		for(nat i = 0; i < this->get_i(); i++)
			this->matrix[i][0] = matrix[i];
	}
	
	/* Initialize a matrix with two dimension and a value for the elements */
	Mat(nat i, nat j, type init_value) 
	{
		init(i,j,init_value);
	}
	
	vector<type> operator[](nat i) const
	{
		return this->matrix[i];
	}
	
	vector<type> &operator[](nat i)
	{
		return matrix[i];
	}
	
	/* Print the matrix - I'll transfer this resource of this class for other*/
	void print() 
	{
		for(int i = 0; i < this->get_i(); i++)
		{
			for(int j = 0; j < this->get_j(); j++)
				cout << setw(3) << matrix[i][j] << " ";
			cout << endl;
		}
		cout << endl;		
	}
	
	void copy(vector<vector<type>> *A) 
	{
		this->matrix = *A;
	}
	
	void set_element(nat i, nat j, type value)
	{
		if(i >= this->get_i() || j >= this->get_j() )
		  throw "d1"; /*definition problem - cannot set a element in a inexist space */
		this->matrix[i][j] = value;
	}
	
	/* Get the vector class' atribute */
	vector<vector<type>> get() 
	{
		return matrix;
	} const
	
	/* Get row numbers */
	nat get_i() 
	{
		return matrix.size();
	} const
	
	/*Get colunn numbers */
	nat get_j() 
	{
		return matrix[0].size();
	} const
	
	/* Math Operations */
	
	/* Product between two matrix */
	Mat<type> prod(Mat<type> B) {
		if(this->get_j() != B.get_i())
			throw "m1"; /* Erro M1: Amn * Bpq aren't define */
		Mat<type> result(this->get_i(),B.get_j(), 0);
		vector<vector<type>> C = result.get();
		
		for(nat i = 0; i < this->get_i(); i++)
			for(nat j = 0; j < B.get_j(); j++)
				for(nat k = 0; k < this->get_j(); k++)
					C[i][j] += this->get()[i][k] * B.get()[k][j];
		
		result.copy(&C);
		return result;
	}
	
	Mat<type> operator*(Mat<type> B) 
	{
		return this->prod(B);
	}
	
	/* Sum between two matrix */
	Mat<type> sum(Mat<type> B) 
	{
		if(this->get_i() != B.get_i() || this->get_j() != B.get_j())
			throw "m2"; /*Erro m2: Diferent order into matrizes*/
		vector<vector<type>> C;
		init(&C,B.get_i(),B.get_j(),0);
		for(nat i = 0; i < B.get_i(); i++)
			for(nat j = 0; j < B.get_j(); j++)
				C[i][j] = this->matrix[i][j] + B.get()[i][j];
		Mat<type> result = &C;
		return result;
	}
	
	Mat<type> operator+(Mat<type> B) {
		return this->sum(B);
	}
	
	Mat<type> sub(Mat<type> B) 
	{
		if(this->get_i() != B.get_i() || this->get_j() != B.get_j())
			throw "m2"; /*Erro m2: Diferent order into matrizes*/
		vector<vector<type>> C;
		init(&C,B.get_i(),B.get_j(),0);
		for(nat i = 0; i < B.get_i(); i++)
			for(nat j = 0; j < B.get_j(); j++)
				C[i][j] = this->matrix[i][j] - B.get()[i][j];
		return {&C};
	}
	
	Mat<type> operator-(Mat<type> B) 
	{
		return this->sub(B);
	}
	
	Mat<type> scalar_prod(type scalar) 
	{
		vector<vector<type>> C = this->get();
		for(nat i = 0; i < this->get_i(); i++)
			for(nat j = 0; j < this->get_j(); j++)
				C[i][j] *= scalar;
		return {&C};
	}
	
	Mat<type> operator*(type k) 
	{
		return this->scalar_prod(k);
	}
	
	void transpose()
	{
		Mat<type> T(this->get_j(), this->get_i(), 0);
		auto t = T.get();
		for(nat i = 0; i < this->get_i(); i++)
			for(nat j = 0; j < this->get_j(); j++)
				t[j][i] = this->matrix[i][j];
		this->copy(&t); 
	}
	
	float det()
	{
		if(this->get_i() != this->get_j())
			throw "m3"; /*The determinant is only possible for square matrizes*/
			
		float det = 0;
		if(this->get_i() > 2)
		{
			for(nat i = 0; i < this->get_i(); i++)
			{
				auto Sub = this->sub_matrix(i,0);
				//cout << (i%2 == 0? 1:-1) << "*" <<this->get()[i][0] << " * " << Sub.det() << endl;
				det +=  (i%2 == 0? 1:-1) * this->get()[i][0] * Sub.det();
			}
		}
		else
			det += this->get()[0][0] * this->get()[1][1] - (this->get()[0][1]*this->get()[1][0]); 
		return det;
	}
	
	Mat<type> sub_matrix(nat ci, nat cj) 
	{
		nat init_i = this->get_i() - 1, init_j = this->get_j() - 1;
		if(ci > this->get_i())
			init_i++;
		if(cj > this->get_j())
			init_j++;
			
		vector<vector<type>> A;
		init(&A,init_i,init_j,0);
		
		nat m = 0, n = 0; 
		
		for(nat i = 0; i < this->get_i(); i ++)
		{	
			float n = 0;
			if(i != ci)
			{
				for(nat j = 0; j < this->get_j(); j++)
				{
					if(j != cj)
					{
						A[m][n] = this->get()[i][j];
						n++;
					}
				}
				m++;
			}
			n = 0;
		}
		
		return {&A};
	}
	
	/* adjunte matirx */	
	Mat<type> adj()
	{
		vector<vector<type>> adj_matrix;
		init(&adj_matrix,this->get_i(),this->get_j(),0);
		
		for(nat i = 0; i < this->get_i(); i++)
			for(nat j = 0; j < this->get_j(); j++)
			{
				auto Aij = this->sub_matrix(i,j);
				adj_matrix[i][j] = ((i+j)%2 == 0?1:-1) * Aij.det();
			}
		return {&adj_matrix};
	}
	
	bool is_colunm()
	{
		if(this->get_j() == 1 && this->get_i() > 1)
			return true;
		return false;
	}
	
	bool is_row()
	{
		if(this->get_i() == 1 && this->get_j() > 1)
			return true;
		return false;
	}
	
	bool is_null()
	{
		if( this->get_i() == 0 && this->get_j() == 0)
			return true;
		return false;
	}
	
	
};

#endif /*Matrix.h*/

/*
int main()
{
	setlocale(LC_ALL,"");
	
 	
	vector<vector<int>> matrix_a = {{23,1},{0,2}};
	Mat<int> M = &matrix_a;
	vector<vector<int>> matrix_b = {{1,0},{0,2}};
	Mat<int> N = &matrix_b;
	
	Mat<int> O = M.prod(N);
	O.transpose();
	O.print();
	return 0;
}
*/
