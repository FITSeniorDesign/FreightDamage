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

private:
    Ui::DamageReport *ui;
};

#endif // DAMAGEREPORT_H
