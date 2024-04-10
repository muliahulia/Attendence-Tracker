#ifndef ListNode_hpp
#define ListNode_hpp



#include "Data.hpp"

template<typename T>
class Node {
public:
   

    Node(const T& d);

    T& getData() { return data; }
    const T& getData() const { return data; }

    Node* getNext() const { return next; }
    void setNext(Node* newNext) { next = newNext; }

private:
    T data;
    Node* next;
};


template<typename T>
inline Node<T>::Node(const T& d) : data(d), next(nullptr) {}

#endif // !ListNode_hpp