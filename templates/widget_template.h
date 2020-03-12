#ifndef TARGET_WIDGET_AUTO_REPLACED_H
#define TARGET_WIDGET_AUTO_REPLACED_H

#include <QWidget>

namespace Ui {
class PLUGIN_WIDGET_AUTO_REPLACED;
}

class PLUGIN_WIDGET_AUTO_REPLACED : public QWidget
{
    Q_OBJECT

public:
    explicit PLUGIN_WIDGET_AUTO_REPLACED(QWidget *parent = 0);
    ~PLUGIN_WIDGET_AUTO_REPLACED();
signals:
//    void internalArgsChanged(int a,int b,int c);

private:
    Ui::PLUGIN_WIDGET_AUTO_REPLACED *ui;
};

#endif // PLUGIN_WIDGET_AUTO_REPLACED_H
