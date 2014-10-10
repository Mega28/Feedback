#include "Student.h"

Student::Student(const std::string& seat,
                 const std::string& firstName,
                 const std::string& lastName,
                 const std::string& email,
                 const std::string& year,
                 const std::string& section):mSeat(seat),mFirstName(firstName),
                                    mLastName(lastName),mMail(email),
                                    mYear(year),mSection(section)
{
}

std::vector<std::string> Student::toStringList()
{
    std::vector<std::string> student = {std::to_string(id_), mSeat, mFirstName, mLastName, mMail, mYear, mSection};
    return student;
}
std::string Student::getSeatNo() const
{
    return mSeat;
}

void Student::setSeatNo(const std::string &seat)
{
    mSeat = seat;
}
std::string Student::getFirstName() const
{
    return mFirstName;
}

void Student::setFirstName(const std::string &firstName)
{
    mFirstName = firstName;
}
std::string Student::getLastName() const
{
    return mLastName;
}

void Student::setLastName(const std::string &lastName)
{
    mLastName = lastName;
}
std::string Student::getSection() const
{
    return mSection;
}

void Student::setSection(const std::string &section)
{
    mSection = section;
}
std::string Student::getMail() const
{
    return mMail;
}

void Student::setMail(const std::string &mail)
{
    mMail = mail;
}
std::string Student::getYear() const
{
    return mYear;
}

void Student::setYear(const std::string &year)
{
    mYear = year;
}



