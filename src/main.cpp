#include <iostream>

#include <memory>
#include "GUI/MainWindow.h"
#include <QApplication>


int main(int argc, char** argv)
{
//    std::shared_ptr<MailClient> client = std::make_shared<MailClient>();
//    client->setConnectionParameters("smtp-mail.outlook.com","ahmabdabd@hotmail.com","superbalaa2(","587");
//    client->sendMail("Hello Again", "You must have missed me","/home/allam/smb.conf_Working");


//    DBClient* database = new DBClient();
//    database->storeStudent(123,"Ahmed","Allam","ahmabdabd@hotmail.com",2012, 1);
//    StudentPtr ahmed = database->getStudentByName("Ahmed","Allam");
//    if(ahmed)
//        std::cout << "Stored email is " << ahmed->getMail() << std::endl;
//    else
//        std::cout << "Couldn' find Ahmed" << std::endl;
    QApplication app(argc,argv,0);
    MainWindow* window = new MainWindow(NULL);
    window->show();

    return app.exec();




}
