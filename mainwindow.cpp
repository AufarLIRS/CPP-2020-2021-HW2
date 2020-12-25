#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

class User
{
  int age;       // private
  QString name;  // private
  static std::vector<User> users_;

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

  static QString getNameOfIndex(int index)
  {
    return users_[index].getName();
  }

  static void add_student(QString name, int age)
  {
    User user(name, age);
    users_.push_back(user);
  }

  static size_t getTotalCount()
  {
    return users_.size();
  }

  void delete_student_name(QString name)
  {
    for (int i = 0; i < User::getTotalCount(); i++)
    {
      if (name == User::users_[i].name)
      {
        User::users_.erase(User::users_.begin() + i);
      }
    }
  }

  static void delete_student_index(int index)
  {
    User::users_.erase(index + User::users_.begin());
  }

  static void Delete_all_users()
  {
    users_.clear();
    qDebug() << "Все студенты удалены " << endl;
  }
};
std::vector<User> User::users_;

int randrange(int randMin, int randMax)
{
  return rand() % (randMin + randMax) + randMin + 1;
}

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  connect(ui->DeleteAllButton, &QPushButton::clicked, this, &MainWindow::deleteAllUser);
  connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::deleteUser);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_addButton_clicked()
{
  QString buff_names[10] = { "Саша", "Паша", "Даша", "Коля", "Оля", "Юра", "Семен", "Артем", "Петя", "Лена" };
  QString name = buff_names[randrange(0, 9)];
  int age = randrange(1, 100);
  User::add_student(name, age);
  qDebug() << "Был добавлен новый студент " << name << " " << age << endl;
}
void MainWindow::deleteUser()
{
  if (User::getTotalCount() > 0)
  {
    int countUsers = User::getTotalCount();
    int index = randrange(1, countUsers);
    User::delete_student_index(index);
    qDebug() << "Студент был удалён";
  }
  else
  {
    qDebug() << "В списке нет студентов";
  }
}
void MainWindow::deleteAllUser()
{
  if (User::getTotalCount() > 0)
  {
    User::Delete_all_users();
    qDebug() << "Все студенты были удалены";
  }
  else
  {
    qDebug() << "В списке нет студентов";
  }
}
