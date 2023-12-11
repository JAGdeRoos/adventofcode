#include <QCoreApplication>
#include <QFile>
#include <QStringList>
#include <QTime>
#include <QElapsedTimer>
/*
The pipes are arranged in a two-dimensional grid of tiles:

*  | is a vertical pipe connecting north and south.
*  - is a horizontal pipe connecting east and west.
*  L is a 90-degree bend connecting north and east.
*  J is a 90-degree bend connecting north and west.
*  7 is a 90-degree bend connecting south and west.
*  F is a 90-degree bend connecting south and east.
*  . is ground; there is no pipe in this tile.
*  S is the starting position of the animal; there is a pipe on this tile, but your sketch doesn't show what shape the pipe has.
*/

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

    QList<QList<QString>> pipes;

    // read file
    while(!file.atEnd())
    {
        line = file.readLine();
        line = line.remove("\n");
        if (!line.isEmpty())
        {
            pipes.append(line.split("", Qt::SkipEmptyParts));
        }
    }

    long long total1=0;
    long long total2=0;
    QString prevChar = "";
    QVector<int> prevIndex;

    for(int y = 0; y < pipes.size(); y++)
    {
        for(int x = 0; x < pipes.at(0).size(); x++)
        {
            if(pipes.at(y).at(x) == "S")
            {
                if(y>0)
                    if(pipes.at(y-1).at(x) == "|" || pipes.at(y-1).at(x) == "F" || pipes.at(y-1).at(x) == "7")
                    {
                        prevChar = pipes.at(y-1).at(x);
                        prevIndex << y << x << y-1 << x;
                        break;
                    }
                if(y<pipes.size())
                    if(pipes.at(y+1).at(x) == "|" || pipes.at(y+1).at(x) == "L" || pipes.at(y+1).at(x) == "J")
                    {
                        prevChar = pipes.at(y+1).at(x);
                        prevIndex << y << x << y+1 << x;
                        break;
                    }
                if(x>0)
                    if(pipes.at(y).at(x-1) == "-" || pipes.at(y).at(x-1) == "F" || pipes.at(y).at(x-1) == "L")
                    {
                        prevChar = pipes.at(y).at(x-1);
                        prevIndex << y << x << y << x-1;
                        break;
                    }
                if(x<pipes.at(y).size())
                    if(pipes.at(y).at(x+1) == "-" || pipes.at(y).at(x+1) == "7" || pipes.at(y).at(x+1) == "J")
                    {
                        prevChar = pipes.at(y).at(x+1);
                        prevIndex << y << x << y << x+1;
                        break;
                    }
                break;
            }
        }
    }

    bool bEndFound = false;
    total1 = 1;

    int prevY = prevIndex.at(0);
    int prevX = prevIndex.at(1);
    int currY = prevIndex.at(2);
    int currX = prevIndex.at(3);

    QString currChar;
    while(!bEndFound)
    {
        if(prevChar == "|")
        {
            qDebug() << prevChar << prevX << currX << prevY << currY;
            if(currY - prevY > 0){ // //from above
                prevY = currY;
                currY++;
            }
            else{
                prevY = currY;
                currY--;
            }
        }
        else if(prevChar == "-")
        {
            qDebug() << prevChar << prevX << currX << prevY << currY;
            if(currX - prevX > 0){ // from left
                prevX = currX;
                currX++;
            }
            else{
                prevX = currX;
                currX--;
            }
        }
        else if(prevChar == "L")
        {
            qDebug() << prevChar << prevX << currX << prevY << currY;
            if(currY - prevY > 0){ // from above
                prevX = currX;
                prevY = currY;
                currX++;
            }
            else{
                prevY = currY;
                currY--;
            }
        }
        else if(prevChar == "J")
        {
            qDebug() << prevChar << prevX << currX << prevY << currY;
            if(currY - prevY > 0){ // from above
                prevX = currX;
                prevY = currY;
                currX--;
            }
            else{
                prevX = currX;
                prevY = currY;
                currY--;
            }
        }
        else if(prevChar == "7")
        {
            qDebug() << prevChar << prevX << currX << prevY << currY;
            if(currY - prevY < 0){ // from below
                prevX = currX;
                prevY = currY;
                currX--;
            }
            else{
                prevX = currX;
                prevY = currY;
                currY++;
            }
        }
        else if(prevChar == "F")
        {
            qDebug() << prevChar << prevX << currX << prevY << currY;
            if(currY - prevY < 0){ // from below
                prevX = currX;
                prevY = currY;
                currX++;
            }
            else{
                prevX = currX;
                prevY = currY;
                currY++;
            }
        }
        prevChar = pipes.at(currY).at(currX);

        total1++;
        if(prevChar == "S")
        {
            bEndFound=true;
            qDebug() << "in the if statement" << total1/2;
        }
    }

    QTime elapsed(0, 0);
    elapsed = elapsed.addMSecs(timer.elapsed());

    qDebug() << "Time elapsed since starting the function: " << elapsed.toString("mm:ss:zzz");
    qDebug() << total1/2 << total2;

    return 0;
}
