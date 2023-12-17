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
    QStringList lineList;

    QVector<QVector<long long>> numbers;

    // read file
    while(!file.atEnd())
    {
        line = file.readLine();
        line = line.remove("\n");
        if (!line.isEmpty())
        {
            lineList = line.split(" ", Qt::SkipEmptyParts);
        }
        QVector<long long> lineNumbers;
        for(const auto &element : lineList)
            lineNumbers.append(element.toLongLong());
        numbers.append(lineNumbers);
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
