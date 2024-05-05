/*
    Clemens Dehnert
    SN: s85492
    MN: 53041
 */
#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

template<class T>
class Node {
public:
    Node();
    Node(T* Obj);
    Node<T>* getpPrev();
    Node<T>* getpNext();
    T* getpObj();
    void setpPrev(Node<T>* pPrev);
    void setpNext(Node<T>* pNext);
    void setpObj(T* Obj);

private:
    Node<T>* pPrev;
    Node<T>* pNext;
    T* pObj;
};

/*Konstruktoren*/
template<class T>
Node<T>::Node(){
    this->pPrev = NULL;
    this->pNext = NULL;
    this->pObj = NULL;
}

template<class T>
Node<T>::Node(T* Obj){
    this->pPrev = NULL;
    this->pNext = NULL;
    this->pObj = Obj;
}

/*Getter*/
template<class T>
Node<T>* Node<T>::getpPrev() {
    return this->pPrev;
}

template<class T>
Node<T>* Node<T>::getpNext() {
    return this->pNext;
}

template<class T>
T* Node<T>::getpObj() {
    return this->pObj;
}

/*Setter*/
template<class T>
void Node<T>::setpPrev(Node<T>* pPrev) {
    this->pPrev = pPrev;
}

template<class T>
void Node<T>::setpNext(Node<T>* pNext) {
    this->pNext = pNext;
}

template<class T>
void Node<T>::setpObj(T* Obj) {
    this->pObj = Obj;
}

#endif
