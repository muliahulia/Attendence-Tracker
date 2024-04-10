#include "List.hpp"


template<typename T>
List<T>::~List() {
    while (head) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
}

template<typename T>
void List<T>::insert(const T& data) {
    Node<T>* newNode = new Node<T>(data);
    newNode->setNext(head);
    head = newNode;
}

template<typename T>
void List<T>::markAbsenceForStudent(const string& studentName, const string& date) {
    Node<T>* current = head;
    while (current != nullptr) {
        if (current->data.getName() == studentName) {
            current->data.markAbsence(date);
            break;
        }
        current = current->next;
    }
}

template<typename T>
void List<T>::editAbsenceForStudent(const string& studentName, const string& date) {
    Node<T>* current = head;
    while (current != nullptr) {
        if (current->data.getName() == studentName) {
            current->data.removeAbsence(date);
            break;
        }
        current = current->next;
    }
}


template<typename T>
void List<T>::insertFront(const T& data) {
    Node<T>* newNode = new Node<T>(data);
    newNode->next = head;
    head = newNode;
    size++;
}

template<typename T>
Node<T>* List<T>::getHead()
{
    return head;
}


template<typename T>
void List<T>::clear() {
    while (head) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
    size = 0;
}

