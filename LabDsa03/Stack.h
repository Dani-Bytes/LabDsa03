#pragma once
#include<iostream>
using namespace std;
class Stack {
private:
    int* arr;
    int top;
    int size;
public:
    Stack() {
        size = 100;
        arr = new int[size];
        top = -1;
    }
    bool isfull() {
        return top == size - 1;
    }
    bool isempty() {
        return top == -1;
    }
    void push(int x) {
        if (isfull()) {
            cout << "Stack Overflow" << endl;
            return;
        }
        top++;
        arr[top] = x;
    }
    int pop() {
        if (isempty()) {
            cout << "Stack Underflow" << endl;
            return -1;
        }
        int x = arr[top];
        top--;
        return x;
    }
    int getsize() {
        return top + 1;
    }
    int gettop() {
        if (!isempty()) {
            return arr[top];
        }
        return -1;
    }
};