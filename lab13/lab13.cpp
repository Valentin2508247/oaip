#include <iostream>
#include <stack>

using namespace std;

struct Node {
    double value;
    Node* prev;
};

struct Stack {
    Node* head;
    int size = 0;

    Node* pop() {
        if (size == 0)
        {
            return NULL;
        }
        Node* result = head;
        head = head->prev;
        size--;
        return result;
    }

    void push(double value) {
        if (size == 0) {
            head = new Node();
            head->value = value;
        }
        else {
            Node* node = new Node();
            node->value = value;
            node->prev = head;
            head = node;
        }
        size++;
    }
};



int main()
{
    Stack* st = new Stack();
    Stack* st2 = new Stack();
    st->push(1.);
    st->push(2.);
    st->push(3.);
    st->push(49.);


    // count average
    double sum = 0, average, n = st->size;
    int count = 0;
    while (st->size > 0) {
        Node* node = st->pop();
        double value = node->value;
        sum += value;
        st2->push(value);
        delete node;
    }
    average = sum / n;

    // count count
    while (st2->size > 0)
    {
        Node* node = st2->pop();
        if (node->value < average)
            count++;
        delete node;
    }
    cout << "There're " << count << " element(s) less than average";
    
    // delete stacks
    delete st;
    delete st2;
}