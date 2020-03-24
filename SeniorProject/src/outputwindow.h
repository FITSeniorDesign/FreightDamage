#ifndef OUTPUTWINDOW_H
#define OUTPUTWINDOW_H

#include <QWidget>
#include <QTableWidget>

namespace Ui {
class OutputWindow;
}

class OutputWindow : public QWidget
{
    Q_OBJECT

public:
    explicit OutputWindow(int rowCount, QWidget *parent = nullptr);
    ~OutputWindow();
    Ui::OutputWindow *ui;
};

#endif // OUTPUTWINDOW_H
