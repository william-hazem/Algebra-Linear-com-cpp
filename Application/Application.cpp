#include <iostream>
using std::cout;
using std::endl;

#include<Matrix.h> //LIAL_MATRIX::Matrix
using LIAL_MATRIX::Matrix;

int main()
{
	try
	{
		Matrix<real> a = { {1,0,0},{0,2,2},{2,0,3} };
		Matrix<real> b = a+a; 
		cout << b  << endl;
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}

	std::cin.get();
	return 0;
}