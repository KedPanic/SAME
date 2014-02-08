#include "SamBox.h"
#include "CSamBox.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CSamBox w;
    if(w.Initialize())
    {
        return a.exec();
    }

    return -1;
}
