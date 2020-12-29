#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <string>

class User
{
    int age;
    QString name;

public:
    explicit User(QString name, int age=18){
        if(age>=18){
            this->age=age;
        }else{
            this->age=18;
        }
        this->name=name;
    }

    static void addStud(User user)
    {
        users.push_back(user);
    }

    static void deleteStudIndex(unsigned int index)
    {
        users.erase(users.begin() + index);
    }

    static void deleteStudName(QString name)
    {
        for (unsigned int i = 0; i < users.size(); i++)
        {
            if (name == users[i].name)
            {
                users.erase(users.begin() + i);
            }
        }
    }

    QString getName(){
        return name;
    }
    int getAge(){
        return age;
    }
    static int getTotalCount(){
        return users.size();
    }
    static std::vector<User> users;
};

std::vector<User> User::users;

QString RandomName()
{
    int a = rand() % (10 - 3 + 1) + 3;
    QString name;
    while (a>0)
    {
    char c = (char) (rand() % (127-33) + 33);
    name += c;
    }
    return name;
}

static int RandomNumber(int min, int max)
{
    return rand() % (max - min + 1);
}

void MainWindow::on_pushButton_clicked()
{
    User userRand = User(RandomName(), RandomNumber(1, 30));
    userRand.addStud(userRand);
}

void DeleteStudByCLick()
{
    User::users[0].getTotalCount();
    User::users.clear();
}

void DeleteRandomStudByClick()
{
    if (!User::users.empty())
    {
        if (User::users[0].getTotalCount() != 1)
        {
            User::users[0].deleteStudIndex(RandomNumber(0, User::users.size()));
        }
        else
            qDebug() << "Not found" << endl;
    }
}

MainWindow :: MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &DeleteStudByCLick);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &DeleteRandomStudByClick);
}

MainWindow::~MainWindow()
{
    delete ui;
}



