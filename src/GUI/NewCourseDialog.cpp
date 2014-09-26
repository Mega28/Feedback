#include "NewCourseDialog.h"
#include "ui_NewCourseDialog.h"
#include <QFileDialog>
#include <iostream>

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

QString NewCourseDialog::getCourseName()
{
    return ui->nameLineEdit->text();
}

QString NewCourseDialog::getCourseCode()
{
    return ui->codeLineEdit->text();
}

QString NewCourseDialog::getFileName()
{
    return ui->fileNameLineEdit->text();
}

QString NewCourseDialog::getDirectory()
{
    return ui->courseDirectoryLineEdit->text();
}
