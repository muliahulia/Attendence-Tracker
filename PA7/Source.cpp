#include "Stacks.hpp"
#include "menu.hpp"
#include "Data.hpp"
#include "List.hpp"
#include <iostream>
#include <ostream>

using std::cout;
using std::endl;
using std::cin;

int main() {
    Menu menu;
    int choice;

    do {
        menu.displayMainMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            menu.importCourseList("data.csv");
            break;
        case 2:
            menu.loadMasterList("MasterList.csv");
            break;
        case 3:
            menu.storeMasterList("MasterList.csv");
            break;
        case 4:
            menu.markAbsences();
            break;
        case 5:
            menu.editAbsences();
            break;
        case 6:
            menu.displayGenerateReportMenu();
            int reportChoice;
            std::cout << "Enter your choice: ";
            std::cin >> reportChoice;
            switch (reportChoice) {
            case 1:
                menu.generateReportAll();
                break;
            case 2:
                menu.generateReportThreshold();
                break;
            default:
                std::cout << "Invalid choice!\n";
                break;
            }
            break;
        case 7:
            std::cout << "Exiting program...\n";
            break;
        default:
            std::cout << "Invalid choice!\n";
            break;
        }
    } while (choice != 7);

    return 0;
}
