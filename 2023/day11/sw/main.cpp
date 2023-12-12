#include <QCoreApplication>
#include <QFile>
#include <QStringList>
#include <QTime>
#include <QElapsedTimer>
#include <QPoint>

#define AMOUNT 1000000

struct Galaxy{
    QPoint location;
    long long number;
};

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

    QVector<QVector<QString>> space;

    // read file
    while(!file.atEnd())
    {
        line = file.readLine();
        line = line.remove("\n");
        if (!line.isEmpty())
        {
            space.append(line.split("", Qt::SkipEmptyParts));
        }
    }

    long long total1=0;
    long long total2=0;
    // solve puzzle...
\

    QVector<Galaxy> galaxies;
    QVector<bool> rowEmpty;
    QVector<bool> colEmpty;
    rowEmpty.resize(space.size(), true);
    colEmpty.resize(space.size(), true);

    // find empty rows/columns
    long long iter = 0;
    for(long long y = 0; y < space.size(); y++)
    {
        for(long long x = 0; x < space.at(y).size(); x ++)
        {
            if(space.at(y).at(x) == "#")
            {
                Galaxy found;
                found.number = ++iter;
                found.location = QPoint(x,y);
                galaxies.append(found);

                rowEmpty[y] = false;
                colEmpty[x] = false;
            }
        }
    }

    for(long long i = 0; i < galaxies.size(); i++)
    {
        for(long long j = i; j < galaxies.size(); j++)
        {
            if(i == j)
                continue;
            long long xDiff1 = 0;
            long long yDiff1 = 0;

            long long xDiff2 = 0;
            long long yDiff2 = 0;

            long long nrOfCols1 = 0;
            long long nrOfRows1 = 0;

            long long nrOfCols2 = 0;
            long long nrOfRows2 = 0;

            if(galaxies.at(i).location.x() != galaxies.at(j).location.x())
            {
                for(int x = qMin(galaxies.at(i).location.x(), galaxies.at(j).location.x());
                        x < qMax(galaxies.at(i).location.x(),galaxies.at(j).location.x());
                        x++)
                {
                    if(colEmpty.at(x))
                    {
                        nrOfRows1 += 2;
                        nrOfRows2 += AMOUNT;
                    }
                    else
                    {
                        nrOfRows1 ++;
                        nrOfRows2 ++;
                    }
                }
                xDiff1 = nrOfRows1;
                xDiff2 = nrOfRows2;
            }
            if(galaxies.at(i).location.y() != galaxies.at(j).location.y())
            {
                for(int y = qMin(galaxies.at(i).location.y(),galaxies.at(j).location.y());
                        y < qMax(galaxies.at(i).location.y(),galaxies.at(j).location.y());
                        y++)
                {
                    if(rowEmpty.at(y))
                    {
                        nrOfCols1 += 2;
                        nrOfCols2 += AMOUNT;
                    }
                    else
                    {
                        nrOfCols1 ++;
                        nrOfCols2 ++;
                    }
                }
                yDiff1 = nrOfCols1;
                yDiff2 = nrOfCols2;
            }
            total1 += xDiff1 + yDiff1;
            total2 += xDiff2 + yDiff2;
        }
    }

    QTime elapsed(0, 0);
    elapsed = elapsed.addMSecs(timer.elapsed());

    qDebug() << "Time elapsed since starting the function: " << elapsed.toString("mm:ss:zzz");
    qDebug() << total1 << total2;

    return 0;
}
