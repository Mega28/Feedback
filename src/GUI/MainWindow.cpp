#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <qdebug.h>
#include <QFileDialog>
#include<QMessageBox>
#include<QString>
#include<QtConcurrent/QtConcurrent>

#include "AboutDialog.h"
#include "NewStudentDialog.h"
#include"StudentsModel.h"
#include "StudentsWindow.h"
#include "NewCourseDialog.h"
MainWindow::MainWindow(QWidget *parent ) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->aboutAction,&QAction::triggered,this,&MainWindow::showAbout);
    connect(ui->manageStudentsAction,&QAction::triggered,
            this,&MainWindow::showStudentsWindow);
    connect(ui->newCourseAction,&QAction::triggered,this,&MainWindow::showNewCourse);
    connect(ui->openCourseAction,&QAction::triggered,this,&MainWindow::showOpenCourse);
    this->setWindowTitle("Feedback");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showNewCourse()
{
    NewCourseDialog* dialog = new NewCourseDialog(this);
    if(dialog->exec())
    {
        //TODO add data verification in the dialog
        //TODO implement Model file creation

        mActiveCourse = std::make_shared<Feedback::Course>(dialog->getCourseInfo(),this);
    }
}

void MainWindow::showAbout()
{
    AboutDialog* dialog = new AboutDialog(this);
    dialog->exec();
}
void MainWindow::showStudentsWindow()
{
    //TODO Implement memory handling
    StudentsWindow* sWindow = new StudentsWindow(mActiveCourse->getStudentMgr(),this);
    sWindow->show();
}

void MainWindow::showOpenCourse()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Choose a course file",NULL,"CourseFile (*.cf)");
    if (!fileName.isNull() && !fileName.isEmpty())
    {
        mActiveCourse = std::make_shared<Feedback::Course>(fileName.toStdString(),this);
    }

}



void MainWindow::showMsg(std::string const& error,Feedback::ERROR_LVL level)
{

    switch(level) {
        case Feedback::ERROR_LVL::MESSAGE:
            //TODO
        case Feedback::ERROR_LVL::ERROR:
            //TODO
        case Feedback::ERROR_LVL::WARNING :
            QMessageBox::warning(this,"Error",QString::fromStdString(error));
            break;


        default:
            break;
    }
}
