#ifndef STUDENTSWINDOW_H
#define STUDENTSWINDOW_H

#include <QMainWindow>
#include "StudentsModel.h"

namespace Ui {
class StudentsWindow;
}

class StudentsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StudentsWindow(Model* model,QWidget *parent = 0);
    void showNewStudent();
    void showImportStudents();
    ~StudentsWindow();

private:
    Ui::StudentsWindow *ui;
    Model* mMainModel;
};

#endif // STUDENTSWINDOW_H
