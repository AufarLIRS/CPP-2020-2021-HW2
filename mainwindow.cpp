#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

class User{
private:
    unsigned short age;
    QString name;
public:
    explicit User(QString name, short age=18){
        if(age>=18)
        {
            this->age=age;
        }
        else
        {
            this->age=18;
        }
        this->name=name;
    }

    QString getName(){
        return name;
    }

    short getAge(){
        return age;
    }

    static unsigned long getTotalCount(){
        return users.size();
    }

    static std::vector<User> users;

    void deleteUserByIndex(unsigned long indexOfDeletedUser) {
        if (indexOfDeletedUser <= users.size()) {
            users.erase(users.begin() + indexOfDeletedUser);
        }
        else {
            qDebug() << "Index of this user is more that our database can contain.";
        }
    }

    static void addUser(User newfag) {
        users.push_back(newfag);
    }

    void deleteUserByName(QString deletedName) {
        for (unsigned long i = 0; i < users.size(); i++) {
            if (users[i].getName() == deletedName) {
                users.erase(users.begin() + i);
                qDebug() << "Deleted successfully.";
            }
            else {
                qDebug() << "User had already been deleted - or just doesn't exist.";
            }
        }
    }

    static User generateUser() {
        std::vector<QString> names = {"?ðò?? ?", "?ò?÷", "?? ? ?",
                                      "? ¡ð?ð?", "?ðò¢? ð¯", "??ý ??",
                                      "??¤ð¯", "?ð ð??", "?¡?÷???ý",
                                      "? ò¡ð?", "???? ", "? ð¡¢ð? ",
                                      "?  ÷   ", "??ð¢ ð?", "???ð? ",
                                      "??ð? ÷?¢ ", "?ð??¤??", "?? ??ðò ",
                                      "?÷¯¢?¡? ÷", "?ð?£ "};
        short int number = rand() % 20;
        User generatedSpeciman {names.at(number), (short)(rand()% 82+18)};
        return generatedSpeciman;
    }
};

static void deleteEveryone() {
    User::users.clear();
    qDebug() << "Sector clear. No witnesses";
}

static void deleteRandom() {
    if (User::users.size() > 0) {
        unsigned long unluckyIndex = rand() % User::users.size();
        User::users.erase(User::users.begin() + unluckyIndex);
        qDebug() << "User with index " << unluckyIndex  << " had just been deleted";
    }
}

std::vector<User> User::users;

MainWindow::~MainWindow()
{
  delete ui;
}

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  connect(ui->DeleteAllUsersButton, &QPushButton::clicked, this, &deleteEveryone);
  connect(ui->DeleteUserButton, &QPushButton::clicked, this, &deleteRandom);
}

void MainWindow::on_AddUserButton_pressed()
{
    User addable = User::generateUser();
    User::addUser(addable);
    qDebug() << "User successfully generated";
}
