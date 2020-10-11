#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <string>
#include <ctime>

class User
{
  int age_;
  QString name_;

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
  }
  static void addUser(User user)
  {
    users.push_back(user);
  }
  static void addUser(QString name, int age = 18)
  {
    User user(name, age);
    addUser(user);
  }
  static bool removeUser(unsigned long index)
  {
    if (index < getTotalCount())
    {
      users.erase(users.begin() + index);
      return true;
    }
    return false;
  }
  static unsigned long removeUser(QString name)
  {
    int erased = 0;
    for (auto i = users.begin(); i < users.end(); i++)
    {
      if (i->name_ == name)
      {
        users.erase(i);
        erased++;
      }
    }
    return erased;
  }
  QString getName()
  {
    return name_;
  }
  int getAge()
  {
    return age_;
  }
  static unsigned long getTotalCount()
  {
    return users.size();
  }
  static std::vector<User> users;
};

std::vector<User> User::users;

std::string randString()
{
  std::string tmp = "";
  static const char alp[] = "abcdefghijklmnopqrstuvwxyz";
  int len = rand() % 25 + 1;
  for (int i = 0; i < len; ++i)
  {
    tmp += alp[rand() % (sizeof(alp) - 1)];
  }
  return tmp;
}

void MainWindow::on_addButton_clicked()
{
  User::addUser(QString::fromStdString(randString()), rand() % 63 + 18);
  // qDebug() << User::getTotalCount();
}

void onDeleteClick()
{
  if (User::getTotalCount() > 0)
  {
    User::removeUser(rand() % User::getTotalCount());
  }
  // qDebug() << User::getTotalCount();
}

void onDeleteAllClick()
{
  User::users.clear();
  // qDebug() << User::getTotalCount();
}

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
  srand(time(NULL));
  ui->setupUi(this);
  connect(ui->deleteButton, &QPushButton::clicked, this, &onDeleteClick);
  connect(ui->deleteAllButton, &QPushButton::clicked, this, &onDeleteAllClick);
}

MainWindow::~MainWindow()
{
  delete ui;
}
