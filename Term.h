#ifndef TERM_H
#define TERM_H

/**
 * This class represents each term of the polynomials.
 */
class Term
{
    /**
     * Make Polynomial class a friend class.
     */
    friend class Polynomial;
    private:
        int coeff;  //Coefficient.
        int degX;   //Exponent on X.
        int degY;   //Exponent on Y.
        Term* next;     //Link to the next term.
};

#endif /* TERM_H */
