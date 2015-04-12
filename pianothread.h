#ifndef PIANOTHREAD
#define PIANOTHREAD
#include "mainwindow.h"
#include <QThread>
#include <QString>

class pianoThread : public QThread {
    public:
        playBeep(int freq, int duration);
        void run();

    private:
        int freq;
        int duration;
};

#endif // PIANOTHREAD

