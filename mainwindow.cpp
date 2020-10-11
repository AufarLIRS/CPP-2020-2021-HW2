#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <iostream>

class User
{
  int age;
  QString name;

public:
  explicit User(QString name, int age = 18)
  {
    if (age >= 18)
    {
      this->age = age;
    }
    else
    {
      this->age = 18;
    }
    this->name = name;
  }
  QString getName()
  {
    return name;
  }
  int getAge()
  {
    return age;
  }

  static size_t getTotalCount()
  {
    return users_.size();
  }

  static void addStudent(QString name, int age)
  {
    User student(name, age);
    users_.push_back(student);
  }

  static bool deleteStudentByIndex(size_t index)
  {
    if ((index < 0) || (index >= getTotalCount()))
    {
      return false;
    }
    else
    {
      users_.erase(users_.begin() + index);
      return true;
    }
  }
  static void deleteAllStudents()
  {
    users_.clear();
  }

  static void deleteStudentByName(QString name)
  {
    for (size_t i = 0; i < users_.size(); i++)
    {
      if (name == users_[i].name)
        users_.erase(users_.begin() + i);
    }
  }
  static void showList()
  {
    if (getTotalCount() == 0)
    {
      qDebug() << "The list is empty!";
    }
    qDebug() << "-----------------------------------------------";
    for (size_t i = 0; i < users_.size(); i++)
    {
      qDebug() << users_[i].name << " " << users_[i].age << "\n";
    }
    qDebug() << "-----------------------------------------------";
  }
  static std::vector<User> users_;
};
std::vector<User> User::users_;

void reactOnDeleteButtonClick()
{
  if (User::getTotalCount() > 0)
  {
    size_t index = rand() % User::getTotalCount();
    User::deleteStudentByIndex(index);
    qDebug() << "Random student has been deleted";
    User::showList();
  }
}

void reactOnDeleteAllButtonClick()
{
  User::deleteAllStudents();
  qDebug() << "All students have been deleted";
  User::showList();
}

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  qDebug() << "Hello!";
  connect(ui->deleteButton, &QPushButton::clicked, this, &reactOnDeleteButtonClick);
  connect(ui->deleteAllButton, &QPushButton::clicked, this, &reactOnDeleteAllButtonClick);
}

MainWindow::~MainWindow()
{
  qDebug() << "See you next time!";
  delete ui;
}

QString randomName()
{
  QString name;
  int length = rand() % 15 + 5;
  static const char alphanum[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                 "abcdefghijklmnopqrstuvwxyz";

  srand((unsigned)time(NULL) * getpid());

  for (int i = 0; i < length; ++i)
    name += alphanum[rand() % (sizeof(alphanum) - 1)];

  return name;
}

void MainWindow::on_addButton_clicked()
{
  QString name = randomName();
  User::addStudent(name, rand() % 54 + 16);
  qDebug() << "New student " << name << " has been added to the list";
  User::showList();
}
