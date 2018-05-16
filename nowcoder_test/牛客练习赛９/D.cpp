#include <bits/stdc++.h>
using namespace std;

template<class T>
class ElemType{
public:
    ElemType(){
        this->next = NULL;
    }
    ElemType(T data){
        this->data = data;
        this->next = NULL;
    }
    void setNext(ElemType<T> * item){
        next = item;
    }
    ElemType * getNext(){
        return next;
    }
    T getData(){
        return data;
    }
private:
    T data;
    ElemType * next;
};

template<class T>
class Stack{
public:
    Stack(){
        head = new ElemType<T>();
        len = 0;
    }
    bool isEmpty(){
        return len == 0;
    }
    T top(){
        return head->getNext()->getData();
    }
    void pop(){
        head->setNext(head->getNext()->getNext());
        --len;
    }
    void push(T data){
        ElemType<T> * tmp = new ElemType<T>(data);
        tmp->setNext(head->getNext());
        head->setNext(tmp);
        ++len;
    }
private:
    ElemType<T> * head;
    int len;
};

template<class T>
class Queue{
public:
    Queue(){
        front = new ElemType<T>();
        rear = front;
        len = 0;
    }
    bool isEmpty(){
        return len == 0;
    }
    T top(){
        return front->getNext()->getData();
    }
    void pop(){
        front->setNext(front->getNext()->getNext());
        if(front->getNext() == NULL) rear = front;
        --len;
    }
    void push(T data){
        ElemType<T> * tmp = new ElemType<T>(data);
        rear->setNext(tmp);
        rear = tmp;
        ++len;
    }
private:
    ElemType<T> * front;
    ElemType<T> * rear;
    int len;
};

int main(){
    Queue<int> que;
    que.push(1);
    que.push(2);
    while(!que.isEmpty()){
        cout << que.top() << endl;
        que.pop();
    }
    return 0;
}
