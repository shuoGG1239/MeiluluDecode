#include "widget.h"
#include "ui_widget.h"
#include "meiluludecode.h"
#include "qdebug.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //MeiLuLuDecode meidecode;
    // meidecode.doMeiluluFileChangeOnce();
    QString file_fullUrl;
    file_fullUrl=QFileDialog::getOpenFileName();
    if(file_fullUrl != NULL)
    {
        Decode mydecode;
        QByteArray srcode=mydecode.getFileByteArray(file_fullUrl);
        mydecode.writeFile(file_fullUrl+".txt",srcode);
    }
}

Widget::~Widget()
{
    delete ui;
}
