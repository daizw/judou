// win_cDemo.cpp : 定义控制台应用程序的入口点。
//

#include "ICTCLAS2011.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef OS_LINUX
#pragma comment(lib, "ICTCLAS2011.lib")
#else
#include <iconv.h>
#endif

//Linux
#ifdef OS_LINUX
	#define _stricmp(X,Y) strcasecmp((X),(Y))
	#define _strnicmp(X,Y,Z) strncasecmp((X),(Y),(Z))
	#define strnicmp(X,Y,Z)	strncasecmp((X),(Y),(Z))
	#define _fstat(X,Y)     fstat((X),(Y))
	#define _fileno(X)     fileno((X))
	#define _stat           stat
	#define _getcwd         getcwd
	#define _off_t          off_t
	#define PATH_DELEMETER  "/"

int MAX_OUTPUT = 1024;
char * g_buf = NULL;
iconv_t g_cd = NULL;
void open_output(const char* to, const char* from)
{
    if (g_cd != NULL)
        iconv_close(g_cd);
    g_cd = iconv_open(to, from);
    if (g_cd == (iconv_t)-1) {
        printf("iconv_open failed!\n");
        exit(EXIT_FAILURE);
    }

    g_buf = (char *)realloc(g_buf, MAX_OUTPUT);
    memset(g_buf, 0, MAX_OUTPUT);
}
char * prepare_output(const char *msg)
{
    int len = strlen(msg);
    if (len > MAX_OUTPUT)
    {
        MAX_OUTPUT = len;
        g_buf = (char *)realloc(g_buf, MAX_OUTPUT);
    }
    memset(g_buf, 0, MAX_OUTPUT);
    char *inptr = (char *)msg;
    char *outptr = g_buf;
    size_t in_left = len;
    size_t out_left = MAX_OUTPUT;

    size_t r = iconv(g_cd, &inptr, &in_left, &outptr, &out_left);
    if (r == -1) {
        printf("iconv failed!\n");
        exit(EXIT_FAILURE);
    }
    return g_buf;
}
void close_output()
{
    if (g_buf != NULL)
        free(g_buf);
    iconv_close(g_cd);
}
#else
	#pragma warning(disable:4786)
	#define PATH_DELEMETER  "\\"
void open_output(const char* from, const char* to) { }
char * prepare_output(const char *msg)
{
    return msg;
}
void close_output() { }
#endif
void SplitGBK(const char *sInput);
void SplitBIG5();
void SplitUTF8();

void SplitGBK(const char *sInput)
{//分词演示

	//初始化分词组件
	if(!ICTCLAS_Init())//数据在当前路径下，默认为GBK编码的分词
	{
		printf("ICTCLAS INIT FAILED!\n");
		return ;
	}

	ICTCLAS_SetPOSmap(ICT_POS_MAP_SECOND);

	char sSentence[2000]="三枪拍案惊奇的主创人员包括孙红雷、小沈阳、闫妮等，导演为张艺谋";
	const char * sResult;

	int nCount;
	ICTCLAS_ParagraphProcessA(sSentence,&nCount);
	printf("nCount=%d\n",nCount);

	ICTCLAS_AddUserWord("孙红雷 yym");//添加孙红雷，作为演员名称
	sResult = ICTCLAS_ParagraphProcess(sSentence,1);
	printf("%s\n", prepare_output(sResult));
	ICTCLAS_AddUserWord("小沈阳 yym");//添加小沈阳，作为演员名称
	sResult = ICTCLAS_ParagraphProcess(sSentence,1);
	printf("%s\n", prepare_output(sResult));
	ICTCLAS_AddUserWord("闫妮 yym");//添加闫妮，作为演员名称
	sResult = ICTCLAS_ParagraphProcess(sSentence,1);
	printf("%s\n", prepare_output(sResult));
	ICTCLAS_AddUserWord("三枪拍案惊奇 dym");//添加三枪拍案惊奇，作为电影名称
	sResult = ICTCLAS_ParagraphProcess(sSentence,1);
	printf("%s\n", prepare_output(sResult));
	

	while(_stricmp(sSentence,"q")!=0)
	{
		sResult = ICTCLAS_ParagraphProcess(sSentence,0);
		printf("%s\nInput string now('q' to quit)!\n", prepare_output(sResult));

		scanf("%s", sSentence);
                open_output("GB18030", "UTF-8");
                char *p = prepare_output(sSentence);
                strcpy(sSentence, p);
                sSentence[strlen(p)+1] = NULL;
                open_output("UTF-8", "GB18030");
                p = prepare_output(sSentence);
	}
	
	//导入用户词典前
	printf(prepare_output("未导入用户词典：\n"));
	sResult = ICTCLAS_ParagraphProcess(sInput, 0);
	printf("%s\n", prepare_output(sResult));

	//导入用户词典后
	printf(prepare_output("\n导入用户词典后：\n"));
	nCount = ICTCLAS_ImportUserDict("userdic.txt");//userdic.txt覆盖以前的用户词典
	//保存用户词典
	ICTCLAS_SaveTheUsrDic();
	printf(prepare_output("导入%d个用户词。\n"), nCount);
	
	sResult = ICTCLAS_ParagraphProcess(sInput, 1);
	printf("%s\n", prepare_output(sResult));

	//动态添加用户词
	printf(prepare_output("\n动态添加用户词后：\n"));
	ICTCLAS_AddUserWord("计算机学院   xueyuan");
	ICTCLAS_SaveTheUsrDic();
	sResult = ICTCLAS_ParagraphProcess(sInput, 1);
	printf("%s\n", prepare_output(sResult));


	//对文件进行分词
	ICTCLAS_FileProcess("testGBK.txt","testGBK_result.txt",1);


	//释放分词组件资源
	ICTCLAS_Exit();
}

void SplitBIG5()
{
	//初始化分词组件
	if(!ICTCLAS_Init("",BIG5_CODE))//数据在当前路径下，设置为BIG5编码的分词
	{
		printf("ICTCLAS INIT FAILED!\n");
		return ;
	}
	ICTCLAS_FileProcess("testBIG.txt","testBIG_result.txt");
	ICTCLAS_Exit();
}
void SplitUTF8()
{
	//初始化分词组件
	if(!ICTCLAS_Init("",UTF8_CODE))//数据在当前路径下，设置为UTF8编码的分词
	{
		printf("ICTCLAS INIT FAILED!\n");
		return ;
	}
	ICTCLAS_FileProcess("testUTF.txt","testUTF_result.txt");
	ICTCLAS_Exit();
}

int main()
{
        open_output("UTF-8", "GB18030");

	const char *sInput = "张华平2009年底调入北京理工大学计算机学院。";
	//分词
	SplitBIG5();
	SplitGBK(sInput);
	SplitUTF8();
	
        //char buf[1024];
        //scanf("%s", buf);
        //open_output("GB18030", "UTF-8");
        //char *p = prepare_output(buf);
        //strcpy(buf, p);
        //open_output("UTF-8", "GB18030");
        //p = prepare_output(buf);
        //printf("%s\n", p);

        close_output();
	return 1;
}

