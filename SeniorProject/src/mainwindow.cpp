#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "PlacementAlgo.h"
#include "damagereport.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_browseButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Select File", "C://", "CSV Files (*.csv)");
    ui->csvLineEdit->setText(filename);
    //cout << filename.toStdString() << endl;
    fillManifestTable(filename);
}

void MainWindow::fillManifestTable(QString filename)
{
    ifstream file(filename.toStdString());
    //file.open(filename.toStdString());

    string input;
    getline(file, input);

    vector<Package> manifest;												// Have a manifest of packages

    if (file) {
        int row = 0;
        while (getline(file, input, '\n')) {									// Iterate over each line in the input
            if (row > ui->tableWidget->rowCount())
            {
                ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            }
            vector<int> packageInfo;											// Vector to hold the package information
            for (int start = 0, end = 0, column = 0; start < (int)input.length(); end++)	// Iterate over the entire string
            {
                if (input[end] == ',') {										// A comma is found
                    string stdString = input.substr(start, end - start);
                    cout << stdString << endl;
                    try {														// Try a statement
                        packageInfo.push_back(stoi(input.substr(start, end)));	// Convert the string to an int and save
                        QString data = QString::fromStdString(stdString);
                        ui->tableWidget->setItem(row, column, new QTableWidgetItem(data));
                    } catch (...) {												// Catch any exception thrown
                        if (stdString == "Yes") {		// Input was yes
                            packageInfo.push_back(1);							// Push on a true
                            ui->tableWidget->setItem(row, column, new QTableWidgetItem("Yes"));
                        }
                        else {												// Input was not yes
                            packageInfo.push_back(0);							// Push on a false
                            ui->tableWidget->setItem(row, column, new QTableWidgetItem("No"));
                            }
                    }
                    start = end + 1;											// Move passed the comma
                    column++;
                }
            }
            row++;

//            manifest.push_back(Package(packageInfo[0], packageInfo[1],			// Add the package object to a list of all package objects
//                    packageInfo[2], packageInfo[3], packageInfo[4],
//                    packageInfo[5], packageInfo[6]));
        }
    }


}

void MainWindow::on_reportButton_clicked()
{
    if (ui->csvLineEdit->text().isEmpty())
    {
        QMessageBox::warning(this, "Warning", "No items to report damages on.");
    }
    else {
        DamageReport *damageReport = new DamageReport();
        damageReport->show();
    }

}
