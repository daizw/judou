// win_cDemo.cpp : �������̨Ӧ�ó������ڵ㡣
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
{//�ִ���ʾ

	//��ʼ���ִ����
	if(!ICTCLAS_Init())//�����ڵ�ǰ·���£�Ĭ��ΪGBK����ķִ�
	{
		printf("ICTCLAS INIT FAILED!\n");
		return ;
	}

	ICTCLAS_SetPOSmap(ICT_POS_MAP_SECOND);

	char sSentence[2000]="��ǹ�İ������������Ա��������ס�С���������ݵȣ�����Ϊ����ı";
	const char * sResult;

	int nCount;
	ICTCLAS_ParagraphProcessA(sSentence,&nCount);
	printf("nCount=%d\n",nCount);

	ICTCLAS_AddUserWord("����� yym");//�������ף���Ϊ��Ա����
	sResult = ICTCLAS_ParagraphProcess(sSentence,1);
	printf("%s\n", prepare_output(sResult));
	ICTCLAS_AddUserWord("С���� yym");//���С��������Ϊ��Ա����
	sResult = ICTCLAS_ParagraphProcess(sSentence,1);
	printf("%s\n", prepare_output(sResult));
	ICTCLAS_AddUserWord("���� yym");//������ݣ���Ϊ��Ա����
	sResult = ICTCLAS_ParagraphProcess(sSentence,1);
	printf("%s\n", prepare_output(sResult));
	ICTCLAS_AddUserWord("��ǹ�İ����� dym");//�����ǹ�İ����棬��Ϊ��Ӱ����
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
                printf("%s\n", p);
	}
	
	//�����û��ʵ�ǰ
	printf(prepare_output("δ�����û��ʵ䣺\n"));
	sResult = ICTCLAS_ParagraphProcess(sInput, 0);
	printf("%s\n", prepare_output(sResult));

	//�����û��ʵ��
	printf(prepare_output("\n�����û��ʵ��\n"));
	nCount = ICTCLAS_ImportUserDict("userdic.txt");//userdic.txt������ǰ���û��ʵ�
	//�����û��ʵ�
	ICTCLAS_SaveTheUsrDic();
	printf(prepare_output("����%d���û��ʡ�\n"), nCount);
	
	sResult = ICTCLAS_ParagraphProcess(sInput, 1);
	printf("%s\n", prepare_output(sResult));

	//��̬����û���
	printf(prepare_output("\n��̬����û��ʺ�\n"));
	ICTCLAS_AddUserWord("�����ѧԺ   xueyuan");
	ICTCLAS_SaveTheUsrDic();
	sResult = ICTCLAS_ParagraphProcess(sInput, 1);
	printf("%s\n", prepare_output(sResult));


	//���ļ����зִ�
	ICTCLAS_FileProcess("testGBK.txt","testGBK_result.txt",1);


	//�ͷŷִ������Դ
	ICTCLAS_Exit();
}

void SplitBIG5()
{
	//��ʼ���ִ����
	if(!ICTCLAS_Init("",BIG5_CODE))//�����ڵ�ǰ·���£�����ΪBIG5����ķִ�
	{
		printf("ICTCLAS INIT FAILED!\n");
		return ;
	}
	ICTCLAS_FileProcess("testBIG.txt","testBIG_result.txt");
	ICTCLAS_Exit();
}
void SplitUTF8()
{
	//��ʼ���ִ����
	if(!ICTCLAS_Init("",UTF8_CODE))//�����ڵ�ǰ·���£�����ΪUTF8����ķִ�
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

	const char *sInput = "�Ż�ƽ2009��׵��뱱������ѧ�����ѧԺ��";
	//�ִ�
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

