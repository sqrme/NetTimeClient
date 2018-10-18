#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nettimeclient.h"
#include "configinfo.h"
#include "timeadjuster.h"
#include <QTimer>
#include "common.h"
#include "iostream"

using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->text_adjust_intval->setMinimum(1);
    ui->text_adjust_intval->setMaximum(MAXADJUSTINTVAL);
    ui->text_zero_protect->setMinimum(1);
    ui->text_zero_protect->setMaximum(MAXPROTECTRANGE);
    this->timeInfo=new TimeInformation{0,0,0,0,0,0,0,0,false,0,false,0,false,0,false,0,false,0,false};

    this->timeAdjuster=new TimeAdjuster();
    ConfigInfo * configInfo=new ConfigInfo();
     if(configInfo->LoadConfig(TIMESERVERCONFIGURE)){
         this->autoAdjust=configInfo->isAutoAdjustEnable();
         this->ui->adjust_check->setChecked(this->autoAdjust);
         this->adjustInteval=configInfo->getAdjustInteval();
         this->ui->text_adjust_intval->setValue(this->adjustInteval);
         this->adjustTimer=new QTimer(this);
         connect(this->adjustTimer,SIGNAL(timeout()),this,SLOT(adjustTime()));
         this->zeroProtectRange=configInfo->getZeroProtectRange();
         this->ui->text_zero_protect->setValue(this->zeroProtectRange);
         this->timeClient=new NetTimeClient();
         this->timer=new QTimer(this);
         connect(this->timer,SIGNAL(timeout()),this,SLOT(updateInfo()));
         timer->setInterval(1000);
         this->timer->start();
         this->timeClient->Run();
     }

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::updateInfo(){
    if(this->timeClient->GetTime(timeInfo)){
        QString dateStr=QString::number(timeInfo->Year)+"-"+QString::number(timeInfo->Month)+"-"+QString::number(timeInfo->Day);
        this->ui->dateView->setText(dateStr);
        QString timeStr=QString::number(timeInfo->Hour)+":"+QString::number(timeInfo->Minute)+":"+QString::number(timeInfo->Second)+"."+QString::number(timeInfo->MSecond);
        this->ui->time_view->setText(timeStr);
        this->ui->Count1Hz_Text->setText(QString::number(timeInfo->Count_1Hz));
        this->ui->Count20Hz_Text->setText(QString::number(timeInfo->Count_20Hz));
    }
}


void MainWindow::on_buttonManualAdjust_clicked()
{
    if(this->timeInfo->Year!=0)
        this->timeAdjuster->Adjust(this->timeInfo);
}

void MainWindow::adjustTime(){
    if(this->timeInfo->Year!=0&& this->autoAdjust)
        this->timeAdjuster->Adjust(this->timeInfo,this->zeroProtectRange);
}

void MainWindow::on_text_adjust_intval_valueChanged(int arg1)
{
    this->adjustInteval=arg1;
}

void MainWindow::on_text_zero_protect_valueChanged(int arg1)
{
    this->zeroProtectRange=arg1;
}

void MainWindow::on_adjust_check_stateChanged(int arg1)
{
    if(this->ui->adjust_check->isChecked()){
        this->autoAdjust=true;
    }else{
        this->autoAdjust=false;
    }
}
