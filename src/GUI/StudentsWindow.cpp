#include "StudentsWindow.h"
#include "ui_StudentsWindow.h"
#include "NewStudentDialog.h"
#include <QFileDialog>

StudentsWindow::StudentsWindow(Model* model,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StudentsWindow),mMainModel(model)
{
    ui->setupUi(this);
    connect(ui->newStudentAction,&QAction::triggered,this,&StudentsWindow::showNewStudent);
    connect(ui->importStudentsAction, &QAction::triggered,this,&StudentsWindow::showImportStudents);
    connect(ui->closeAction,&QAction::triggered,this,&StudentsWindow::close);
    StudentsModel* studentModel = new StudentsModel(mMainModel);
    ui->studentsTableView->setModel(studentModel);
}

StudentsWindow::~StudentsWindow()
{
    delete ui;
}

void StudentsWindow::showNewStudent()
{
    NewStudentDialog* dialog = new NewStudentDialog();
    if(dialog->exec())
    {
        mMainModel->addStudent(dialog->getSeat().toStdString(),
                           dialog->getFirstName().toStdString(),
                           dialog->getLastName().toStdString(),
                           dialog->getEmail().toStdString(),
                           dialog->getYear().toStdString(),
                           dialog->getSection().toStdString());
    }
}
void StudentsWindow::showImportStudents()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Import Students Data",NULL,"Spreadsheet (*.csv)");
    mMainModel->importStudentsFromFile(fileName.toStdString());
}
