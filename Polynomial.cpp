#include "Polynomial.h"
#include <fstream>

using std::cout;
using std::endl;
using std::cin;


Polynomial::Polynomial()
{
    headA = nullptr;    
    headB = nullptr;
    headC = nullptr;
    headDx = nullptr;
    headDy = nullptr;
    lengthA = 0;   
    lengthB = 0;

}

Polynomial::~Polynomial()
{
    deleteTerm(headA);     
    deleteTerm(headB);
    deleteTerm(headC);
    deleteTerm(headDx);
    deleteTerm(headDy);
    delete headA;     
    delete headB;
    delete headC;
    delete headDx;
    delete headDy;
}

void Polynomial::readInput()
{
    int numTerms, cef, x, y; 
    std::string fileName;  
    cout << "File names are data1.txt, data2.txt, ... data5.txt\nPlease choose a file name: ";
    cin >> fileName;
    std::ifstream fin;
    fin.open(fileName.c_str()); 
    
    while (!fin)    
    {
        fin.clear();
        cout << "could not find the file \"" << fileName << "\"...\nEnter a file name again: ";
        cin >> fileName;
        fin.open(fileName.c_str());
    }
    cout << endl;
    fin >> numTerms;
    for (int i = 0; i < numTerms; i++) 
    {
        fin >> cef >> x >> y;
        headA = addToList(headA, cef, x, y);
        lengthA++;  //Increment the length of list.
    }
    fin >> numTerms;
    for (int j = 0; j < numTerms; j++) 
    {
        fin >> cef >> x >> y;
        headB = addToList(headB, cef, x, y);
        lengthB++;  
    }
    fin.close();
}

Term* Polynomial::addToList(Term* head, const int cef, const int x, const int y)
{
    Term* newTerm = new Term;   
    newTerm->coeff = cef;
    newTerm->degX = x;
    newTerm->degY = y;
    newTerm->next = nullptr;
    
    if (head == nullptr) 
    {
        head = newTerm;
    }
    else
    {
        newTerm->next = head;  
        head = newTerm;
    }
    return head;
}

void Polynomial::mergeSort()  
{
    headA = mergeSort(headA, lengthA); 
    headB = mergeSort(headB, lengthB);
}

Term* Polynomial::mergeSort(Term* &head, int size)
{
    if (size < 2)  
    {
        return head;
    }
    int mid = size / 2;   
    Term* temp;
    Term* left = head; 
    temp = left;
    for (int i = 0; i < mid - 1; i++)
    {
        temp = temp->next;  
    }
    Term* right = temp->next;   
    temp->next = nullptr;   
    
    mergeSort(left, mid); 
    mergeSort(right, size - mid);
    head = mergeNow(left, right);   
    return head;
}

Term* Polynomial::mergeNow(Term* &left, Term* &right)
{
    Term* temp = nullptr;   
    
    if (left == nullptr)
    {
        return right;   
    }
    if (right == nullptr)
    {
        return left;   
    }
    if (left->degX > right->degX)   
    {
        temp = left;    //temp points to the left term.
        temp->next = mergeNow(left->next, right);  
    }
    else if (left->degX < right->degX) 
    {
        temp = right;   //temp points to the right term.
        temp->next = mergeNow(right->next, left);  
    }
    else
    {
        if (left->degY > right->degY)  
        {
            temp = left;    //temp points to the left term.
            temp->next = mergeNow(left->next, right);   
        }
        else
        {
            temp = right;   //temp points to the right term.
            temp->next = mergeNow(right->next, left); 
        }
    }
    return temp;   
}

