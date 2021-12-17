﻿#include <iostream>
#include <string>
#include <utility>
#include <queue>
#include <deque>

using namespace std;

class deq {
private:
    struct Comp {
        int data;
        Comp *next;
        Comp *prev;
    };
    Comp *top = 0;
    Comp *front = 0;
    int size = 0;
public:
    deq();
    ~deq();
    int datafront() {
        return front->data;
    }
    void push_front(int n) {
        Comp *el = new Comp();
        el->data = n;
        if (front == 0) {
            front = el;
            top = el;
            el->next = 0;
            el->prev = 0;
        }
        else {
            front->prev = el;
            el->next = front;
            front = el;
            el->prev = 0;
        }
        size++;
    }
    int len() {
        return size;
    }
    void push_back(int n) {
        Comp *el = new Comp();
        el->data = n;
        if (top == 0) {
            top = el;
            front = el;
            el->prev = 0;
            el->next = 0;
        }
        else {
            top->next = el;
            el->prev = top;
            top = el;
            el->next = 0;
        }
        size++;
    }
    void pop_front() {
        if (size == 1) top = 0;
        Comp *del = front;
        front = front->next;
        delete del;
        size--;
    }
    void pop_back() {
        if (size == 1) front = 0;
        Comp *del = top;
        top = top->prev;
        delete del;
        size--;
    }
};

deq::~deq() {
    while (size != 0) pop_back();
}

deq::deq() {
    Comp *top = 0;
    Comp *front = 0;
    int size = 0;
}

int main() {
    auto *first = new deq();
    auto *second = new deq();
    char s;
    int n, x;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> s;
        if ((s == '+') or (s == '*')) {
            cin >> x;
            if (s == '+') second->push_back(x);
            else second->push_front(x);
        }
        if (s == '-') std::cout << first->datafront() << '\n', first->pop_front();
        if (second->len() > first->len()) first->push_back(second->datafront()), second->pop_front();
    }
    delete first;
    delete second;
    return 0;
}
