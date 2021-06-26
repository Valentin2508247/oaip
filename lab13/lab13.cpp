#include <iostream>
#include <stack>

using namespace std;
int main()
{
    // init stack
    stack<double>* st = new stack<double>();
    stack<double>* st2 = new stack<double>();
    st->push(-29);
    st->push(1);
    st->push(2);
    st->push(3);
    st->push(4);
    st->push(5);
    st->push(1);
    st->push(-37);
    st->push(1);

    // count average
    double sum = 0, average, n = st->size();
    int count = 0;
    while (!st->empty()) {
        double value = st->top();
        sum += value;
        st->pop();
        st2->push(value);
    }
    average = sum / n;

    // count count
    while (!st2->empty())
    {
        double value = st2->top();
        st2->pop();
        if (value < average)
            count++;
    }
    cout << "There're " << count << " element(s) less than average";

    // delete stack
    delete st;
    delete st2;
}