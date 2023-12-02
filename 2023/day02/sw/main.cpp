#include <QCoreApplication>
#include <QFile>
#include <QStringList>

#define RED 12
#define GREEN 13
#define BLUE 14

enum eColors {
    red = 0,
    green,
    blue
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile* file = new QFile("../input.txt");

    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
        return 0;

    QStringList colors = {"red", "green", "blue"};

    QString line;
    QStringList hands;
    QStringList cubes;
    QStringList numbers;

    int32_t iIndex = 0;
    int32_t iID = 0;
    int32_t iFirstTotal = 0;
    int32_t iSecondTotal = 0;

    int32_t iRed;
    int32_t iGreen;
    int32_t iBlue;
    bool bPossible;

    while (!file->atEnd())
    {
        bPossible = true;

        iRed = 0;
        iGreen = 0;
        iBlue = 0;

        line = file->readLine();

        line.remove("Game ");
        iIndex = line.lastIndexOf(":");
        iID = line.left(iIndex).toInt();
        hands = line.right(line.size()-iIndex).split(";");

        for(const QString &hand : hands)
        {
            cubes = hand.split(",");
            for(const QString &cube : cubes)
            {
                numbers = cube.split(" ");
                //qDebug() << numbers;
                if(numbers.at(2).contains(colors.at(red)))
                {
                    if (numbers.at(1).toInt() > RED)
                        bPossible = false;
                    if (numbers.at(1).toInt() > iRed)
                        iRed = numbers.at(1).toInt();
                }
                else if(numbers.at(2).contains(colors.at(green)))
                {
                    if (numbers.at(1).toInt() > GREEN)
                        bPossible = false;
                    if (numbers.at(1).toInt() > iGreen)
                        iGreen = numbers.at(1).toInt();
                }
                else if(numbers.at(2).contains(colors.at(blue)))
                {
                    if (numbers.at(1).toInt() > BLUE)
                        bPossible = false;
                    if (numbers.at(1).toInt() > iBlue)
                        iBlue = numbers.at(1).toInt();
                }
            }
        }
        if(bPossible)
            iFirstTotal += iID;
        iSecondTotal += (iRed * iGreen * iBlue);
        qDebug() << iID << iFirstTotal << iSecondTotal << iRed << iGreen << iBlue << bPossible << line;
    }
    return a.exec();
}
