#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <vector>
#include <cstdlib>
#include <QRandomGenerator64>
#include <ctime>

class User
{
  int age_;
  QString name_;
  static int total_count_;

public:
  explicit User(QString name, int age = 18)
  {
    if (age >= 18)
    {
      this->age_ = age;
    }
    else
    {
      this->age_ = 18;
    }
    this->name_ = name;
    total_count_++;
  }

  /*addStudents изменил под условия задачи.
  Из массива mas берется рандомное имя и вместе с рандомным
  возрастом от 18 до 25 записывается в student(name, age)*/

  static void addStudents(QString name, int age)
  {
    QString mas[30] = {
      "Anatoliy", "Katya",   "Masha",     "Eva",      "Zema",  "Slavik",    "Margo",  "Yri",      "Vladimir", "Evilina",
      "Alesha",   "Vasiliy", "Dima",      "Ruslan",   "Oleg",  "Mikhail",   "Igor",   "Ivan",     "Gleb",     "Denis",
      "Alina",    "Alisa",   "Anastasia", "Viktoria", "Darya", "Ekaterina", "Kamila", "Kristina", "Ksenia",   "Natalya",
    };
    User student(name, age);
    name = mas[rand() % 30];
    std::uniform_real_distribution<double> distribution(18, 25);
    age = distribution(*QRandomGenerator::global());
    qDebug() << "Added a new student";
    qDebug() << "Name:" << name << "Age:" << age;
    users_.push_back(student);
    qDebug() << "Total number of students:" << User::getTotalCount();
    qDebug() << "";
  }

  static void deleteAllUsers()
  {
    User::users_.clear();
    qDebug() << "All users have been deleted!";
  }

  static void deleteRandomUser()
  {
    int total_ = User::getTotalCount();
    if (total_ == 0)
    {
      qDebug() << "All users have been deleted!";
    }
    else
    {
      srand((unsigned)time(0));
      int randomNumber_;
      for (unsigned int i = 0; i < users_.size(); i++)
      {
        randomNumber_ = (rand() % users_.size()) + 0;
      }
      User::users_.erase(User::users_.begin() + randomNumber_);
      qDebug() << "A random user has been deleted!";
    }
  }

  static size_t getNum()
  {
    return users_.size();
  }

  // deleteStudentByNumber оставил не тронутым.

  static void deleteStudentByNumber(int num)
  {
    users_.erase(users_.begin() + num);
  }

  // deleteStudentByName оставил не тронутым.

  static void deleteStudentByName(QString name)
  {
    for (unsigned int i = 0; i < users_.size(); i++)
    {
      if (users_[i].getName() == name)
      {
        users_.erase(users_.begin() + i);
      }
      else
      {
        qDebug() << "Nothing happened!";
      }
    }
  }

  QString getName()
  {
    return name_;
  }

  int getAge()
  {
    return age_;
  }

  static int getTotalCount()
  {
    return total_count_;
  }

  static std::vector<User> users_;
};

int User::total_count_ = 0;
std::vector<User> User::users_;

/*Пытался через QMessageBox и arg(...) реализовать вывод переменой
на экран, но переменная не выводилась*/

void MainWindow::on_addButton_clicked()
{
  int age = 0;
  QString name = 0;

  qDebug() << "User clicked on 'Add' button";
  QMessageBox* msg = new QMessageBox();
  User::addStudents(name, age);
  QString status = QString("Addeded student with name %1 and with age %2").arg(name).arg(age);
  msg->QMessageBox::information(this, "Student", status);
}

void MainWindow::on_deleteButton_clicked()
{
  qDebug() << "User clicked on 'Delete' button";
  User::deleteRandomUser();
}

void MainWindow::on_deleteAllButton_clicked()
{
  qDebug() << "User clicked on 'Delete ALl' button";
  User::deleteAllUsers();
}

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  connect(ui->deleteAllButton, &QPushButton::clicked, this, &MainWindow::on_deleteAllButton_clicked);
  connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::on_deleteButton_clicked);
}

MainWindow::~MainWindow()
{
  delete ui;
}
