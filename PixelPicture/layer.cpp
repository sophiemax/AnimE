#include "layer.h"

Layer::Layer(int r, int c)
{
    originalnumberofcolumns = r;
    numberofcolumns = r;
    originalnumberofrows = c;
    numberofrows = c;
    startindex = 0;
    for(int i = 0; i < r*c; i++)
    {
        LayerPixel *lp = new LayerPixel();
        lp->index = i;
        pixels.append(lp);
    }
}

Layer::Layer(Layer *l, int r, int c)
{
    originalnumberofrows = r;
    originalnumberofcolumns = c;
    numberofrows = l->getNumberofRows();
    numberofcolumns = l->getNumberofColumns();
    startindex = l->getStartIndex();
    name = l->getName();
    transparent = l->getTransparency();

    for(int i = 0; i < numberofrows*numberofcolumns; i++)
    {
        LayerPixel *lp = new LayerPixel(l->getLayerPixel(i));
        pixels.append(lp);
        //if(lp->color == l->getColorofPixel(i))
            //QTextStream(stdout) << "YESS" << endl;
    }
}

Layer::~Layer()
{
    while (!pixels.isEmpty())
        delete pixels.takeFirst();
}

QString Layer::getName()
{
    return name;
}

void Layer::setName(QString s)
{
    name = s;
}

void Layer::setColorofPixel(int i, QColor color)
{
    int index = calculateCurrentIndex(i);

    pixels[index]->clear = false;
    pixels[index]->color = color;
}

QColor Layer::getColorofPixel(int i)
{
    int index = calculateCurrentIndex(i);

    return pixels[index]->color;
}
void Layer::setTransparency(bool t)
{
    transparent = t;
}

bool Layer::getTransparency()
{
    return transparent;
}

bool Layer::isPixelClear(int i)
{
    int index = calculateCurrentIndex(i);
    return pixels[index]->clear;
}

void Layer::clearPixel(int i)
{
    int index = calculateCurrentIndex(i);
    pixels[index]->clear = true;
}

void Layer::clear()
{
    while (!pixels.isEmpty())
        delete pixels.takeFirst();
    numberofcolumns = originalnumberofcolumns;
    numberofrows = originalnumberofrows;
    startindex = 0;
    for(int i = 0; i < numberofcolumns * numberofrows; i++)
    {
        LayerPixel *lp = new LayerPixel();
        lp->index = i;
        pixels.append(lp);
    }
}

void Layer::setStartIndex(int index)
{
    startindex = index;
}

int Layer::getStartIndex()
{
    return startindex;
}

int Layer::getNumberofColumns()
{
    return numberofcolumns;
}

int Layer::getNumberofRows()
{
    return numberofrows;
}

int Layer::getSize()
{
    return pixels.size();
}

LayerPixel *Layer::getLayerPixel(int index)
{
    return pixels[index];
}

void Layer::moveUp()
{
    QTextStream(stdout) << startindex << endl;
    QTextStream(stdout) << numberofrows << endl;
    //Ha az kijelző felső soránál kezdődik a layer is, és a layer első sorának minden pixele clear,
    //akkor valójában nem csúsztatjuk a layert, hanem felfele másoljuk a pixeladatokat.
    if(isinFirstRow(startindex) && isFirstRowClear())
    {
        QTextStream(stdout) << "Az első sor üres volt!" << endl;
        for(int i = 0; i < numberofcolumns; i++)
        {
            for(int j = 1; j < numberofrows; j++)
            {
                int previousindex = calculateCurrentIndex(j-1,i);
                int index = calculateCurrentIndex(j,i);

                pixels[previousindex]->clear = pixels[index]->clear;
                pixels[previousindex]->color = pixels[index]->color;
            }
            //ha a layer pont annyi sorból áll, mint a kijelző, az utolsó sort nem töröljük, hanem feltöltjük üresre
            if(numberofrows == originalnumberofrows)
            {
                int index = calculateCurrentIndex(numberofrows-1,i);
                pixels[index]->clear = true;
            }
        }
        //ha nem, a legalsó sort töröljük, mivel mindent felmásoltunk, abban már nincsen valid adat
        if(numberofrows > originalnumberofrows)
        {
            QTextStream(stdout) << "A layer nagyobb, mint a kijelző." << endl;
            QTextStream(stdout) << "Az alsó sort töröljük, mert nincs benne valid adat" << endl;
            for(int i = numberofcolumns-1; i >= 0; i--)
            {
                int index = calculateCurrentIndex(numberofrows-1,i);
                pixels.removeAt(index);
            }
            numberofrows -= 1;
        }
    }
    else
    {
        QTextStream(stdout) << "Az első sor NEM volt üres!" << endl;
        //ha a kijelző utolsó soránál végződik a layer, hozzá kell adnunk a layerhez egy sort alulra
        if(isinLastRow(startindex + (originalnumberofrows-1)*numberofcolumns))
        {
            QTextStream(stdout) << "Sort adunk hozzá a layer végéhez!" << endl;
            QTextStream(stdout) << startindex << endl;
            QTextStream(stdout) << originalnumberofrows << endl;
            QTextStream(stdout) << numberofcolumns << endl;
            numberofrows += 1;
            for(int i = 0; i < numberofcolumns; i++)
            {
                LayerPixel *lp = new LayerPixel();
                lp->clear = true;

                pixels.append(lp);
            }
        }
        startindex += numberofcolumns;
    }

    QTextStream(stdout) << startindex << endl;
    QTextStream(stdout) << numberofrows << endl;
}

