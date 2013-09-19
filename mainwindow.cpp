#include <QFileSystemModel>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "flickrauth.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lbRegister->setOpenExternalLinks(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_leLoginUser_returnPressed()
{
    QString nullStr("");
    if ((nullStr.compare(ui->leLoginUser->text()) == 0) && (nullStr.compare(ui->leLoginPass->text()) == 0))
    {
        ui->lbLoginError->setText("Invalid username and password provided!");
        return;
    }
    else if (nullStr.compare(ui->leLoginUser->text()) == 0)
    {
        ui->lbLoginError->setText("Invalid username provided!");
        return;
    }
    else if (nullStr.compare(ui->leLoginPass->text()) == 0)
    {
        ui->lbLoginError->setText("Invalid password provided!");
        return;
    }
}

void MainWindow::on_leLoginPass_textChanged(const QString &arg1)
{
    ui->lbLoginError->setText("");
}

void MainWindow::on_leLoginPass_returnPressed()
{
    QString nullStr("");
    if ((nullStr.compare(ui->leLoginUser->text()) == 0) && (nullStr.compare(ui->leLoginPass->text()) == 0))
    {
        ui->lbLoginError->setText("Invalid username and password provided!");
        return;
    }
    else if (nullStr.compare(ui->leLoginUser->text()) == 0)
    {
        ui->lbLoginError->setText("Invalid username provided!");
        return;
    }
    else if (nullStr.compare(ui->leLoginPass->text()) == 0)
    {
        ui->lbLoginError->setText("Invalid password provided!");
        return;
    }
}

void MainWindow::on_leLoginUser_textChanged(const QString &arg1)
{
    ui->lbLoginError->setText("");
}

void MainWindow::on_btLogin_clicked()
{
    QString nullStr("");
    if ((nullStr.compare(ui->leLoginUser->text()) == 0) && (nullStr.compare(ui->leLoginPass->text()) == 0))
    {
        ui->lbLoginError->setText("Invalid username and password provided!");
        return;
    }
    else if (nullStr.compare(ui->leLoginUser->text()) == 0)
    {
        ui->lbLoginError->setText("Invalid username provided!");
        return;
    }
    else if (nullStr.compare(ui->leLoginPass->text()) == 0)
    {
        ui->lbLoginError->setText("Invalid password provided!");
        return;
    }
    FlickrAuth fAuth(ui->centralWidget, ui->leLoginUser->text(), ui->leLoginPass->text(), ui->cbRememberMe->isChecked());
}
