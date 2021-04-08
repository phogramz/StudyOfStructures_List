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

    T& operator[](const int index);//��������. ������. [] ��� �������� ������ �� ����. ����� ������

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

//�������� �������� �� ������(����������� �����)
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

//���������� �������� � ����� ������(����������� �����)
template<typename T>
void TList<T>::push_back(T data)
{
    if (head == nullptr && tail == nullptr)
    {
        head = new Node<T>(data);//��������� ������ ��� ������� ��������(������)
        tail = head;//...(� ������)
    }
    else
    {
          Node<T> *current = this->tail;
          current->pNext = new Node<T>(data);//�������� ������ �������� � ����� ������
          tail = current->pNext;//�������� ������ �� ����
          tail->pPrev = current;//�������� ������ �� ����������

    }
    Size++;
}

//�������������� ������(data) �������� ������(����������� �����)
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
T &TList<T>::operator[](const int index) //����� �������� �� �������
{
    int counter = 0;
    Node<T> *current = this->head; //�������� ���������� ��������� *current = head
    while(current != nullptr) //���� �� ������
    {
       if (counter == index)
       {
           return current->data;//������� ������ �� ������� ��������
       }
       current = current->pNext;
       counter++;
    }
}

#endif // TLIST_H
