#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:

    void on_leLoginUser_returnPressed();

    void on_leLoginPass_textChanged(const QString &arg1);

    void on_leLoginPass_returnPressed();

    void on_leLoginUser_textChanged(const QString &arg1);

    void on_btLogin_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
