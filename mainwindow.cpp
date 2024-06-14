#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "header.h"
#include <QFileDialog>
#include "tagsviewform.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    std::string name = "/mnt/shared/Linux Files/1AOjSL-hZrg.tiff";
    ui->tableWidgetTiffData->setEditTriggers(0);
    ui->tableWidgetGeoData->setEditTriggers(0);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->tabGeoData), false);
    this->setFixedSize(899, 636);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonOpen_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("TIFF Files (*.tiff *.tif);;All Files (*)"));

    if (!filePath.isEmpty()) {
        pathName = filePath.toStdString();
        ui->pathLabel->setText(filePath);

        ui->tableWidgetTiffData->setRowCount(0);
        tiffTagsInFile.clear();
        GeoTiffTagsInFile.clear();

        TiffTagsVieawer tif(pathName.data());
        tif.fillTagVecFromFile();

        numPages = tiffTagsInFile.size();
        ui->numTagsLabel->setText(std::to_string(tiffTagsInFile[0].size()).c_str());
        curPage = 1;

        ui->pageLabel->setText(QString("страница %1 из %2").arg(curPage).arg(numPages));
        if(tif.isBigTiff)
            ui->isBigTiffLabel->setText("Да");
        else
            ui->isBigTiffLabel->setText("Нет");


        // Set up the table widget
        ui->tableWidgetTiffData->setColumnCount(5);
        QStringList headers = {"Код", "Название", "Тип данных", "количество", "Значения"};
        ui->tableWidgetTiffData->setHorizontalHeaderLabels(headers);

        // Stretch the last column to fill the remaining space
        ui->tableWidgetTiffData->horizontalHeader()->setStretchLastSection(true);


        int row = 0;
            for (const auto& tag : tiffTagsInFile[0]) {
                ui->tableWidgetTiffData->insertRow(row);
                ui->tableWidgetTiffData->setItem(row, 0, new QTableWidgetItem(QString::number(tag.code)));
                ui->tableWidgetTiffData->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(tag.name)));
                ui->tableWidgetTiffData->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(tag.type)));
                ui->tableWidgetTiffData->setItem(row, 3, new QTableWidgetItem(QString::number(tag.count)));
                ui->tableWidgetTiffData->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(tag.values)));
                ++row;
            }

        int defaultRowHeight = 10;
        for (int row = 0; row < ui->tableWidgetTiffData->rowCount(); ++row) {
            ui->tableWidgetTiffData->setRowHeight(row, defaultRowHeight);
        }
        ui->tableWidgetTiffData->setColumnWidth(0, 60);
        ui->tableWidgetTiffData->setColumnWidth(1, 200);
        ui->tableWidgetTiffData->setColumnWidth(2, 80);
        ui->tableWidgetTiffData->setColumnWidth(3, 70);

        if(tif.isGeoTiff)
        {
            ui->tableWidgetGeoData->setRowCount(0);
            ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->tabGeoData), true);

            // Set GeoTIFF data to the labels
            ui->keyDirectoryVersionLabel->setText(QString::number(GeoTiffHeaderInFile.KeyDirectoryVersion));
            ui->keyVersionLabel->setText(QString("%1.%2").arg(GeoTiffHeaderInFile.KeyRevision).arg(GeoTiffHeaderInFile.MinorRevision));
            ui->numbKeysLabel->setText(QString::number(GeoTiffHeaderInFile.NumberOfKeys));

            ui->uLLabel->setText(QString::fromStdString(getStringGeoCoordinates(geoCornerCoordinatesInFile.upperLeft)));
            ui->lLLabel->setText(QString::fromStdString(getStringGeoCoordinates(geoCornerCoordinatesInFile.lowerLeft)));
            ui->uRLabel->setText(QString::fromStdString(getStringGeoCoordinates(geoCornerCoordinatesInFile.upperRight)));
            ui->lRLabel->setText(QString::fromStdString(getStringGeoCoordinates(geoCornerCoordinatesInFile.lowerRight)));
            ui->centerLabel->setText(QString::fromStdString(getStringGeoCoordinates(geoCornerCoordinatesInFile.center)));

            //ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->tabGeoData), true);

            // Set up the table widget
            ui->tableWidgetGeoData->setColumnCount(4);
            QStringList headers = {"Код", "Название", "Тип данных", "Значениe"};
            ui->tableWidgetGeoData->setHorizontalHeaderLabels(headers);

            // Stretch the last column to fill the remaining space
            ui->tableWidgetGeoData->horizontalHeader()->setStretchLastSection(true);


            for (int i = 0; i < GeoTiffTagsInFile.size(); ++i) {
                ui->tableWidgetGeoData->insertRow(i);
                ui->tableWidgetGeoData->setItem(i, 0, new QTableWidgetItem(QString::number(GeoTiffTagsInFile[i].code)));
                ui->tableWidgetGeoData->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(GeoTiffTagsInFile[i].name)));
                ui->tableWidgetGeoData->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(GeoTiffTagsInFile[i].type)));
                ui->tableWidgetGeoData->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(GeoTiffTagsInFile[i].value)));
            }

            int defaultRowHeight = 10;
            for (int row = 0; row < ui->tableWidgetGeoData->rowCount(); ++row) {
                ui->tableWidgetGeoData->setRowHeight(row, defaultRowHeight);
            }
            ui->tableWidgetGeoData->setColumnWidth(0, 60);
            ui->tableWidgetGeoData->setColumnWidth(1, 200);
            ui->tableWidgetGeoData->setColumnWidth(2, 80);
        }
        else
        {
            ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->tabGeoData), false);
        }
    }
}

