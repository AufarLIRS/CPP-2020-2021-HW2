#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <string>
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;
using std::string;

class User{
    int age; // private
    std::string name; //private
    static int total_count;
public:
    explicit User(std::string name, int age=18){
        if(age>=18){
            this->age=age;
        }else{
            this->age=18;
        }
        this->name=name;
        total_count++;
    }
    std::string getName(){
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
int User::total_count = 0;
std::vector<User> User::users_;



std::string names [10] = {"Liam","Olivia","Noah","Emma","Oliver","Ava","Willian","Sophia","James","Charlotte"};
  int ages [10] = {10,11,12,13,14,15,16,17,18,19};

void deleteall(){
   qDebug() << "All users deleted ";
   User::users_.clear();
}

void deleteuser(){
   if (!User::users_.empty()) {
       qDebug() << "Random user deleted ";
       int RandIndex = rand() % User::users_.size();
       User::users_.erase(User::users_.begin()+RandIndex);
   }
}

void printStudents(){
    for(int i = 0 ; i < User::users_.size(); i++ ){
         QString qstrnames = QString::fromStdString(names[i]);
         qDebug() << "student name:"<< i << qstrnames << "  " ;
     }

}

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  connect(ui->Delete_All_Button, &QPushButton::clicked,this, &deleteall);
  connect(ui->Delete_Button, &QPushButton::clicked,this, &deleteuser);
  connect(ui->printst,&QPushButton::clicked,this, &printStudents );
}
void MainWindow::on_AddButton_clicked(){
     qDebug() << "New student added ";
     int RandName = rand() % 10;
     int RandAge = rand() % 10;
     User student(names[RandName] ,ages[RandAge]);
     User::users_.push_back(student);


}

MainWindow::~MainWindow()
{
  delete ui;
}



