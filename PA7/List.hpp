#ifndef List_hpp
#define List_hpp



#include "ListNode.hpp"
#include <fstream>
#include <string>

using std::string;

template<typename T>
class List {
private:
    Node<T>* head; 
    int size;

public:
    List() : head(nullptr), size(0) {}

    ~List();

    void insertFront(const T& data);
    
    Node<T>* getHead();

    void editAbsenceForStudent(const string& studentName, const string& date);
    void markAbsenceForStudent(const string& studentName, const string& date);
    void insert(const T& data);
    void clear();
};

#endif // !1
