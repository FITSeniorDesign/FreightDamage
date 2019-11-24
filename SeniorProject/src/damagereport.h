#ifndef DAMAGEREPORT_H
#define DAMAGEREPORT_H

#include <QWidget>

namespace Ui {
class DamageReport;
}

class DamageReport : public QWidget
{
    Q_OBJECT

public:
    explicit DamageReport(QWidget *parent = nullptr);
    ~DamageReport();

private slots:
    void on_submitButton_clicked();

private:
    Ui::DamageReport *ui;
};

#endif // DAMAGEREPORT_H
