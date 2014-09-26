#ifndef MODEL_H
#define MODEL_H

#include "DBClient.h"
#include "Mailclient.h"
#include "ErrorHandler.h"
class Model
{
public:
    Model();
    /** Register an error handler to be used to output exception messages.
     * @brief registerErrorHandler
     * @param handler A class implementing the ErrorHandler interface.
     */
    void registerErrorHandler(ErrorHandler* handler);
    bool addStudent(const std::string& seatNo,
                    const std::string& firstName,
                    const std::string& lastName,
                    const std::string& email,
                    const std::string& year,
                    const std::string& section);
    bool importStudentsFromFile(std::string const& filename);
    int getStudentsCount(const std::string &course);
    int getStudentColumnSize();
    StringListList getStudents();
    StringList getStudentHeader();
    bool editStudentData(const std::string &SID,
                         const std::string &columnName,
                         const std::string &newData);
    bool removeStudent(const std::string &SID);
private:
    DBClient* mDb;
    MailClient* mMail;
    ErrorHandler* mErrorHandler;

};




#endif // MODEL_H
