#include "damagereport.h"
#include "ui_damagereport.h"

DamageReport::DamageReport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DamageReport)
{
    ui->setupUi(this);
}

DamageReport::~DamageReport()
{
    delete ui;
}
