#include <QCoreApplication>
#include <QFile>
#include <QStringList>
#include <QTime>
#include <QDateTime>

struct Map
{
    int64_t llSourceStart;
    int64_t llDestinationStart;
    int64_t llRangeSize;
};

int main(void)
{
    QFile file("../input.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file";
        return 1;
    }

    int64_t startTime = QDateTime::currentMSecsSinceEpoch();
    int64_t endTime;

    int iIndex = 0;
    QString line = "";
    QStringList seeds;
    QStringList numbers;

    QVector<Map> empty;
    QVector<QVector<Map>> XtoY;

    while(!file.atEnd()) // populate seeds and maps
    {
        line = file.readLine();
        line = line.remove("\n");
        if (!line.isEmpty())
        {
            if(line.contains("seeds: "))
            {
                line = line.remove(0,line.indexOf(":")+1);
                seeds = line.split(" ", Qt::SkipEmptyParts);
            }
            else if(line.at(0).isDigit())
            {
                numbers = line.split(" ", Qt::SkipEmptyParts);
                XtoY[iIndex-1].push_back({ numbers[1].toLongLong(), numbers[0].toLongLong(), numbers[2].toLongLong() });
            }
        }
        else
        {
            iIndex++;
            XtoY.push_back(empty);
        }
    }

    int64_t llLowestLocation = 0;
    int64_t llLowestSeed = 0;
    int64_t llIndex = 0;

    int64_t llInVal       = -1;
    int64_t llOutVal      = -1;

    int i = 0;
    int64_t j;

    for (i = 0; i < seeds.size(); i += 2)
    {
        for (j = seeds[i].toLongLong(); j <= (seeds[i].toLongLong() + seeds[i + 1].toLongLong()); ++j)
        {
            ++llIndex;

            llInVal     = j;
            llOutVal    = -1;

            for (const auto &vector : XtoY)
            {
                for (const auto &map : vector)
                {
                    if (llInVal >= map.llSourceStart && llInVal <= (map.llSourceStart + map.llRangeSize -1))
                    {
                        llOutVal = map.llDestinationStart + (llInVal - map.llSourceStart);
                        break;
                    }
                }
                if (llOutVal != -1)
                    llInVal = llOutVal;
                llOutVal = -1;
            }

            if (llInVal < llLowestLocation || llLowestLocation == 0)
            {
                llLowestLocation = llInVal;
                llLowestSeed = j;
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

    return 0;
}
