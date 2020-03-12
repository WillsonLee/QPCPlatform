#ifndef TYPENAMEDISPLAYER_H
#define TYPENAMEDISPLAYER_H
#include <QString>
#include <QStringList>
#include <QMap>

class TypeNameDisplayer
{
public:
    TypeNameDisplayer();
    static void initMaps();
    static QString toDisplay(QString name);
    static QString fromDisplay(QString name);
    static QStringList allDisplayTypeStrings();
    static void addTypeStrMap(QString type,QString display);
private:
    static QMap<QString,QString> typeToDisplay;
    static QMap<QString,QString> displayToType;
};

#endif // TYPENAMDISPLAYER_H
