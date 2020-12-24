#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


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

   static void addUser(User user)
   {
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
 QString RandomName()
  {
    QString E;
    char c;
    int r;
    srand(time(NULL));
    for (int i = 0; i < 6; i++)
    {
      r = rand() % 26;  // generate a random number
      c = 'a' + r;
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
      Rand.addUser(Rand);
      qDebug() << "User hac been created: " << Rand.getName() + " " + Rand.getAge();
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

 void MainWindow::deleteAllOfUsers()
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


 MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
 {
     ui->setupUi(this);
     connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::deleteUser);
     connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::deleteAllOfUsers);

 }
MainWindow::~MainWindow()
{
    delete ui;
}

