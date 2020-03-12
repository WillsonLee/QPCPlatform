#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QObject>
#include <QLabel>
#include <QLinearGradient>

class CustomLabel : public QLabel
{
public:
    CustomLabel(QWidget *parent=Q_NULLPTR);
public:
    void setColors(QColor c1, QColor c2);
protected:
    void paintEvent(QPaintEvent *event);
private:
    QLinearGradient grad;
    QColor c1;
    QColor c2;
};

#endif // CUSTOMLABEL_H
