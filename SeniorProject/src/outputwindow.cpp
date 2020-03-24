#include "outputwindow.h"
#include "ui_outputwindow.h"

OutputWindow::OutputWindow(int rowCount, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OutputWindow)
{
    ui->setupUi(this);
    ui->sortedTable->setRowCount(rowCount);
    ui->sortedTable->horizontalHeader()->setStretchLastSection(true);
}

OutputWindow::~OutputWindow()
{
    delete ui;
}
