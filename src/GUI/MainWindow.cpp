#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <qdebug.h>
#include <QFileDialog>
#include<QMessageBox>
#include<QString>
#include<QtConcurrent/QtConcurrent>

#include "AboutDialog.h"
#include "NewStudentDialog.h"
#include "../DBClient.h"
#include"StudentsModel.h"
#include "StudentsWindow.h"
#include "NewCourseDialog.h"
MainWindow::MainWindow(Model* model,QWidget *parent ) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mModel(model)
{
    ui->setupUi(this);
    connect(ui->aboutAction,&QAction::triggered,this,&MainWindow::showAbout);
    connect(ui->manageStudentsAction,&QAction::triggered,
            this,&MainWindow::showStudentsWindow);
    connect(ui->newCourseAction,&QAction::triggered,this,&MainWindow::showNewCourse);
    mModel->registerErrorHandler(this);
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
    }
}

void MainWindow::showAbout()
{
    AboutDialog* dialog = new AboutDialog(this);
    dialog->exec();
}
void MainWindow::showStudentsWindow()
{
    StudentsWindow* sWindow = new StudentsWindow(mModel,this);
    sWindow->show();
}



void MainWindow::showMsg(std::string const& error,ERROR_LVL level)
{

    switch(level) {
        case ERROR_LVL::MESSAGE:
            //TODO
        case ERROR_LVL::ERROR:
            //TODO
        case ERROR_LVL::WARNING :
                QMessageBox::warning(this,"Error",QString::fromStdString(error));
                break;


        default:
            break;
    }
}
