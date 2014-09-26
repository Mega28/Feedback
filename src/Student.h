#ifndef STUDENT_H
#define STUDENT_H

#include<string>
#include<memory>

class Student
{
public:
    Student(const std::string& seat,
            const std::string& firstName,
            const std::string& lastName,
            const std::string& email,
            const std::string& year,
            const std::string& section);
    void setName(const std::string& firstName, const std::string& lastName);
    void setMail(const std::string& email);
    void setYear(const std::string& year);
    std::string getName();
    std::string getFirstName();
    std::string getLastName();
    std::string getMail();
    std::string getYear();
    std::string getSeat();
    std::string getSection();

private:
    std::string mSeat;
    std::string mFirstName;
    std::string mLastName;
    std::string mMail;
    std::string mYear;
    std::string mSection;

};

typedef std::shared_ptr<Student> StudentPtr;

#endif // STUDENT_H
