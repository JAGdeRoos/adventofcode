#include <QCoreApplication>
#include <QFile>
#include <QStringList>
#include <QTime>
#include <QDateTime>

struct Hand
{
    QString cards;
    int64_t iBid;
    int64_t iType;
    int64_t iRank;
};

enum handType
{
    HighCard = 1,
    OnePair,
    TwoPair,
    ThreeOfAKind,
    FullHouse,
    FourOfAKind,
    FiveOfAKind
};

QMap<QChar, int> map;

bool hand_sorter(Hand const& lhs, Hand const& rhs);
int getType(QString hand);

int main(int argc, char *argv[])
{
    map.insert('2', 2);
    map.insert('3', 3);
    map.insert('4', 4);
    map.insert('5', 5);
    map.insert('6', 6);
    map.insert('7', 7);
    map.insert('8', 8);
    map.insert('9', 9);
    map.insert('T', 10);
    map.insert('J', 1); // 11 for part 1, 1 for part 2
    map.insert('Q', 12);
    map.insert('K', 13);
    map.insert('A', 14);

    QCoreApplication a(argc, argv);

    QFile file("../input.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return 0;

    QString line = "";
    QStringList lineParts;
    QVector<Hand> hands;

    while(!file.atEnd()) // populate seeds and maps
    {
        line = file.readLine();
        line = line.remove("\n");
        if (!line.isEmpty())
        {
            Hand newCard;
            lineParts = line.split(" ", Qt::SkipEmptyParts);
            newCard.cards = lineParts.at(0);
            newCard.iBid = lineParts.at(1).toInt();
            newCard.iType = getType(newCard.cards);

            hands.append(newCard);
        }
    }

    std::sort(hands.begin(), hands.end(), &hand_sorter);

    long long iTotal = 0;
    int len = hands.size()-1;
    for(int i = len; i >= 0; i--)
    {
        hands[i].iRank = i+1;
        iTotal += hands[i].iRank * hands[i].iBid;
    }
    qDebug() << iTotal << hands.size()-1;
}

bool hand_sorter(Hand const& lhs, Hand const& rhs) {
    if (lhs.iType != rhs.iType)
        return lhs.iType < rhs.iType;

    for(int x=0; x<lhs.cards.size(); x++)
    {
        int iVal = map.value(lhs.cards[x]);
        int jVal = map.value(rhs.cards[x]);
        if(iVal != jVal)
        {
            return iVal < jVal;
        }
    }

    return false;
}

int getType(QString hand)
{

    std::sort(hand.begin(), hand.end());

    int len = hand.length();

    QVector<int> counts;
    int jCount = 0;
    // Loop through the sorted string to find duplicates
    for (int i = 0; i < len; i++) {
        int count = 1;
        if(hand[i] == 'J')
            jCount++;
        // Counting the occurrences of each character
        while (i < len - 1 && hand[i] == hand[i + 1])
        {
            if(hand[i] == 'J')
                jCount++;
            count++;
            i++;
        }
        // Printing the duplicate character and its count
        if(hand[i] != 'J' || count == len)
            counts.append(count);
    }

    std::sort(counts.begin(), counts.end());
    counts.last() += jCount;

    int retVal = 0;
    switch (counts.size())
    {
    case 1: retVal = FiveOfAKind; break;
    case 2:
        if(counts.contains(4))
            retVal = FourOfAKind;
        else
            retVal = FullHouse;
        break;
    case 3:
        if(counts.contains(3))
            retVal = ThreeOfAKind;
        else
            retVal = TwoPair;
        break;
    case 4: retVal = OnePair; break;
    case 5: retVal = HighCard; break;
    }
    return retVal;
}


