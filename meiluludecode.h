#ifndef MEILULUDECODE_H
#define MEILULUDECODE_H

#include <QFileInfo>
#include <QFileDialog>
#include "decode.h"

#define SENTENCE_NUM_STEP  4  //保存句子数的数据格式为4字节,位于文件开头
#define SENTENCE_LEN_STEP  4  //保存句长的数据格式为4字节
#define MIDDLE_STEP        32 //中间未知的固定长度间隔

class MeiLuLuDecode
{
public:
    MeiLuLuDecode();

    void meiluluOnefileDecode(const QString &srcurl,const QString &dsturl,
                                      Decode::CodeType dstCodestyle);
    void doMeiluluFileChangeOnce();

private:
    MeiLuLuDecode(const MeiLuLuDecode &cpy);
};

#endif // MEILULUDECODE_H
