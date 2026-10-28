#include <string>
#include <cassert>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

class BrowserHistory 
{

private:
    /**
     * Create a struct Node containing a url and pointers to the next
     * and previous Nodes. 
     * 
     * Create instance variables for any Nodes that we need to keep
     * track of
     */
     // YOUR CODE HERE
    struct Node{
        string url;
        Node* prev;
        Node* next;
        Node(string str){
            url=str;
            next=nullptr;
            prev=nullptr;
        }
     };
     Node* curr;
     Node* head;

public:
    /**
     * Constructor
     * 
     * Initialize instance variables with homepage
     */
    BrowserHistory(string str) 
    {
        // YOUR CODE HERE
        head=new Node(str);
        curr=head;
    }
    /**
     * Destructor
     * 
     * Called when deleting object - should free up any remaining
     * dynamically allocated memory referenced by the object
     */
    ~BrowserHistory()
    {
        // YOUR CODE HERE
        curr=head;
        Node* temp;
        if(curr->next)temp=curr->next;
        if(!curr->next){
            delete curr;
            return;
        }
        while(curr){
            delete curr;
            if(temp){
                curr=temp;
                temp=temp->next;
            }
        }
    }
    
    /**
     * Goes to url from the current page and clears all forward history
     */
    void visit(string str) 
    {
        // YOUR CODE HERE
        Node* del = curr->next;
        Node* nextNode;
        while (del) {
            nextNode = del->next;
            delete del;
            del = nextNode;
        }
        Node* newNode = new Node(str);
        newNode->prev = curr;
        curr->next = newNode;
        curr = newNode;
    }
    
    /** 
     * Move steps back in history. If you can only move back x steps 
     * in the history and steps > x, you will move back only x steps. 
     * Return the current url after moving back in history at most 
     * steps times.
     */ 
    string back(int steps) 
    {
        // YOUR CODE HERE
        for(int i=0;i<steps;i++){
            if(curr==head)return head->url;
            curr=curr->prev;
        }
        return curr->url;
    }

    /** 
    * Move steps forward in history. If you can only forward x steps in
    * the history and steps > x, you will forward only x steps. Return
    * the current url after forwarding in history at most steps.
    */ 
    string forward(int steps) 
    {
        // YOUR CODE HERE
        for(int i=0;i<steps;i++){
            if(curr->next==nullptr)return curr->url;
            curr=curr->next;
        }
        return curr->url;
    }
};
int main()
{
    // Example test - write at least 5 unique cases of your own!
    BrowserHistory* bh = new BrowserHistory("google.com"); // start at google
    bh->visit("amazon.com"); // go to amazon (google 1 back in history)
    bh->visit("wikipedia.com"); // go to wikipedia (google 2 back in history)
    bh->visit("cppreference.com"); // go to cppreference (google 3 back in history)
    assert(bh->back(2) == "amazon.com"); // go back 2, should be at amazon
    assert(bh->forward(1) == "wikipedia.com"); // go forward 1, should be at wikipedia
    assert(bh->forward(1) == "cppreference.com");
    assert(bh->forward(1) == "cppreference.com");
    assert(bh->back(3) == "google.com");
    assert(bh->back(1) == "google.com");
    assert(bh->forward(2) == "wikipedia.com");
    cout << "Tests passed" << endl;

    
}
