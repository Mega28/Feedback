#ifndef STUDENT_H
#define STUDENT_H

#include<string>
#include<memory>
#include<vector>

#include <odb/core.hxx>

#pragma db object pointer(std::shared_ptr)
class Student
{
public:
    friend class odb::access;


    Student(const std::string& seat,
            const std::string& firstName,
            const std::string& lastName,
            const std::string& email,
            const std::string& year,
            const std::string& section);
    std::vector<std::string> toStringList();

    static int getParametersCount() {
        return parametersCount;
    }
    static std::vector<std::string> getHeader() {
        std::vector<std::string> header = {"ID","Seat", "First","Last","Email","Year","Section"};
        return header;
    }

    std::string getSeatNo() const;
    void setSeatNo(const std::string &seat);

    std::string getFirstName() const;
    void setFirstName(const std::string &firstName);

    std::string getLastName() const;
    void setLastName(const std::string &lastName);

    std::string getSection() const;
    void setSection(const std::string &section);

    std::string getMail() const;
    void setMail(const std::string &mail);

    std::string getYear() const;
    void setYear(const std::string &year);

private:
    Student(){}
#pragma db id auto        // (5)
    unsigned long id_;
    std::string mSeat;
    std::string mFirstName;
    std::string mLastName;
    std::string mMail;
    std::string mYear;
    std::string mSection;

    static constexpr int parametersCount = 7;

};

#pragma db view object(Student)
struct StudentCount
{
  #pragma db column("count(*)")
  std::size_t count;
};





typedef std::shared_ptr<Student> StudentPtr;

#endif // STUDENT_H
