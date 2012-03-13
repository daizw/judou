/****************************************************************************
 *
 * Copyright (c) 2011
 *     Kevin Zhang
 *     All rights reserved.
 *
 * This file is the confidential and proprietary property of 
 * Kevin Zhang and the possession or use of this file requires 
 * a written license from the author.
 * Filename: 
 * Abstract:
 *          ICTCLAS2011.h: definition of the ICTCLAS2011
 * Author:   Kevin Zhang 
 *          (pipy_zhang@msn.com)
 * Date:     2010-12-09
 *
 * Notes:
 *                
 ****************************************************************************/
#if !defined(__ICTCLAS_2010_LIB_INCLUDED__)
#define __ICTCLAS_2010_LIB_INCLUDED__
#ifdef __cplusplus 
//extern "C" 
//{ 
#endif 


#ifdef OS_LINUX
	#define ICTCLAS_API 
#else
	#ifdef ICTCLAS_EXPORTS		
		#define ICTCLAS_API __declspec(dllexport)				
	#else
		#define ICTCLAS_API 
	#endif
#endif

#define POS_MAP_NUMBER 4 //add by qp 2008.11.25
#define ICT_POS_MAP_FIRST 1  //������һ����ע��
#define ICT_POS_MAP_SECOND 0 //������������ע��
#define  PKU_POS_MAP_SECOND 2 //���������ע��
#define PKU_POS_MAP_FIRST 3	//����һ����ע��
#define  POS_SIZE 8

struct result_t{
  int start; //start position,��������������еĿ�ʼλ��
  int length; //length,����ĳ���
  char  sPOS[POS_SIZE];//word type������IDֵ�����Կ��ٵĻ�ȡ���Ա�
  int	iPOS;

  int word_ID; //�����δ��¼�ʣ����0����-1

  int word_type; //add by qp 2008.10.29 �����û��ʵ�;1�����û��ʵ��еĴʣ�0�����û��ʵ��еĴ�

  int weight;//add by qp 2008.11.17 word weight
 };


#define ICTCLAS_STATUS_UNUSED 0
#define ICTCLAS_STATUS_USED 1

#define GBK_CODE 0
#define UTF8_CODE GBK_CODE+1
#define BIG5_CODE GBK_CODE+2

/*********************************************************************
 *
 *  Func Name  : Init
 *
 *  Description: Init ICTCLAS
 *              The function must be invoked before any operation listed as following
 *
 *  Parameters : const char * sInitDirPath=NULL
 *       sInitDirPath: Initial Directory Path, where file Configure.xml and Data directory stored.
 * the default value is NULL, it indicates the initial directory is current working directory path
 *
 *  Returns    : success or fail
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2002-8-6
 *********************************************************************/
#ifndef CODE_LIMIT
ICTCLAS_API bool ICTCLAS_Init(const char * sInitDirPath=0,int encode=GBK_CODE);
#else
ICTCLAS_API bool ICTCLAS_Init(const char * sInitDirPath=0,int encode=GBK_CODE,const char *sLicenseCodes=0);
#endif
/*********************************************************************
 *
 *  Func Name  : ICTCLAS_Exit
 *
 *  Description: Exist ICTCLAS and free related buffer
 *              Exit the program and free memory
 *The function must be invoked while you needn't any lexical anlysis
 *
 *  Parameters : None
 *
 *  Returns    : success or fail
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2002-8-6
 *********************************************************************/
ICTCLAS_API bool ICTCLAS_Exit();
/*********************************************************************
 *
 *  Func Name  : ImportUserDict
 *
 *  Description: Import User-defined dictionary
 *  Parameters : Text filename for user dictionary 
 *  Returns    : The  number of  lexical entry imported successfully
 *  Author     : Kevin Zhang
 *  History    : 
 *              1.create 2003-11-28
 *********************************************************************/
ICTCLAS_API unsigned int ICTCLAS_ImportUserDict(const char *sFilename);

/*********************************************************************
 *
 *  Func Name  : ParagraphProcessing
 *
 *  Description: Process a paragraph
 *    
 *
 *  Parameters : sParagraph: The source paragraph 
 *               sResult: The result
 *				 bPOStagged:Judge whether need POS tagging, 0 for no tag;default:1
 *  i.e.  �Ż�ƽ��1978��3��9�ճ����ڽ���ʡ�����ء�
 *        Result: ��/nr  ��ƽ/nr  ��/p  1978��/t  3��/t  9��/t  ������/v  ����ʡ/ns  ������/ns  ��/w   
 *  Returns    : the result buffer pointer 
 *
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2003-12-22
 *********************************************************************/
