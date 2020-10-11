#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

void reactOnDeleteButtonClick();
void reactOnDeleteAllButtonClick();

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  connect(ui->pushButton_2, &QPushButton::clicked, this, &reactOnDeleteButtonClick);
  connect(ui->pushButton_3, &QPushButton::clicked, this, &reactOnDeleteAllButtonClick);
}

MainWindow::~MainWindow()
{
  delete ui;
}

const char* names[10] = { "Sasha", "Pasha", "Dasha", "Kolya", "Olya", "Yura", "Semyon", "Artem", "Petya", "Lena" };

class User
{
  int age;       // private
  QString name;  // private
  static int total_count;

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
    total_count++;
  }
  User createUser(int age, QString name)
  {
    return User(name, age);
  }
  QString getName()
  {
    return name;
  }
  int getAge()
  {
    return age;
  }
  static int getTotalCount()
  {
    return total_count;
  }
  static void addUser(User user)
  {
    User::users_.push_back(user);
  }
  static void deleteUserOfIndex(int index)
  {
    users_.erase(users_.begin() + index);
    total_count--;
  }
  static void deleteUserOfName(QString name)
  {
    for (unsigned long long i = 0; i < users_.size(); i++)
    {
      if (users_[i].getName() == name)
        users_.erase(users_.begin() + i);
    }
    total_count--;
  }
  static int getCountOfUsers()
  {
    return (users_.size());
  }
  static std::vector<User> users_;
};

int User::total_count = 0;
std::vector<User> User::users_;

void reactOnDeleteButtonClick()
{
  if (User::getTotalCount() != 0)
  {
    int randindex = rand() % (User::getTotalCount());
    User::deleteUserOfIndex(randindex);
    qDebug() << User::users_[randindex].getName() << " gone";
  }
  else
    qDebug() << "All already gone, try to add new user";
}

void reactOnDeleteAllButtonClick()
{
  if (User::getTotalCount() != 0)
  {
    while (User::getTotalCount() != 0)
      User::deleteUserOfIndex(0);
    qDebug() << "All students gone :(";
  }
  else
  {
    qDebug() << "All already gone, try to add new user";
  }
}

void MainWindow::on_pushButton_clicked()
{
  User student(names[rand() % 10], rand() % 33 + 18);
  User::addUser(student);
  QMessageBox msg(QMessageBox::Information, "New student arrived!", "Hello " + student.getName() + "!");
  qDebug() << "Name:" << student.getName();
  qDebug() << "Age:" << student.getAge();
  qDebug() << msg.exec();
  qDebug() << User::getTotalCount();
}
