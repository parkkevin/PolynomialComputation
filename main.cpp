#include "Polynomial.h"


int main()
{
    Polynomial polynomial;
    
    polynomial.readInput();
    polynomial.mergeSort();
    polynomial.addition();
    polynomial.derivativeX();
    polynomial.derivativeY();
    polynomial.print();
    
    return 0;
}