void Layer::moveDown()
{
    QTextStream(stdout) << startindex << endl;
    QTextStream(stdout) << numberofrows << endl;
    //Ha az kijelző alsó soránál végződik a layer is, és a layer alsó sorának minden pixele clear,
    //akkor valójában nem csúsztatjuk a layert, hanem lefele másoljuk a pixeladatokat.
    QTextStream(stdout) << numberofrows << endl;
    if(isinLastRow(startindex + (originalnumberofrows-1)*numberofcolumns) && isLastRowClear())
    {
        QTextStream(stdout) << "Az utolsó sor üres volt!" << endl;
        for(int i = 0; i < numberofcolumns; i++)
        {
            for(int j = numberofrows - 2; j >= 0; j--)
            {
                int nextindex = calculateCurrentIndex(j+1,i);
                int index = calculateCurrentIndex(j,i);
                pixels[nextindex]->clear = pixels[index]->clear;
                pixels[nextindex]->color = pixels[index]->color;
            }
            //ha a layer pont annyi sorból áll, mint a kijelző, az első sort nem töröljük, hanem feltöltjük üresre
            if(numberofrows == originalnumberofrows)
            {
                int index = calculateCurrentIndex(0,i);
                pixels[index]->clear = true;
            }
        }
        //ha nem, a legfelső sort töröljük, mivel mindent lemásoltunk, abban már nincsen valid adat
        if(numberofrows > originalnumberofrows)
        {
            QTextStream(stdout) << "A layer nagyobb, mint a kijelző." << endl;
            QTextStream(stdout) << "Az első sort töröljük, mert nincs benne valid adat" << endl;
            for(int i = numberofcolumns-1; i >= 0; i--)
            {
                int index = calculateCurrentIndex(0,i);
                pixels.removeAt(index);
            }
            numberofrows -= 1;
            startindex -= numberofcolumns;
        }
    }
    else
    {
        QTextStream(stdout) << "Az utolsó sor NEM volt üres!" << endl;
        //ha a kijelző első soránál végződik a layer, hozzá kell adnunk a layerhez egy sort felülre
        if(isinFirstRow(startindex))
        {
            QTextStream(stdout) << "Sort adunk hozzá a layer elejéhez!" << endl;
            numberofrows += 1;
            for(int i = 0; i < numberofcolumns; i++)
            {
                LayerPixel *lp = new LayerPixel();
                lp->clear = true;

                int index = calculateCurrentIndex(0,i);
                pixels.insert(index,lp);
            }
        }
        else
            startindex -= numberofcolumns;
    }

    QTextStream(stdout) << startindex << endl;
    QTextStream(stdout) << numberofrows << endl;
}

