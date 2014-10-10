#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include <odb/database.hxx>
#include <memory>
#include "ErrorHandler.h"
#include "Student.h"
#include <Student-odb.h>
namespace Feedback {

class StudentManager
{
public:
    StudentManager(std::shared_ptr<odb::core::database> database,
                   ErrorHandler* handler);
    bool store(const std::string& seatNo,
                      const std::string& firstName,
                      const std::string& lastName,
                      const std::string& email,
                      const std::string& academicYear,
                      const std::string& section);
    bool store(const StudentPtr student);
    StudentPtr getByName(const std::string& firstName,const std::string& lastName);
    std::vector<StudentPtr> getByYear(const std::string& year);
    std::vector<StudentPtr> query(const std::string& sqlQuery);

    int getCount();
    int getAttribCount();
    std::vector<StudentPtr> getAll();
    std::vector<std::string> getAttribHeader();
    bool remove(const std::string &keyValue);
    StudentPtr getByID(int ID);
    bool update(StudentPtr student);

    bool importFromFile(const std::string& filename);
private:
    std::shared_ptr<odb::core::database> mDatabase;
    ErrorHandler* mErrorHandler;
};


}

#endif // STUDENTMANAGER_H
