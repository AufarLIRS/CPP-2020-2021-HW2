#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <cstdlib>
#include <ctime>
#include <string>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

class User
{
    private:
        int age; // private
        QString name; //private
        static int total_count;
        static std::vector<User> users_;

    public:
        explicit User(QString name, int age)
        {
            this->age = age;
            this->name = name;
        }
        QString getName()
        {
            return this->name;
        }
        int getAge()
        {
            return this->age;
        }
        static int getTotalCount()
        {
            return total_count;
        }
        static int addUser(QString name, int age)
        {
            if (age >= 18)
            {
                users_.push_back(User(name, age));
                total_count++;
                return (1);
            }
            return (0);
        }
        static int deleteUser(QString name)
        {
            std::vector<User>::iterator it = users_.begin();
            if (total_count == 0)
                return (0);
            while (it != users_.end())
            {
                if (QString::compare(name, it->getName()) == 0)
                {
                    users_.erase(it);
                    total_count--;
                    return (1);
                }
                it++;
            }
            return (0);
        }
        static int deleteUserById(int id)
        {
            int id_temp = 0;
            std::vector<User>::iterator it = users_.begin();

            if (total_count == 0)
                return (0);
            while (it != users_.end())
            {
                if (id_temp == id)
                {
                    users_.erase(it);
                    total_count--;
                    return (1);
                }
                it++;
                id_temp++;
            }
            return (0);
        }
        int getSizeList()
        {
            return (users_.size());
        }
};

int User::total_count = 0;
std::vector<User> User::users_;

void MainWindow::on_addButton_clicked()
{
    int count = User::getTotalCount();
    QString name = QString::number(count * time(NULL));
    if (User::addUser(name, time(NULL)))
    {
        QMessageBox msg(QMessageBox::Information, "User add", "User was added");
        qDebug() << msg.exec();
    }
    else
    {
        QMessageBox msg1(QMessageBox::Information, "User add", "User was not added");
        qDebug() << msg1.exec();
    }
}

void MainWindow::on_deleteButton_clicked()
{
    if (User::deleteUserById(User::getTotalCount() - 1))
    {
        QMessageBox msg(QMessageBox::Information, "User delete", "User was deleted");
        qDebug() << msg.exec();
    }
    else
    {
        QMessageBox msg1(QMessageBox::Information, "User delete", "User was not deleted");
        qDebug() << msg1.exec();
    }
}

void MainWindow::on_deleteAllButton_clicked()
{
    if (User::getTotalCount() == 0)
    {
        QMessageBox msg1(QMessageBox::Information, "User delete all", "Users not was deleted");
        qDebug() << msg1.exec();
    }
    else
    {
        QMessageBox msg(QMessageBox::Information, "User delete all", "Users was deleted");
        qDebug() << msg.exec();
    }
    while (User::getTotalCount() != 0)
    {
        User::deleteUserById(User::getTotalCount() - 1);
    }
}
