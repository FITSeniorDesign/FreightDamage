#include "damagereport.h"
#include "ui_damagereport.h"
#include <QMessageBox>

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

void DamageReport::on_submitButton_clicked()
{
    QLineEdit *trailerNum = ui->trailerNumText;
    QLineEdit *packageID = ui->packageIDText;
    QTextEdit *description = ui->descriptionText;
    QLineEdit *employee = ui->employeeText;
    QLineEdit *supervisor = ui->supervisorText;
    QLineEdit *date = ui->dateText;

    if (trailerNum->text().isEmpty() || packageID->text().isEmpty() || description->document()->isEmpty()
            || employee->text().isEmpty() || supervisor->text().isEmpty() || date->text().isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Please fill in all required fields.");
    } else {
        this->close();
    }

}
