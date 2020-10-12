#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <cstdlib>
#include <ctime>

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
  static std::vector<User> users_;

  static void addUser(int age, QString name)
  {
    User user = User(name, age);
    users_.push_back(user);
  }
  static void deleteByIndex(int a)
  {
    users_.erase(users_.begin() + a);
  }
  static void deleteByName(QString name)
  {
    for (size_t i = 0; i < users_.size(); i++)
    {
      if (users_[i].getName() == name)
      {
        users_.erase(users_.begin() + i);
      }
    }
  }
};

int User::total_count = 0;
std::vector<User> User::users_;

void deleteButton_clicked()
{
  if (!User::users_.empty())
  {
    srand(time(NULL));
    int r = rand() % User::users_.size();
    qDebug() << "Случайный пользователь с именем " << User::users_[r].getName() << " и возрастом"
             << User::users_[r].getAge() << "Удален";
    User::deleteByIndex(r);
  }
  else
  {
    qDebug() << "Список пуст, удалять некого.";
  }
}

void deleteAllButton_clicked()
{
  if (!User::users_.empty())
  {
    User::users_.clear();
    qDebug() << "Все студенты удалены";
  }
  else
  {
    qDebug() << "Список пуст, удалять некого.";
  }
}

void MainWindow::on_addButton_clicked()
{
  QString names[10] = { "Alex",    "Roman", "Isaac",  "Richard",   "Michael",
                        "Jessica", "Emma",  "Rachel", "Jenniffer", "Masha" };
  srand(time(NULL));
  int i = rand() % 9;
  int age = rand() % 100;
  QString name = names[i];
  User user = User(name, age);
  user.addUser(age, name);
  qDebug() << "Пользователь с именем " << user.getName() << " и возрастом" << user.getAge() << "добавлен";
}

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  connect(ui->deleteAllButton, &QPushButton::clicked, this, &deleteAllButton_clicked);
  connect(ui->deleteButton, &QPushButton::clicked, this, &deleteButton_clicked);
}

MainWindow::~MainWindow()
{
  delete ui;
}
