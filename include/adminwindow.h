#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include "search_save_services.h"

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = 0);
    ~AdminWindow();

private slots:
    void on_searchButtonn_clicked();

    void on_toolButton_clicked();

    void on_addButton_clicked();

private:
    Ui::AdminWindow *ui;
    Search_Save_Services service;
};

#endif // ADMINWINDOW_H
