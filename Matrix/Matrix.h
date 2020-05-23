#pragma once

#ifndef MATRIX_H
#define MATRIX_H

/**
 * Global Variables
 */

const short int matrix_print_set = 3;
const short int matrix_print_precision = 2;
/**
 * Includes
 */

#include<vector>
#include<iostream>
#include <iomanip>

#include "MatrixException.h"

#ifdef LIAL_FRACTION
#include <Fraction.h>
#endif // !LIAL_FRACTION

/**
 *  Alias
 */

typedef unsigned long long natural;

#ifdef LIAL_FRACTION
typedef Fraction real;
#else
typedef double real;
#endif // LIAL_FRACTION

namespace LIAL
{
    template<typename Type = real>
    class Matrix
    {
        friend std::ostream& operator<<(std::ostream& output, Matrix* matrix_ptr) 
        {
            output << *matrix_ptr;
            delete matrix_ptr;
            return output;
        }
        friend std::ostream& operator<<(std::ostream& output, const Matrix& matrix)
        {
            // A definir o matrix_print_precision
            output << std::setprecision(matrix_print_precision);
            for (auto it_i : matrix.get())
            {
                for (auto it_j : it_i)
                    output << std::setw(matrix_print_set) << it_j << ' ';
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

        std::vector<std::vector<Type>>* matrix_ptr = 0;

        /**
         *
         * Private Functions
         *
         */

        void initMatrix(size_t i, size_t j, Type init_value)
        {
            if (i == 0)
            {
                matrix_ptr = 0;
            }
            else
            {
                //Initializer a double vector, 2d Matrix.
                std::vector<Type> column(j, init_value);
                matrix_ptr = new std::vector<std::vector<Type>>(i, column);
            }
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
            matrix_ptr = 0;
        }

        Matrix(const Matrix& matrix)
        {
            this->set(matrix);
        }

        Matrix(Matrix* matrix_ptr)
        {
            this->set(*matrix_ptr);
            //descoment may cause problem with the extrautilities header
            //delete matrix_ptr;
        }

        Matrix(size_t i, size_t j = 1, Type init_value = 0)
        {
            initMatrix(i, j, init_value);
        }

        Matrix(std::initializer_list<Type> init_row)
        {
            matrix_ptr = new std::vector<std::vector<Type>>(1, init_row);
        }

        Matrix(std::initializer_list<std::initializer_list<Type>> init_matrix)
        {
            matrix_ptr = new std::vector<std::vector<Type>>(init_matrix.begin(), init_matrix.end());
        }

        Matrix(std::vector<std::vector<Type>>& init_vector)
        {
            matrix_ptr = new std::vector<std::vector<Type>>(init_vector.begin(), init_vector.end());
        }

        virtual ~Matrix()
        {
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
            if(matrix_ptr != 0)
                return matrix_ptr->size(); 
            return 0;
        }

        // Get number of columns.
        size_t get_j() const
        {
            if (this->get_i() >= 1)
                return (*matrix_ptr)[0].size();
            return 0;
        }

        // Return the vector instance
        std::vector<std::vector<Type>> get() const
        {
            return *this->matrix_ptr;
        }

        std::vector<std::vector<Type>>& get()
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

        std::vector<Type> operator[] (const size_t i) const
        {
            return  (*matrix_ptr)[i];
        }

        std::vector<Type>& operator[](const size_t i)
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
                throw LIAL_DIM_ERRO;
            Matrix result(this->get_i(), this->get_j(), 0);
            for (size_t i = 0; i < this->get_i(); i++)
                for (size_t j = 0; j < this->get_j(); j++)
                    (result)[i][j] = (*this)[i][j] + matrix[i][j];
            return result;
        }

        void operator+=(const Matrix<Type>& matrix)
        {
            if (!this->isSameDimension(matrix))
                throw LIAL_DIM_ERRO;
            for (size_t i = 0; i < this->get_i(); i++)
                for (size_t j = 0; j < this->get_j(); j++)
                    (*this)[i][j] += matrix[i][j];
        }

        Matrix<Type> operator*(const Type scalar) const
        {
            Matrix result(*this);
            for (size_t i = 0; i < this->get_i(); i++)
                for (size_t j = 0; j < this->get_j(); j++)
                    (result)[i][j] *= scalar;
            return result;
        }

        void operator*=(const Type scalar) const
        {
            for (size_t i = 0; i < this->get_i(); i++)
            {
                for (size_t j = 0; j < this->get_j(); j++)
                {
                    (*this)[i][j] *= scalar;
                }
            }
        }

        Matrix<Type> operator-(const Matrix<Type>& matrix) const
        {
            return *this + (matrix * -1);
        }

        void operator-=(const Matrix& matrix) const
        {
            for (size_t i = 0; i < this->get_i(); i++)
            {
                for (size_t j = 0; j < this->get_j(); j++)
                {
                    (*this)[i][j] -= matrix[i][j];
                }
            }
        }

        Matrix operator/(const Type scalar) const
        {
            Matrix result(*this);
            for (size_t i = 0; i < this->get_i(); i++)
                for (size_t j = 0; j < this->get_j(); j++)
                    (result)[i][j] /= scalar;
            return result;
        }

        Matrix operator*(const Matrix& matrix) const
        {
            if (this->get_j() != matrix.get_i())
                throw LIAL_DIM_ERRO;
            Matrix result(this->get_i(), matrix.get_j(), 0);
            for (size_t i = 0; i < matrix.get_i(); i++)
                for (size_t j = 0; j < matrix.get_j(); j++)
                    for (size_t k = 0; k < matrix.get_i(); k++)
                        (result)[i][j] += (*this)[i][k] * matrix[k][j];
            return result;
        }

        void operator*=(const Matrix& matrix)
        {
            if (this->get_j() != matrix.get_i())
                throw LIAL_DIM_ERRO;
            this->copyMatrix(*this * matrix);
        }

        Matrix sub(size_t si, size_t sj) const
        {
            Matrix sub_matrix_ptr(this->get_i()-1, this->get_j()-1, 0);
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
                            (sub_matrix_ptr)[m][n] = (*this)[i][j];
                            n++;
                        }
                    }
                    m++;
                }
            }
            return sub_matrix_ptr;
        }

        #ifndef LIAL_FRACTION
        real det()
        {
            real det_value = 0.0f;
            if (!this->isSquare())
                throw LIAL_NOTSQUARE_MATRIX;
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
            return (this->get_i() == matrix.get_i()) && (this->get_j() == matrix.get_j());
        }

        bool isRevesible() const
        {
            return (this->det() == 0);
        }

        bool isNull() const
        {
            for (auto _it : this->get())
            {
                for (auto it : _it)
                {
                    if (it != 0)
                        return false;
                }
            }
            return true;
        }

        bool isEmpty() const
        {
            return this->get_i() == 0;
        }
    };

} //namespace LIAL

#endif // Matrix.h
