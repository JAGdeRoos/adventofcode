#include <QCoreApplication>
#include <QFile>
#include <QStringList>
#include <QTime>
#include <QDateTime>

struct Race
{
    long long Time = 0;
    long long Record = 0;
    long long NumberOfWays = 0;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile file("../input.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return 0;

    QVector<Race> races;

    QString line;
    QStringList times;
    QStringList distances;

    while(!file.atEnd()) // populate seeds and maps
    {
        line = file.readLine();
        line = line.remove("\n");
        if (!line.isEmpty())
        {
            if(line.contains("Time: "))
            {
                line = line.remove(0,line.indexOf(":")+1);
                times = line.split(" ", Qt::SkipEmptyParts);
            }
            if(line.contains("Distance: "))
            {
                line = line.remove(0,line.indexOf(":")+1);
                distances = line.split(" ", Qt::SkipEmptyParts);
            }
        }
    }
    QString time = ""; //part2
    QString distance = "";

    for (long long i = 0; i < times.size(); i++)
    {
        time += times[i];
        distance += distances[i];
    }
    Race newRace;

    newRace.Time = time.toLongLong();
    newRace.Record = distance.toLongLong();

    races.append(newRace);

    qDebug() << newRace.Time << newRace.Record;

    long long iTotal = 0;
    for(auto race : races)
    {
        for(long long i = 1; i < race.Time; i++)
        {
            long long speed = i;
            long long distance = speed * (race.Time - i);

            if(distance > race.Record)
                race.NumberOfWays++;

        }
        if(iTotal == 0)
            iTotal = race.NumberOfWays;
        else
            iTotal *= race.NumberOfWays;
        qDebug() << iTotal << race.NumberOfWays;
    }
}
