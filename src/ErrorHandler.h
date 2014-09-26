#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

enum class ERROR_LVL { MESSAGE, WARNING, ERROR};

class ErrorHandler
{
public:
    ErrorHandler() {}
    virtual void showMsg(std::string const& error,ERROR_LVL level)=0;
};

#endif // ERRORHANDLER_H
