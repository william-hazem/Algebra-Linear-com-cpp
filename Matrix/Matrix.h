#pragma once

#ifndef MATRIX_H
#define MATRIX_H

typedef double real;

/**
 * Global Variables
 */

const short int matrix_print_set = 3;
const short int matrix_print_precision = 2;

/**
 * Includes
 */

#include<vector>
using std::vector;
using std::initializer_list;
#include<iostream>
using std::ostream;
#include <iomanip>
using std::setprecision;
using std::setw;

#include "MatrixException.h"

#ifdef LIAL_FRACTION
#include <Fraction.h>
#endif // !LIAL_FRACTION

/**
 *  Alias
 */

typedef unsigned int natural;
#ifdef LIAL_FRACTION
typedef Fraction real;
#else
typedef double real;
#endif // LIAL_FRACTION

namespace LIAL_MATRIX
{
    /**
     * Class Definition
     */

    template<typename Type>
    class Matrix
    {
        void msg(const char* msg) { std::cout << msg << std::endl; }

        friend std::ostream& operator<<(std::ostream& output, Matrix* matrix_ptr) 
        {
            output << *matrix_ptr;
            delete matrix_ptr;
            return output;
        }
        friend std::ostream& operator<<(std::ostream& output, const Matrix& matrix)
        {
            output << setprecision(matrix_print_precision);
            for (auto it_i : matrix.get())
            {
                for (auto it_j : it_i)
                    output <<setw(matrix_print_set) << it_j << ' ';
                output << '\n';
            }
            return output;
        }
    private:

        /**
         *
         * Private Variable
         *
         */

        vector<vector<Type>>* matrix_ptr = 0;

        /**
         *
         * Private Functions
         *
         */

        void initMatrix(size_t i, size_t j, Type init_value)
        {
            vector<Type> column(j, init_value);
            matrix_ptr = new vector<vector<Type>>(i, column);
        }

        bool deleteMatrix()
        {
            if (!matrix_ptr)
                return false;
            delete matrix_ptr;
            matrix_ptr = 0;
            return true;
        }

        void copyMatrix(const Matrix& matrix)
        {
            deleteMatrix(); // Delete the old matrix
            matrix_ptr = new std::vector<std::vector<Type>>(matrix.get());
        }

        void moveMatrix(Matrix* matrix)
        {
            this->copyMatrix(*matrix);
            delete matrix;
            matrix = 0;
        }
    public:

        /**
         *
         * Public Functions
         *
         */

        Matrix()
        {
            msg("ctor");
            matrix_ptr = 0;
        }

        Matrix(const Matrix& matrix)
        {
            msg("ctor");
            this->set(matrix);
        }

        Matrix(Matrix* matrix_ptr)
        {
            msg("ctor by ptr");
            this->set(*matrix_ptr);
            delete matrix_ptr;
        }

        Matrix(size_t i, size_t j = 1, Type init_value = 0)
        {
            msg("ctor");
            initMatrix(i, j, init_value);
        }

        Matrix(initializer_list<Type> init_row)
        {
            msg("ctor");
            matrix_ptr = new vector<vector<Type>>(1, init_row);
        }

        Matrix(initializer_list<initializer_list<Type>> init_matrix)
        {
            msg("ctor");
            matrix_ptr = new vector<vector<Type>>(init_matrix.begin(), init_matrix.end());
        }

        Matrix(vector<vector<Type>>& init_vector)
        {
            msg("ctor");
            matrix_ptr = new vector<vector<Type>>(init_vector.begin(), init_vector.end());
        }

        virtual ~Matrix()
        {
            msg("dtor");
            delete matrix_ptr;
            matrix_ptr = 0;
        }
        
        /**
         *
         * Get Methods
         *
         */

        // Get number of rows.
        size_t get_i() const 
        { 
            return matrix_ptr->size(); 
        }

        // Get number of columns.
        size_t get_j() const
        {
            if (this->get_i() >= 1)
                return (*matrix_ptr)[0].size();
            else
                return 0;
        }

        // Return the vector instance
        vector<vector<Type>> get() const
        {
            return *this->matrix_ptr;
        }

        vector<vector<Type>>& get()
        {
            return *this->matrix_ptr;
        }

        /**
         *
         * Set Methods
         *
         */

        void set(const Matrix& matrix)
        {   
            this->copyMatrix(matrix);
        }

        /**
         *
         * Operator Overloads
         *
         */

        bool operator==(const Matrix<Type>& matrix) const
        {
            return this->get() == matrix.get();
        }

        bool operator!=(const Matrix<Type>& matrix) const
        {
            return !(this->get() == matrix.get());
        }

        vector<Type> operator[] (const size_t i) const
        {
            return  (*matrix_ptr)[i];
        }

        vector<Type>& operator[](const size_t i)
        {
            return (*matrix_ptr)[i];
        }

        // Copy operation
        void operator=(const Matrix& matrix)
        {
            this->set(matrix);
        }

