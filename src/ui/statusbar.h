#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include "../services/copy_service/copy_service.h"

namespace Ui {
class StatusBar;
}

class StatusBar : public QWidget
{
    Q_OBJECT

public:
    explicit StatusBar(QWidget *parent = 0);
    ~StatusBar();
    QPushButton *GetButton();
    void SetCopyService(Copy_Service* service);

private slots:
    void on_CancelButton_clicked();

private:
    Ui::StatusBar *ui;
    Copy_Service* service = NULL;
};

#endif // STATUSBAR_H
