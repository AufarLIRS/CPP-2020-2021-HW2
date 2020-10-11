#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>


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

    static std::vector<User> users_;




    size_t getTotalCount(){
        return users_.size();
    }

};

int User::total_count = 0;
std::vector<User> User::users_;

static void add_student(User user){
    User::users_.push_back(user);
}


void delete_student_name(QString name){
    for(int i = 0; i < User::users_.size(); i++){
        if(name == User::users_[i].getName()){
            User::users_.erase(User::users_.begin() + i);
        }
    }
}

static void delete_student_index(int index){
     User::users_.erase(index + User::users_.begin());
 }
int randrange(int randMin,int randMax)
{
  return rand()%(randMin+randMax)+randMin+1;
}



void Delete_all_users()
{
  User::users_.clear();
   qDebug() << "Все студенты удалены " <<  endl;
}

void Delete_random_user()
{
  int randomNum = randrange(0, User::users_.size() - 1);
  delete_student_index(randomNum);
  qDebug() << "Студент удален" <<  endl;
}

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  connect(ui->DeleteAllButton, &QPushButton::clicked, this, &Delete_all_users);
  connect(ui->deleteButton, &QPushButton::clicked, this, &Delete_random_user);
}


MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::on_addButton_clicked()
{
    QString buff_names[10] = { "Саша", "Паша", "Даша", "Коля", "Оля",
                           "Юра", "Семен", "Артем", "Петя", "Лена" };
    QString name = buff_names[randrange(0, 10)];
    int age = randrange(1, 100);
    User new_user(name, age);
    User::users_.push_back(new_user);
    qDebug() << "Был добавлен новый студент " << name << " " << age << endl;
}

