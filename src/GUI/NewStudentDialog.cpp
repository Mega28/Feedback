#include "NewStudentDialog.h"
#include "ui_NewStudentDialog.h"
#include<QString>

NewStudentDialog::NewStudentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewStudentDialog)
{
    ui->setupUi(this);

}

NewStudentDialog::~NewStudentDialog()
{
    delete ui;
}

QString NewStudentDialog::getSeat()
{
    return ui->seatNumberLineEdit->text();
}

QString NewStudentDialog::getFirstName()
{
    return ui->firstNameLineEdit->text();
}

QString NewStudentDialog::getLastName()
{
    return ui->lastNameLineEdit->text();
}

QString NewStudentDialog::getEmail()
{
    return ui->emailLineEdit->text();
}

QString NewStudentDialog::getYear()
{
    //TODO
    return ui->yearComboBox->currentText();
}
QString NewStudentDialog::getSection()
{
    return ui->sectionLineEdit->text();
}
