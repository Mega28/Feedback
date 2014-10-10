#ifndef COURSEINFO_H
#define COURSEINFO_H


#include <string>
#include <memory>
#include <odb/core.hxx>

namespace Feedback {

#pragma db object pointer(std::shared_ptr)
class CourseInfo {
public:
    CourseInfo(const std::string& courseName,
               const std::string& courseCode,
               const std::string& courseFilename,
               const std::string& courseDirectory):
        mName(courseName), mCode(courseCode), mFilename(courseFilename), mDirectory(courseDirectory)
    {

    }
    CourseInfo(){}

#pragma db id auto
    unsigned long mID;
    std::string mName;
    std::string mCode;
    std::string mFilename;
    std::string mDirectory;


};

typedef std::shared_ptr<CourseInfo> CourseInfoPtr;
}

#endif // COURSEINFO_H