void Layer::moveLeft()
{
    QTextStream(stdout) << startindex << endl;
    QTextStream(stdout) << numberofcolumns << endl;

    //Ha az kijelző első oszlopában kezdődik a layer is, és a layer első oszlopának minden pixele clear,
    //akkor valójában nem csúsztatjuk a layert, hanem balra másoljuk a pixeladatokat.
    if(isinFirstColumn(startindex) && isFirstColumnClear())
    {
        QTextStream(stdout) << "Az első oszlop üres volt!" << endl;
        for(int j = 0; j < numberofrows; j++)
        {
            for(int i = 1; i < numberofcolumns; i++)
            {
                int previousindex = calculateCurrentIndex(j,i-1);
                int index = calculateCurrentIndex(j,i);

                pixels[previousindex]->clear = pixels[index]->clear;
                pixels[previousindex]->color = pixels[index]->color;
            }
            //ha a layer pont annyi oszlopból áll, mint a kijelző, az utolsó oszlopot nem töröljük, hanem feltöltjük üresre
            if(numberofcolumns == originalnumberofcolumns)
            {
                int index = calculateCurrentIndex(j,numberofcolumns-1);
                pixels[index]->clear = true;
            }
        }
        //ha nem, a legutolsó oszlopot töröljük, mivel mindent balramásoltunk, abban már nincsen valid adat
        if(numberofcolumns > originalnumberofcolumns)
        {
            QTextStream(stdout) << "A layer nagyobb, mint a kijelző." << endl;
            QTextStream(stdout) << "Az utolsó oszlopot töröljük, mert nincs benne valid adat" << endl;
            for(int j = numberofrows-1; j >= 0; j--)
            {
                int index = calculateCurrentIndex(j,numberofcolumns-1);
                pixels.removeAt(index);
            }
            int startrow = startindex/numberofcolumns;
            startindex -= startrow;
            numberofcolumns -= 1;
        }
    }
    else
    {
        QTextStream(stdout) << "Az első oszlop NEM volt üres!" << endl;
        //ha a kijelző utolsó oszlopánál vége van a layernek, hozzá kell adnunk a layerhez egy oszlopot a végére
        if(isinLastColumn(startindex + originalnumberofcolumns - 1))
        {
            int startrow = startindex/numberofcolumns;
            startindex += startrow;

            QTextStream(stdout) << "Oszlopot adunk hozzá a layer végéhez!" << endl;
            numberofcolumns += 1;
            for(int j = 0; j < numberofrows; j++)
            {
                LayerPixel *lp = new LayerPixel();
                lp->clear = true;
                int index = calculateCurrentIndex(j,numberofcolumns-1);
                pixels.insert(index, lp);
            }
        }
        startindex += 1;
        //a kijelző kezdetét jelző startindex eggyel jobbra csúszott.
    }

    QTextStream(stdout) << "<End>" << endl;
    QTextStream(stdout) << startindex + originalnumberofcolumns - 1 << endl;
    QTextStream(stdout) << isinLastColumn(startindex + originalnumberofcolumns - 1) << endl;
    QTextStream(stdout) << startindex << endl;
    QTextStream(stdout) << numberofcolumns << endl;
    QTextStream(stdout) << "</End>" << endl;
}

