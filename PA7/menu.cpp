#include "Menu.hpp"
#include "List.hpp"
#include "data.hpp"
#include "Stacks.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

void Menu::displayMainMenu() {
    std::cout << "Main Menu:\n"
        << "1. Import course list\n"
        << "2. Load master list\n"
        << "3. Store master list\n"
        << "4. Mark absences\n"
        << "5. BONUS: Edit absences\n"
        << "6. Generate report\n"
        << "7. Exit\n";
}

void Menu::displayGenerateReportMenu() {
    std::cout << "Generate Report Menu:\n"
        << "1. Generate report for all students\n"
        << "2. Generate report for students with absences exceeding threshold\n";
}

void Menu::importCourseList(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    list.clear();

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string record;
        std::vector<std::string> fields;
        while (std::getline(ss, record, ',')) {
            fields.push_back(record);
        }

        if (fields.size() < 6) {
            std::cerr << "Error: Invalid record format in file " << filename << std::endl;
            continue;
        }

        Data data;
        data.setIDNumber(std::stoi(fields[0]));
        data.setName(fields[1]);
        data.setEmail(fields[2]);
        data.setUnits(std::stoi(fields[3]));
        data.setProgram(fields[4]);
        data.setLevel(fields[5]);
        data.setNumAbsences(0);
        Stack absences; 
        data.setAbsenceDates(absences);

        list.insertFront(data);
    }

    file.close();
    std::cout << "Course list imported successfully from " << filename << std::endl;
}

void Menu::loadMasterList(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    list.clear();

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string record;
        std::vector<std::string> fields;
        while (std::getline(ss, record, ',')) {
            fields.push_back(record);
        }

        if (fields.size() < 7) {
            std::cerr << "Error: Invalid record format in file " << filename << std::endl;
            continue;
        }

        Data data;
        data.setIDNumber(std::stoll(fields[0]));
        data.setName(fields[1]);
        data.setEmail(fields[2]);
        data.setUnits(std::stoi(fields[3]));
        data.setProgram(fields[4]);
        data.setLevel(fields[5]);
        data.setNumAbsences(std::stoi(fields[6]));

        for (size_t i = 7; i < fields.size(); ++i) {
            data.getAbsenceDates().push(fields[i]);
        }

        list.insertFront(data);
    }

    file.close();
    std::cout << "Master list loaded successfully from " << filename << std::endl;
}

void Menu::storeMasterList(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    Node<Data>* current = list.getHead();
    while (current) {
        file << current->getData().getIDNumber() << "," << current->getData().getName() << ","
            << current->getData().getEmail() << "," << current->getData().getUnits() << ","
            << current->getData().getProgram() << "," << current->getData().getLevel() << ","
            << current->getData().getNumAbsences();

        Stack dates = current->getData().getAbsenceDates();
        while (!dates.isEmpty()) {
            std::string poppedDate = current->getData().getAbsenceDates().pop();
            file << "," << poppedDate;
        }

        file << "\n";
        current = current->getNext();
    }

    file.close();
    std::cout << "Master list stored successfully in " << filename << std::endl;
}

void Menu::markAbsences() {
    Node<Data>* current = list.getHead();
    std::string currentDate = getCurrentDate();

    while (current) {
        std::string input;
        std::cout << "Is student " << current->getData().getName() << " absent today? (yes/no): ";
        std::cin >> input;

        if (input == "yes") {
            current->getData().getAbsenceDates().push(currentDate);
            current->getData().setNumAbsences(current->getData().getNumAbsences() + 1);
        }

        current = current->getNext();
    }
}

void Menu::editAbsences() {
    int id;
    std::cout << "Enter student ID to edit absences: ";
    std::cin >> id;

    Node<Data>* current = list.getHead();
    while (current) {
        if (current->getData().getIDNumber() == id) {
            std::cout << "Current absences for student " << current->getData().getName() << ":\n";
            Stack dates = current->getData().getAbsenceDates();
            Stack tempDates;
            while (!dates.isEmpty()) {
                std::string date = dates.pop();
                std::cout << date << std::endl;
                tempDates.push(date);
            }

            std::string dateToRemove;
            std::cout << "Enter date to remove absence (YYYY-MM-DD): ";
            std::cin >> dateToRemove;

            while (!tempDates.isEmpty()) {
                std::string date = tempDates.pop();
                if (date != dateToRemove) {
                    current->getData().getAbsenceDates().push(date);
                }
            }

            current->getData().setNumAbsences(current->getData().getNumAbsenceDates());
            std::cout << "Absences updated for student " << current->getData().getName() << std::endl;
            return;
        }

        current = current->getNext();
    }

    std::cerr << "Error: Student with ID " << id << " not found in the master list\n";
}

void Menu::generateReportAll() {
    std::ofstream file("report_all.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file report_all.txt\n";
        return;
    }

    Node<Data>* current = list.getHead();
    while (current) {
        file << "Student: " << current->getData().getName() << "\n";
        file << "Number of absences: " << current->getData().getNumAbsences() << "\n";
        if (!current->getData().getAbsenceDates().isEmpty()) {
            Stack absenceDates = current->getData().getAbsenceDates();
            Stack stack;
            while (!absenceDates.isEmpty()) {
                std::string date = absenceDates.pop();
                file << "Absence date: " << date << "\n";
                stack.push(date);
            }
            file << "Most recent absence: " << stack.peek() << "\n";
        }
        file << "\n";
        current = current->getNext();
    }

    file.close();
    std::cout << "Report generated successfully: report_all.txt\n";
}

void Menu::generateReportThreshold() {
    int threshold;
    std::cout << "Enter absence threshold: ";
    std::cin >> threshold;

    std::ofstream file("report_threshold.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file report_threshold.txt\n";
        return;
    }

    Node<Data>* current = list.getHead();
    while (current) {
        if (current->getData().getNumAbsences() >= threshold) {
            file << "Student: " << current->getData().getName() << "\n";
            file << "Number of absences: " << current->getData().getNumAbsences() << "\n";
            file << "\n";
        }
        current = current->getNext();
    }

    file.close();
    std::cout << "Report generated successfully: report_threshold.txt\n";
}

std::string Menu::getCurrentDate() {
    time_t currentTime;
    struct tm now;
    char buffer[80];

    time(&currentTime);

    if (localtime_s(&now, &currentTime) != 0) {
        return "";
    }

    if (strftime(buffer, sizeof(buffer), "%Y-%m-%d", &now) == 0) {
        return "";
    }

    return std::string(buffer);
}
