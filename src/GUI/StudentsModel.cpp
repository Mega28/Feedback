#include "StudentsModel.h"
#include "../Feedback.h"


StudentsModel::StudentsModel(std::shared_ptr<Feedback::StudentManager> activeStudents):mActiveStudents(activeStudents)
{

}

QModelIndex StudentsModel::index(int row, int column, const QModelIndex &parent) const
{
    return createIndex(row,column);
}

QModelIndex StudentsModel::parent(const QModelIndex &child) const
{
    //TODO
    return QModelIndex();
}

int StudentsModel::rowCount(const QModelIndex &parent) const
{
    return mActiveStudents->getCount();
}

int StudentsModel::columnCount(const QModelIndex &parent) const
{
    return mActiveStudents->getAttribCount();
}

QVariant StudentsModel::data(const QModelIndex &index, int role) const
{
    if(role==Qt::DisplayRole)
    {
        std::vector<StudentPtr> studentsList = mActiveStudents->getAll();
        StudentPtr student = studentsList[index.row()];

        StringList rowData = student->toStringList();
        QString data = QString::fromStdString(rowData[index.column()]);
        return data;
    } else {
        return QVariant();
    }
}

QVariant StudentsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role==Qt::DisplayRole)
    {
        if(orientation== Qt::Horizontal )
        {
            QString header = QString::fromStdString((mActiveStudents->getAttribHeader())[section]);
            header=header.toLower();
            header[0] = header[0].toUpper();
            return header;
        } else {
            return section;
        }
    } else
    {
        return QAbstractItemModel::headerData(section,orientation,role);
    }
}

bool StudentsModel::insertRows(int row, int count, const QModelIndex &parent)
{

    beginInsertRows(QModelIndex(),this->rowCount(QModelIndex()),
                    this->rowCount(QModelIndex())+count);
    for(int rowNum=0;rowNum<count;rowNum++)
    {
        mActiveStudents->store("NULL","fName","lName","mail@example.com","2014","1");
    }
    endInsertRows();
}

Qt::ItemFlags StudentsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool StudentsModel::setData(const QModelIndex &index,
                              const QVariant &value, int role)
{

    QModelIndex keyIndex=this->createIndex(index.row(),0);

    if (index.isValid() && role == Qt::EditRole) {
        StudentPtr student = mActiveStudents->getByID(this->data(keyIndex, Qt::DisplayRole).toString().toInt());
        editStudent(student,index.column(),value.toString().toStdString());
        mActiveStudents->update(student);
        emit dataChanged(index, index);
        return true;
    }
    return false;
}
bool StudentsModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    beginRemoveRows(QModelIndex(), position, position+rows-1);
    StringList keyData; // SIDs of the students to be deleted;

    for (int row = 0; row < rows; ++row) {
        keyData.push_back(this->data(this->createIndex(position+row,0),Qt::DisplayRole).toString().toStdString());
    }
    for(auto key:keyData){
        mActiveStudents->remove(key);
    }
    endRemoveRows();
    return true;
}

void StudentsModel::editStudent(StudentPtr student,int index,const std::string& newData)
{
    switch (index)
    {
        case 1:
            student->setSeatNo(newData);
        case 2:
            student->setFirstName(newData);
            break;
        case 3:
            student->setLastName(newData);
            break;
        case 4:
            student->setMail(newData);
            break;
        case 5:
            student->setYear(newData);
            break;
        case 6:
            student->setSection(newData);
            break;
    default:
        throw; // Shoud show an error message here
    }

}