Term* Polynomial::addition()
{
    if (headA == nullptr && headB == nullptr)  
    {
        return nullptr;
    }
    if (headA == nullptr)  
    {
        return headB;
    }
    if (headB == nullptr)  
    {
        return headA;
    }
    Term* A = headA;
    Term* B = headB;
    headC = new Term;  
    Term* C = headC;   
    while(A != nullptr && B != nullptr)
    {
        if (C != nullptr)
        {
            C->next = new Term;
            C = C->next;
        }
        if (A->degX == B->degX)
        {
            if (A->degY == B->degY)
            {
                if (A->coeff + B->coeff != 0) 
                {
                    C->coeff = A->coeff + B->coeff; 
                    C->degX = A->degX;  
                    C->degY = A->degY;
                    C->next = nullptr;  
                    A = A->next;   
                    B = B->next;
                }
                else
                {
                    A = A->next;    
                    B = B->next;
                    continue;
                }
            }
            else if (A->degY > B->degY) 
            {
                C->coeff = A->coeff;   
                C->degX = A->degX;
                C->degY = A->degY;
                C->next = nullptr;
                A = A->next;  
            }
            else    //B's Y exponent is larger.
            {
                C->coeff = B->coeff;   
                C->degX = B->degX;
                C->degY = B->degY;
                C->next = nullptr;
                B = B->next;   
            }
        }
        else if (A->degX > B->degX) 
        {
            C->coeff = A->coeff;
            C->degX = A->degX;
            C->degY = A->degY;
            C->next = nullptr;
            A = A->next;
        }
        else   
        {
            C->coeff = B->coeff;
            C->degX = B->degX;
            C->degY = B->degY;
            C->next = nullptr;
            B = B->next;
        }
    }
    if (A == nullptr && B == nullptr)  
    {
        return headC;   
    }
    Term* temp; 
    if (A == nullptr)
    {
        temp = B;  
    }
    else if (B == nullptr)
    {
        temp = A;  
    }
    while (temp != nullptr) 
    {
        C->next = new Term;
        C = C->next;
        C->coeff = temp->coeff; 
        C->degX = temp->degX;
        C->degY = temp->degY;
        C->next = nullptr;
        temp = temp->next;
    }
    return headC;
}

void Polynomial::derivativeX() 
{
    if (headC == nullptr)
    {
        return;   
    }
    Term* C = headC;   
    headDx = new Term;  
    Term* D = headDx;   
    while(C != nullptr)
    {
        if (C != headC) 
        {
            D->next = new Term;
            D = D->next;
        }
        D->coeff = C->coeff * C->degX;
        D->degX = C->degX - 1; 
        D->degY = C->degY; 
        D->next = nullptr;
        C = C->next;   
    }
}

void Polynomial::derivativeY() 
{
    if (headC == nullptr)
    {
        return; //Empty list returned.
    }
    Term* C = headC;   
    headDy = new Term; 
    Term* D = headDy;  
    while(C != nullptr)
    {
        if (C != headC) 
        {
            D->next = new Term;
            D = D->next;
        }
        D->coeff = C->coeff * C->degY;  
        D->degY = C->degY - 1;  
        D->degX = C->degX; 
        D->next = nullptr;
        C = C->next;   
    }
}

void Polynomial::print(const Term* ptr)
{ 
    if (ptr == nullptr)
    {
       cout << "\nThe list is empty" << endl;
       return;
    }
    else
    {
        while (ptr != nullptr) 
        {
            if (ptr->coeff > 0)
            {
                cout << " + " << ptr->coeff;
            }
            else if (ptr->coeff == 0) 
            {
                cout << "";
                ptr = ptr->next;
                continue;
            }
            else   
            {
                cout << " " << ptr->coeff;
            }
            if (ptr->degX != 0) 
            {
                cout << "x^" << ptr->degX;
            }
            if (ptr->degY != 0) 
            {
                cout << "y^" << ptr->degY;
            }
            ptr = ptr->next; 
        }
    }
    cout << endl;
}

void Polynomial::print()
{
    cout << "Polynomial A is: ";
    print(headA);
    cout << endl;
    cout << "Polynomial B is: ";
    print(headB);
    cout << endl;
    cout << "C after adding A and B is: ";
    print(headC);
    cout << endl;
    cout << "Derivative of C with respect to X is: ";
    print(headDx);
    cout << endl;
    cout << "Derivative of C with respect to Y is: ";
    print(headDy);
    cout << endl;
}

void Polynomial::deleteTerm(Term* &ptr)
{
    while (ptr != nullptr)  //Deletes all the terms.
    {
        Term* deleteMe = ptr;
        ptr = ptr->next;
        delete deleteMe;
    }
}
























