#ifndef STUDENTSMODEL_H
#define STUDENTSMODEL_H
#include<QAbstractItemModel>
#include"../Feedback.h"
#include<memory>

class StudentsModel : public QAbstractItemModel
{
public:
    StudentsModel(std::shared_ptr<Feedback::StudentManager> activeStudents);
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int position, int rows, const QModelIndex &parent);
private:
    std::shared_ptr<Feedback::StudentManager> mActiveStudents;
    void editStudent(StudentPtr student, int index, const std::string &newData);
};


#endif // STUDENTSMODEL_H