int getMaxLengthValue(string values)
{
    int k = 0;
    int kmax = 0;
    for (int i = 0; i < values.size(); i++)
        if (values[i] != ' ')
        {
            k++;
            if (k > kmax)
                kmax = k;
        }
        else
            k = 0;

    return kmax;
}

string getStructValues(string values)
{
    int maxLen = getMaxLengthValue(values);
    int len;
    for (int i = 0; i < values.size(); i++)
    {
        len = 0;
        if (values[i] != ' ')
        {
            while (values[i] != ' ' || i >= values.size())
            {
                i++;
                len++;
            }
            if (len < maxLen)
                for (int k = 0; k < (maxLen - len) * 2; k++)
                    values.insert(i - len, " ");
            i += (maxLen - len) * 2;
        }
    }
    return values;
}

void MainWindow::on_buttonViewContents_clicked()
{
    if (ui->tabWidget->currentWidget() == ui->tabTiffData) {
        if (ui->tableWidgetTiffData->selectedItems().count() == 5) {
            QString val = ui->tableWidgetTiffData->selectedItems().at(4)->text();
            QString st = ui->tableWidgetTiffData->selectedItems().at(3)->text();
            if (st != "1" && ui->tableWidgetTiffData->selectedItems().at(2)->text() != "ASCII") {
                std::string str = val.toStdString();
                val = QString::fromStdString(getStructValues(str)); // Предполагается, что у вас есть функция getStructValues
            }
            tagsviewform *forma = new tagsviewform();
            forma->setTextBoxValue(val);
            forma->show();
        }
    } else if (ui->tabWidget->currentWidget() == ui->tabGeoData) {
        if (ui->tableWidgetGeoData->selectedItems().count() == 4) {
            QString val = ui->tableWidgetGeoData->selectedItems().at(3)->text();
            tagsviewform *forma = new tagsviewform();
            forma->setTextBoxValue(val);
            forma->show();
        }
    }
}


void MainWindow::on_nextPageBt_clicked()
{
    if (curPage < numPages)
    {
        curPage++;
        ui->pageLabel->setText(QString("страница %1 из %2").arg(curPage).arg(numPages));
        ui->tableWidgetTiffData->setRowCount(0);
        ui->numTagsLabel->setText(std::to_string(tiffTagsInFile[curPage - 1].size()).c_str());
        int row = 0;
        for (const auto& tag : tiffTagsInFile[curPage - 1]) {
            ui->tableWidgetTiffData->insertRow(row);
            ui->tableWidgetTiffData->setItem(row, 0, new QTableWidgetItem(QString::number(tag.code)));
            ui->tableWidgetTiffData->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(tag.name)));
            ui->tableWidgetTiffData->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(tag.type)));
            ui->tableWidgetTiffData->setItem(row, 3, new QTableWidgetItem(QString::number(tag.count)));
            ui->tableWidgetTiffData->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(tag.values)));
            ++row;
        }

        int defaultRowHeight = 10;
        for (int row = 0; row < ui->tableWidgetTiffData->rowCount(); ++row) {
            ui->tableWidgetTiffData->setRowHeight(row, defaultRowHeight);
        }
        ui->tableWidgetTiffData->setColumnWidth(0, 60);
        ui->tableWidgetTiffData->setColumnWidth(1, 200);
        ui->tableWidgetTiffData->setColumnWidth(2, 80);
        ui->tableWidgetTiffData->setColumnWidth(3, 70);
    }
}

void MainWindow::on_prevPageBt_clicked()
{
    if (curPage > 1)
    {
        curPage--;
        ui->pageLabel->setText(QString("страница %1 из %2").arg(curPage).arg(numPages));
        ui->tableWidgetTiffData->setRowCount(0);
        ui->numTagsLabel->setText(std::to_string(tiffTagsInFile[curPage - 1].size()).c_str());
        int row = 0;
        for (const auto& tag : tiffTagsInFile[curPage - 1]) {
            ui->tableWidgetTiffData->insertRow(row);
            ui->tableWidgetTiffData->setItem(row, 0, new QTableWidgetItem(QString::number(tag.code)));
            ui->tableWidgetTiffData->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(tag.name)));
            ui->tableWidgetTiffData->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(tag.type)));
            ui->tableWidgetTiffData->setItem(row, 3, new QTableWidgetItem(QString::number(tag.count)));
            ui->tableWidgetTiffData->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(tag.values)));
            ++row;
        }

        int defaultRowHeight = 10;
        for (int row = 0; row < ui->tableWidgetTiffData->rowCount(); ++row) {
            ui->tableWidgetTiffData->setRowHeight(row, defaultRowHeight);
        }
        ui->tableWidgetTiffData->setColumnWidth(0, 60);
        ui->tableWidgetTiffData->setColumnWidth(1, 200);
        ui->tableWidgetTiffData->setColumnWidth(2, 80);
        ui->tableWidgetTiffData->setColumnWidth(3, 70);
    }
}


