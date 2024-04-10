#ifndef menu_hpp
#define menu_hpp

#include "List.hpp"
#include "Data.hpp"
#include <string> 

class Menu {
private:
    List<Data> list;

public:
    void displayMainMenu();
    void displayGenerateReportMenu();
    void importCourseList(const std::string& filename);
    void loadMasterList(const std::string& filename);
    void storeMasterList(const std::string& filename);
    void markAbsences();
    void editAbsences();
    void generateReportAll();
    void generateReportThreshold();
    std::string getCurrentDate();
};
#endif 