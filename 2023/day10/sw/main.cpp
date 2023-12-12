#include <QCoreApplication>
#include <QFile>
#include <QStringList>
#include <QTime>
#include <QElapsedTimer>
#include <QPoint>

//The pipes are arranged in a two-dimensional grid of tiles:
// enum pipeType{
//     NS = '|', //is a vertical pipe connecting north and south.
//     EW = '-', //is a horizontal pipe connecting east and west.
//     NE = 'L', //is a 90-degree bend connecting north and east.
//     NW = 'J', //is a 90-degree bend connecting north and west.
//     SW = '7', //is a 90-degree bend connecting south and west.
//     SE = 'F', //is a 90-degree bend connecting south and east.
//     GN = '.', //is ground; there is no pipe in this tile.
//     ST = 'S' //is the starting position of the animal; there is a pipe on this tile, but your sketch doesn't show what shape the pipe has.
// };

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


    QVector<QVector<QPair<int, QString>>> path;
    QPair<QPoint, QString> start;
    QString prevChar = "";
    QPoint prevPoint;
    QPoint currPoint;

    for(int y = 0; y < pipes.size(); y++){
        for(int x = 0; x < pipes.at(0).size(); x++){
            if(pipes.at(y).at(x) == "S"){
                start.first = {x,y};
                if(y>0)
                    if(pipes.at(y-1).at(x) == "|" || pipes.at(y-1).at(x) == "F" || pipes.at(y-1).at(x) == "7"){
                        prevChar = pipes.at(y-1).at(x);
                        prevPoint = QPoint(x,y);
                        currPoint = QPoint(x,y-1);
                        start.second.append("N");
                    }
                if(y<pipes.size())
                    if(pipes.at(y+1).at(x) == "|" || pipes.at(y+1).at(x) == "L" || pipes.at(y+1).at(x) == "J"){
                        prevChar = pipes.at(y+1).at(x);
                        prevPoint = QPoint(x,y);
                        currPoint = QPoint(x,y+1);
                        start.second.append("S");
                    }
                if(x>0)
                    if(pipes.at(y).at(x-1) == "-" || pipes.at(y).at(x-1) == "F" || pipes.at(y).at(x-1) == "L"){
                        prevChar = pipes.at(y).at(x-1);
                        prevPoint = QPoint(x,y);
                        currPoint = QPoint(x-1,y);
                        start.second.append("W");
                    }
                if(x<pipes.at(y).size())
                    if(pipes.at(y).at(x+1) == "-" || pipes.at(y).at(x+1) == "7" || pipes.at(y).at(x+1) == "J"){
                        prevChar = pipes.at(y).at(x+1);
                        prevPoint = QPoint(x,y);
                        currPoint = QPoint(x+1,y);
                        start.second.append("E");
                    }
                break;
            }
        }
    }

    if(start.second == "NS") start.second = '|';
    if(start.second == "EW") start.second = '-';
    if(start.second == "NE") start.second = 'L';
    if(start.second == "NW") start.second = 'J';
    if(start.second == "SW") start.second = '7';
    if(start.second == "SE") start.second = 'F';

    qDebug() << start;
    bool bEndFound = false;
    total1 = 1;

    path.resize(pipes.size());

    while(!bEndFound)
    {
        if(prevChar == "|"){
            path[currPoint.y()].push_back({currPoint.x(), prevChar});
            if(currPoint.y() - prevPoint.y() > 0){ // //from above
                prevPoint = currPoint;
                currPoint.setY(currPoint.y()+1);
            }
            else{
                prevPoint = currPoint;
                currPoint.setY(currPoint.y()-1);
            }
        }
        else if(prevChar == "-"){
            if(currPoint.x() - prevPoint.x() > 0){ // from left
                prevPoint = currPoint;
                currPoint.setX(currPoint.x()+1);
            }
            else{
                prevPoint = currPoint;
                currPoint.setX(currPoint.x()-1);
            }
        }
        else if(prevChar == "L"){
            path[currPoint.y()].push_back({currPoint.x(), prevChar});
            if(currPoint.y() - prevPoint.y() > 0){ // from above
                prevPoint = currPoint;
                currPoint.setX(currPoint.x()+1);
            }
            else{
                prevPoint = currPoint;
                currPoint.setY(currPoint.y()-1);
            }
        }
        else if(prevChar == "J"){
            path[currPoint.y()].push_back({currPoint.x(), prevChar});
            if(currPoint.y() - prevPoint.y() > 0){ // from above
                prevPoint = currPoint;
                currPoint.setX(currPoint.x()-1);
            }
            else{
                prevPoint = currPoint;
                currPoint.setY(currPoint.y()-1);
            }
        }
        else if(prevChar == "7"){
            path[currPoint.y()].push_back({currPoint.x(), prevChar});
            if(currPoint.y() - prevPoint.y() < 0){ // from below
                prevPoint = currPoint;
                currPoint.setX(currPoint.x()-1);
            }
            else{
                prevPoint = currPoint;
                currPoint.setY(currPoint.y()+1);
            }
        }
        else if(prevChar == "F"){
            path[currPoint.y()].push_back({currPoint.x(), prevChar});
            if(currPoint.y() - prevPoint.y() < 0){ // from below
                prevPoint = currPoint;
                currPoint.setX(currPoint.x()+1);
            }
            else{
                prevPoint = currPoint;
                currPoint.setY(currPoint.y()+1);
            }
        }
        prevChar = pipes.at(currPoint.y()).at(currPoint.x());

        total1++;
        if(prevChar == "S"){
            bEndFound=true;
        }
    }

    path[start.first.y()].push_back({start.first.x(), start.second});

    // Part 2: Calculate number of tiles inside the path.
    for (auto row : path)
    {
        std::sort(row.begin(), row.end());
        bool bInside = false;
        for (auto i = row.begin(); i < row.end(); i++)
        {
            // If this interval is inside the path, increment the P2 answer accordingly.
            if (bInside)
                total2 += i->first - (i - 1)->first - 1; // delta x - 1
            // Vertical pipes simply toggle whether we are inside.
            if (i->second == "|") {
                bInside = !bInside;
                continue;
            }
            QString corner1 = i->second;
            i++;
            QString corner2 = i->second;
            if((corner1 == "L" && corner2 == "7") || (corner1 == "7" && corner2 == "L") ||
               (corner1 == "F" && corner2 == "J") || (corner1 == "J" && corner2 == "F"))
                bInside = !bInside;
        }
    }

    QTime elapsed(0, 0);
    elapsed = elapsed.addMSecs(timer.elapsed());

    qDebug() << "Time elapsed since starting the function: " << elapsed.toString("mm:ss:zzz");
    qDebug() << total1/2 << total2;

    return 0;
}


