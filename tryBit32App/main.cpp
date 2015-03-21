//
//  main.cpp
//  tryBit32App
//
//  Created by liyoudi on 15/3/19.
//  Copyright (c) 2015年 liyoudi. All rights reserved.
//

//#include <iostream>
//
//#include <unistd.h>
#include <string>

#define NULL 0

extern "C" unsigned int sleep(unsigned int) ;
extern "C" int printf(const char *, ...);
extern "C" void	 exit(int);

class FakeThreadItem;
class FakeThreadResumeParam;

typedef unsigned int FtRspType;

FakeThreadItem * try_GetItemPtr(FtRspType llMainRsp)
{
    FakeThreadItem *pTmp = 0;
    pTmp = (FakeThreadItem *) llMainRsp;
    return pTmp;
}

// ==============
extern "C" FakeThreadItem * FakeThread_StartWithRsp(FtRspType llNewRsp, void (*pfunc) (), FakeThreadItem *pItem, FtRspType *pSaveMainRsp );
extern "C" FakeThreadResumeParam * FakeThread_YieldWithMainRsp(FtRspType llMainRsp, FtRspType *pThreadRsp);
extern "C" FakeThreadItem * FakeThread_GetItemPtr(FtRspType llMainRsp);
extern "C" void FakeThread_ResumeWithThreadRsp(FtRspType llThreadRsp, FtRspType *pSaveMainRsp, FakeThreadItem *pItem, FakeThreadResumeParam *pResumeParam);
// ==============

extern "C" FtRspType FakeThread_GetRSP();

// ==============
FtRspType llMainRsp = 123212321;
FtRspType gFtRsp = 0;

#define gnStackSize 20
int *pnIntStack = new int[gnStackSize];

typedef FakeThreadItem * (*fnStartWithRsp)(FtRspType llNewRsp, void (*pfunc) (), FakeThreadItem *pItem, FtRspType *pSaveMainRsp );

void PrintStack(int *pStack, int nSize)
{
    int nIndex = 0;
    for (; nIndex < nSize; ++nIndex)
    {
        printf("0x%x\n", pStack[nIndex]);
    }
    printf("\n");
}
static void  SomeFunc()
{
    std::string someStr;
    someStr = "oooooo";
    PrintStack((int *) llMainRsp - 20, 20);
    printf("this is in %s\n", __FUNCTION__);
    FakeThreadItem *pItem = NULL;
    pItem = FakeThread_GetItemPtr(llMainRsp);
    printf("this is in %s, pItem is %p\n", __FUNCTION__, pItem);
    
    FakeThreadResumeParam *pTmpParam = NULL;
    
    pTmpParam = FakeThread_YieldWithMainRsp(llMainRsp, &gFtRsp);
    
    printf("pTmpParam = %p\n", pTmpParam);
    std::string someTmpStr = "ok";

    pTmpParam = FakeThread_YieldWithMainRsp(llMainRsp, &gFtRsp);
    printf("pTmpParam = %p\n", pTmpParam);
    someTmpStr = "ok";

    FakeThread_YieldWithMainRsp(llMainRsp, &gFtRsp);
}
static void FuncWithoutYield()
{
    printf("%s\n", __FUNCTION__);
}
// ==============

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("sizeof(void *) = %ld\n", sizeof((void *) argv));
    printf("sizeof(long long) = %ld\n", sizeof(long long));
    printf("sizeof(long) = %ld\n", sizeof(long));
    //
    int nIndex = 0;
    for (nIndex = 0; nIndex < gnStackSize; nIndex++)
    {
        pnIntStack[nIndex] = 0x11111100 + nIndex;
    }
    
    FakeThreadItem *pItem = NULL;
    for(nIndex = 0;nIndex < gnStackSize;++nIndex)
    {
        pItem = FakeThread_GetItemPtr((FtRspType) (pnIntStack + nIndex));
        printf("pItem = %p\n", pItem);
    }
    
    fnStartWithRsp fn = FakeThread_StartWithRsp;

    fn((FtRspType) (pnIntStack + gnStackSize - 4), FuncWithoutYield, (FakeThreadItem *) 0x12568901, &llMainRsp);

    fn((FtRspType) (pnIntStack + gnStackSize - 4), SomeFunc, (FakeThreadItem *) 0x12568901, &llMainRsp);
    
    FakeThread_ResumeWithThreadRsp(gFtRsp, &llMainRsp, NULL, (FakeThreadResumeParam *) 0x234231);
    std::string someTmpStr = "ok";
    FakeThread_ResumeWithThreadRsp(gFtRsp, &llMainRsp, NULL, (FakeThreadResumeParam *) 0x111111);
    std::string someTmpStr2 = "ok";
    return 0;
}
