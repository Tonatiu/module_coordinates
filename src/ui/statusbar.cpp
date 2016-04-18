#include "statusbar.h"
#include "ui_statusbar.h"

StatusBar::StatusBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatusBar)
{
    ui->setupUi(this);
}

StatusBar::~StatusBar()
{
    delete ui;
}

void StatusBar::on_CancelButton_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::warning(this, "Cancelar acción", "¿Quiere cancelar copiado de las escenas?",
                                                             QMessageBox::Yes| QMessageBox::No);
    if(reply == QMessageBox::No)
        return;
    this->service->stop_service();
    this->hide();

}

void StatusBar::SetCopyService(Copy_Service *service){
    this->service = service;
}

QPushButton *StatusBar::GetButton(){
    return ui->CancelButton;
}
