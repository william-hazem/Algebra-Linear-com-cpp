/*
	A header with overloads 
*/

#include "Alias.h"

#include <iostream>
#include <vector>
using namespace std;

template<typename type>
istream& operator >> (istream& input, vector<type> &A)
{
	/*	Ler elementos para um vector, quando o tamanho for especificado. 	*/
	if(A.size() != 0)
		for(nat i = 0; i < A.size(); i++)
			cin >> A[i];
	/*	Ler elementos para um vector, quando o tamanho não for especificado.*/
	else
	{
		type *inp;
		nat i = 0;
		
		while(true)
		{
			inp = new type[i+1];
			try
			{
				cin >> inp[i];
				
			}
			catch(exception &e)
			{
				break;
			}
			A.push_back(inp[i]);
			delete[] inp;
			if(char a = input.peek() == '\n')
				break;
			i++;
			/*	Quando houver um caractere de espaço (\n) no buffer a condição abaixo será verdadeira 
				Isto é um críterio de parada. Visto que, quando o usuário aperta a tecla enter(\n), subentende-se que os dados necessários foram informados.*/
			
		}
	}
	return input;
}
