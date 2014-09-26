#include "Model.h"
#include <fstream>

const size_t DATA_COUNT = 6;

Model::Model()
{
    mDb = new DBClient(mErrorHandler);
}


bool Model::addStudent(const std::string &seatNo,
                       const std::string &firstName,
                       const std::string &lastName,
                       const std::string &email,
                       const std::string &year,
                       const std::string &section)
{
    mDb->storeStudent(seatNo,firstName,lastName,email,year,section);
    mErrorHandler->showMsg("Student Added!.",ERROR_LVL::MESSAGE);
}

bool Model::importStudentsFromFile(std::string const& filename)
{

    std::ifstream file;
    file.open(filename);
    if (file.is_open())
    {
       std::string line;
       int lineCount=0;
       std::vector<StudentPtr> students;
       while(std::getline(file,line))
       {
           lineCount++;
           size_t pos = 0;
           std::vector<std::string> tokens;
           while ((pos = line.find(',')) != std::string::npos)
           {
               tokens.push_back(line.substr(0, pos));
               line.erase(0, pos + 1);
           }
           tokens.push_back(line);
           if (tokens.size()!= DATA_COUNT)
           {
               std::string errorMsg = "Error importing file. Invalid data at line ";
               errorMsg += std::to_string(lineCount);
               errorMsg += ".";
               mErrorHandler->showMsg(errorMsg,ERROR_LVL::ERROR);
               std::cout << errorMsg << std::endl;
               continue;
           }
           StudentPtr student = std::make_shared<Student>(tokens[0],tokens[1],tokens[2],
                   tokens[3],tokens[4],tokens[5]);
           students.push_back(student);
       }
       int studentCount=0;
       for (auto student: students)
       {
           if(!mDb->storeStudent(*student))
           {
               //TODO
               std::cout << "Error in storing a student" << std::endl;
           } else {
               studentCount++;
           }
       }
       std::string msg = "Successfully imported ";
       msg += std::to_string(studentCount);
       msg += " students.";
       std::cout << msg << std::endl;
       mErrorHandler->showMsg(msg,ERROR_LVL::MESSAGE);
       file.close();
    } else
    {
        //TODO
        std::cout << "Failed to open file!" << std::endl;
    }

}


void Model::registerErrorHandler(ErrorHandler *handler)
{
    mErrorHandler = handler;
}

int Model::getStudentsCount(const std::string &course)
{
    //TODO Implement per course
    return mDb->getRowCount("STUDENT");
}

// Need here a better name
int Model::getStudentColumnSize()
{
    return mDb->getColumnCount("STUDENT");
}

StringListList Model::getStudents()
{
    return mDb->getStudents();
}
StringList Model::getStudentHeader()
{
    return mDb->getTableHeader("STUDENT");
}

bool Model::editStudentData(const std::string& SID,const std::string& columnName,
                            const std::string& newData)
{
    return mDb->editData("STUDENT","SID",SID,columnName,newData);
}

bool Model::removeStudent(const std::string& SID)
{
    return mDb->deleteRow("STUDENT","SID",SID);
}
