#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}
class User{
    int age; // private
    QString name; //private
    static int total_count;
public:
    explicit User(QString name, int age=18){
        if(age>=18){
            this->age=age;
        }else{
            this->age=18;
        }
        this->name=name;
        total_count++;
    }
    QString getName(){
        return name;
    }
    int getAge(){
        return age;
    }
    static int getTotalCount(){
        return total_count;
    }
    static std::vector<User> users_;
};
QString Random_names[5] = {"Alex", "Nick", "Alesha", "Fedor", "Timur"};


int User::total_count = 0;
std::vector<User> User::users_;
void MainWindow::on_pushButton_2_clicked()
{
    User newUser (Random_names[rand()%5], rand()%100);
    User::users_.push_back(newUser);
    qDebug() << "User " << newUser.getName() << (" years old ") << newUser.getAge() << " was add!";
}

void MainWindow::on_pushButton_3_clicked()
{
    auto user = User::users_.begin() + rand()%User::getTotalCount();
    QString name = user->getName();
    User::users_.erase(user);
    qDebug() << name << " was deleted";
}

void MainWindow::on_pushButton_clicked()
{
    User::users_.clear();
    qDebug() << "all people were deleted";
}

