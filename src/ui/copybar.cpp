#include "copybar.h"


CopyBar::CopyBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CopyBar)
{
    ui->setupUi(this);
}

CopyBar::~CopyBar()
{
    delete ui;
}

void CopyBar::on_CancelButton_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::warning(this, "Cancelar copiado", "Se cancelará el copiado de escenas",
                         QMessageBox::Yes);

}

Ui::CopyBar *CopyBar::GetUi(){
    return this->ui;
}
