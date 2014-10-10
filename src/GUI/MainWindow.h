#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../Feedback.h"
#include <memory>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public Feedback::ErrorHandler
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0 );
    ~MainWindow();
    void showAbout();
    virtual void showMsg(std::string const& error, Feedback::ERROR_LVL level);


    void showStudentsWindow();
    void showNewCourse();
    void showOpenCourse();
private:
    Ui::MainWindow *ui;
    std::shared_ptr<Feedback::Course> mActiveCourse;
};

#endif // MAINWINDOW_H
