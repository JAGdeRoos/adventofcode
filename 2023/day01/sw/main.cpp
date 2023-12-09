#include <QCoreApplication>
#include <QFile>
#include <QStringList>

int main(void)
{
    QFile file("../input.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file";
        return 1;
    }

    int iFirst = 0;
    int iSecond= 0;
    int iNumber= 0;
    int iTotal = 0;
    int iFirstNumberIndex = 0;
    int iSecondNumberIndex = 0;

    QStringList numbers = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    QString line;

    while (!file.atEnd())
    {
        line = file.readLine();

        iFirstNumberIndex = line.size();
        iSecondNumberIndex = -1;
        for (const auto &number : numbers){
            if (line.contains(number))
            {
                if(line.indexOf(number) < iFirstNumberIndex)
                {
                    iFirst = &number - &numbers[0];
                    iFirstNumberIndex = line.indexOf(number);
                }
                if(line.lastIndexOf(number) > iSecondNumberIndex)
                {
                    iSecond = &number - &numbers[0];
                    iSecondNumberIndex = line.lastIndexOf(number);
                }
            }
        }
        for (int i = 0; i < line.size(); i++){
            if(line.at(i).isDigit())
            {
                if(i < iFirstNumberIndex)
                    iFirst = line.at(i).digitValue();
                break;
            }
        }
        for (int i = line.size()-1; i >= 0; i--){
            if(line.at(i).isDigit())
            {
                if(i > iSecondNumberIndex)
                    iSecond = line.at(i).digitValue();
                break;
            }
        }

        iNumber = QString(QString::number(iFirst) + QString::number(iSecond)).toInt();
        iTotal += iNumber;
        qDebug() << iNumber << iTotal << line;
    }

    qDebug() << "end \n";
    return 0;
}
