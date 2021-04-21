//本程序是基于 VS2015 版本，X86 ！！！
//创建头文件DumpFile.h, 将下列代码放进文件中

#pragma once
#include <windows.h>
#include <Dbghelp.h>
#include <iostream>  
#include <vector>  
#include <tchar.h>
using namespace std;


#pragma comment(lib, "Dbghelp.lib")


namespace NSDumpFile
{
	void CreateDumpFile(LPCWSTR lpstrDumpFilePathName, EXCEPTION_POINTERS *pException)
	{
		// 创建Dump文件  
		HANDLE hDumpFile = CreateFile(((LPCWSTR)lpstrDumpFilePathName), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);


		// Dump信息  
		MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
		dumpInfo.ExceptionPointers = pException;
		dumpInfo.ThreadId = GetCurrentThreadId();
		dumpInfo.ClientPointers = TRUE;


		// 写入Dump文件内容  
		MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);


		CloseHandle(hDumpFile);
	}


	LPTOP_LEVEL_EXCEPTION_FILTER WINAPI MyDummySetUnhandledExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter)
	{
		return NULL;
	}


	BOOL PreventSetUnhandledExceptionFilter()
	{
		//Windows 本身的32位的动态链接库，确保自己有这个库
		HMODULE hKernel32 = LoadLibrary(_T("kernel32.dll"));
		if (hKernel32 == NULL)
			return FALSE;


		void *pOrgEntry = GetProcAddress(hKernel32, "SetUnhandledExceptionFilter");
		if (pOrgEntry == NULL)
			return FALSE;


		unsigned char newJump[100];
		DWORD dwOrgEntryAddr = (DWORD)pOrgEntry;
		dwOrgEntryAddr += 5; // add 5 for 5 op-codes for jmp far


		void *pNewFunc = &MyDummySetUnhandledExceptionFilter;
		DWORD dwNewEntryAddr = (DWORD)pNewFunc;
		DWORD dwRelativeAddr = dwNewEntryAddr - dwOrgEntryAddr;


		newJump[0] = 0xE9;  // JMP absolute
		memcpy(&newJump[1], &dwRelativeAddr, sizeof(pNewFunc));
		SIZE_T bytesWritten;
		BOOL bRet = WriteProcessMemory(GetCurrentProcess(), pOrgEntry, newJump, sizeof(pNewFunc) + 1, &bytesWritten);
		return bRet;
	}


	LONG WINAPI UnhandledExceptionFilterEx(struct _EXCEPTION_POINTERS *pException)
	{
		TCHAR szMbsFile[MAX_PATH] = { 0 };
		::GetModuleFileName(NULL, szMbsFile, MAX_PATH);
		TCHAR* pFind = _tcsrchr(szMbsFile, '\\');
		if (pFind)
		{
			*(pFind + 1) = 0;
			//这边是生成的DUMP文件的名称
			_tcscat_s(szMbsFile, _T("CrashDumpFile.dmp"));
			CreateDumpFile((LPCWSTR)szMbsFile, pException);
		}


		//这边提示的消息可根据自己的需求设计
		// TODO: MiniDumpWriteDump
		MessageBox(NULL, _T("***又双叒叕崩溃了，惊不惊喜？意不意外？***"), _T("错误"), MB_OK);
		//FatalAppExit(-1, _T("***又双叒叕崩溃了，惊不惊喜？意不意外？***"));
		return EXCEPTION_CONTINUE_SEARCH;
	}


	void RunCrashHandler()
	{
		SetUnhandledExceptionFilter(UnhandledExceptionFilterEx);
		PreventSetUnhandledExceptionFilter();
	}
};


#define DeclareDumpFile() NSDumpFile::RunCrashHandler();

