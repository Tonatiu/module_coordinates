#ifndef COPYTHREAD_H
#define COPYTHREAD_H

#include <QtCore>
#include <string>

using namespace std;

class CopyThread: public QThread
{
public:
    CopyThread(string origin, string destiny, string filename);
private:
    string origin;
    string destiny;
    string filename;
    void run();
};

#endif // COPYTHREAD_H
