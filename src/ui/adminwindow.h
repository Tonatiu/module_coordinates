#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QProgressBar>
#include <opencv2/opencv.hpp>
#include <QSqlDatabase>
#include "./src/services/search_save_services.h"
#include "ui_adminwindow.h"
#include "../services/copy_service/copy_service.h"
#include "../services/filter/datafilter.h"
#include "../sceneprocesor/processingthread.h"

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
    std::string status = "Status: ";
    std::string queueLength;
    SceneDataRelations scene_data_relations;
};

#endif // ADMINWINDOW_H
