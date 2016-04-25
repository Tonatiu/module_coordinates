#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <opencv2/opencv.hpp>
#include <QSqlDatabase>
#include "./src/services/search_save_services.h"
#include "ui_adminwindow.h"
#include "../services/copy_service/copy_service.h"
#include "../services/filter/datafilter.h"
#include "../sceneprocesor/processingthread.h"
#include "copybar.h"

namespace Ui {
class AdminWindow;
}
using namespace std;

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

    void set_end_process_message();

    void set_start_process_message();

    void start_copy_service();

    void start_process_service();

    void start_node_call_service();
private:
    Ui::AdminWindow *ui;
    Search_Save_Services service;
    string status = "Status: ";
    string queueLength;
    SceneDataRelations scene_data_relations;
    string node_path = "../postgis/scripts/mongoTransition.js";
    string end_process_message = "Status: Se han terminado de procesar las escenas";
    string start_process_message = "Status: En este momento se están procesando escenas";
    Copy_Service* copy_service;
    ProcessingThread* scene_process_thread;
    string scenes_destiny_path;
};

#endif // ADMINWINDOW_H
