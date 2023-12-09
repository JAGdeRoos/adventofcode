#include <QCoreApplication>
#include <QFile>
#include <QStringList>
#include <QTime>
#include <QDateTime>

int main(void)
{
    QFile file("../input.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file";
        return 1;
    }

    QString line = "";
    QStringList lineList;

    QVector<QVector<long long>> numbers;

    while(!file.atEnd()) // populate seeds and maps
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

    QVector<QVector<QVector<long long>>> numberDiffs;

    for(const auto &numberLine:numbers)
    {
        QVector<QVector<long long>> lineNumberDiffs;
        QVector<long long> prevNumberDiff;

        prevNumberDiff = numberLine;

        while(true)
        {
            bool allValuesZero = true;
            long long prevVal = prevNumberDiff.at(0);
            long long currVal = 0;
            long long diff = 0;

            QVector<long long> numberDiff;

            for(int i=1;i<prevNumberDiff.size();i++)
            {
                currVal = prevNumberDiff.at(i);
                diff = currVal - prevVal;
                if(diff != 0)
                    allValuesZero = false;
                numberDiff.append(diff);
                prevVal = currVal;
            }
            lineNumberDiffs.append(numberDiff);
            prevNumberDiff = numberDiff;

            if(allValuesZero)
            {
                numberDiffs.append(lineNumberDiffs);
                //qDebug() << "Filled " << numberDiffs << lineNumberDiffs << allValuesZero;
                break;
            }
        }
    }
    long long totalPartOne = 0;

    //add up all last values
    for(int i=0; i<numberDiffs.size(); i++)
    {
        for(const auto &diffs:numberDiffs.at(i))
        {
            totalPartOne += diffs.last();
        }
        totalPartOne += numbers.at(i).last();
    }
    QVector<long long> totalsPartTwo;
    for(int i=0; i<numberDiffs.size(); i++)
    {
        long long totalPartTwo = 0;
        for(int j=numberDiffs.at(i).size()-1; j>=0; j--)
        {
            totalPartTwo *= -1;
            totalPartTwo += numberDiffs.at(i).at(j).first();
        }
        totalPartTwo *= -1;
        totalPartTwo += numbers.at(i).first();

        totalsPartTwo.append(totalPartTwo);
    }

    long long total = 0;
    for(auto totals:totalsPartTwo)
        total += totals;
    qDebug() << "\n" << totalPartOne << total;

    return 0;
}
