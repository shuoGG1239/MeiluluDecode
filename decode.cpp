#include "decode.h"

Decode::Decode()
{
    //编码类型初始化
    codeTypeList.append("UTF-8");
    codeTypeList.append("UTF-16LE");
    codeTypeList.append("UTF-16BE");
    codeTypeList.append("GBK");
}
Decode::~Decode()
{
}


/**
 * @brief 读取某个文件的全部数据(二进制形式),适合文件小时使用
 *
 * @param  url 文件的路径
 * @return QByteArray 文件的二进制array
 */
QByteArray Decode::getFileByteArray(const QString &url)
{
    QFile file(url);
    QByteArray filearraybyte;
    if(file.open(QFile::ReadOnly))
    {
        filearraybyte=file.readAll();
    }
    else
        filearraybyte=NULL;
    file.close();
    return filearraybyte;
}


/**
 * @brief 读取某个文件的全部数据(string的形式),适合文件小时使用
 *
 * @param url 文件的路径
 * @return QString 文件的string
 */
QString Decode::getFileStr(const QString &url)
{
    QFile file(url);
    QString filestr;
    if(file.open(QFile::ReadOnly))
    {
        QTextStream datastream(&file);
        filestr=datastream.readAll();
    }
    else
        filestr="";
    file.close();
    return filestr;
}


/**
 * @brief 编码类型转换(类型限制在CodeType可选范围内)
 *
 * @param data  被转换的数据
 * @param srcCodestyle 源数据类型
 * @param dstCodestyle 目标数据类型
 * @return QByteArray  转换完的数据
 */
QByteArray Decode::codeTransform(QByteArray &data, CodeType srcCodestyle, CodeType dstCodestyle)
{
    QByteArray datatransformed;
    //codecForName实例不用手动delete,QTextCodec在析构函数已将其销毁(我猜)
    QTextCodec *srcStyle = QTextCodec::codecForName(codeTypeList.at(srcCodestyle).toLatin1());
    QTextCodec *dstStyle = QTextCodec::codecForName(codeTypeList.at(dstCodestyle).toLatin1());
    datatransformed=dstStyle->fromUnicode(srcStyle->toUnicode(data));
    return datatransformed;
}

/**
 * @brief 编码类型转换(转换类型不限,类型为字符串,是近似匹配,所以也不用太纠结)
 *
 * @param data  被转换的数据
 * @param srcCodestyle 源数据类型
 * @param dstCodestyle 目标数据类型
 * @return QByteArray  转换完的数据
 */
QByteArray Decode::codeTransform(QByteArray &data,
                             const QString &srcCodestyle, const QString &dstCodestyle)
{
    QByteArray datatransformed;
    //codecForName实例不用手动delete,QTextCodec在析构函数已将其销毁(我猜)
    QTextCodec *srcStyle = QTextCodec::codecForName(srcCodestyle.toLatin1());
    QTextCodec *dstStyle = QTextCodec::codecForName(dstCodestyle.toLatin1());
    datatransformed=dstStyle->fromUnicode(srcStyle->toUnicode(data));
    return datatransformed;
}

/**
 * @brief 将数据写入某文件,若文件不存在则创建并写入其中
 *
 * @param url 被写的文件的路径,若只写文件名则文件在exe的根目录
 * @param inputdata 写入的数据
 * @return bool 写入是否成功
 */
bool Decode::writeFile(const QString &url, QByteArray &inputdata)
{
    QFile newfile(url);
    bool openisOK;
    openisOK=newfile.open(QFile::ReadWrite);
    if(true==openisOK)
        newfile.write(inputdata);
    return openisOK;
}


/**
 * @brief 文件编码转化,此函数一个解决,一条龙
 *
 * @param srcurl 源路径(包括路径和文件名等)
 * @param dsturl 目标路径(包括路径和文件名等)
 * @param srcCodestyle 源编码
 * @param dstCodestyle 目标编码
 */
void Decode::doFilechange(const QString &srcurl,const QString &dsturl,
                  CodeType srcCodestyle, CodeType dstCodestyle)
{
    QByteArray srcdata=this->getFileByteArray(srcurl);
    QByteArray dstdata=this->codeTransform(srcdata,srcCodestyle,dstCodestyle);
    this->writeFile(dsturl,dstdata);
}


