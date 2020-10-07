#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>  //first- in system files, later - in project files
#include <QMessageBox>
#include <QRandomGenerator64>
#include <cstdlib>
 #include <sstream>
 #include <string>
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
int User::total_count = 0;
std::vector<User> User::users_;

static void ListOfUsers(User new_user){
    User::users_.push_back(new_user);
}
static void DeleteUserById(size_t id){
    QString user;
    if(id<0 || id>=User::users_.size()){
        qDebug()<<"все пользователи удалены";
        return;
    }
    if(User::users_.size()==0)
    {
        qDebug()<<"все пользователи удалены";
        return;
    }
    else
    {
        user=User::users_[id].getName();
        User::users_.erase(User::users_.begin() + id);
    }
    qDebug()<<"пользователь"<< user << "удален!"<<endl;
}
static size_t GetUserSize(){
    return User::users_.size();
}
static void DeleteUserByName(QString name){
    for(unsigned int i=0; i < User::users_.size(); i++)
    {
        if(User::users_[i].getName()== name)
            User::users_.erase(User::users_.begin() + i);
    }
}
int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    // Равномерно распределяем рандомное число в нашем диапазоне
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}
void DeleteOnClick()
{
    qint64 val = getRandomNumber(0,User::users_.size()-1);
    DeleteUserById(val);


}
void DeletAllOnClick()
{
    User::users_.clear();
    qDebug()<<"все пользователи удалены";
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->Delete_button, &QPushButton::clicked, this, &DeleteOnClick);
    connect(ui->Delete_all_button, &QPushButton::clicked, this, &DeletAllOnClick);
    qDebug() << "App started! ";
    //&- взятие адреса функции/переменной/поля в классе/т.д.
}

MainWindow::~MainWindow()
{
    qDebug() << "App closed! ";
    delete ui;
}


void MainWindow::on_submitPushButton_clicked()
{
    qDebug() << "User clicked on submit button";
    // ui->nameLineEdit->setText("Aufar");
    //User student(ui->nameLineEdit->text(), ui->ageLineEdit->text().toInt());

   // QMessageBox msg(QMessageBox::Information,"New student arrived!",
   //                "Hello "+ student.getName() + "!");
    // qDebug() << "Name:" << student.getName();
    // qDebug() << "Age:" << student.getAge();
    //qDebug() << msg.exec();
    qDebug() << User::getTotalCount();
    //User::users_.push_back(student);
    //qDebug() << "Last student age:" << User::users_.end()->getAge();
    //qDebug() << "Last student name:" << User::users_.end()->getName();
    qDebug() << "Total count:" << User::users_.size();
    qDebug() << "First student name ([0]):" << User::users_[0].getName();
    qDebug() << "First student name (at):" << User::users_.at(0).getName();
    qDebug() << "------------------------";
}


void MainWindow::on_add_button_clicked()
{
    int randAge=getRandomNumber(16,100);
    QString names[20]={"Timur","Niyaz","Igor","Ruslan","Svetlana",
                       "Alsu","Valeriy","Semen","Kamil'","Dias",
                       "Sergey","Nikita","Alexander","Ildar","Ilshat",
                       "Anonim","Winston","Camel","Malboro","Maxim"
                     };
    QString name=names[getRandomNumber(0,20)];
    User new_user(name,randAge);
    User::users_.push_back(new_user);
    qDebug()<<"add new user " << name <<randAge <<endl;
}

