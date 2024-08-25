#pragma once

template <typename Q>
class Node {
public:
    Node* next;
    Q value;
    Node(Q val) : value(val), next(nullptr) {}
};

template <typename L>
class Queue {
    Node<L>* head;
    Node<L>* tail;

public:
    Queue() : head(nullptr), tail(nullptr) {}
    ~Queue() {
        while (head) {
            Node<L>* temp = head;
            head = head->next;
            delete temp;
        }
    }
    Queue(const Queue& other) : head(nullptr), tail(nullptr) {
        for (Node<L>* temp = other.head; temp; temp = temp->next) {
            push(temp->value);
        }
    }

    void push(L value) {
        if (!head) {
            head = new Node<L>(value);
            tail = head;
        }
        else {
            tail->next = new Node<L>(value);
            tail = tail->next;
        }
    }

    void pop() {
        if (!head) {
            return;
        }
        else {
            Node<L>* temp = head;
            head = head->next;
            delete temp;
            temp = nullptr;
        }
    }
    bool empty() {
        return head == NULL;
    }
    L back() {
        if (!head) {
            return L();
        }
        else {
            return tail->value;
        }
    }

    L front() {
        if (!head) {
            return L();
        }
        else {
            return head->value;
        }
    }

    void print() {
        if (!head) {
            return;
        }
        for (Node<L>* temp = head; temp != nullptr; temp = temp->next) {
            cout << temp->value << " ";
        }
    }
};



template <class T1, class T2>
struct Pair {
    
    T1 first;   
    T2 second;  

    Pair() : first(T1()), second(T2()) {}
    Pair(const T1& x, const T2& y) : first(x), second(y) {}

};


template <class T1, class T2>
Pair<typename decay<T1>::type, typename decay<T2>::type> make_Pair(T1&& x, T2&& y) {
    return Pair<typename decay<T1>::type, typename decay<T2>::type>(forward<T1>(x), forward<T2>(y));
}



    