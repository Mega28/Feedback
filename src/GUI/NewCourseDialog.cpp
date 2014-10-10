#include "NewCourseDialog.h"
#include "ui_NewCourseDialog.h"
#include <QFileDialog>
#include <iostream>
#include "../presistent/CourseInfo.h"

NewCourseDialog::NewCourseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewCourseDialog)
{
    ui->setupUi(this);
    connect(ui->courseDirectoryButton,&QToolButton::clicked,
            this,&NewCourseDialog::courseDirectoryButtonClicked);
    connect(ui->courseDirectoryLineEdit,&QLineEdit::textChanged,
            this,&NewCourseDialog::courseDirectoryLineEditChanged);
    mLineEditPalette = new QPalette();
    ui->courseDirectoryLineEdit->setPalette(*mLineEditPalette);
    mOkButton =  ui->buttonBox->addButton(QDialogButtonBox::Ok);
    this->setWindowTitle("Create New Course...");
}


NewCourseDialog::~NewCourseDialog()
{
    delete mLineEditPalette;
    delete ui;
}

void NewCourseDialog::courseDirectoryButtonClicked()
{
    QString directory = QFileDialog::getExistingDirectory(this,
                                                         "Choose Directory");
    if(!directory.isEmpty())
    {
        ui->courseDirectoryLineEdit->setText(directory);
    }

}

void NewCourseDialog::courseDirectoryLineEditChanged()
{
    QDir directory(ui->courseDirectoryLineEdit->text());


    if(directory.isReadable())
    {
        mLineEditPalette->setColor(QPalette::Text,Qt::black);
        ui->courseDirectoryLineEdit->setPalette(*mLineEditPalette);
        mOkButton->setDisabled(false);
    } else

    {
        mLineEditPalette->setColor(QPalette::Text,Qt::red);
        ui->courseDirectoryLineEdit->setPalette(*mLineEditPalette);
        mOkButton->setDisabled(true);
    }


}

Feedback::CourseInfoPtr NewCourseDialog::getCourseInfo()
{
    QString fileName = ui->fileNameLineEdit->text();
    QString directory = ui->courseDirectoryLineEdit->text();
    if(fileName.right(3)!=".cf")
        fileName = fileName+".cf";
    fileName= directory+"/"+fileName;
    std::cout << fileName.right(3).toStdString() << std::endl;
    return std::make_shared<Feedback::CourseInfo>(
                ui->nameLineEdit->text().toStdString(),
                ui->codeLineEdit->text().toStdString(),
                fileName.toStdString(),
                directory.toStdString());
}
