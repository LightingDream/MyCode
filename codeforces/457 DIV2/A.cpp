#include <bits/stdc++.h>
using namespace std;

template<class T>
class ElemType{
public:
    ElemType(){
        next = NULL;
    }
    ElemType(T data):data(data){
        next = NULL;
    }
    void setNext(ElemType<T> * elem){
        next = elem;
    }
    ElemType<T> * getNext(){
        return next;
    }
    T getData(){
        return data;
    }
private:
    T data;
    ElemType<T> * next;
};


template<class T>
class Stack{
public:
    Stack(){
        head = new ElemType<T>();
        len = 0;
    }
    int size(){
        return len;
    }
    void push(T data){
        ElemType<T> * elem = new ElemType<T>(data);
        elem->setNext(head->getNext());
        head->setNext(elem);
        ++len;
    }
    void pop(){
        head->setNext(head->getNext()->getNext());
        --len;
    }
    bool isEmpty(){
        return size() == 0;
    }
    T top(){
        return head->getNext()->getData();
    }
private:
    ElemType<T> * head;
    int len;
};

using namespace std;

class Matrix{
public:
    //int mat[2][2];
    int row;
    int col;
    Matrix(){
        row = 2;
        col = 2;
        //memset(mat, 0, sizeof mat);
    }
    Matrix operator * (const Matrix &rhs) const{
        Matrix res = {row, rhs.col};
    }
};

int main(){
    Stack<char> sta;
    sta.push(48);
    sta.push(49);
    while(!sta.isEmpty()){
        cout << sta.top() << endl;
        sta.pop();
    }
    return 0;
}
