#include "meiluludecode.h"

MeiLuLuDecode::MeiLuLuDecode()
{
}


/**
 * @brief
 *
 * @param srcurl 源路径(包括路径和文件名等)
 * @param dsturl 目标路径(包括路径和文件名等)
 * @param dstCodestyle 目标编码
 */
void MeiLuLuDecode::meiluluOnefileDecode(const QString &srcurl,const QString &dsturl,
                                  Decode::CodeType dstCodestyle)
{
    Decode code1;
    QByteArray dstarray;
    QByteArray srcarray=code1.getFileByteArray(srcurl);
    QList<QByteArray> arraylist; //用来存所有的句子,一个句子为一个成员
    quint32 curpos=0;            //当前字节位置
    quint16 curtextsize;         //当前句子的字节数
    quint16 sentencetotalnum;    //句子总数
    sentencetotalnum =(quint16)(srcarray.at(curpos))+((quint16)(srcarray.at(curpos+1)))*256;
    curpos+=SENTENCE_NUM_STEP;
    /*先开个循环把每个句子提取到arraylist中*/
    for(int i=0;i<sentencetotalnum;i++)
    {
        curpos+=MIDDLE_STEP;
        curtextsize=(quint8)(srcarray.at(curpos))+((quint16)(srcarray.at(curpos+1)))*256;//这里偷懒只用2个字节
        curpos+=SENTENCE_LEN_STEP;
        QByteArray newarray;
        newarray=srcarray.mid(curpos,curtextsize-1); //每个句子最后是0,这个字节去掉
        arraylist.append(newarray);
        curpos+=curtextsize;
    }
    /*再开个循环对每个句子进行精加工转为agemo格式并合并为一个bytearray*/
    QByteArray finalsrcarray; //这个将会保存agemo格式的utf8数据流
    for(int i=0;i<arraylist.size();i++)
    {
        QByteArray newarray=arraylist.at(i);
        newarray.replace(QString("<CR>").toUtf8(),QString("\r\n").toUtf8());//换行符替换
        QString linetitle;
        if(0!=i) //第一个句子开头不用换行
            linetitle+="\r\n\r\n#### ";
        else
            linetitle+="#### ";
        linetitle+=QString::number(i+1);
        linetitle+=" ####\r\n";
        finalsrcarray.append(linetitle.toUtf8());
        finalsrcarray.append(newarray);
    }
    //编码转换:utf8 --> dstCodestyle (梅露露的源文本都是用utf8编码保存的)
    dstarray=code1.codeTransform(finalsrcarray,Decode::UTF8,dstCodestyle);
    code1.writeFile(dsturl,dstarray);
}


/**
 * @brief 在 windows选择并转化一个文件,最后转换完的文件保存到同一个目录下;
 *          执行该函数的时候会立即弹出文件选择界面
 */
void MeiLuLuDecode::doMeiluluFileChangeOnce()
{
    QString file_fullUrl, file_name, file_path, filebasename;
    file_fullUrl=QFileDialog::getOpenFileName();
    if(NULL != file_fullUrl)
    {
        QFileInfo fileinfo1(file_fullUrl);       //file路径全名转为fileinfo对象,好分离出文件名称和后缀
        file_name = fileinfo1.fileName();        //分离出本体的名字(包括后缀)
        file_path = fileinfo1.absolutePath();    //分离出路径
        filebasename=fileinfo1.baseName();       //文件名称

        QString saveFileUrl=file_path+"/"+filebasename+"."+"txt"; //转化完保存在同一个目录下
        this->meiluluOnefileDecode(file_fullUrl, saveFileUrl, Decode::UTF16LE);
    }
}
