/*
    Clemens Dehnert
    SN: s85492
    MN: 53041
 */
#ifndef LIST_H
#define LIST_H

#include <iostream>
using namespace std;
#include "List.h"
#include "Node.h"

template<class T>
class List {
public:
    List();
    void addToList(T* Obj);
    void removeFromList(int index);
    T* getFromList(int index);
    int getSize();
    void swapWithNext(int index);

private:
    Node<T> listHead;
    Node<T>* pFirst;
    Node<T>* pLast;
    Node<T>* pCurr;
    int setCurr(int index);
    int size;
};

/*Initialisierung*/
template<class T>
List<T>::List() {
    this->pFirst = &listHead;
    this->pLast = &listHead;
    this->pCurr = &listHead;
    listHead.setpPrev(NULL);
    listHead.setpNext(NULL);
    listHead.setpObj(NULL);
    this->size = 0;
}

/*Iteriere Curr nach Index*/
template<class T>
int List<T>::setCurr(int index) {
    this->pCurr = this->pFirst;
    if (index > size) {
        return 0;
    }
    for (int i = 0; i < index; i++) {
        this->pCurr = this->pCurr->getpNext();
    }
    return 1;
}

/*Füge Element am Listenende hinzu*/
template<class T>
void List<T>::addToList(T* Obj) {
    Node<T>* node = new Node<T>(Obj);
    this->pCurr = node;

    if (size == 0) {
        //Listenkopf
        this->pFirst = node;
        this->pLast = node;
        //Neues Element
        node->setpPrev(&listHead);
        node->setpNext(&listHead);
        //Vorgänger / Nachfolger
        listHead.setpPrev(node);
        listHead.setpNext(node);
    }else{
        //Neues Element
        node->setpPrev(pLast);
        node->setpNext(&listHead);
        //Vorgänger
        pLast->setpNext(node);
        //Nachfolger
        listHead.setpPrev(node);
        //Listenkopf
        this->pLast = node;
    }
    this->size++;

    return;
}

/*Entferne Listenelement nach Index*/
template<class T>
void List<T>::removeFromList(int index) {
    if (setCurr(index) == 1) {
        if(pFirst == pCurr){
            //Listenkopf
            pFirst = pCurr->getpNext();
        }
        if(pLast == pCurr){
            //Listenkopf
            pLast = pCurr->getpPrev();
        }
        this->pCurr->getpPrev()->setpNext(this->pCurr->getpNext());
        this->pCurr->getpNext()->setpPrev(this->pCurr->getpPrev());
        delete this->pCurr;
        this->pCurr = this->pFirst;
        size--;
    }
    else {
        cout << "Indexüberschreitung beim Löschen" << endl;
    }

    return;
}

/*Gebe Objekt an Listenstelle zurück*/
template<class T>
T* List<T>::getFromList(int index) {
    if (setCurr(index) == 1) {
        return this->pCurr->getpObj();
    }
    cout << "Indexüberschreitung beim Abfragen" << endl;
    return NULL;
}

template<class T>
int List<T>::getSize() {
    return this->size;
}

/*Tausche Listenelement (für Bubblesort)*/
template<class T>
void List<T>::swapWithNext(int index) {
    if(setCurr(index) == 1 && size > 1){
        Node<T>* Aktuell = pCurr;
        Node<T>* Nachfolger = Aktuell->getpNext();

        if(Nachfolger == &listHead){
                T* temp = Aktuell->getpObj();
                Aktuell->setpObj(pFirst->getpObj());
                pFirst->setpObj(temp);
        }else{
                T* temp = Aktuell->getpObj();
                Aktuell->setpObj(Nachfolger->getpObj());
                Nachfolger->setpObj(temp);
        }

    }
}

#endif
