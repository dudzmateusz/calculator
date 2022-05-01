#include "calculator.h"
#include "./ui_calculator.h"
#include <QRegularExpression>
#include <math.h>

double calcVal = 0.0;
double save = 0.0;
double solution = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;
bool sqrTrigger = false;
bool history = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for (int i = 0; i<10; ++i){
        QString butName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }
    connect(ui->Add, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Sqr, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Equals, SIGNAL(released()), this, SLOT(EqualButtonPressed()));
    connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(ChangeNumberSign()));
    connect(ui->Clear, SIGNAL(released()), this, SLOT(ClearButtonPressed()));
    connect(ui->Dot, SIGNAL(released()), this, SLOT(AddDotButtonPressed()));
    connect(ui->MemAdd, SIGNAL(released()), this, SLOT(MemAddButtonPressed()));
    connect(ui->MemGet, SIGNAL(released()), this, SLOT(MemGetButtonPressed()));
    connect(ui->MemClear, SIGNAL(released()), this, SLOT(MemClearButtonPressed()));
    connect(ui->History, SIGNAL(released()), this, SLOT(HistoryNumPressed()));


}

Calculator::~Calculator()
{
    delete ui;
}




void Calculator::NumPressed(){

    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    if ((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)) {
        ui->Display->setText(butVal);
    } else {
    QString newVal = displayVal + butVal;
    double dblNewVal = newVal.toDouble();
    ui->Display->setText(QString::number(dblNewVal, 'g', 16));
    }

}


void Calculator::MathButtonPressed() {
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    sqrTrigger = false;
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    if (QString::compare(butVal, "/", Qt::CaseInsensitive)== 0){
        divTrigger = true;
    }else if (QString::compare(butVal, "*", Qt::CaseInsensitive)== 0){
        multTrigger = true;
    } else if (QString::compare(butVal, "+", Qt::CaseInsensitive)== 0){
        addTrigger = true;
    } else if (QString::compare(butVal, "x^2", Qt::CaseInsensitive)== 0){
        sqrTrigger = true;
        solution = sqrt(calcVal);
    } else {
        subTrigger = true;
    }

    ui->History->setText(((QString::number(calcVal))+(QString(butVal))));
    ui->Display->setText("");
    if (sqrTrigger == true) {
        ui->Display->setText(QString::number(solution));
    }
}

void Calculator::EqualButtonPressed() {
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    if (addTrigger || subTrigger || multTrigger || divTrigger){
        if (addTrigger){
            solution = calcVal + dblDisplayVal;

        } else if (subTrigger){
            solution = calcVal - dblDisplayVal;
        } else if (multTrigger){
            solution = calcVal * dblDisplayVal;
        } else{

            solution = calcVal / dblDisplayVal;
        }

        ui->Display->setText(QString::number(solution));
        ui->History->setText(QString::number(solution));
    }
    }

void Calculator::ChangeNumberSign(){
    QString displayVal = ui->Display->text();
    QRegularExpression rx("[-]?[0-9.]*");
    QRegularExpressionMatch match = rx.match(displayVal);
    if(match.hasMatch()){
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;
        ui->Display->setText((QString::number(dblDisplayValSign)));

    }

}

void Calculator::ClearButtonPressed(){
    double solution = 0.0;
    ui->Display->setText(QString::number(solution));
}

void Calculator::AddDotButtonPressed(){
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    QString dot = ".";
    if (displayVal.isEmpty()){
    } else {
        ui->Display->setText((QString::number(dblDisplayVal))+(QString(dot)));
    }
}

void Calculator::MemAddButtonPressed(){
    QString displayVal = ui->Display->text();
    save += displayVal.toDouble();
}

void Calculator::MemGetButtonPressed(){
    ui->Display->setText(QString::number(save));
}

void Calculator::MemClearButtonPressed(){
    save = 0.0;
}


