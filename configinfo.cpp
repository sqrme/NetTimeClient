#include "configinfo.h"
#include <iostream>
#include <fstream>
#include "string.h"
#include <vector>
#include "stdlib.h"
#include <string>
#include <list>
#include "unistd.h"
#include "log.h"

ConfigInfo::ConfigInfo()
{
    this->localIP="";
    this->sendIP="";
    this->port=0;
    this->autoAdjust=false;
    this->adjustInteval=-1;
    this->zeroProtectRange=-1;
}


/*
过滤字符空格等字符
*/
string ConfigInfo::trimStr(string str){
    string resultStr="";
    string::iterator is=str.begin();
    while(is!=str.end()){
        if(*is!=' ' && *is!='\t')
            resultStr.push_back(*is);
        is++;
    }
    return resultStr;
}

//判断是否为数字
bool ConfigInfo::isNumber(string numStr){
     string numbers="0123456789";
     bool ret=true;
     string::iterator is=numStr.begin();
     while(is!=numStr.end()){
         if(numbers.find(*is)==string::npos){
             ret=false;
             break;
         }
         is++;
     }
     return ret;
}

//判断是否为合法ip地址
bool ConfigInfo::isIPString(const string ipstr){
    string numbers="0123456789";
    string ips=ipstr;
    string ipn;
    vector<string> ipv;
    bool ret=true;

    int index=ips.find('.');
    ipn=ips.substr(0,index);
    ipv.push_back(ipn);
    for(int i=0;i<3;i++){
        ips=ips.substr(ipn.length()+1,ips.length()-ipn.length());
        index=ips.find('.');
        ipn=ips.substr(0,index);
        ipv.push_back(ipn);
    }
    if(!(ipv.size()==4)){
        ret=false;
    }else{
        for(int i=0;i<4;i++){
            if(!isNumber(ipv.at(i))){
                ret=false;
                break;
            }
            int ipValue=atoi(ipv.at(i).c_str());
            if(ipValue<0 || ipValue>255){
                ret=false;
            }
        }
    }

    return ret;
}


/*
  example:
    本机IP：192.168.92.16
    发送IP：232.6.6.6
    端口号：6666

  载入配置
  如果载入失败则返回false 并输出提示性信息
*/
bool ConfigInfo::LoadConfig(string configFileName){
    bool ret=false;
    string str,temp;
    int start=-1,okCount=0;
    ifstream file(configFileName);
    if(!file){
        cout<<"配置文件打开错误！";
        return ret;
    }

    while(getline(file,str)){
        str=trimStr(str);
        if(strstr(str.c_str(),"#")){
            continue;
        }

        // 本机IP
        else if(strstr(str.c_str(),"本机IP：")){
            start=str.find('：')+1;
            temp=str.substr(start,str.length()-start);
            if(isIPString(temp)){
                this->localIP=temp;
                okCount++;
            }
            else{
                break;
            }
        }
        //组播地址
        else if(strstr(str.c_str(),"组播地址：")){
            start=str.find('：')+1;;
            temp=str.substr(start,str.length()-start);
            if(isIPString(temp)){
                this->sendIP=temp;
                okCount++;
            }
            else{
                break;
            }
        }
        //端口
        else if(strstr(str.c_str(),"端口号：")){
            start=str.find('：')+1;
            temp=str.substr(start,str.length()-start);
            if(isNumber(temp)){
                int tempValue=atoi(temp.c_str());
                if(tempValue>0){
                    this->port=tempValue;
                    okCount++;
                }else{
                    break;
                }
            }else{
                break;
            }
        }
        //组播源：
        else if(strstr(str.c_str(),"组播源：")){
            start=str.find('：')+1;;
            temp=str.substr(start,str.length()-start);
            if(isIPString(temp)){
                this->sourceIP=temp;
                okCount++;
            }
            else{
                break;
            }
        }

        //#自动校时是否启用？ 是 or 否
        else if(strstr(str.c_str(),"自动校时：")){
            start=str.find('：')+1;
            temp=str.substr(start,str.length()-start);
            str=trimStr(str);
            if(temp.compare("是")==0){
                this->autoAdjust=true;
                okCount++;
            }
            else if(temp.compare("否")==0){
                this->autoAdjust=false;
                okCount++;
            }
            else{
                break;
            }
        }

        //自动校时间隔：120
        else if(strstr(str.c_str(),"自动校时间隔：")){
            string cs="自动校时间隔：";
            temp=str.substr(cs.length(),str.length()-cs.length());
            if(isNumber(temp)){
                int tempValue=atoi(temp.c_str());
                if(tempValue>1){
                    this->adjustInteval=tempValue;
                    okCount++;
                }else{
                    break;
                }
            }else{
                break;
            }
        }

        //校时保护范围：
        else if(strstr(str.c_str(),"校时保护范围：")){
            string js="校时保护范围：";
            temp=str.substr(js.length(),str.length()-js.length());
            if(isNumber(temp)){
                int tempValue=atoi(temp.c_str());
                if(tempValue>5){
                    this->zeroProtectRange=tempValue;
                    okCount++;
                }else{
                    break;
                }
            }else{
                break;
            }
        }
     }
    file.close();

    if(okCount==7){
        ret=true;
        Log::RaiseLogInfo(Info,"配置文件载入成功！");
    }
    else{
        Log::RaiseLogInfo(Error,"配置文件载入失败！");
    }
    return ret;
}

string ConfigInfo::getLocalIP(){
    return this->localIP;
}

string ConfigInfo::getSendIP(){
    return this->sendIP;
}

string ConfigInfo::getSourceIP(){
    return this->sourceIP;
}

int ConfigInfo::getPort(){
    return this->port;
}

bool ConfigInfo::isAutoAdjustEnable(){
    return this->autoAdjust;
}

int ConfigInfo::getAdjustInteval(){
    return this->adjustInteval;
}

int ConfigInfo::getZeroProtectRange(){
    return this->zeroProtectRange;
}







