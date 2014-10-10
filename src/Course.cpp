#include "Course.h"
#include<odb/sqlite/database.hxx>
#include<odb/core.hxx>
#include <odb/transaction.hxx>
#include <odb/schema-catalog.hxx>
#include <iostream>


Feedback::Course::Course(const std::string &fileName, Feedback::ErrorHandler *handler): mErrorHandler(handler)
{
    try
      {
        mDatabase = std::make_shared<odb::sqlite::database>(fileName,SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
        mStudentMgr = std::make_shared<StudentManager>(mDatabase,mErrorHandler);
        odb::core::transaction t (mDatabase->begin ());
        odb::result<CourseInfo> r(mDatabase->query<CourseInfo> (true));
        mInfo = r.begin().load();
        t.commit();
      }
      catch (const odb::exception& e)
      {
        mErrorHandler->showMsg(e.what(),ERROR_LVL::ERROR);
       }
}

Feedback::Course::Course(Feedback::CourseInfoPtr info, Feedback::ErrorHandler *handler):mErrorHandler(handler)
{
    try
    {
        std::cout << info->mFilename << std::endl;
        mDatabase = std::make_shared<odb::sqlite::database>(info->mFilename,SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
        mInfo = info;
        odb::transaction t (mDatabase->begin ());
        odb::schema_catalog::create_schema (*mDatabase);
        t.commit ();
        odb::transaction t2 (mDatabase->begin ());
        mDatabase->persist<CourseInfo>(mInfo);
        t2.commit();

        mStudentMgr = std::make_shared<StudentManager>(mDatabase,mErrorHandler);
    }
    catch (const odb::exception& e)
    {
      mErrorHandler->showMsg(e.what(),ERROR_LVL::ERROR);
  }

}

std::shared_ptr<Feedback::StudentManager> Feedback::Course::getStudentMgr()
{
    return mStudentMgr;
}

bool Feedback::Course::importStudentsFromFile(std::string const& filename)
{
    return mStudentMgr->importFromFile(filename);
}
Feedback::CourseInfoPtr Feedback::Course::getInfo() const
{
    return mInfo;
}

bool Feedback::Course::updateInfo(const CourseInfoPtr info)
{
    try {
        odb::core::transaction t(mDatabase->begin());
        mDatabase->update(info);
        t.commit();
        mInfo = info;
        return true;
    }catch (const odb::exception& e)
    {
      mErrorHandler->showMsg(e.what(),ERROR_LVL::ERROR);
      return false;
    }

}

