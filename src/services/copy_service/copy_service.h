#ifndef COPY_SERVICE_H
#define COPY_SERVICE_H

#include "copythread.h"
#include <QtCore>
#include <iostream>

using namespace std;

class Copy_Service: public QThread
{
public:
    Copy_Service(vector<string> *queue, string destiny_path, string origin_path);
    bool GetStatus();
    void stop_service();
private:
    vector<string> *scene_path_queue;
    string Destiny_Path;
    string Origin_Path;
    bool copy_status = true;
    bool running = true;
    void run();
};

#endif // COPY_SERVICE_H
