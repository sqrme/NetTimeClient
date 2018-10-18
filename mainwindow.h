#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "nettimeclient.h"
#include "timeadjuster.h"
#include "common.h"


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

    void updateInfo();
    void adjustTime();

    void on_buttonManualAdjust_clicked();

    void on_text_adjust_intval_valueChanged(int arg1);

    void on_text_zero_protect_valueChanged(int arg1);

    void on_adjust_check_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    NetTimeClient *timeClient;
    TimeInformation* timeInfo;
    QTimer * timer;
    QTimer *adjustTimer;
    TimeAdjuster * timeAdjuster;
    bool autoAdjust;
    int adjustInteval;
    int zeroProtectRange;

};

#endif // MAINWINDOW_H
