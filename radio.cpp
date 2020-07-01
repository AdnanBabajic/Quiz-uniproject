#include "radio.h"
#include "ui_radio.h"
#include <QDebug>

radio::radio(QString id, QString qid, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::radio)
{
    ui->setupUi(this);

    setID(id);
    setQuestion(qid);
    loadQuestion();
    loadAnswers();

    answer1 = false;
    answer2 = false;
    answer3 = false;
    answer4 = false;
    answer5 = false;

    checkRightAnswer();
}

radio::~radio()
{
    delete ui;
}

void radio::openDB()
{
    base = new database();
    db = base->getDatabase();
}

void radio::setID(QString id)
{
    this->userID = id;
}

void radio::setQuestion(QString qid)
{
    this->questionID = qid;
}

void radio::loadQuestion()
{
    openDB();

    QSqlQuery qry;
    qry.prepare("SELECT TekstPitanja FROM Pitanja WHERE RedniBroj='"+questionID+"' ");
    qry.exec();
    qry.next();
    ui->label->setText(qry.value(0).toString());
}

void radio::loadAnswers()
{

    QSqlQuery qry;
    qry.prepare("SELECT Odgovor1, Odgovor2, Odgovor3, Odgovor4, Odgovor5 FROM Pitanja WHERE RedniBroj='"+questionID+"' ");
    qry.exec();
    qry.next();
    ui->ans1->setText(qry.value(0).toString());
    ui->ans2->setText(qry.value(1).toString());
    ui->ans3->setText(qry.value(2).toString());
    ui->ans4->setText(qry.value(3).toString());
    ui->ans5->setText(qry.value(4).toString());
}

void radio::checkRightAnswer()
{
    QSqlQuery qry;
    qry.prepare("SELECT TacanOdg1, TacanOdg2, TacanOdg3 FROM Pitanja WHERE RedniBroj='"+questionID+"' ");
    qry.exec();
    qry.next();

    if(ui->ans1->text() == qry.value(0).toString()
            || ui->ans1->text() == qry.value(1).toString()
                || ui->ans1->text() == qry.value(2).toString()) answer1 = true;

    if(ui->ans2->text() == qry.value(0).toString()
            || ui->ans2->text() == qry.value(1).toString()
                || ui->ans2->text() == qry.value(2).toString()) answer2 = true;

    if(ui->ans3->text() == qry.value(0).toString()
            || ui->ans3->text() == qry.value(1).toString()
                || ui->ans3->text() == qry.value(2).toString()) answer3 = true;

    if(ui->ans4->text() == qry.value(0).toString()
            || ui->ans4->text() == qry.value(1).toString()
                || ui->ans4->text() == qry.value(2).toString()) answer4 = true;

    if(ui->ans5->text() == qry.value(0).toString()
            || ui->ans5->text() == qry.value(1).toString()
            || ui->ans5->text() == qry.value(2).toString()) answer5 = true;
}

void radio::checkSelected()
{
    finalRes = false;

    if(ui->ans1->isChecked()) {
        if(answer1 == true) finalRes = true;
        else finalRes = false;
        }

    if(ui->ans2->isChecked()) {
        if(answer2 == true) finalRes = true;
        else finalRes = false;
        }

    if(ui->ans3->isChecked()) {
        if(answer3 == true) finalRes = true;
        else finalRes = false;
        }

    if(ui->ans4->isChecked()) {
        if(answer4 == true) finalRes = true;
        else finalRes = false;
        }

    if(ui->ans5->isChecked()) {
        if(answer5 == true) finalRes = true;
        else finalRes = false;
    }
}

void radio::pointsInsert()
{
    QSqlQuery qry;
    qry.prepare("SELECT Bodovi FROM Studenti WHERE RedniBroj='"+userID+"' ");
    qry.exec();
    qry.next();

    int points = qry.value(0).toInt();

    if(finalRes == true) points++;

    qry.prepare("UPDATE Studenti SET Bodovi=:value WHERE RedniBroj='"+userID+"' ");
    qry.bindValue(":value", points);
    qry.exec();
}

void radio::writeAnswred()
{
    QSqlQuery qry;

    finalWriteRes = new QString();
    if(finalRes == true) *finalWriteRes = "true";
    else *finalWriteRes = "false";
    questionToString();

    qry.prepare("UPDATE Odgovori SET '"+*questionTable+"'=:value WHERE RedniBrojStudenta='"+userID+"' ");
    qry.bindValue(":value", *finalWriteRes);
    qry.exec();
}

void radio::questionToString()
{
    questionTable = new QString();

    if(questionID == "1") *questionTable = "Pitanje1";
    else if(questionID == "2") *questionTable = "Pitanje2";
    else if(questionID == "3") *questionTable = "Pitanje3";
    else if(questionID == "4") *questionTable = "Pitanje4";
    else if(questionID == "5") *questionTable = "Pitanje5";
    else if(questionID == "6") *questionTable = "Pitanje6";
    else if(questionID == "7") *questionTable = "Pitanje7";
    else if(questionID == "8") *questionTable = "Pitanje8";
    else if(questionID == "9") *questionTable = "Pitanje9";
    else if(questionID == "10") *questionTable = "Pitanje10";
    else if(questionID == "11") *questionTable = "Pitanje11";
    else if(questionID == "12") *questionTable = "Pitanje12";
    else if(questionID == "13") *questionTable = "Pitanje13";
    else if(questionID == "14") *questionTable = "Pitanje14";
    else if(questionID == "15") *questionTable = "Pitanje15";
    else if(questionID == "16") *questionTable = "Pitanje16";
    else if(questionID == "17") *questionTable = "Pitanje17";
    else if(questionID == "18") *questionTable = "Pitanje18";
    else if(questionID == "19") *questionTable = "Pitanje19";
    else if(questionID == "20") *questionTable = "Pitanje20";
    else if(questionID == "21") *questionTable = "Pitanje21";
    else if(questionID == "22") *questionTable = "Pitanje22";
    else if(questionID == "23") *questionTable = "Pitanje23";
    else if(questionID == "24") *questionTable = "Pitanje24";
    else if(questionID == "25") *questionTable = "Pitanje25";
}

void radio::on_pushButton_clicked()
{
    checkSelected();
    pointsInsert();
    writeAnswred();
    emit answered();
    this->close();
}
