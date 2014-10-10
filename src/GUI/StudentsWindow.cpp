#include "StudentsWindow.h"
#include "ui_StudentsWindow.h"
#include "NewStudentDialog.h"
#include <QFileDialog>

StudentsWindow::StudentsWindow(
        std::shared_ptr<Feedback::StudentManager> activeStudents,
        QWidget *parent):
    QMainWindow(parent), ui(new Ui::StudentsWindow),mActiveManager(activeStudents)
{
    ui->setupUi(this);
    connect(ui->newStudentAction,&QAction::triggered,this,&StudentsWindow::showNewStudent);
    connect(ui->importStudentsAction, &QAction::triggered,this,&StudentsWindow::showImportStudents);
    connect(ui->closeAction,&QAction::triggered,this,&StudentsWindow::close);
    StudentsModel* studentModel = new StudentsModel(mActiveManager);
    ui->studentsTableView->setModel(studentModel);
}

StudentsWindow::~StudentsWindow()
{
    delete ui->studentsTableView->model();
    delete ui;
}


void StudentsWindow::showNewStudent()
{
    NewStudentDialog* dialog = new NewStudentDialog();
    if(dialog->exec())
    {
        mActiveManager->store(dialog->getSeat().toStdString(),
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
    if (!fileName.isNull() && !fileName.isEmpty())
    {
        mActiveManager->importFromFile(fileName.toStdString());
    } else
    {
        //TODO show some warning
    }
}
