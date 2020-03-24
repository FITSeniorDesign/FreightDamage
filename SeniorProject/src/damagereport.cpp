#include "damagereport.h"
#include "ui_damagereport.h"
#include "mainwindow.h"
#include <QMessageBox>

DamageReport::DamageReport(MainWindow *mainWindow, QStringList *packageIDnums, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DamageReport)
{
    ui->setupUi(this);
    this->mainWindow = mainWindow;

    for (int row=0; row< packageIDnums->size(); row++)
    {
        ui->packageIDCombo->addItem(packageIDnums->at(row));
    }

}

DamageReport::~DamageReport()
{
    delete ui;
}

void DamageReport::on_submitButton_clicked()
{
    QLineEdit *trailerNum = ui->trailerNumText;
    QComboBox *packageID = ui->packageIDCombo;
    QTextEdit *description = ui->descriptionText;
    QLineEdit *employee = ui->employeeText;
    QLineEdit *supervisor = ui->supervisorText;
    QLineEdit *date = ui->dateText;

    if (trailerNum->text().isEmpty() || (packageID->currentIndex() == -1) || description->document()->isEmpty()
            || employee->text().isEmpty() || supervisor->text().isEmpty() || date->text().isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Please fill in all required fields.");
    } else {
        this->close();
        int damPackage = packageID->currentIndex();
        mainWindow->setRowColor(damPackage, Qt::red);
    }

}
