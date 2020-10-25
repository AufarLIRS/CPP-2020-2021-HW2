#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <experimental/random>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  connect(ui->DeleteButton, &QPushButton::clicked, this, &MainWindow::deleteUser);
  connect(ui->DeleteAllButton, &QPushButton::clicked, this, &MainWindow::deleteAllUser);
}

MainWindow::~MainWindow()
{
  delete ui;
}

class User
{
  int age;
  QString name;
  static std::vector<User> users_;

public:
  explicit User(QString name, int age)
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

  static int getTotalCount()
  {
    return users_.size();
  }

  static void addUser(QString name, int age)
  {
    User user(name, age);
    users_.push_back(user);
  }

  static void deleteByName(QString name)
  {
    int size = User::getTotalCount();

    for (int i = 0; i < size; i++)
    {
      if (User::users_[i].name == name)
      {
        User::users_.erase(User::users_.begin() + i);
      }
    }
  }

  static void deleteByIndex(int index)
  {
    User::users_.erase(User::users_.begin() + index);
  }

  static void getUserInfo()
  {
    if (getTotalCount() == 0)
    {
      qDebug() << "There is no Users ";
    }
    else
    {
      qDebug() << getTotalCount();
      for (int i = 0; i < getTotalCount(); i++)
      {
        qDebug() << users_[i].name << " - " << users_[i].age;
      }
    }
  }

  static void removeAllUsers()
  {
    users_.clear();
  }
};

std::vector<User> User::users_;

void MainWindow::on_AddButton_clicked()
{
  QString first_name[5] = { "dave ", "steve ", "martin ", "john ", "dan " };
  QString last_name[5] = { "kant", "jones", "johnson", "jackson", "gomez" };

  QString name = first_name[rand() % 5] + last_name[rand() % 5];

  int age = std::experimental::randint(18, 99);
  User::addUser(name, age);
  User::getUserInfo();
}

void MainWindow::deleteUser()
{
  int getCount = User::getTotalCount();
  if (getCount > 0)
  {
    int index = rand() % getCount;
    User::deleteByIndex(index);

    qDebug() << "User has been deleted ";
    User::getUserInfo();
  }
}

void MainWindow::deleteAllUser()
{
  if (User::getTotalCount() > 0)
  {
    User::removeAllUsers();
    qDebug() << "Users have been deleted successfully. ";
  }
  else
  {
    qDebug() << "There are no users!!";
  }
}
