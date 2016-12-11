#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "decode.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void meiluluOnefileDecode(const QString &srcurl,const QString &dsturl,
                                      Decode::CodeType dstCodestyle);
    void doMeiluluFileChangeOnce();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
