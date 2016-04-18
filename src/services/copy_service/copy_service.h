#ifndef COPY_SERVICE_H
#define COPY_SERVICE_H

#include "../queue/pathqueue.h"
#include <QtCore>
#include <QMessageBox>

using namespace std;

class Copy_Service: public QThread
{
public:
    Copy_Service(pathQueue *queue, string destiny_path, string origin_path);
    bool GetStatus();
    void stop_service();
private:
    pathQueue *scene_path_queue;
    string Destiny_Path;
    string Origin_Path;
    bool copy_status = true;
    bool running = true;
    void run();
    bool CopyTo(string file_name);
};

#endif // COPY_SERVICE_H
