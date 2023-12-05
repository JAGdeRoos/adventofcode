#include <QCoreApplication>
#include <QFile>
#include <QStringList>
#include <limits>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile* file = new QFile("../input.txt");

    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
        return 0;

    QString line = "";
    QStringList numbers;

    int iIndex = 0;
    QVector<long long> seeds;
    QMap<long long, long long> empty;
    QVector<QMap<long long, long long>> XtoY;

    long long seedNr=-1;
    long long locationNr=-1;

    while(!file->atEnd())   // populate seeds and maps
    {
        line = file->readLine();

        line = line.remove("\n");
        if (!line.isEmpty())
        {
            if(line.contains("seeds: "))
            {
                line = line.remove(0,line.indexOf(":")+1);

                for(const QString &seed:line.split(" ", Qt::SkipEmptyParts))
                    seeds.append(seed.toLongLong());

//                numbers = line.split(" ", Qt::SkipEmptyParts);
//                for(int i=0; i < numbers.size()-1; i+=2)
//                {
//                    seeds.append(numbers.at(i).toLongLong());
//                    for(long long j=1; j < numbers.at(i+1).toLongLong(); j++)
//                        seeds.append(numbers.at(i).toLongLong()+j);
//                }
            }
            else
            {
                if(line.at(0).isDigit())
                {
                    numbers = line.split(" ", Qt::SkipEmptyParts);

                    if(!XtoY[iIndex-1].contains(numbers[1].toLongLong()-1))
                        XtoY[iIndex-1].insert(numbers[1].toLongLong()-1, -1);
                    XtoY[iIndex-1].insert(numbers[1].toLongLong(), numbers[0].toLongLong());
                    XtoY[iIndex-1].insert(numbers[1].toLongLong()+numbers[2].toLongLong()-1, numbers[0].toLongLong()+numbers[2].toLongLong()-1);
                    if(!XtoY[iIndex-1].contains(numbers[1].toLongLong()+numbers[2].toLongLong()))
                        XtoY[iIndex-1].insert(numbers[1].toLongLong()+numbers[2].toLongLong(), -1);
                }
            }
        }
        else
        {
            iIndex++;
            XtoY.append(empty);
            XtoY.last().insert(0,-1);
            XtoY.last().insert(std::numeric_limits<long long int>::max(), -1);
        }
    }
    for(long long seed : seeds)
    {
        long long inVal = seed;
        long long outVal = -1;
        for(QMap map : XtoY)
        {
            outVal = -1;
            long long prevKey = -1;
            for (auto i = map.cbegin(), end = map.cend(); i != end; ++i)
            {
                if(prevKey < 0 && inVal <= i.key())
                {
                    if(i.value() == -1)
                        outVal = inVal;
                    else
                        outVal = inVal + (i.value() - i.key());
                    break;
                }
                else if (inVal > prevKey && inVal <= i.key())
                {
                    if(i.value() == -1)
                        outVal = inVal;
                    else
                        outVal = inVal + (i.value() - i.key());
                    break;
                }
                prevKey = i.key();
            }
            inVal = outVal;
        }
        if(locationNr < 0)
        {
            locationNr = outVal;
            seedNr = seed;
        }
        else if (outVal < locationNr)
        {
            locationNr = outVal;
            seedNr = seed;
        }
    }

    QMap<long long, long long>  map;
    QVector<long long> endPoints;
    bool bFirst = true;

    long long prevKey = -1;
    for(int i=XtoY.size()-1; i >= 0; i--)
    {
        prevKey = -1;
        map = XtoY[i];
        for (auto j = map.cbegin(), end = map.cend(); j != end; ++j)
        {
            if(bFirst)
            {
                prevKey =  j.key();
                endPoints.append(prevKey);
            }
            else
            {
                if(j.key() == -1)
                    ;//skip
                else if (j.key() == 0)
                {
                    prevKey = j.key();
                }
                else
                {

                }
            }
        }
        bFirst = false;
    }
    qDebug() << endPoints;
    qDebug() << seedNr << locationNr << seeds;//<< XtoY;


    file->close();
    return a.exec();
}
