#include "StudentManager.h"
#include<odb/core.hxx>
#include<fstream>

Feedback::StudentManager::StudentManager(std::shared_ptr<odb::core::database> database,
                                         ErrorHandler *handler)
    : mDatabase(database), mErrorHandler(handler)
{
}

bool Feedback::StudentManager::store(const StudentPtr student)
{
    try {
    odb::core::transaction t (mDatabase->begin ());

          // Make objects persistent and save their ids for later use.
          //
    unsigned long student_id = mDatabase->persist (student);
    t.commit ();
    return true;
    } catch (const odb::exception& e)
    {
      mErrorHandler->showMsg(e.what(),ERROR_LVL::ERROR);
      return false;
    }
}

bool Feedback::StudentManager::store(const std::string& seatNo,
                            const std::string& firstName,
                            const std::string& lastName,
                            const std::string& email,
                            const std::string& academicYear,
                            const std::string& section)
{
    if(seatNo=="" || firstName =="" || lastName=="" || email=="" || section=="")
        return false;

    std::shared_ptr<Student> student(new Student(seatNo,firstName,lastName,email,academicYear,section));
    this->store(student);

}

StudentPtr Feedback::StudentManager::getByName(const std::string& firstName,const std::string& lastName)
{
    StudentPtr student;
    try
     {

         odb::core::transaction t (mDatabase->begin ());
         odb::result<Student> r(mDatabase->query<Student> (odb::query<Student>::mFirstName == firstName &&
                                                           odb::query<Student>::mLastName == lastName));
         // Didn't handle multiple students with the same name
         student =r.end().load();

         t.commit ();

     }
     catch (const odb::exception& e)
     {
       mErrorHandler->showMsg(e.what(),ERROR_LVL::ERROR);
     }
    return student;
}

std::vector<StudentPtr> Feedback::StudentManager::getByYear(const std::string& year)
{
    // TODO

    return std::vector<StudentPtr>();
}

std::vector<StudentPtr> Feedback::StudentManager::query(const std::string& sqlQuery)
{
//    execQuery(sqlQuery);
//    std::vector<StudentPtr> resultList;
//    StudentPtr student;
//    for (auto argv:mLastQueryResult)
//    {
//        student = std::make_shared<Student>(argv[1],argv[2],argv[3],
//                argv[4],argv[5],argv[6]);
//        resultList.push_back(student);
//    }
//    return resultList;

}
StudentPtr Feedback::StudentManager::getByID(int ID)
{
    StudentPtr student;
    try
     {

         odb::core::transaction t (mDatabase->begin ());
         odb::result<Student> r(mDatabase->query<Student> (odb::query<Student>::id == ID));
         // Didn't handle multiple students with the same name
         student =r.begin().load();

         t.commit ();

     }
     catch (const odb::exception& e)
     {
       mErrorHandler->showMsg(e.what(),ERROR_LVL::ERROR);
     }
    return student;

}


int Feedback::StudentManager::getCount()
{
    // tableName is ignored right now
    int count=0;
    try
     {

         odb::core::transaction t (mDatabase->begin ());
         count = (mDatabase->query<StudentCount> (true)).begin ()->count;
         t.commit ();

     }
     catch (const odb::exception& e)
     {
       mErrorHandler->showMsg(e.what(),ERROR_LVL::ERROR);
     }
    return count;

}
int Feedback::StudentManager::getAttribCount()
{
    return Student::getParametersCount();
}

std::vector<StudentPtr> Feedback::StudentManager::getAll()
{
    std::vector<StudentPtr> students;

    try
     {

         odb::core::transaction t (mDatabase->begin ());
         odb::result<Student> r(mDatabase->query<Student> (true));
         // Didn't handle multiple students with the same name
         for (auto i = r.begin();i!=r.end();i++)
         {
             students.push_back(i.load());
         }
         t.commit ();

     }
     catch (const odb::exception& e)
     {
       mErrorHandler->showMsg(e.what(),ERROR_LVL::ERROR);
     }
    return students;

}

std::vector<std::string> Feedback::StudentManager::getAttribHeader()
{
    return Student::getHeader();
}

bool Feedback::StudentManager::update(StudentPtr student)
{
    try
      {
        odb::core::transaction t (mDatabase->begin ());

        mDatabase->update (student);
        t.commit ();
        return true;
      }
    catch (const odb::exception& e)
    {
      mErrorHandler->showMsg(e.what(),ERROR_LVL::ERROR);
      return false;
    }

}

bool Feedback::StudentManager::importFromFile(const std::string &filename)
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
           if (tokens.size()!= (Student::getParametersCount()-1))
           {
               std::string errorMsg = "Error importing file. Invalid data at line ";
               errorMsg += std::to_string(lineCount);
               errorMsg += ".";
               mErrorHandler->showMsg(errorMsg,ERROR_LVL::ERROR);
               continue;
           }
           StudentPtr student = std::make_shared<Student>(tokens[0],tokens[1],tokens[2],
                   tokens[3],tokens[4],tokens[5]);
           students.push_back(student);
       }
       int studentCount=0;
       for (auto student: students)
       {
           if(!store(student))
           {
               //TODO
               mErrorHandler->showMsg("Error in storing a student",ERROR_LVL::ERROR);
           } else {
               studentCount++;
           }
       }
       std::string msg = "Successfully imported ";
       msg += std::to_string(studentCount);
       msg += " students.";
       mErrorHandler->showMsg(msg,ERROR_LVL::MESSAGE);
       file.close();
    } else
    {
        //TODO
        mErrorHandler->showMsg("Failed to open file!",ERROR_LVL::ERROR);
    }

}

bool Feedback::StudentManager::remove(const std::string& keyValue)
{
    // TODO
    return false;
}

