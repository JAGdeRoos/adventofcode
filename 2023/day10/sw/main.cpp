#include <QCoreApplication>
#include <QFile>
#include <QStringList>
#include <QTime>
#include <QElapsedTimer>

int main(void)
{
    QElapsedTimer timer;
    timer.start();

    QFile file("../input.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file";
        return 1;
    }
    QString line = "";

    QList<QList<QString>> pipes;

    // read file
    while(!file.atEnd())
    {
        line = file.readLine();
        line = line.remove("\n");
        if (!line.isEmpty())
        {
            pipes.append(line.split("", Qt::SkipEmptyParts));
        }
    }

    qDebug() << pipes;
    bool bStartFound = false;
    bool bEndFound = false;

    QVector<QVector<int>> searchArea;

    searchArea.append({0,0});
    searchArea.append({static_cast<int>(pipes.size()), static_cast<int>(pipes.at(0).size())});

    while(!bEndFound)
    {
        for(int i = searchArea.first().first(); i < searchArea.last().first(); i++)
        {
            for(int j = searchArea.first().last(); j < searchArea.last().last(); j++)
            {
                if(pipes.at(i).at(j) == "S" && !bStartFound)
                {
                    qDebug() << i << j;
                    bStartFound = true;
                    break;
                }
            }
        }

        bEndFound=true;
    }

    long long total1=0;
    long long total2=0;
    // solve puzzle...









    QTime elapsed(0, 0);
    elapsed = elapsed.addMSecs(timer.elapsed());

    qDebug() << "Time elapsed since starting the function: " << elapsed.toString("mm:ss:zzz");
    qDebug() << total1 << total2;

    return 0;
}
