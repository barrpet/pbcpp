#ifndef PB_LINKED_LIST_HPP
#define PB_LINKED_LIST_HPP

#include <iostream>
#include <cstddef>
#include <vector>

template <typename T>
class LinkedList
{
  private:
    class Node
    {
      public:
        T         data;
        Node*     next;
        Node*     prev;

        Node() : next(NULL), prev(NULL) { }
        Node(const T& value) : data(value), next(NULL), prev(NULL) { }
    };
    
    private:
        Node*       _head;
        Node*       _tail;
        size_t      _size;
    
    public:
        LinkedList() : _head(NULL), _tail(NULL), _size(0) { }
        LinkedList(const LinkedList<T>&);

        size_t size() { return this->_size; }
        bool isEmpty() { return this->_size == 0; }
        
        void insertFront(const T&); //done
        void insertBack(const T&);  //done
        
        void clear();   //done
        
        T& popFront();  //done
        T& popBack();   //done

        T& peekFront() { return this->_head->data; }
        T& peekBack() { return this->_tail->data; }

        bool removeFront(); //done
        bool removeBack();  //done

        bool removeFirstOccurrence(const T&);   //done
        bool removeLastOccurrence(const T&);    //done

        T getAt(size_t);
        
        bool contains(const T&) //done

        std::vector<T> toVector();
        
        void printList();
        
        friend std::ostream& operator<<(std::ostream& out, const LinkedList<T>& list);
};

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& toCopy)
{
    if(this == &toCopy) { return; }
    
    if(toCopy.isEmpty())
    {
        this->_head = NULL;
        this->_tail = NULL;
        this->_size = 0;
        return;
    }

    //TODO: copy the linked list
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    this->clear();
}

template <typename T>
void LinkedList<T>::insertFront(const T& value)
{
    Node* newNode = new Node(value);
    if(this->isEmpty())
    {
        this->_head = newNode;
        this->_tail = newNode;
    }
    else
    {
        newNode->next = this->_head;
        this->_head->prev = newNode;
        this->_head = newNode;
    }
    this->_size++;
}

template <typename T>
void LinkedList<T>::insertBack(const T& value)
{
    Node* newNode = new Node(value);
    if(this->isEmpty())
    {
        this->_head = newNode;
        this->_tail = newNode;
    }
    else
    {
        newNode->prev = this->_tail;
        this->_tail->next = newNode;
        this->_tail = newNode;
    }
    this->_size++;
}

template <typename T>
void LinkedList<T>::clear()
{
    Node* current = this->_head;
    Node* temp = this->_head;
    
    while(current != NULL)
    {
        temp = current->next;
        delete current;
        current = temp;
    }
    
    this->_head = NULL;
    this->_tail = NULL;
    this->_size = 0;
}

template <typename T>
void LinkedList<T>::contains(const T& value)
{
    Node* current = this->_head;
    while(current != NULL)
    {
        if(current->data == value)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

template <typename T>
bool LinkedList<T>::removeFront()
{
    if(this->isEmpty()) { return false; }
    if(this->_size == 1)
    {
        this->clear();
        return true;
    }

    Node* oldFront = this->_head;
    Node* newFront = this->_head->next;
    newFront->prev = NULL;
    this->_head = newFront;
    delete oldFront;
    this->_size--;
    return true;
}

template <typename T>
bool LinkedList<T>::removeBack()
{
    if(this->isEmpty()) { return false; }
    if(this->_size == 1)
    {
        this->clear();
        return true;
    }

    Node* oldBack = this->_tail;
    Node* newBack = this->_tail->prev;
    newBack->next = NULL;
    this->_tail = newBack;
    delete oldBack;
    this->_size--;
    return true;
}

template <typename T>
bool LinkedList<T>::removeFirstOccurrence(const T& value)
{
    if(this->isEmpty()) { return false; }

    Node* current = this->_head;
    while(current != NULL)
    {
        if(current->data == value)
        {
            if(current == this->_head)
            {
                return this->removeFront();
            }
            else if(current == this->_tail)
            {
                return this->removeBack();
            }
            else
            {
                Node* cur_next = current->next;
                Node* cur_prev = current->prev;
                cur_prev->next = cur_next;
                cur_next->prev = cur_prev;
                delete current;
                this->_size--;
                return true;
            }
        }
        current = current->next;
    }
    return false;
}

template <typename T>
bool LinkedList<T>::removeLastOccurrence(const T& value)
{
    if(this->isEmpty()) { return false; }

    Node* current = this->_tail;
    while(current != NULL)
    {
        if(current->data == value)
        {
            if(current == this->_head)
            {
                return this->removeFront();
            }
            else if(current == this->_tail)
            {
                return this->removeBack();
            }
            else
            {
                cur_next = current->next;
                cur_prev = current->prev;
                cur_prev->next = cur_next;
                cur_next->prev = cur_prev;
                delete current;
                this->_size--;
                return true;
            }
        }
        current = current->prev;
    }
    return false;
}

template <typename T>
T& LinkedList<T>::popFront()
{
    T ret = this->_head->data;
    this->removeFront();
    return ret;
}

template <typename T>
T& LinkedList<T>::popBack()
{
    T ret = this->_tail->data;
    this->removeBack();
    return ret;
}

#endif  //PB_LINKED_LIST_HPP
