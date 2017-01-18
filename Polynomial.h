#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "Term.h"
#include <iostream>

/**
 * This class performs various tasks such as reading input from files, sorting the terms, addition, differentiation,
 * and printing the result.
 */
class Polynomial
{
    private:
        Term* headA;    //Head term for polynomial A.
        Term* headB;    //Head term for polynomial B.
        Term* headC;    //Head term for A and B added.
        Term* headDx;   //Head term for the derivative of C.
        Term* headDy;   //Head term for the derivative of C.
        int lengthA;    //Length of polynomial A.
        int lengthB;    //Length of polynomial B.
    
        /**
         * This function creates linked list of unsorted polynomial terms.
         */
        Term* addToList(Term* head, const int cef, const int x, const int y);
    
        /**
         * This function prints the result.
         */
        void print(const Term* ptr);
    
        /**
         * This functin deletes each terms.
         */
        void deleteTerm(Term* &ptr);
    
        /**
         * This function sorts two polynomials using merge sort.
         */
        Term* mergeSort(Term* &head, int size);
    
        /**
         * This function is called by mergeSort in order to merge two lists.
         */
        Term* mergeNow(Term* &left, Term* &right);
        
    public:
    
        /**
         * This is the default constructor. It initializes head pointers.
         */
        Polynomial();
    
        /**
         * This is the deconstructor.
         */
        ~Polynomial();
    
        /**
         * This function reads input from files.
         */
        void readInput();
    
        /**
         * This function prints the result.
         */
        void print();
    
        /**
         * This functin adds two polynomials.
         */
        Term* addition();
    
        /**
         * This function differentiates in terms of X.
         */
        void derivativeX();
    
        /**
         * This function differentiates in terms of Y.
         */
        void derivativeY();
    
        /**
         * This function is called by main() and it, in return, calls the other overloaded mergeSort.
         */
        void mergeSort();
};


#endif  /* POLYNOMIAL_H */