        /**
         * Matrix Essencials
         *-----------------------------------------------------------------------------------------
         * Matrix Math
         */

        

        /*
         * Operators Overload and Matrix Operations
         */

        Matrix<Type> operator+(const Matrix<Type>& matrix) const
        {
            if (this->get_i() != matrix.get_i() || this->get_j() != matrix.get_j())
                throw "d1";
            Matrix result(this->get_i(), this->get_j(), 0);
            for (size_t i = 0; i < this->get_i(); i++)
                for (size_t j = 0; j < this->get_j(); j++)
                    (result)[i][j] = (*this)[i][j] + matrix[i][j];
            return result;
        }

        Matrix<Type> operator*(const Type scalar) const
        {
            Matrix<Type>* result = new Matrix<Type>(*matrix_ptr);
            for (size_t i = 0; i < this->get_i(); i++)
                for (size_t j = 0; j < this->get_j(); j++)
                    (*result)[i][j] *= scalar;
            return *result;
        }

        Matrix<Type> operator-(const Matrix<Type>& matrix) const
        {
            return *this + (matrix * -1);
        }

        Matrix<Type> operator/(const Type scalar) const
        {
            Matrix<Type>* result = new Matrix<Type>(*matrix_ptr);
            for (size_t i = 0; i < this->get_i(); i++)
                for (size_t j = 0; j < this->get_j(); j++)
                    (*result)[i][j] /= scalar;
            return *result;
        }

        Matrix operator*(const Matrix& matrix) const
        {
            if (this->get_i() != matrix.get_i() || this->get_j() != matrix.get_j())
                throw "d1";
            Matrix<Type>* result = new Matrix<Type>(matrix.get_i(), matrix.get_j(), 0);
            for (size_t i = 0; i < matrix.get_i(); i++)
                for (size_t j = 0; j < matrix.get_j(); j++)
                    for (size_t k = 0; k < matrix.get_i(); k++)
                        (*result)[i][j] += (*this)[i][k] * matrix[k][j];
            return *result;
        }

        Matrix sub(size_t si, size_t sj) const
        {
            Matrix* sub_matrix_ptr = new Matrix(this->get_i()-1, this->get_j()-1, 0);
            size_t m = 0;
            for (size_t i = 0; i < this->get_i(); i++)
            {
                size_t n = 0;
                if (i != si)
                {
                    for (size_t j = 0; j < this->get_j(); j++)
                    {
                        if (j != sj)
                        {
                            (*sub_matrix_ptr)[m][n] = (*this)[i][j];
                            n++;
                        }
                    }
                    m++;
                }
            }
            return *sub_matrix_ptr;
        }

        #ifndef LIAL_FRACTION
        real det()
        {
            real det_value = 0.0f;
            if (!this->isSquare())
                throw MathDefinition("Determinant not defined for matrix [A]ij when i != j.");
            //Determinant calculation
            for (size_t i = 0; i < this->get_i(); i++)
            {
                if (this->get_i() > 1)
                    det_value += (double)(i % 2 == 0 ? 1 : -1) * (double)(*this)[i][0] * (double)sub(i, 0).det();
                else
                    return (*this)[0][0];
            }
            return det_value;
        }
        #else
        Fraction det()
        {
            // COMING SOON
        }
        #endif

        void transpose()
        {
            Matrix* transposed = new Matrix(this->get_j(), this->get_i(), 0);
            for (size_t i = 0; i < this->get_i(); i++)
            {
                for (size_t j = 0; j < this->get_j(); j++)
                {
                    (*transposed)[j][i] = (*this)[i][j];
                }
            }
            this->set(*transposed);
            delete transposed;
        }

        Matrix<real> adjugate()
        {
            Matrix<real>* cofactor_matrix = new Matrix<real>(this->get_i(), this->get_j());
            for (size_t i = 0; i < this->get_i(); i++)
                for (size_t j = 0; j < this->get_j(); j++)
                    (*cofactor_matrix)[i][j] = (((i + j) % 2) == 0 ? 1 : -1) * this->sub(i, j).det();
            cofactor_matrix->transpose(); //adjugate matrix
            return *cofactor_matrix;
        }

        Matrix<real>* inverse()
        {
            real det_value = this->det();
            if(det_value == 0)
                return 0;
            Matrix<real>* inversed = new Matrix<real>(adjugate() / det_value);
            return inversed;
        }

        /**
         *Utility Functions
         */
        
        bool isColumnMatrix() const
        {
            return this->get_j() == 1;
        }

        bool isRowMatrix() const
        {
            return this->get_i() == 1;
        }

        bool isSquare() const
        {
            return this->get_i() == this->get_j();
        }
        
        bool isSameDimension(const Matrix& matrix) const
        {
            return (this->get_i() == matrix.get_i() && this->get_j() == matrix.get_j());
        }

        bool isRevesible() const
        {
            return (this->det() == 0);
        }

        bool isNull() const
        {
            return (this->get_i() == 0 && this->get_j == 0);
        }
    };

} //namespace LIAL_MATRIX

#endif // Matrix.h
