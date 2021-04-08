#ifndef TLIST_H
#define TLIST_H

#include <iostream>

using namespace std;

template<typename T>
class TList
{
public:
    TList();
   ~TList();

    int pop_indexNode(const int index);
    void push_back(T data);
    int edit_node(T data, const int index);
    int getSize() {return Size; }

    T& operator[](const int index);//перегруз. операт. [] для передачи ссылки на элем. через индекс

private:

    template<typename N>
    class Node
    {
    public:
        Node *pNext;
        Node *pPrev;
        N data;

        Node(N data = N()
           , Node *pNext = nullptr
           , Node *pPrev = nullptr)
        {
            this->data = data;
            this->pNext = pNext;
            this->pPrev = pPrev;
        }
    };

    int Size;
    Node<T> *head;
    Node<T> *tail;
};

template<typename T>
TList<T>::TList()
{
    Size = 0;
    head = nullptr;
    tail = head;
}

template<typename T>
TList<T>::~TList()
{

}

//Удаление элемента из списка(программная часть)
template<typename T>
int TList<T>::pop_indexNode(const int index)
{
    if (Size/2 >= index)
    {
        Node<T> *current = head;
        int counter = 0;
        while (current != nullptr)
        {
            if (counter == index && current != head && current != tail)
            {
                Node<T> *temporaryPrev = current->pPrev;
                Node<T> *temporaryNext = current->pNext;
                temporaryPrev->pNext = temporaryNext;
                temporaryNext->pPrev = temporaryPrev;
                delete current;
                Size--;
                return index;
            }
            else if (counter == index && head)
            {
                Node<T> *temporaryNext = current->pNext;
                temporaryNext->pPrev = nullptr;
                head = temporaryNext;
                delete current;
                Size--;
                return index;
            }
            current = current->pNext;
            counter++;
        }
    }
    else
    {
        Node<T> *current = tail;
        int counter = Size-1;
        while (current != nullptr)
        {
            if (counter == index && current != head && current != tail)
            {
                Node<T> *temporaryPrev = current->pPrev;
                Node<T> *temporaryNext = current->pNext;
                temporaryPrev->pNext = temporaryNext;
                temporaryNext->pPrev = temporaryPrev;
                delete current;
                Size--;
                return index;
             }
             else if (counter == index && tail)
             {
                 Node<T> *temporaryPrev = current->pPrev;
                 temporaryPrev->pNext = nullptr;
                 tail = temporaryPrev;
                 delete current;
                 Size--;
                 return index;
              }
            current = current->pPrev;
            counter--;
        }
    }
    return -1;
}

//Добавление элемента в конец списка(программная часть)
template<typename T>
void TList<T>::push_back(T data)
{
    if (head == nullptr && tail == nullptr)
    {
        head = new Node<T>(data);//выделение памяти для первого элемента(головы)
        tail = head;//...(и хвоста)
    }
    else
    {
          Node<T> *current = this->tail;
          current->pNext = new Node<T>(data);//создание нового элемента в конце списка
          tail = current->pNext;//указание хвоста на него
          tail->pPrev = current;//создание ссылки на предыдущий

    }
    Size++;
}

//Редактирование данных(data) элемента списка(программная часть)
template<typename T>
int TList<T>::edit_node(T data, const int index)
{
    Node<T> *current = head;
    int counter = 0;
    while (current != nullptr)
    {
        if (counter == index)
        {
            current->data = data;
            return index;
        }
        current = current->pNext;
        counter++;
    }
}

template<typename T>
T &TList<T>::operator[](const int index) //поиск элемента по индексу
{
    int counter = 0;
    Node<T> *current = this->head; //создание временного указателя *current = head
    while(current != nullptr) //цикл по списку
    {
       if (counter == index)
       {
           return current->data;//возврат данных из нужного элемента
       }
       current = current->pNext;
       counter++;
    }
}

#endif // TLIST_H
