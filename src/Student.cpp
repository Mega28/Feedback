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

void Student::setName(const std::string& firstName, const std::string& lastName)
{
    mFirstName = firstName;
    mLastName = lastName;
}

void Student::setMail(const std::string& email)
{
    mMail=email;
}

void Student::setYear(const std::string& year)
{
    mYear = year;
}

std::string Student::getName()
{
    return mFirstName+""+mLastName;
}

std::string Student::getFirstName()
{
    return mFirstName;
}

std::string Student::getLastName()
{
    return mLastName;
}

std::string Student::getMail()
{
    return mMail;
}

std::string Student::getYear()
{
    return mYear;
}

std::string Student::getSection()
{
    return mSection;
}

std::string Student::getSeat()
{
    return mSeat;
}



