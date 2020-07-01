#include "answers.h"
#include "ui_answers.h"

answers::answers(QString id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::answers)
{
    ui->setupUi(this);

    setID(id);
    openDB();

    querryValue = new int();
    ui->spinBox->setMinimum(1);
    ui->spinBox->setMaximum(25);
    this->resize(300, 50);

    setLabelText(ui->spinBox->text().toInt());
    connect(ui->spinBox,SIGNAL(valueChanged(int)),this,SLOT(setLabelText(int)));
}

answers::~answers()
{
    delete ui;
}

void answers::openDB()
{
    base = new database();
    db = base->getDatabase();
}


void answers::setID(QString id)
{
    this->userID = id;
}


void answers::setLabelText(int QuestionID)
{
    QSqlQuery qry;

    qry.prepare("SELECT * FROM Odgovori WHERE RedniBrojStudenta = '"+userID+"' ");
    qry.exec();
    qry.next();

    ui->label->setText(qry.value(QuestionID).toString());
}
