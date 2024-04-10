#ifndef Data_hpp
#define Data_hpp



#include "Stacks.hpp" 
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>

using std::string;
using std::vector;

class Data {
private:
    int recordNumber;
    long long IDNumber;
    string name;
    string email;
    int units;
    string program;
    string level;
    int numAbsences;
    Stack absenceDates;
    int numAbsenceDates; 

public:
    Data(int recordNumber = 0, long long IDNumber = 0, string name = "", string email = "", int units = 0, string program = "", string level = "", int numAbsences = 0)
        : recordNumber(recordNumber), IDNumber(IDNumber), name(name), email(email), units(units), program(program), level(level), numAbsences(numAbsences), numAbsenceDates(0) {}

    // Getter functions
    int getRecordNumber() const { return recordNumber; }
    long long getIDNumber() const { return IDNumber; }
    const string& getName() const { return name; }
    const string& getEmail() const { return email; }
    int getUnits() const { return units; }
    const string& getProgram() const { return program; }
    const string& getLevel() const { return level; }
    int getNumAbsences() const { return numAbsences; }
    Stack& getAbsenceDates() { return absenceDates; }
    int getNumAbsenceDates() const { return numAbsenceDates; }

    // Setter functions
    void setIDNumber(long long IDNumber) { this->IDNumber = IDNumber; }
    void setName(const string& name) { this->name = name; }
    void setEmail(const string& email) { this->email = email; }
    void setUnits(int units) { this->units = units; }
    void setProgram(const string& program) { this->program = program; }
    void setLevel(const string& level) { this->level = level; }
    void setNumAbsences(int numAbsences) { this->numAbsences = numAbsences; }
    void setAbsenceDates(const Stack& stack) { absenceDates = stack; }

    void markAbsence(const string& date) {
        absenceDates.push(date);
        numAbsences++;
        numAbsenceDates++;
    }
};

#endif // !1