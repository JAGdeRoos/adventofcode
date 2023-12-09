#include <QCoreApplication>
#include <QFile>
#include <QStringList>

struct strNumber{
    int value;
    int lineNr;
    QVector<int> index;
};

int main(void)
{
    QFile file("../input.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file";
        return 1;
    }

    QString line = "";
    QString winningNumbersString;
    QString numbersYouHaveString;
    QStringList winningNumbers;
    QStringList numbersYouHave;

    int iIndex=0;
    int iID=0;

    int iCurrentCardPoints;
    int iNumberOfMatches;
    int iFirstTotalPoints = 0;
    int iSecondTotalPoints = 0;

    bool bFirstMatch;

    QVector<int> copies(198,1);

    qDebug() << copies;
    copies.append(0);

    while(!file.atEnd())
    {
        line = file.readLine();

        line.remove("Card ");
        iIndex = line.lastIndexOf(":");
        iID = line.left(iIndex).toInt();

        line = line.remove(0,line.indexOf(":")+1);
        line = line.remove("\n");

        winningNumbersString = line.split("|").at(0);

        winningNumbers = line.split("|").at(0).split(" ", Qt::SkipEmptyParts);
        numbersYouHave = line.split("|").at(1).split(" ", Qt::SkipEmptyParts);

        iNumberOfMatches = 0;
        iCurrentCardPoints = 0;
        bFirstMatch = true;
        for(const QString &number : numbersYouHave)
            for(const QString &winning : winningNumbers)
                if (number == winning)
                {
                    if (bFirstMatch)
                    {
                        bFirstMatch = false;
                        iCurrentCardPoints = 1;
                    }
                    else
                    {
                        iCurrentCardPoints *= 2;
                    }
                    iNumberOfMatches++;
                }
        iFirstTotalPoints += iCurrentCardPoints;

        for(int i=0; i<iNumberOfMatches; i++)
            copies[iID+i] += copies[iID-1];

        iSecondTotalPoints += copies[iID-1];
        qDebug() << iID << iFirstTotalPoints << iSecondTotalPoints << copies[iID-1] << iNumberOfMatches;
    }
    return 0;
}