ICTCLAS_API const char * ICTCLAS_ParagraphProcess(const char *sParagraph,int bPOStagged=1);
/*********************************************************************
 *
 *  Func Name  : ParagraphProcessingA
 *
 *  Description: Process a paragraph
 *    
 *
 *  Parameters : sParagraph: The source paragraph 
 *               pResultCount: pointer to result vector size
 *  Returns    : the pointer of result vector, it is managed by system,user cannot alloc and free it 
 *  Author     :  
 *  History    : 
 *              1.create 2006-10-26
 *********************************************************************/
ICTCLAS_API const result_t * ICTCLAS_ParagraphProcessA(const char *sParagraph,int *pResultCount);
/*********************************************************************
 *
 *  Func Name  : ICTCLAS_GetParagraphProcessAWordCount
 *
 *  Description: Get ProcessAWordCount, API for C#
 *    
 *
 *  Parameters : sParagraph: The source paragraph 
 *               pResultCount: pointer to result vector size
 *  Returns    : the pointer of result vector, it is managed by system,user cannot alloc and free it 
 *  Author     :  
 *  History    : 
 *              1.create 2007-3-15
 *********************************************************************/
ICTCLAS_API int ICTCLAS_GetParagraphProcessAWordCount(const char *sParagraph);
/*********************************************************************
 *
 *  Func Name  : ICTCLAS_ParagraphProcessAW
 *
 *  Description: Process a paragraph, API for C#
 *    
 *
 *  Parameters : sParagraph: The source paragraph 
 *               pResultCount: pointer to result vector size
 *  Returns    : the pointer of result vector, it is managed by system,user cannot alloc and free it 
 *  Author     :  
 *  History    : 
 *              1.create 2007-3-15
 *********************************************************************/
ICTCLAS_API void ICTCLAS_ParagraphProcessAW(int nCount,result_t * result);

/*********************************************************************
 *
 *  Func Name  : ICTCLAS_FileProcess
 *
 *  Description: Process a text file
 *    
 *
 *  Parameters : sSourceFilename: The source file name  
 *               sResultFilename: The result file name 
 *				 bPOStagged:Judge whether need POS tagging, 0 for no tag;default:1
 *  i.e. FileProcess("E:\\Sample\\Corpus_NewPOS\\199802_Org.txt","E:\\Sample\\Corpus_NewPOS\\199802_Org_cla.txt");
 *  Returns    : success: 
 *               fail: 
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2005-11-22
 *********************************************************************/
ICTCLAS_API double ICTCLAS_FileProcess(const char *sSourceFilename,const char *sResultFilename,int bPOStagged=1);
/*********************************************************************
 *
 *  Func Name  : ICTCLAS_FileProcessEx
 *
 *  Description: Process a text file
 *               (string,frequency) sort by frequency
 *
 *  Parameters : sSourceFilename: The source file name  
 *               sResultFilename: The result file name 
 *  i.e. FileProcess("E:\\Sample\\Corpus_NewPOS\\199802_Org.txt","E:\\Sample\\Corpus_NewPOS\\199802_Org_cla.txt");
 *  Returns    : success: 
 *               fail: 
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2007-04-07
 *********************************************************************/
ICTCLAS_API double ICTCLAS_FileProcessEx(const char *sSourceFilename,const char *sResultFilename);
/*********************************************************************
*
*  Func Name  : ICTCLAS_GetUniProb
*
*  Description: Get Unigram Probability
*    
*
*  Parameters : sSourceFilename: The source file name  
*               sResultFilename: The result file name 
*  i.e. FileProcess("E:\\Sample\\Corpus_NewPOS\\199802_Org.txt","E:\\Sample\\Corpus_NewPOS\\199802_Org_cla.txt");
*  Returns    : success: 
*               fail: 
*  Author     : Kevin Zhang  
*  History    : 
*              1.create 2005-11-22
*********************************************************************/
ICTCLAS_API double ICTCLAS_GetUniProb(const char *sWord);
/*********************************************************************
*
*  Func Name  : ICTCLAS_IsWord
*
*  Description: Get Unigram Probability
*    
*
*  Parameters : sSourceFilename: The source file name  
*               sResultFilename: The result file name 
*  i.e. FileProcess("E:\\Sample\\Corpus_NewPOS\\199802_Org.txt","E:\\Sample\\Corpus_NewPOS\\199802_Org_cla.txt");
*  Returns    : success: 
*               fail: 
*  Author     : Kevin Zhang  
*  History    : 
*              1.create 2005-11-22
*********************************************************************/
ICTCLAS_API bool ICTCLAS_IsWord(const char *sWord);
/*********************************************************************
*
*  Func Name  : ICTCLAS_AddUserWord
*
*  Description: add a word to the user dictionary ,example:���	
*													 i3s	n
*
*  Parameters : sFilename: file name
*               
*  Returns    : 1,true ; 0,false
*
*  Author     :   
*  History    : 
*              1.create 11:10:2008
*********************************************************************/
ICTCLAS_API int ICTCLAS_AddUserWord(const char *sWord);//add by qp 2008.11.10



