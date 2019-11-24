#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void fillManifestTable(QString filename);

private slots:
    void on_browseButton_clicked();

    void on_reportButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
