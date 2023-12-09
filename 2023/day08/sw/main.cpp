#include <QCoreApplication>
#include <QFile>
#include <QStringList>
#include <QTime>
#include <QDateTime>

struct Node
{
    QString Input;
    QString Left;
    QString Right;
};

struct strInput
{
    QString Input;
    QString in;
    QString out;
    bool done;
    long long iters;
};

long long findDenominator(long long n1, long long n2);

int main(void)
{
    QFile file("../input.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file";
        return 1;
    }

    QString line = "";
    QStringList lineParts;
    QStringList directions;
    QVector<Node> nodes;

    line = file.readLine();
    line = line.remove("\n");
    directions = line.split("", Qt::SkipEmptyParts);

    while(!file.atEnd()) // populate seeds and maps
    {
        line = file.readLine();
        line = line.remove("\n");
        if (!line.isEmpty())
        {
            line = line.remove("=").remove("(").remove(")").remove(",");
            lineParts = line.split(" ", Qt::SkipEmptyParts);

            Node newNode;
            newNode.Input = lineParts.at(0);
            newNode.Left = lineParts.at(1);
            newNode.Right = lineParts.at(2);

            nodes.append(newNode);
        }
    }
    bool atEnd = false;

    QVector<strInput> inputs;

    for(int i=0; i<nodes.size(); ++i)
    {
        if(nodes.at(i).Input[2] == 'A')
        {
            strInput newInput;
            newInput.Input = nodes.at(i).Input;
            newInput.in = nodes.at(i).Input;
            newInput.done = false;
            inputs.append(newInput);
        }
    }

    for(const auto &input : inputs)
    {
        qDebug() << input.Input;
    }

    long long j=0;
    int size = directions.size();
    QVector<long long> iters;
    while(!atEnd)
    {
        for(int x = 0; x<inputs.size(); x++)
        {
            for(int i=0; i<nodes.size(); ++i)
            {
                if(nodes.at(i).Input == inputs[x].in)
                {
                    if(directions.at(j%size) == "L")
                        inputs[x].out = nodes.at(i).Left;
                    else
                        inputs[x].out = nodes.at(i).Right;
                    break;
                }
            }
            if(inputs[x].out[2] == 'Z')
            {
                iters.append(j+1);
                inputs[x].done = true;
            }
            inputs[x].in = inputs[x].out;
        }
        j++;
        QVector<int> toRemove;
        if(inputs.size())
        {
            for(int y = 0; y<inputs.size(); y++)
            {
                if(inputs[y].done)
                {
                    toRemove.append(y);
                }
            }
            for(int index:toRemove)
            {
                inputs.remove(index);
            }
        }
        else
            atEnd = true;
    }
    qDebug() << j << iters;
    long long total=iters.at(0);
    for(int i = 1; i < iters.size(); i++)
    {
        total = findDenominator(total, iters.at(i));
    }
    qDebug() << total;
    return 0;
}

long long findDenominator(long long n1, long long n2)
{
    long long hcf, temp, lcm;

    hcf = n1;
    temp = n2;

    while(hcf != temp)
    {
        if(hcf > temp)
            hcf -= temp;
        else
            temp -= hcf;
    }

    lcm = (n1 * n2) / hcf;

    return lcm;
}