/*********************************************************************
*
*  Func Name  : Save
*
*  Description: Save dictionary to file
*
*  Parameters :
*               
*  Returns    : 1,true; 2,false
*
*  Author     :   
*  History    : 
*              1.create 11:10:2008
*********************************************************************/
ICTCLAS_API int ICTCLAS_SaveTheUsrDic();

/*********************************************************************
*
*  Func Name  : ICTCLAS_DelUsrWord
*
*  Description: delete a word from the  user dictionary
*
*  Parameters : 
*  Returns    : -1, the word not exist in the user dictionary; else, the handle of the word deleted
*
*  Author     :   
*  History    : 
*              1.create 11:10:2008
*********************************************************************/
ICTCLAS_API int ICTCLAS_DelUsrWord(const char *sWord);

/*********************************************************************
*
*  Func Name  : ICTCLAS_KeyWord
*
*  Description: Extract keyword from paragraph
*
*  Parameters : resultKey, the returned key word 
				nCountKey, the returned key num
*  Returns    : 0, failed; else, 1, successe
*
*  Author     :   
*  History    : 
*              1.create 11:10:2008
*********************************************************************/
ICTCLAS_API int ICTCLAS_KeyWord(result_t * resultKey, int &nCountKey);

/*********************************************************************
*
*  Func Name  : ICTCLAS_FingerPrint
*
*  Description: Extract a finger print from the paragraph
*
*  Parameters :
*  Returns    : 0, failed; else, the finger print of the content
*
*  Author     :   
*  History    : 
*              1.create 11:10:2008
*********************************************************************/
ICTCLAS_API unsigned long ICTCLAS_FingerPrint();

/*********************************************************************
*
*  Func Name  : ICTCLAS_SetPOSmap
*
*  Description: select which pos map will use
*
*  Parameters :nPOSmap, ICT_POS_MAP_FIRST  ������һ����ע��
						ICT_POS_MAP_SECOND  ������������ע��
						PKU_POS_MAP_SECOND   ���������ע��
						PKU_POS_MAP_FIRST 	  ����һ����ע��
*  Returns    : 0, failed; else, success
*
*  Author     :   
*  History    : 
*              1.create 11:10:2008
*********************************************************************/
ICTCLAS_API int ICTCLAS_SetPOSmap(int nPOSmap);


/*********************************************************************
*
*  class CICTCLAS
*   ������
*		   ICTCLAS �࣬ʹ��֮ǰ�������ICTCLAS_Init(),�˳��������ICTCLAS_Exit
*		   ��ʹ�ù����п���ʹ�ö��CICTCLAS��֧�ֶ��̷ִ߳ʴ���
*
*  History    : 
*              1.create 2005-11-10
*********************************************************************/
#ifdef OS_LINUX
class  CICTCLAS {
#else
class  __declspec(dllexport) CICTCLAS {
#endif
	public:
		CICTCLAS();
		~CICTCLAS();
		bool FileProcess(const char *sSourceFilename,const char *sResultFilename,int bPOStagged=1);
		//Process a file��������C�µ�ICTCLAS_FileProcess
		const char * ParagraphProcess(const char *sLine,int bPOStagged=1); 
		//Process a file��������C�µ�ICTCLAS_FileProcess
		/*********************************************************************
		 *
		 *  Func Name  : ParagraphProcessAW
		 *
		 *  Description: Process a paragraph, API for C#
		 *    
		 *
		 *  Parameters : sParagraph: The source paragraph 
		 *               pResultCount: pointer to result vector size
		 *  Returns    : the pointer of result vector, it is managed by system,user cannot alloc and free it 
		 *  Author     :  
		 *  History    : 
		 *              1.create 2007-3-15
		 *********************************************************************/
		void ParagraphProcessAW(int nCount,result_t * result);
		int GetParagraphProcessAWordCount(const char *sParagraph);
		int m_nStatus;//ʹ��״̬
	private:
		unsigned int m_nHandle;//�ó�Ա��Ϊ�����Handleֵ����ϵͳ�Զ����䣬�û������޸�
};
#ifdef __cplusplus 
//} 
#endif 
#endif//#define __ICTCLAS_LIB_INCLUDED__
