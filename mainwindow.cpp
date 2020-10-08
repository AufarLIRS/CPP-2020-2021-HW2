#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtGlobal>

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
  static int getTotalCount()
  {
    return total_count;
  }
  static std::vector<User> users_;

  void AddUser(User stud)
  {
    users_.push_back(stud);
  }

  void DeleteByIndex(int k)  //пример: 0 1 2 3 4 5 Удалить k=2 Результат 0 2 3 4 5
  {
    if (k <= users_.size())
    {
      users_.erase(users_.begin() + k - 1);
      total_count -= 1;
    }
  }

  void DeleteByName(QString name)  //удаляет первое совпадающее имя
  {
    for (int i = 0; i < users_.size(); i++)
    {
      if (users_[i].getName() == name)
      {
        users_.erase(users_.begin() + i);
        total_count -= 1;
        break;
      }
    }
  }
  int GetCount()
  {
    return users_.size();
  }
  void CountNull()
  {
    total_count = 0;
  };
};

int User::total_count = 0;
std::vector<User> User::users_;
QString RandomName()
{
  QString E;
  char c;
  int r;
  srand(time(NULL));  // initialize the random number generator
  for (int i = 0; i < 6; i++)
  {
    r = rand() % 26;  // generate a random number
    c = 'a' + r;      // Convert to a character from a-z
    E += c;
  }
  return E;
}
static int RandomNum(int low, int high)
{
  return (qrand() % ((high + 1) - low) + low);
}

void MainWindow::on_pushButton_clicked()
{
  User Rand = User(RandomName(), RandomNum(1, 100));
  Rand.AddUser(Rand);
}

void ClearUsers()
{
  User::users_[0].CountNull();
  User::users_.clear();
}
void DeleteRandom()
{
  if (!User::users_.empty())
  {
    if (User::users_[0].GetCount() != 1)
    {
      User::users_[0].DeleteByIndex(RandomNum(0, User::users_.size()));
    }
    else
      ClearUsers();
  }
}

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  connect(ui->pushButton_2, &QPushButton::clicked, this, &DeleteRandom);

  connect(ui->pushButton_3, &QPushButton::clicked, this, &ClearUsers);
}

MainWindow::~MainWindow()
{
  delete ui;
}
