#ifndef STUDENTSMODEL_H
#define STUDENTSMODEL_H
#include "../Model.h"
#include<QAbstractItemModel>

class StudentsModel : public QAbstractItemModel
{
public:
    StudentsModel(Model* mainModel);
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
    Model* mMainModel;
};


#endif // STUDENTSMODEL_H
