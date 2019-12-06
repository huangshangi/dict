#ifndef YOUDAOTRANSLATOR_H
#define YOUDAOTRANSLATOR_H


#include <string>

using namespace std;
class YoudaoTranslator
{


private:

    string jcUrlDict;//日-》中
    string cjUrlDict;
    string jcUrlTran;
    string cjUrlTran;

public:
    virtual void setjcUrlDict(string s);

    virtual void setcjUrlDict(string s);

    virtual void setjcUrlTran(string s);

    virtual void setcjUrlTran(string s);

    virtual string getjcUrlDict();

    virtual string getcjUrlDict();

    virtual string getjcUrlTran();

    virtual string getcjUrlTran();

    virtual string queryDict(string source, string target, string data);

    virtual string queryTran(string source, string target, string data);

    virtual string parseDict(string data);

    virtual string parseTran(string data);

    virtual string excute(int type);

    virtual void setLangSupp();//获取支持语言


};

#endif // YOUDAOTRANSLATOR_H
