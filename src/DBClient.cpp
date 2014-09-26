#include "DBClient.h"
#include <exception>
#include <string>
#include <iostream>
#include "Student.h"

DBClient::DBClient(ErrorHandler *handler): mErrorHandler(handler)
{
    int rs = sqlite3_open_v2("res/feedbacker.sqlite",&mDatabase,SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE,NULL);
    if(rs)
    {
        std::string errorMsg = "Something went wrong while opening the database: ";
        errorMsg += std::string(sqlite3_errmsg(mDatabase));
        std::cout<< errorMsg << std::endl;
        mErrorHandler->showMsg(errorMsg,ERROR_LVL::ERROR);
        throw ;
    }
    std::cout<< "Database opened!" << std::endl;
}

DBClient::~DBClient()
{
    sqlite3_close_v2(mDatabase);
}
bool DBClient::storeStudent(Student& student)
{
    this->storeStudent( student.getSeat(),
                        student.getFirstName(),
                        student.getLastName(),
                        student.getMail(),
                        student.getYear(),
                        student.getSection());

}

bool DBClient::storeStudent(const std::string& seatNo,
                            const std::string& firstName,
                            const std::string& lastName,
                            const std::string& email,
                            const std::string& academicYear,
                            const std::string& section)
{

    std::string sql;
    char* error;
    if(seatNo=="" || firstName =="" || lastName=="" || email=="" || section=="")
        return false;
    sql = "INSERT INTO STUDENT "  \
            "VALUES (NULL,"+seatNo+",'"+firstName+"', '"+ lastName+"', '"+email
            +"', '"+academicYear+"',"+section+"); ";
    int rs=sqlite3_exec(mDatabase,sql.c_str(),NULL,NULL,&error);
    if(rs)
    {
        std::string errorMsg = "Something went wrong while trying to save student: ";
        errorMsg += sqlite3_errmsg(mDatabase); //error;
        std::cout<< errorMsg << std::endl;
        mErrorHandler->showMsg(errorMsg,ERROR_LVL::ERROR);
        throw;
    } else
    {
        std::cout << firstName+lastName << " Stored successfully!" << std::endl;
        return true;
    }

}

StudentPtr DBClient::getStudentByName(const std::string& firstName,const std::string& lastName)
{
    StudentPtr student;
    auto studentsList = this->queryStudents("SELECT * FROM STUDENT WHERE FIRST='"+firstName+"' AND LAST='"+lastName+"'");
    if(studentsList.size()>0)
        student=studentsList[0];
    return student;
}

std::vector<StudentPtr> DBClient::getStudentsByYear(const std::string& year)
{

    return this->queryStudents("SELECT * FROM STUDENT WHERE YEAR='"+year+"'");
}

std::vector<StudentPtr> DBClient::queryStudents(const std::string& sqlQuery)
{
    execQuery(sqlQuery);
    std::vector<StudentPtr> resultList;
    StudentPtr student;
    for (auto argv:mLastQueryResult)
    {
        student = std::make_shared<Student>(argv[1],argv[2],argv[3],
                argv[4],argv[5],argv[6]);
        resultList.push_back(student);
    }
    return resultList;

}
int DBClient::callBack(void *NotUsed, int argc, char **argv, char **azColName){
    StringList data,header;
    for(size_t col=0;col<argc;col++)
    {
        if(argv[col]!=NULL)
        {
            data.push_back(std::string(argv[col]));
        } else {
            data.push_back("NULL");
        }
        if(azColName[col]!=NULL)
        {
            header.push_back(std::string(azColName[col]));
        } else {
            header.push_back(NULL);
        }
    }
    if(argc>0)
    {
        mLastQueryResult.push_back(data);
        mLastQueryHeader.push_back(header);
    }

    return 0;
}

int DBClient::execQuery(const std::string &sql)
{
    char* error;
    mLastQueryResult.clear();
    mLastQueryHeader.clear();
    int rs=sqlite3_exec(mDatabase,sql.c_str(),&DBClient::callBack,NULL,&error);
    if(rs)
    {
        std::cout<< "Something went wrong while trying to Query the database: " << error << std::endl;
        throw ;
    }
    return rs;

}
StringListList DBClient::mLastQueryResult;
StringListList DBClient::mLastQueryHeader;

int DBClient::getRowCount(const std::string &tableName)
{
    this->execQuery("SELECT COUNT(*) FROM "+tableName);
    return std::stoi((mLastQueryResult[0])[0]);

}
int DBClient::getColumnCount(const std::string &tableName)
{
    this->execQuery("PRAGMA table_info("+tableName+");");
    return mLastQueryResult.size();
}

StringListList DBClient::getStudents()
{
    this->execQuery("SELECT * FROM STUDENT");
    return mLastQueryResult;

}
StringList DBClient::getTableHeader(const std::string &tableName)
{
    this->execQuery("PRAGMA table_info("+tableName+");");
    StringList header;
    for(auto it=mLastQueryResult.begin();it<mLastQueryResult.end();it++)
    {
        header.push_back((*it)[1]);
    }
    return header;
}

bool DBClient::editData(const std::string& tableName,
                        const std::string& keyColumn, const std::string& keyValue,
                        const std::string& columnName, const std::string& newData)
{
    return this->execQuery("UPDATE "+tableName+" SET "+columnName+"='"+newData+"' WHERE "+keyColumn+"='"+keyValue+"';");
}

bool DBClient::deleteRow(const std::string& tableName,
                         const std::string& keyColumn,
                         const std::string& keyValue)
{
    return this->execQuery("DELETE FROM "+tableName+" WHERE "+keyColumn+" = '"+keyValue+"';");
}
