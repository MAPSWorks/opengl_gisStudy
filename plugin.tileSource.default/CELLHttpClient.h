#pragma once

#include "curl/curl.h"

#include <string>
#include <vector>

using namespace std;

class CELLHttpClient  
{  
public:  
    CELLHttpClient(void)
    {
        m_bDebug    =   false;
    }
    ~CELLHttpClient(void)
    {

    }
protected:
    static size_t onWriteData(void* buffer, size_t size, size_t nmemb, void* lpVoid)  
    {  
        std::vector<char>*  outBuf  =   (std::vector<char>*)lpVoid;
        if (outBuf == 0)
        {
            return  nmemb;
        }
        size_t  srcSize =  outBuf->size(); 
        outBuf->resize(srcSize + size * nmemb);
        char*   pDst    =   &(*outBuf)[srcSize];
        memcpy(pDst,buffer,nmemb * size);

        return nmemb;  
    }
    static int onDebug(CURL *, curl_infotype itype, char * pData, size_t size, void *)  
    {  
        if(itype == CURLINFO_TEXT)  
        {  
            //printf("[TEXT]%s\n", pData);  
        }  
        else if(itype == CURLINFO_HEADER_IN)  
        {  
            printf("[HEADER_IN]%s\n", pData);  
        }  
        else if(itype == CURLINFO_HEADER_OUT)  
        {  
            printf("[HEADER_OUT]%s\n", pData);  
        }  
        else if(itype == CURLINFO_DATA_IN)  
        {  
            printf("[DATA_IN]%s\n", pData);  
        }  
        else if(itype == CURLINFO_DATA_OUT)  
        {  
            printf("[DATA_OUT]%s\n", pData);  
        }  
        return 0;  
    }

public:  
    /** 
    * @brief HTTP POST请求 
    * @param strUrl 输入参数,请求的Url地址,如:http://www.baidu.com 
    * @param strPost 输入参数,使用如下格式para1=val1¶2=val2&… 
    * @param strResponse 输出参数,返回的内容 
    * @return 返回是否Post成功 
    */  
    int post(const char* strUrl, const char* strPost)  
    {  
        CURLcode res;  
        CURL* curl = curl_easy_init();  
        if(NULL == curl)  
        {  
            return CURLE_FAILED_INIT;  
        } 
        if(m_bDebug)  
        {  
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);  
            curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, onDebug);  
        }  
        FILE*   pFile   =   fopen("c:/aa.jpg","wb");

        curl_easy_setopt(curl, CURLOPT_URL, strUrl);  
        curl_easy_setopt(curl, CURLOPT_POST, 1);  
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strPost);  
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);  
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, onWriteData);  
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)pFile);  
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);  
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);  
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);  
        res = curl_easy_perform(curl);  
        curl_easy_cleanup(curl);  

        fclose(pFile);

        return res;  
    }  
  
    /** 
    * @brief HTTP GET请求 
    * @param strUrl 输入参数,请求的Url地址,如:http://www.baidu.com 
    * @param strResponse 输出参数,返回的内容 
    * @return 返回是否Post成功 
    */  
    int get(const char* strUrl,std::vector<char>& responseRes)  
    {  
        CURLcode    res;  
        CURL*       curl = curl_easy_init();  
        if(NULL == curl)  
        {  
            return CURLE_FAILED_INIT;  
        }  
        if(m_bDebug)  
        {  
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);  
            curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, onDebug);  
        }  

        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");


        curl_easy_setopt(curl, CURLOPT_URL, strUrl);  
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);  
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, onWriteData);  
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&responseRes);  
        /** 
        *   当多个线程都使用超时处理的时候，同时主线程中有sleep或是wait等操作。 
        *   如果不设置这个选项，libcurl将会发信号打断这个wait从而导致程序退出。 
        */  
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);  
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);  
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);  
        res = curl_easy_perform(curl);  
        curl_easy_cleanup(curl);  


        return res;  
    }  
  
    /** 
    * @brief HTTPS POST请求,无证书版本 
    * @param strUrl 输入参数,请求的Url地址,如:https://www.alipay.com 
    * @param strPost 输入参数,使用如下格式para1=val1¶2=val2&… 
    * @param strResponse 输出参数,返回的内容 
    * @param pCaPath 输入参数,为CA证书的路径.如果输入为NULL,则不验证服务器端证书的有效性. 
    * @return 返回是否Post成功 
    */  
    
    int posts(const std::string & strUrl, const std::string & strPost, std::string & strResponse, const char * pCaPath)  
    {  
        CURLcode    res;  
        CURL*       curl    =   curl_easy_init();  
        if(NULL == curl)  
        {  
            return CURLE_FAILED_INIT;  
        }  
        if(m_bDebug)  
        {  
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);  
            curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, onDebug);  
        }  
        curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());  
        curl_easy_setopt(curl, CURLOPT_POST, 1);  
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strPost.c_str());  
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);  
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, onWriteData);  
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&strResponse);  
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);  
        if(NULL == pCaPath)  
        {  
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);  
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);  
        }  
        else  
        {  
            //缺省情况就是PEM，所以无需设置，另外支持DER  
            //curl_easy_setopt(curl,CURLOPT_SSLCERTTYPE,"PEM");  
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);  
            curl_easy_setopt(curl, CURLOPT_CAINFO, pCaPath);  
        }  
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);  
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);  
        res = curl_easy_perform(curl);  
        curl_easy_cleanup(curl);  
        return res;  
    }  
  
    /** 
    * @brief HTTPS GET请求,无证书版本 
    * @param strUrl 输入参数,请求的Url地址,如:https://www.alipay.com 
    * @param strResponse 输出参数,返回的内容 
    * @param pCaPath 输入参数,为CA证书的路径.如果输入为NULL,则不验证服务器端证书的有效性. 
    * @return 返回是否Post成功 
    */  
    int gets(const std::string & strUrl, std::string & strResponse, const char * pCaPath)  
    {  
        CURLcode res;  
        CURL* curl = curl_easy_init();  
        if(NULL == curl)  
        {  
            return CURLE_FAILED_INIT;  
        }  
        if(m_bDebug)  
        {  
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);  
            curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, onDebug);  
        }  
        curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());  
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);  
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, onWriteData);  
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&strResponse);  
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);  
        if(NULL == pCaPath)  
        {  
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);  
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);  
        }  
        else  
        {  
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);  
            curl_easy_setopt(curl, CURLOPT_CAINFO, pCaPath);  
        }  
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);  
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);  
        res = curl_easy_perform(curl);  
        curl_easy_cleanup(curl);  
        return res;  
    }  
  
private:  
    bool m_bDebug;  
};  