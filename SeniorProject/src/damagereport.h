#ifndef DAMAGEREPORT_H
#define DAMAGEREPORT_H

#include <QWidget>
#include <QTableWidget>
#include "mainwindow.h"

namespace Ui {
class DamageReport;
}

class DamageReport : public QWidget
{
    Q_OBJECT

public:
    explicit DamageReport(MainWindow *window, QStringList *packageIDnums, QWidget *parent = nullptr);
    MainWindow *mainWindow;
    ~DamageReport();

private slots:
    void on_submitButton_clicked();

private:
    Ui::DamageReport *ui;
};

#endif // DAMAGEREPORT_H
