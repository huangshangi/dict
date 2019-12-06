#include "YoudaoTranslator.h"

void YoudaoTranslator::setjcUrlDict(string s)
{
    jcUrlDict = s;
}

void YoudaoTranslator::setcjUrlDict(string s)
{
    cjUrlDict = s;
}

void YoudaoTranslator::setjcUrlTran(string s)
{
    jcUrlTran = s;
}

void YoudaoTranslator::setcjUrlTran(string s)
{
    cjUrlTran = s;
}

string YoudaoTranslator::getjcUrlDict()
{
    return jcUrlDict;
}

string YoudaoTranslator::getcjUrlDict()
{
    return cjUrlDict;
}

string YoudaoTranslator::getjcUrlTran()
{
    return jcUrlTran;
}

string YoudaoTranslator::getcjUrlTran()
{
    return cjUrlTran;
}
string YoudaoTranslator::queryDict(string source, string target, string data){

    return "";
}
string YoudaoTranslator::queryTran(string source, string target, string data){

    return "";
}

string YoudaoTranslator::parseDict(string data){

    return "";
}

string YoudaoTranslator::parseTran(string data){

    return "";
}

void YoudaoTranslator::setLangSupp(){

}

string YoudaoTranslator::excute(int type)
{
    //翻译单词
    if (type == 0) {

    }
    return string();
}
