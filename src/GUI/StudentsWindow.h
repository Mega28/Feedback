#ifndef STUDENTSWINDOW_H
#define STUDENTSWINDOW_H

#include <QMainWindow>
#include "StudentsModel.h"

#include "../Feedback.h"

namespace Ui {
class StudentsWindow;
}

class StudentsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StudentsWindow(std::shared_ptr<Feedback::StudentManager> activeStudents,QWidget *parent = 0);
    void showNewStudent();
    void showImportStudents();
    ~StudentsWindow();

private:
    Ui::StudentsWindow *ui;
    std::shared_ptr<Feedback::StudentManager> mActiveManager;
};

#endif // STUDENTSWINDOW_H
