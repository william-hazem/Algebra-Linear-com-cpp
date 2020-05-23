#include <iostream>
using std::cout;
using std::endl;

#include<lial.h> //LIAL::Matrix
using LIAL::Matrix;

int main()
{
	try
	{
		Matrix<real> t1;

		if (LIAL::createMatrix(&t1, 2, 2))
		{
			cout << t1;
			cout << "OK!\n";
		}


		Matrix<real> a = { 
			{1,0,0},
			{0,2,2},
			{2,0,3} }; // 3x3
		Matrix<> b = { 
			{1,0}, 
			{2,0}, 
			{0, 1} }; //3x2
		cout << "a * b\n" <<
			a * b << endl;

		cout << " a * 2 " <<
			a * 2 << endl;

		a += a;
		cout << "a + a\n"
			<< a << endl;

		cout << a * a << endl;
		a *= a;
		cout << a << endl;
		cout << "is null: " <<
			a.isNull() <<
			'\n';
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}

	std::cin.get();
	return 0;
}