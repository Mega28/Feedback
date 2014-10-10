#ifndef COURSE_H
#define COURSE_H

#include<string>
#include<memory>
#include"StudentManager.h"
#include<odb/database.hxx>
#include"ErrorHandler.h"
#include "presistent/Student.h"
#include <Student-odb.h>
#include "presistent/CourseInfo.h"
#include <CourseInfo-odb.h>


typedef std::vector<std::string> StringList;

namespace Feedback {

class Course
{
public:
    Course(const std::string& fileName, ErrorHandler *handler);
    Course(CourseInfoPtr info, ErrorHandler *handler);
    /** Get the student manager of this course to perform student database operations.
     * @brief getStudentMgr
     * @return Shared pointer to the Student Manager of this course.
     */
    std::shared_ptr<StudentManager> getStudentMgr();
    bool importStudentsFromFile(const std::string &filename);
    CourseInfoPtr getInfo() const;
    bool updateInfo(const CourseInfoPtr info);

private:

    int execQuery(const std::string& sql);

    std::shared_ptr<Feedback::StudentManager> mStudentMgr;
    std::shared_ptr<odb::core::database> mDatabase;
    ErrorHandler* mErrorHandler;
    CourseInfoPtr mInfo;

};

}


#endif // COURSE_H