void Layer::moveRight()
{
    //Ha az kijelző utolsó oszlopában végződik a layer is, és a layer utolsó oszlopának minden pixele clear,
    //akkor valójában nem csúsztatjuk a layert, hanem jobbra másoljuk a pixeladatokat.
    if(isinLastColumn(startindex + originalnumberofcolumns - 1) && isLastColumnClear())
    {

        QTextStream(stdout) << "Az utolsó oszlop üres volt!" << endl;
        for(int j = 0; j < numberofrows; j++)
        {
            for(int i = numberofcolumns - 2; i >= 0; i--)
            {
                int nextindex = calculateCurrentIndex(j,i+1);
                int index = calculateCurrentIndex(j,i);
                pixels[nextindex]->clear = pixels[index]->clear;
                pixels[nextindex]->color = pixels[index]->color;
            }
            //ha a layer pont annyi oszlopból áll, mint a kijelző, az első oszlopot nem töröljük, hanem feltöltjük üresre
            if(numberofcolumns == originalnumberofcolumns)
            {
                int index = calculateCurrentIndex(j,0);
                pixels[index]->clear = true;
            }
        }
        //ha nem, a legelső oszlopot töröljük, mivel mindent jobbramásoltunk, abban már nincsen valid adat
        if(numberofcolumns > originalnumberofcolumns)
        {
            QTextStream(stdout) << "A layer nagyobb, mint a kijelző." << endl;
            QTextStream(stdout) << "Az első oszlopot töröljük, mert nincs benne valid adat" << endl;
            for(int j = numberofrows-1; j >= 0; j --)
            {
                int index = calculateCurrentIndex(j,0);
                pixels.removeAt(index);
            }

            int startrow = startindex/numberofcolumns + 1;
            startindex -= startrow;
            numberofcolumns -= 1;
        }
    }
    else
    {
        QTextStream(stdout) << "Az utolsó oszlop NEM volt üres!" << endl;
        //ha a kijelző első oszlopánál kezdődik a layer, hozzá kell adnunk a layerhez egy oszlopot az elejére
        if(isinFirstColumn(startindex))
        {
            int startrow = startindex/numberofcolumns;
            startindex += startrow;
            QTextStream(stdout) << "Oszlopot adunk hozzá a layer elejéhez!" << endl;
            numberofcolumns += 1;
            for(int j = 0; j < numberofrows; j++)
            {
                LayerPixel *lp = new LayerPixel();
                lp->clear = true;

                int index = calculateCurrentIndex(j,0);
                pixels.insert(index, lp);
            }
        }
        else
            startindex -=1;
        //a kijelző kezdetét jelző startindex eggyel balra csúszott.
    }

    QTextStream(stdout) << startindex << endl;
    QTextStream(stdout) << numberofcolumns << endl;
}

//megnézi, hogy a layer első oszlopában minden pixel clear-e
bool Layer::isFirstColumnClear()
{
    bool clear = true;
    for(int i = 0; i < numberofcolumns * numberofrows; i += numberofcolumns)
        if(pixels[i]->clear == false)
            clear = false;
    return clear;
}

//megnézi, hogy a layer utolsó oszlopában minden pixel clear-e
bool Layer::isLastColumnClear()
{
    bool clear = true;
    for(int j = 0; j < numberofrows; j++)
    {
        int index = calculateCurrentIndex(j,numberofcolumns-1);
        if(pixels[index]->clear == false)
            clear = false;
    }
    return clear;
}

//megnézi, hogy a layer első sorában minden pixel clear-e
bool Layer::isFirstRowClear()
{
    bool clear = true;
    for(int i = 0; i < numberofcolumns; i++)
        if(pixels[i]->clear == false)
            clear = false;
    return clear;
}

//megnézi, hogy a layer utolsó sorában minden pixel clear-e
bool Layer::isLastRowClear()
{
    bool clear = true;
    for(int i = numberofcolumns * (numberofrows-1); i < numberofcolumns * numberofrows; i++)
        if(pixels[i]->clear == false)
            clear = false;
    return clear;
}

//megnézi, hogy az adott indexű pixel a layer első oszlopában van-e
bool Layer::isinFirstColumn(int index)
{
    if(index % numberofcolumns == 0)
        return true;
    return false;
}

//megnézi, hogy az adott indexű pixel a layer utolsó oszlopában van-e
bool Layer::isinLastColumn(int index)
{
    if(index % numberofcolumns == (numberofcolumns - 1))
        return true;
    return false;
}

//megnézi, hogy az adott indexű pixel a layer első sorában van-e
bool Layer::isinFirstRow(int index)
{
    if(index < numberofcolumns)
        return true;
    return false;
}

//megnézi, hogy az adott indexű pixel a layer utolsó sorában van-e
bool Layer::isinLastRow(int index)
{
    if(index >= numberofcolumns * (numberofrows-1))
        return true;
    return false;
}

//kiszámolja az eredeti kijelzőindexből az aktuális layerindexet (a képernyő indexének megfelelő pixel indexét)
int Layer::calculateCurrentIndex(int originalIndex)
{
    int originalrowofindex = originalIndex / originalnumberofcolumns;
    int originalcolumnofindex = originalIndex - originalrowofindex * originalnumberofcolumns;

    int index = startindex + originalrowofindex*numberofcolumns + originalcolumnofindex;
    return index;
}

//kiszámolja az aktuális layerindexet, bemenete az, hogy a pixel a layerben hanyadik sorban és oszlopban
int Layer::calculateCurrentIndex(int row, int column)
{
    return (row * numberofcolumns + column);
}
