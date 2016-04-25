#ifndef COPYBAR_H
#define COPYBAR_H

#include <QWidget>
#include <QMessageBox>
#include "ui_copybar.h"

namespace Ui {
class CopyBar;
}

class CopyBar : public QWidget
{
    Q_OBJECT

public:
    Ui::CopyBar *GetUi();
    explicit CopyBar(QWidget *parent = 0);
    ~CopyBar();

private slots:
    void on_CancelButton_clicked();
private:
    Ui::CopyBar *ui;
};

#endif // COPYBAR_H
