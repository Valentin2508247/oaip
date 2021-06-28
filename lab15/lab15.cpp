#include <iostream>

using namespace std;

struct Node {
    int value;
    Node* prev;
    Node* next;
};

struct List {
    int size = 0;
    Node* head;
    Node* tail;

    //void add(int value) {
    //    add(value, size);
    //}

    void add(int value) {
        Node* node = new Node();
        node->value = value;
        if (size == 0) {
            head = node;
            tail = node;
        }
        else if (size == 1) {
            head->prev = node;
            node->next = head;
            tail = node;
        }
        else if (size > 1){
            tail->prev = node;
            node->next = tail;
            tail = node;
        }
        size++;
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

    int find(int target) {
        if (size == 0)
            return -1;
        return search(head, target);
    }

    int search(Node* current, int target) {
        if (current->value == target)
            return 0;
        if (current == tail)
            return -1;
        else return 1 + search(current->prev, target);
    }

    void bubleSort() {
        if (size <= 1)
            return;
        for (int i = 0; i < size; i++) {
            doWalk();
        }
    }

    void doWalk() {
        Node* current = head, *next = head->prev;
        for (int i = 0; i < size - 1; i++) {
            if (current->value > next->value) {
                int temp = next->value;
                next->value = current->value;
                current->value = temp;
                current = next;
                next = next->prev;
            }
        }
    }

    void doDeleteElementsBetweenMinMax() {
        if (size <= 2)
            return;
        int min = head->value, min_index = 0;
        int max = head->value, max_index = 0;
        Node* min_node = head;
        Node* max_node = head;
        Node* current = head;
        for (int i = 0; i < size; i++) {
            if (current->value > max) {
                max = current->value;
                max_index = i;
                max_node = current;
            }
            if (current->value < min) {
                min = current->value;
                min_index = i;
                min_node = current;
            }
            current = current->prev;
        }

        if (min_index == max_index)
            return;
        if (min_index < max_index) {
            Node* current = min_node->prev;
            while (current != max_node) {
                Node* next = current->prev;
                delete current;
                current = next;
            }
            min_node->prev = max_node;
            max_node->next = min_node;
            size = size - max_index + min_index + 1;
        }
        else if (min_index > max_index) {
            Node* current = max_node->prev;
            while (current != min_node) {
                Node* next = current->prev;
                delete current;
                current = next;
            }
            max_node->prev = min_node;
            min_node->next = max_node;
            size = size - min_index + max_index + 1;
        }
    }

    void doDelete() {
        if (size == 0) {
            return;
        }
        if (size == 1)
        {
            delete head;
            size = 0;
            return;
        }
        else {
            Node* current = head;
            Node* next;
            while (current != tail) {
                next = current->prev;
                delete current;
                current = next;
            }
            delete tail;
            size = 0;
            return;
        }
    }
};


int main()
{
    List* list = new List();

    list->add(10);
    list->add(2);
    list->add(3);
    list->add(4);
    list->add(5);
    list->add(6);
    list->add(7);

    list->print();
    cout << "Delete elements between min and max\n";
    list->doDeleteElementsBetweenMinMax();
    list->print();
    cout << "Sort linked list\n";
    list->bubleSort();
    list->print();
    cout << "Delete elements between min and max\n";
    list->doDeleteElementsBetweenMinMax();
    list->print();

    int var = 10;
    cout << "Find '" << var << "' element\n";
    int index = list->find(var);
    if (index == -1)
        cout << "Element " << var << " not found";
    else
        cout << "Index: " << index;
    
    list->doDelete();
    delete list;
}