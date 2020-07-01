#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDate>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    log = new login(this);

    programStart();
    connect(log,SIGNAL(loginSuccessful(QString)),this,SLOT(loggedIn(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::deaktPitanja()
{
    ui->pitanje1->setEnabled(false);
    ui->pitanje2->setEnabled(false);
    ui->pitanje3->setEnabled(false);
    ui->pitanje4->setEnabled(false);
    ui->pitanje5->setEnabled(false);
    ui->pitanje6->setEnabled(false);
    ui->pitanje7->setEnabled(false);
    ui->pitanje8->setEnabled(false);
    ui->pitanje9->setEnabled(false);
    ui->pitanje10->setEnabled(false);
    ui->pitanje11->setEnabled(false);
    ui->pitanje12->setEnabled(false);
    ui->pitanje13->setEnabled(false);
    ui->pitanje14->setEnabled(false);
    ui->pitanje15->setEnabled(false);
    ui->pitanje16->setEnabled(false);
    ui->pitanje17->setEnabled(false);
    ui->pitanje18->setEnabled(false);
    ui->pitanje19->setEnabled(false);
    ui->pitanje20->setEnabled(false);
    ui->pitanje21->setEnabled(false);
    ui->pitanje22->setEnabled(false);
    ui->pitanje23->setEnabled(false);
    ui->pitanje24->setEnabled(false);
    ui->pitanje25->setEnabled(false);
}

void MainWindow::aktPitanja()
{
    ui->pitanje1->setEnabled(true);
    ui->pitanje2->setEnabled(true);
    ui->pitanje3->setEnabled(true);
    ui->pitanje4->setEnabled(true);
    ui->pitanje5->setEnabled(true);
    ui->pitanje6->setEnabled(true);
    ui->pitanje7->setEnabled(true);
    ui->pitanje8->setEnabled(true);
    ui->pitanje9->setEnabled(true);
    ui->pitanje10->setEnabled(true);
    ui->pitanje11->setEnabled(true);
    ui->pitanje12->setEnabled(true);
    ui->pitanje13->setEnabled(true);
    ui->pitanje14->setEnabled(true);
    ui->pitanje15->setEnabled(true);
    ui->pitanje16->setEnabled(true);
    ui->pitanje17->setEnabled(true);
    ui->pitanje18->setEnabled(true);
    ui->pitanje19->setEnabled(true);
    ui->pitanje20->setEnabled(true);
    ui->pitanje21->setEnabled(true);
    ui->pitanje22->setEnabled(true);
    ui->pitanje23->setEnabled(true);
    ui->pitanje24->setEnabled(true);
    ui->pitanje25->setEnabled(true);
}

void MainWindow::openDB()
{
    db = base->getDatabase();
}

void MainWindow::programStart()
{
    ui->label->setFixedWidth(200);
    this->setFixedHeight(600);
    this->setFixedWidth(800);
    ui->progressBar->setValue(0);
    ui->progressBar->setVisible(false);
    ui->progressBar->setMaximum(25);
    deaktPitanja();
    checkDB();
    openDB();
    setButtonColors();

    ui->ending->setVisible(false);
    ui->logout->setVisible(false);
    ui->restart->setVisible(false);
    ui->actionOdgovoreno->setEnabled(false);

}

void MainWindow::setButtonColors()
{
    ui->pitanje1->setStyleSheet("background-color:red");
     ui->pitanje2->setStyleSheet("background-color:red");
      ui->pitanje3->setStyleSheet("background-color:red");
       ui->pitanje4->setStyleSheet("background-color:red");
        ui->pitanje5->setStyleSheet("background-color:red");

     ui->pitanje6->setStyleSheet("background-color:blue");
      ui->pitanje7->setStyleSheet("background-color:blue");
       ui->pitanje8->setStyleSheet("background-color:blue");
        ui->pitanje9->setStyleSheet("background-color:blue");
         ui->pitanje10->setStyleSheet("background-color:blue");

      ui->pitanje11->setStyleSheet("background-color:yellow");
       ui->pitanje12->setStyleSheet("background-color:yellow");
        ui->pitanje13->setStyleSheet("background-color:yellow");
         ui->pitanje14->setStyleSheet("background-color:yellow");
          ui->pitanje15->setStyleSheet("background-color:yellow");

       ui->pitanje16->setStyleSheet("background-color:green");
        ui->pitanje17->setStyleSheet("background-color:green");
         ui->pitanje18->setStyleSheet("background-color:green");
          ui->pitanje19->setStyleSheet("background-color:green");
           ui->pitanje20->setStyleSheet("background-color:green");

        ui->pitanje21->setStyleSheet("background-color:purple");
         ui->pitanje22->setStyleSheet("background-color:purple");
          ui->pitanje23->setStyleSheet("background-color:purple");
           ui->pitanje24->setStyleSheet("background-color:purple");
            ui->pitanje25->setStyleSheet("background-color:purple");
}


void MainWindow::loggedIn(QString userID)
{
    labelUpdate(userID);
    log->close();

    currentID = new QString();
    *currentID = userID;

    ui->progressBar->setVisible(true);
    ui->ending->setVisible(true);
    ui->logout->setVisible(true);
    ui->restart->setVisible(true);
    ui->exit->setVisible(false);

    ui->actionLog_in->setEnabled(false);
    ui->actionOdgovoreno->setEnabled(true);

    aktPitanja();
    StatusBarUpdate();
    checkAnsweredQuestions();  
}

void MainWindow::on_actionLog_in_triggered()
{
    log->exec();
}

void MainWindow::labelUpdate(QString userID)
{
     QSqlQuery qry;

    qry.prepare("SELECT Ime, Prezime FROM Studenti WHERE RedniBroj='"+userID+"' ");
    qry.exec();
    qry.next();
    QString ime = qry.value(0).toString();
    ui->label->setText(qry.value(0).toString() + " " + qry.value(1).toString());
}

bool MainWindow::checkDB()
{
    base = new database();

    if(base->connOpen()) {
        ui->label->setText("Baza podataka je otvorena");
        return true;
    }
    else {
        ui->label->setText("Baza podataka nije otvorena");
        return false;
    }
}

void MainWindow::StatusBarUpdate()
{
    QSqlQuery qry;
    qry.prepare("SELECT Bodovi FROM Studenti WHERE RedniBroj='"+*currentID+"' ");
    qry.exec();
    qry.next();

    currentPoints = new int(qry.value(0).toInt());
    ui->progressBar->setValue(*currentPoints);
}

void MainWindow::insertDate()
{
    QString* date = new QString();
    *date = QDate::currentDate().toString();

    QSqlQuery qry;
    qry.prepare("UPDATE Studenti SET Datum=:value WHERE RedniBroj='"+*currentID+"' ");
    qry.bindValue(":value", *date);
    qry.exec();
}

void MainWindow::setPointsToZero()
{

    QSqlQuery qry;
    int points=0;
    qry.prepare("UPDATE Studenti SET Bodovi=:value WHERE RedniBroj='"+*currentID+"' ");
    qry.bindValue(":value", points);
    qry.exec();
}

void MainWindow::setDateToNull()
{
    QSqlQuery qry;
    qry.prepare("UPDATE Studenti SET Datum=NULL WHERE RedniBroj='"+*currentID+"' ");
    qry.exec();
}

void MainWindow::checkAnsweredQuestions()
{
   QSqlQuery qry;

   qry.prepare("SELECT * FROM Odgovori WHERE RedniBrojStudenta= '"+*currentID+"' ");
   qry.exec();
   qry.next();

   if(qry.value(1).toString() != "Nije odgovoreno") ui->pitanje1->setEnabled(false);
   else ui->pitanje1->setEnabled(true);

   if(qry.value(2).toString() != "Nije odgovoreno") ui->pitanje2->setEnabled(false);
   else ui->pitanje2->setEnabled(true);

   if(qry.value(3).toString() != "Nije odgovoreno") ui->pitanje3->setEnabled(false);
   else ui->pitanje3->setEnabled(true);

   if(qry.value(4).toString() != "Nije odgovoreno") ui->pitanje4->setEnabled(false);
   else ui->pitanje4->setEnabled(true);

   if(qry.value(5).toString() != "Nije odgovoreno") ui->pitanje5->setEnabled(false);
   else ui->pitanje5->setEnabled(true);

   if(qry.value(6).toString() != "Nije odgovoreno") ui->pitanje6->setEnabled(false);
   else ui->pitanje6->setEnabled(true);

   if(qry.value(7).toString() != "Nije odgovoreno") ui->pitanje7->setEnabled(false);
   else ui->pitanje7->setEnabled(true);

   if(qry.value(8).toString() != "Nije odgovoreno") ui->pitanje8->setEnabled(false);
   else ui->pitanje8->setEnabled(true);

   if(qry.value(9).toString() != "Nije odgovoreno") ui->pitanje9->setEnabled(false);
   else ui->pitanje9->setEnabled(true);

   if(qry.value(10).toString() != "Nije odgovoreno") ui->pitanje10->setEnabled(false);
   else ui->pitanje10->setEnabled(true);

   if(qry.value(11).toString() != "Nije odgovoreno") ui->pitanje11->setEnabled(false);
   else ui->pitanje11->setEnabled(true);

   if(qry.value(12).toString() != "Nije odgovoreno") ui->pitanje12->setEnabled(false);
   else ui->pitanje12->setEnabled(true);

   if(qry.value(13).toString() != "Nije odgovoreno") ui->pitanje13->setEnabled(false);
   else ui->pitanje13->setEnabled(true);

   if(qry.value(14).toString() != "Nije odgovoreno") ui->pitanje14->setEnabled(false);
   else ui->pitanje14->setEnabled(true);

   if(qry.value(15).toString() != "Nije odgovoreno") ui->pitanje15->setEnabled(false);
   else ui->pitanje15->setEnabled(true);

   if(qry.value(16).toString() != "Nije odgovoreno") ui->pitanje16->setEnabled(false);
   else ui->pitanje16->setEnabled(true);

   if(qry.value(17).toString() != "Nije odgovoreno") ui->pitanje17->setEnabled(false);
   else ui->pitanje17->setEnabled(true);

   if(qry.value(18).toString() != "Nije odgovoreno") ui->pitanje18->setEnabled(false);
   else ui->pitanje18->setEnabled(true);

   if(qry.value(19).toString() != "Nije odgovoreno") ui->pitanje19->setEnabled(false);
   else ui->pitanje19->setEnabled(true);

   if(qry.value(20).toString() != "Nije odgovoreno") ui->pitanje20->setEnabled(false);
   else ui->pitanje20->setEnabled(true);

   if(qry.value(21).toString() != "Nije odgovoreno") ui->pitanje21->setEnabled(false);
   else ui->pitanje21->setEnabled(true);

   if(qry.value(22).toString() != "Nije odgovoreno") ui->pitanje22->setEnabled(false);
   else ui->pitanje22->setEnabled(true);

   if(qry.value(23).toString() != "Nije odgovoreno") ui->pitanje23->setEnabled(false);
   else ui->pitanje23->setEnabled(true);

   if(qry.value(24).toString() != "Nije odgovoreno") ui->pitanje24->setEnabled(false);
   else ui->pitanje24->setEnabled(true);

   if(qry.value(25).toString() != "Nije odgovoreno") ui->pitanje25->setEnabled(false);
   else ui->pitanje25->setEnabled(true);

}

void MainWindow::restartAnsweredTable()
{
    QSqlQuery qry;

    qry.prepare("DELETE FROM Odgovori WHERE RedniBrojStudenta = '"+*currentID+"' ");
    qry.exec();

    qry.prepare("INSERT INTO Odgovori DEFAULT VALUES");
    qry.exec();
    qry.prepare("UPDATE Odgovori SET RedniBrojStudenta=:value WHERE RedniBrojStudenta IS NULL ");
    qry.bindValue(":value", *currentID);
    qry.exec();
}

void MainWindow::logout()
{
    free(currentID);
    ui->progressBar->setVisible(false);
    ui->actionLog_in->setEnabled(true);
    ui->ending->setVisible(false);
    ui->logout->setVisible(false);
    ui->restart->setVisible(false);
    ui->exit->setVisible(true);
    ui->actionOdgovoreno->setEnabled(false);

    ui->label->setText("Uspješno ste se odjavili.");
    deaktPitanja();
}

void MainWindow::endSession()
{
    this->close();
}

void MainWindow::restartProgress()
{
    setPointsToZero();
    setDateToNull();
    restartAnsweredTable();
    checkAnsweredQuestions();
    StatusBarUpdate();
}

void MainWindow::checkIfAllAreAnswered()
{
    QSqlQuery qry;

    qry.prepare("SELECT * FROM Odgovori WHERE RedniBrojStudenta = '"+*currentID+"' ");
    qry.exec();
    qry.next();

    for(int i=1; i<=25; i++) {
        if(qry.value(i).toString() != "true") {
            insertDate();
            break;
        }
    }
}

int *MainWindow::getCurrentPoints() const
{
    return currentPoints;
}

void MainWindow::setCurrentPoints(int *value)
{
    currentPoints = value;
}

void MainWindow::questionAnswered()
{
    checkAnsweredQuestions();
    checkIfAllAreAnswered();
    StatusBarUpdate();
}

void MainWindow::on_pitanje1_clicked()
{
    rad = new radio(*currentID, "1");
    connect(rad,SIGNAL(answered()),this,SLOT(questionAnswered()));
    rad->exec();
}

void MainWindow::on_pitanje2_clicked()
{
    rad = new radio(*currentID, "2");
    connect(rad,SIGNAL(answered()),this,SLOT(questionAnswered()));
    rad->exec();
}

void MainWindow::on_pitanje3_clicked()
{
    rad = new radio(*currentID, "3");
    connect(rad,SIGNAL(answered()),this,SLOT(questionAnswered()));
    rad->exec();
}

void MainWindow::on_pitanje4_clicked()
{
    rad = new radio(*currentID, "4");
    connect(rad,SIGNAL(answered()),this,SLOT(questionAnswered()));
    rad->exec();
}

void MainWindow::on_pitanje5_clicked()
{
    rad = new radio(*currentID, "5");
    connect(rad,SIGNAL(answered()),this,SLOT(questionAnswered()));
    rad->exec();
}

void MainWindow::on_pitanje6_clicked()
{
    com = new combo(*currentID, "6");
    connect(com,SIGNAL(answered()),this,SLOT(questionAnswered()));
    com->exec();
}

void MainWindow::on_pitanje7_clicked()
{
    com = new combo(*currentID, "7");
    connect(com,SIGNAL(answered()),this,SLOT(questionAnswered()));
    com->exec();
}

void MainWindow::on_pitanje8_clicked()
{
    com = new combo(*currentID, "8");
    connect(com,SIGNAL(answered()),this,SLOT(questionAnswered()));
    com->exec();
}

void MainWindow::on_pitanje9_clicked()
{
    com = new combo(*currentID, "9");
    connect(com,SIGNAL(answered()),this,SLOT(questionAnswered()));
    com->exec();
}

void MainWindow::on_pitanje10_clicked()
{
    com = new combo(*currentID, "10");
    connect(com,SIGNAL(answered()),this,SLOT(questionAnswered()));
    com->exec();
}

void MainWindow::on_pitanje11_clicked()
{
    but = new button(*currentID, "11");
    connect(but,SIGNAL(answered()),this,SLOT(questionAnswered()));
    but->exec();
}

void MainWindow::on_pitanje12_clicked()
{
    but = new button(*currentID, "12");
    connect(but,SIGNAL(answered()),this,SLOT(questionAnswered()));
    but->exec();
}

void MainWindow::on_pitanje13_clicked()
{
    but = new button(*currentID, "13");
    connect(but,SIGNAL(answered()),this,SLOT(questionAnswered()));
    but->exec();
}

void MainWindow::on_pitanje14_clicked()
{
    but = new button(*currentID, "14");
    connect(but,SIGNAL(answered()),this,SLOT(questionAnswered()));
    but->exec();
}

void MainWindow::on_pitanje15_clicked()
{
    but = new button(*currentID, "15");
    connect(but,SIGNAL(answered()),this,SLOT(questionAnswered()));
    but->exec();
}

void MainWindow::on_pitanje16_clicked()
{
    che = new check(*currentID, "16");
    connect(che,SIGNAL(answered()),this,SLOT(questionAnswered()));
    che->exec();
}

void MainWindow::on_pitanje17_clicked()
{
    che = new check(*currentID, "17");
    connect(che,SIGNAL(answered()),this,SLOT(questionAnswered()));
    che->exec();
}

void MainWindow::on_pitanje18_clicked()
{
    che = new check(*currentID, "18");
    connect(che,SIGNAL(answered()),this,SLOT(questionAnswered()));
    che->exec();
}

void MainWindow::on_pitanje19_clicked()
{
    che = new check(*currentID, "19");
    connect(che,SIGNAL(answered()),this,SLOT(questionAnswered()));
    che->exec();
}
void MainWindow::on_pitanje20_clicked()
{
    che = new check(*currentID, "20");
    connect(che,SIGNAL(answered()),this,SLOT(questionAnswered()));
    che->exec();
}

void MainWindow::on_pitanje21_clicked()
{
    che = new check(*currentID, "21");
    connect(che,SIGNAL(answered()),this,SLOT(questionAnswered()));
    che->exec();
}

void MainWindow::on_pitanje22_clicked()
{
    che = new check(*currentID, "22");
    connect(che,SIGNAL(answered()),this,SLOT(questionAnswered()));
    che->exec();
}

void MainWindow::on_pitanje23_clicked()
{
    che = new check(*currentID, "23");
    connect(che,SIGNAL(answered()),this,SLOT(questionAnswered()));
    che->exec();
}

void MainWindow::on_pitanje24_clicked()
{
    che = new check(*currentID, "24");
    connect(che,SIGNAL(answered()),this,SLOT(questionAnswered()));
    che->exec();
}

void MainWindow::on_pitanje25_clicked()
{
    che = new check(*currentID, "25");
    connect(che,SIGNAL(answered()),this,SLOT(questionAnswered()));
    che->exec();
}

void MainWindow::on_ending_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Upozorenje", "Jeste li sigurni da želite završiti?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        endSession();
    }
}

void MainWindow::on_actionPregled_triggered()
{
    view = new overview();
    view->exec();
}

void MainWindow::on_restart_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Upozorenje", "Jeste li sigurni da želite resetirati?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        restartProgress();
    }
}

void MainWindow::on_logout_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Upozorenje", "Jeste li sigurni da se želite odjaviti?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        logout();
    }

}

void MainWindow::on_exit_clicked()
{
    this->close();
}

void MainWindow::on_actionOdgovoreno_triggered()
{
    answer = new answers(*currentID);
    answer->exec();
}
