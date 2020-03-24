#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTableWidget>
#include <QColor>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

    QStringList packageIDnums;


public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void fillManifestTable(QString filename);
    QTableWidget* getmainTable() const;
    void setRowColor(int row, Qt::GlobalColor color);

private slots:
    void on_browseButton_clicked();

    void on_reportButton_clicked();

    void on_sortFreightButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
