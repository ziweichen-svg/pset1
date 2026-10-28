#include <cassert>
#include <iostream>
#include <cmath>
using std::cout;
using std::endl;

/**
 * This struct describes a term in a polynomial with a link to
 * the next term. Note that the head of the polynomial shall be
 * the term with the highest exponent and each term will point
 * to a term with a lower exponent. 
 */
struct Node
{
    int coeff;
    int exp;
    Node* next;
    Node(int c, int e)
    {
        coeff = c;
        exp = e;
        next = nullptr;
    }
};

// Evaluate polynomial given by head for the given x
double eval(Node* head, double x)
{
    // YOUR CODE HERE
    double result = 0.0;
    Node* curr = head;
    while (curr){
        result += curr->coeff*pow(x, curr->exp);
        curr = curr->next;
    }
    return result;
}

// Adds the two polynomials given by head1 and head2 and returns
// the head of the resulting polynomial
Node* addPolynomials(Node* head1, Node* head2)
{
    // YOUR CODE HERE
    Node* result=nullptr;
    Node* curr=nullptr;
    while(head1&&head2){
        Node* NewNode=nullptr;
        if(head1->exp>head2->exp){
            NewNode=new Node(head1->coeff,head1->exp);
            head1=head1->next;
        }else if(head1->exp<head2->exp){
            NewNode=new Node(head2->coeff,head2->exp);
            head2=head2->next;
        }else{
            NewNode=new Node(head1->coeff+head2->coeff,head1->exp);
            head1=head1->next;
            head2=head2->next;
        }
        if(result==nullptr){
            result=NewNode;
            curr=result;
        }else{
            curr->next=NewNode;
            curr=curr->next;
        }
    }
    while(head1){
        Node* NewNode=new Node(head1->coeff,head1->exp);
        curr->next=NewNode;
        curr=curr->next;
        head1=head1->next;
    }
    while(head2){
        Node* NewNode=new Node(head2->coeff,head2->exp);
        curr->next=NewNode;
        curr=curr->next;
        head2=head2->next;
    }
    return result;
}

void del(Node* head){
    Node* toDel=head;
    while(head){
        head=head->next;
        delete toDel;
        toDel=head;
    }
}

int main()
{
    // Example test - write at least 5 unique cases of your own!

    // p1 represents 3x^2 - 5x + 7
    Node* p1 = new Node(3, 2);
    p1->next = new Node(-5, 1);
    p1->next->next = new Node(7, 0);

    // p2 represents 6x - 3
    Node* p2 = new Node(6, 1);
    p2->next = new Node(-3, 0);

    // recall that floating point arithmetic can be finicky! 
    double epsilon = .00001;
    assert(abs(eval(p1, 2.0) - 9.0) < epsilon);

    // p3 should be 3x^2 + x + 4
    Node* p3 = addPolynomials(p1, p2);
    assert(p3->coeff == 3 && p3->exp == 2);
    assert(p3->next->coeff == 1 && p3->next->exp == 1);
    assert(p3->next->next->coeff == 4 && p3->next->next->exp == 0);
    cout<<"test success"<<endl;
    // can we do this better?
    del(p1);
    del(p2);
    del(p3);
    cout<<"sucs";
    /*
    delete p1->next->next;
    delete p1->next;
    delete p1;
    delete p2->next;
    delete p2;
    delete p3->next->next;
    delete p3->next;
    delete p3;
    */
}

