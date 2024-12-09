#include <iostream>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node* next;
    Node(T val) : data(val), next(nullptr) {}
};

template <typename T>
class Queue {
private:
    Node<T>* first;
    Node<T>* last;

public:
    Queue() : first(nullptr), last(nullptr) {}

    void push(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (last == nullptr) {
            first = last = newNode;
        }
        else {
            last->next = newNode;
            last = newNode;
        }
    }

    int front()
    {
        if (first != nullptr)
        {
            return first->data;
        }
    }

    void pop() {
        if (first == nullptr) {
            return;
        }
        Node<T>* temp = first;
        first = first->next;
        if (first == nullptr) {
            last = nullptr;
        }

        delete temp;
    }
    void print(){
        if (first == nullptr) {
            return;
        }
        Node<T>* temp = first;
        cout << "El: ";
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    bool is_empty(){ return first == nullptr; }
};