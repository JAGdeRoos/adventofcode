#include <QCoreApplication>
#include <QFile>
#include <QStringList>
#include <QTime>
#include <QDateTime>

struct Map
{
    long long llSourceStart;
    long long llDestinationStart;
    long long llRangeSize;
};

int main(int argc, char *argv[])
{
    long long startTime = QDateTime::currentMSecsSinceEpoch();
    long long endTime;

    QCoreApplication a(argc, argv);

    QFile* file = new QFile("../input.txt");

    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
        return 0;

    int iIndex = 0;
    QString line = "";
    QStringList seeds;
    QStringList numbers;

    QVector<Map> empty;
    QVector<QVector<Map>> XtoY;

    while(!file->atEnd()) // populate seeds and maps
    {
        line = file->readLine();
        line = line.remove("\n");
        if (!line.isEmpty())
        {
            if(line.contains("seeds: "))
            {
                line = line.remove(0,line.indexOf(":")+1);
                seeds = line.split(" ", Qt::SkipEmptyParts);
            }
            else
            {
                if(line.at(0).isDigit())
                {
                    numbers = line.split(" ", Qt::SkipEmptyParts);
                    XtoY[iIndex-1].push_back({ numbers[1].toLongLong(), numbers[0].toLongLong(), numbers[2].toLongLong() });
                }
            }
        }
        else
        {
            iIndex++;
            XtoY.push_back(empty);
        }
    }

    long long llLowestLocation = 0;
    long long llLowestSeed = 0;
    long long llIndex = 0;

    long long llSeedNumber  =  0;
    long long llInVal       = -1;
    long long llOutVal      = -1;

    int i = 0;
    long long j;

    for (i = 0; i < seeds.size(); i += 2) // assign correct (part 2) seed things
    {
        for (j = seeds[i].toLongLong(); j <= (seeds[i].toLongLong() + seeds[i + 1].toLongLong()); j++) // for each seed...
        {
            llIndex++;

            llSeedNumber= j;

            llInVal     = llSeedNumber;
            llOutVal    = -1;

            for (const auto &conversion : XtoY)
            {
                for (Map map : conversion)
                {
                    if (llInVal >= map.llSourceStart && llInVal <= (map.llSourceStart + map.llRangeSize -1))
                    {
                        llOutVal = map.llDestinationStart + (llInVal - map.llSourceStart);
                        break;
                    }
                    if (llOutVal == -1)
                        llOutVal = llInVal;
                }
                llInVal = llOutVal;
                llOutVal = -1;
            }

            llOutVal = llInVal; // only when done with the nested for

            if (llOutVal == 0)
                llLowestLocation = llOutVal;
            if (llLowestLocation == 0)
                llLowestLocation = llOutVal;
            else if (llOutVal < llLowestLocation)
            {
                llLowestLocation = llOutVal;
                llLowestSeed = llSeedNumber;
                qDebug() << " New Lowest Seed:" << llLowestSeed << "Location: " << llLowestLocation;
            }
            if (llIndex % 100000000 == 0)
                qDebug() << "llIndex: " << llIndex;
        }
    }

    endTime = QDateTime::currentMSecsSinceEpoch();
    qint64 elapsedMilliseconds = endTime - startTime;
    QTime elapsed(0, 0);
    elapsed = elapsed.addMSecs(elapsedMilliseconds);

    qDebug() << "Time elapsed since starting the function: " << elapsed.toString("mm:ss:zzz");
    qDebug() << "llLowestLocation: " << llLowestLocation << " - " "llLowestSeed: "<< llLowestSeed;
    qDebug() << "Number of seeds checked: " << llIndex;
}
