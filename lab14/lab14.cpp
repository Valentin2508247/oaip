#include <iostream>

using namespace std;

struct Node {
public:
    int value;
    Node* prev;
};

struct Queue {
public:
    int size = 0;
    Node* head;
    Node* tail;


    void enqueue(int value) {
        Node* node = new Node();
        node->value = value;

        if (size == 0) {
            tail = node;
            head = node;
            size++;
            return;
        }
        else if (size == 1)
        {
            head->prev = node;
            tail = node;
            size++;
            return;
        }
        else if (size > 1) {
            tail->prev = node;
            tail = node;
            size++;
            return;
        }
    }

    Node* dequeue() {
        if (size == 0) {
            return NULL;
        }
        else if (size == 1)
        {
            Node* result = head;
            head = NULL;
            tail = NULL;
            size--;
            return result;
        }
        else if (size > 1) {
            Node* result = head;
            head = head->prev;
            size--;
            return result;
        }
    }

    void print() {
        if (size == 0)
            return;
        
        Node* current = head;
        cout << "start ";
        while (true) {
            cout << current->value << " ";
            current = current->prev;
            if (current == tail) {
                cout << current->value << " end\n";
                return;
            }
        }
    }
};

void swapTailHead(Queue* queue) {
    int temp = queue->tail->value;
    queue->tail->value = queue->head->value;
    queue->head->value = temp;
}

int main()
{
    Queue* queue = new Queue();
    queue->enqueue(1);
    queue->enqueue(2);
    queue->enqueue(3);
    queue->enqueue(4);
    queue->enqueue(5);
    queue->enqueue(6);

    queue->print();
    swapTailHead(queue);
    queue->print();

    //cout << queue->dequeue()->value << endl;
    //cout << queue->dequeue()->value << endl;
    //cout << queue->dequeue()->value << endl;
    //cout << queue->dequeue()->value << endl;
    //cout << queue->dequeue()->value << endl;
    //cout << queue->dequeue()->value << endl;

    while (queue->size > 0) {
        delete queue->dequeue();
    }
    delete queue;
}