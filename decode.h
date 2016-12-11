#ifndef DECODE_H
#define DECODE_H

#include <qstring.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qtextcodec.h>


/**
 * @brief 汉化解码类
 *
 */
class Decode
{
public:
    enum CodeType
    {
        UTF8=0,
        UTF16LE=1,
        UTF16BE=2,
        GBK=3,
    };
    Decode();
    ~Decode();


    QString getFileStr(const QString &url);
    QByteArray getFileByteArray(const QString &url);
    QByteArray codeTransform(QByteArray &data, CodeType srcCodestyle, CodeType dstCodestyle);
    QByteArray codeTransform(QByteArray &data,
                                 const QString &srcCodestyle, const QString &dstCodestyle);
    bool writeFile(const QString &url, QByteArray &inputdata);

    /*偷懒集成型函数*/
    void doFilechange(const QString &srcurl,const QString &dsturl,
                      CodeType srcCodestyle, CodeType dstCodestyle);



protected:


private:
    QStringList codeTypeList;


private slots:

};

#endif // DECODE_H
