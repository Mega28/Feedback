#ifndef DBCLIENT_H
#define DBCLIENT_H

#include <sqlite3.h>
#include <string>
#include <vector>
#include "Student.h"
#include "ErrorHandler.h"

typedef std::vector<std::string> StringList;
typedef std::vector<StringList> StringListList;

class DBClient
{
public:
    DBClient(ErrorHandler* handler);
    ~DBClient();
    bool storeStudent(const std::string& seatNo,
                      const std::string& firstName,
                      const std::string& lastName,
                      const std::string& email,
                      const std::string& academicYear,
                      const std::string& section);
    bool storeStudent(Student& student);
    StudentPtr getStudentByName(const std::string& firstName,const std::string& lastName);
    std::vector<StudentPtr> getStudentsByYear(const std::string& year);
    std::vector<StudentPtr> queryStudents(const std::string& sqlQuery);

    int getRowCount(const std::string &tableName);
    int getColumnCount(const std::string &tableName);
    StringListList getStudents();
    StringList getTableHeader(const std::string &tableName);
    bool editData(const std::string &tableName,
                  const std::string &keyColumn, const std::string &keyValue,
                  const std::string &columnName, const std::string &newData);
    bool deleteRow(const std::string &tableName, const std::string &keyColumn, const std::string &keyValue);
private:
    sqlite3* mDatabase;
    static StringListList mLastQueryResult;
    static StringListList mLastQueryHeader;
    static int callBack(void *NotUsed, int argc, char **argv, char **azColName);
    int execQuery(const std::string& sql);
    ErrorHandler* mErrorHandler;
};



#endif // DBCLIENT_H
