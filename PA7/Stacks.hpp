#ifndef Stacks_hpp
#define Stacks_hpp

#include <iostream>
#include <vector>
#include <string>
using std::vector;
using std::string;

class Stack {
private:
    vector<string> dates;

public:
    void push(const string& date) {
        dates.push_back(date);
    }

    std::string pop() {
        if (!isEmpty()) {
            std::string poppedDate = dates.back();
            dates.pop_back();
            return poppedDate;
        }
        return "";
    }

    string peek() const {
        if (!isEmpty()) {
            return dates.back();
        }
        return "";
    }

    bool isEmpty() const {
        return dates.empty();
    }

};

#endif // Stacks_hpp
