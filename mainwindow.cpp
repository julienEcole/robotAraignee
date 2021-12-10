#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    ui->lcdNumber->display(position);
}


void MainWindow::on_commandLinkButton_clicked()
{

}


void MainWindow::on_commandLinkButton_3_clicked()
{

}


void MainWindow::on_commandLinkButton_4_clicked()
{

}


void MainWindow::on_commandLinkButton_5_clicked()
{

}


void MainWindow::on_commandLinkButton_6_clicked()
{

}


void MainWindow::on_commandLinkButton_7_clicked()
{

}


void MainWindow::on_pushButton_4_clicked()
{

}

