#include <QCoreApplication>
#include <QFile>
#include <QStringList>

struct strNumber{
    int value;
    int lineNr;
    QVector<int> index;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile* file = new QFile("../input.txt");

    QString prevLine;
    QString currLine;
    QString nextLine;

    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
        return 0;

    int iFirstTotal = 0;
    int iSecondTotal = 0;

    QVector<strNumber> numbers;

    bool bStop = false;
    bool bSymbol = false;

    QVector<int> index;
    index.clear();

    QString numberString = "";

    nextLine = file->readLine();

    int iLineNr = 0;
    while (!bStop)
    {
        prevLine = currLine;
        currLine = nextLine;
        if(!file->atEnd())
        {
            nextLine = file->readLine();
        }
        else
        {
            nextLine = "";
            bStop = true;
        }

        for(int i = 0; i < currLine.size(); i++)
        {
            if(currLine.at(i).isDigit())
            {
                if(index.isEmpty())
                {
                    numberString = currLine.at(i);
                    index.append(i);
                }
                else if (index.at(index.size()-1) == i-1)
                {
                    numberString += currLine.at(i);
                    index.append(i);
                }
            }
            else if(!index.isEmpty())
            {
                for(auto j:index)
                {
                    if (j > 0)
                    {
                        if(!prevLine.isEmpty())
                            if (!prevLine.at(j-1).isDigit() && prevLine.at(j-1) != '.')
                                bSymbol = true;
                        if (!currLine.at(j-1).isDigit() && currLine.at(j-1) != '.')
                            bSymbol = true;
                        if(!nextLine.isEmpty())
                            if (!nextLine.at(j-1).isDigit() && nextLine.at(j-1) != '.')
                                bSymbol = true;
                    }
                    if(!prevLine.isEmpty())
                        if (!prevLine.at(j).isDigit() && prevLine.at(j) != '.')
                            bSymbol = true;
                    if(!nextLine.isEmpty())
                        if (!nextLine.at(j).isDigit() && nextLine.at(j) != '.')
                            bSymbol = true;
                    if (j < currLine.size())
                    {
                        if(!prevLine.isEmpty())
                            if (!prevLine.at(j+1).isDigit() && prevLine.at(j+1) != '.' && (prevLine.at(j+1) != '\n'))
                                bSymbol = true;
                        if (!currLine.at(j+1).isDigit() && currLine.at(j+1) != '.' && (currLine.at(j+1) != '\n'))
                            bSymbol = true;
                        if(!nextLine.isEmpty())
                            if (!nextLine.at(j+1).isDigit() && nextLine.at(j+1) != '.' && (nextLine.at(j+1) != '\n'))
                                bSymbol = true;
                    }
                    if (bSymbol)
                        break;
                }
                if (bSymbol)
                {
                    //qDebug() << numberString;

                    strNumber newNumber;

                    newNumber.index = index;
                    newNumber.value = numberString.toInt();
                    newNumber.lineNr = iLineNr;

                    numbers.append(newNumber);

                    iFirstTotal += newNumber.value;
                    bSymbol = false;
                }
                index.clear();
                numberString = "";
            }
        }
        iLineNr++;
    }
    //qDebug() << numbers.size();
    QFile* file2 = new QFile("../input.txt");

    prevLine = "";
    currLine = "";
    nextLine = "";

    if (!file2->open(QIODevice::ReadOnly | QIODevice::Text))
        return 0;

    iLineNr = 0;
    bStop = false;

    nextLine = file2->readLine();
    QVector<int> values;
    while(!bStop)
    {
        prevLine = currLine;
        currLine = nextLine;
        if(!file2->atEnd())
        {
            nextLine = file2->readLine();
        }
        else
        {
            nextLine = "";
            bStop = true;
        }

        for(int i = 0; i < currLine.size(); i++)
        {
            if(currLine.at(i) == '*')
            {
                for (const auto &number : numbers)
                {
                    if (number.lineNr == (iLineNr - 1) || number.lineNr == iLineNr || number.lineNr == (iLineNr + 1))
                    {
                        //qDebug() << number.value << number.lineNr << number.index << i;
                        for(auto j : number.index)
                        {
                            if (j-1 == i || j == i || j+1 == i)
                            {
                                values.append(number.value);
                                //qDebug() << number.value << number.lineNr << number.index;
                                break;
                            }
                        }
                    }
                }
                if(values.size() == 1)
                    values.clear();
                if(values.size() > 1)
                {
                    qDebug() << values;
                    iSecondTotal += (values.at(0) * values.at(1));
                    values.clear();
                }
            }
        }
        qDebug() << iFirstTotal << iSecondTotal <<  currLine;
        iLineNr++;
    }
    return a.exec();
}
