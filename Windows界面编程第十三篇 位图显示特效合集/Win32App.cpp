// Win32App.cpp : Defines the entry point for the application.
//


/*
	Windows界面编程之位图显示特效
	By MoreWindows
	博客：http://blog.csdn.net/MoreWindows
	微博：http://weibo.com/MoreWindows
	-----------------------------------------------------------
	    Windows界面编程之位图显示特效系列目录：
	1. 《Windows界面编程第九篇 位图显示特效 交错效果》
	http://blog.csdn.net/morewindows/article/details/8696720
	2. 《Windows界面编程第十篇 位图显示特效 百叶窗效果》
	http://blog.csdn.net/morewindows/article/details/8696722
	3. 《Windows界面编程第十一篇 位图显示特效 随机积木效果》
	http://blog.csdn.net/morewindows/article/details/8696724
	4. 《Windows界面编程第十二篇 位图显示特效 飞入效果与伸展效果》
	http://blog.csdn.net/morewindows/article/details/8696726
	5. 《Windows界面编程第十三篇 位图显示特效合集》
	http://blog.csdn.net/morewindows/article/details/8696730
*/

#include <windows.h>
#include <time.h>
#include "resource.h"
#include <shellapi.h> 
#pragma comment(lib, "shell32.lib")   

const char szAppName[] = "Win32App_MoreWindows";
const char szWindowTitleName[] = "《位图显示特效 交错 百叶窗 随机积木 飞入与伸展》- By MoreWindows";

BOOL InitApplication(HINSTANCE hinstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG     msg;
	
	if (!InitApplication(hInstance, nCmdShow))
	{
		return 0;
	}
	
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
	return 0;
}



BOOL InitApplication(HINSTANCE hinstance, int nCmdShow)
{
	HWND      hwnd;
	WNDCLASS  wndclass;
	
	
	wndclass.style       = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra  = 0;
	wndclass.cbWndExtra  = 0;
	wndclass.hInstance   = 0;
	wndclass.hIcon       = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor     = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndclass.lpszMenuName  = NULL;
	wndclass.lpszClassName = szAppName;
	
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, "Program Need Windows NT!", szAppName, MB_ICONERROR);
		return FALSE;
	}
	
	hwnd = CreateWindow(szAppName, 
		szWindowTitleName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		900,
		600,
		NULL, 
		LoadMenu(hinstance, MAKEINTRESOURCE(IDR_MENU1)),
		hinstance,
		NULL);
	
	if (hwnd == NULL)
		return FALSE;
	
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	
	return TRUE;
}

// 交错 - 水平
//《Windows界面编程第九篇 位图显示特效 交错效果》
//http://blog.csdn.net/morewindows/article/details/8696720
void AnimateDraw_StaggeredHorizontal(HDC hdc, HDC hdcMem, int nWidth, int nHeight, UINT nIntervalTime = 10)
{
	int i, j;
	for (i = 0;i <= nHeight; i += 2) 
	{
		for (j = i; j > 0; j -= 2)
		{
			// 奇数行 从上往下
			BitBlt(hdc, 0, j - 1, nWidth, 1, hdcMem, 0, nHeight - (i - j - 1), SRCCOPY);
			// 偶数行 从下往上
			BitBlt(hdc, 0, nHeight - j, nWidth, 1, hdcMem,	0, i - j, SRCCOPY); 
		} 
		Sleep(nIntervalTime); 
	}
	BitBlt(hdc, 0, 0, nWidth, nHeight, hdcMem, 0, 0, SRCCOPY);
}

// 交错 - 垂直
//《Windows界面编程第九篇 位图显示特效 交错效果》
//http://blog.csdn.net/morewindows/article/details/8696720
void AnimateDraw_StaggeredVertical(HDC hdc, HDC hdcMem, int nWidth, int nHeight, UINT nIntervalTime = 10)
{
	int i, j;
	for (i = 0; i <= nWidth; i += 2) 
	{
		for (j = i; j > 0; j -= 2)
		{
			// 奇数列 从左往右
			BitBlt(hdc, j - 1, 0, 1, nHeight, hdcMem, nWidth - (i - j - 1), 0, SRCCOPY);
			// 偶数行 从右往左
			BitBlt(hdc, nWidth - j, 0, 1, nHeight, hdcMem, i - j, 0, SRCCOPY); 
		} 
		Sleep(nIntervalTime); 
	}
	BitBlt(hdc, 0, 0, nWidth, nHeight, hdcMem, 0, 0, SRCCOPY);
}

//百叶窗效果 - 水平
//《Windows界面编程第十篇 位图显示特效 百叶窗效果》
//http://blog.csdn.net/morewindows/article/details/8696722
void AnimateDraw_JalousieHorizontal(HDC hdc, HDC hdcMem, int nWidth, int nHeight, UINT nIntervalTime = 15, UINT nJalousieNum = 10)
{
	int nJalousieHeight;
	nJalousieHeight = nHeight / nJalousieNum; //每个窗子的高度
	int i, j;
	for (i = 0; i <= nJalousieHeight; i++) 
	{
		for(j = 0; j < nJalousieNum; j++) //每个窗子
		{
			BitBlt(hdc, 0, j * nJalousieHeight, nWidth, i, hdcMem, 0, j * nJalousieHeight, SRCCOPY);
		}
		Sleep(nIntervalTime);
	}
	BitBlt(hdc, 0, 0, nWidth, nHeight, hdcMem, 0, 0, SRCCOPY);
}

//百叶窗效果 - 垂直
//《Windows界面编程第十篇 位图显示特效 百叶窗效果》
//http://blog.csdn.net/morewindows/article/details/8696722
void AnimateDraw_JalousieVertical(HDC hdc, HDC hdcMem, int nWidth, int nHeight, UINT nIntervalTime = 15, UINT nJalousieNum = 10)
{
	int nStep;
	nStep = nWidth / nJalousieNum;//每个窗子的高度
	int i, j;
	for (i = 0; i <= nStep; i++ ) 
	{
		for(j = 0;j < nJalousieNum; j++)//每个窗子
		{
			BitBlt(hdc, j * nStep, 0, i, nHeight,hdcMem, j * nStep, 0, SRCCOPY);
		}
		Sleep(nIntervalTime);
	}
	BitBlt(hdc, 0, 0, nWidth, nHeight, hdcMem, 0, 0, SRCCOPY);
}

// 随机积木
//《Windows界面编程第十一篇 位图显示特效 随机积木效果》
//http://blog.csdn.net/morewindows/article/details/8696724
void AnimateDraw_RandomBlocks(HDC hdc, HDC hdcMem, int nWidth, int nHeight, UINT nIntervalTime = 15,
							  int nRowBlocks = 10, int nColBlocks = 10)
{
	int nStepRow, nStepCol, nDisplayCount;
	int nSumBlocks = nRowBlocks * nColBlocks;
	bool *pFlagArray = new bool[nSumBlocks];
	memset(pFlagArray, 0, sizeof(bool) * nSumBlocks);

	nStepRow = nWidth / nRowBlocks;
	nStepCol = nHeight / nColBlocks;
	srand((unsigned)time(NULL));
	nDisplayCount = 0; //已显示方格个数
	while (true) 
	{ 
		int row = rand() % nRowBlocks; 
		int col = rand() % nColBlocks; 
		if (pFlagArray[row * nColBlocks + col]) 
			continue;
		pFlagArray[row * nColBlocks + col] = true;

		BitBlt(hdc, row * nStepRow, col * nStepCol, nStepRow, nStepCol, 
			hdcMem, row * nStepRow, col * nStepCol, SRCCOPY);
		nDisplayCount++;
		if (nDisplayCount >= nSumBlocks)
			break;
		Sleep(nIntervalTime); 
	}
	BitBlt(hdc, 0, 0, nWidth, nHeight, hdcMem, 0, 0, SRCCOPY);
}

// 飞入与伸展 - 从上往下
//《Windows界面编程第十二篇 位图显示特效 飞入效果与伸展效果》
//http://blog.csdn.net/morewindows/article/details/8696726
void AnimateDraw_FlyingTopToBottom(HDC hdc, HDC hdcMem, int nWidth, int nHeight, UINT nIntervalTime = 2, BOOL bFade = TRUE)
{
	int j;
	if (bFade)
	{
		for (j = 0; j <= nHeight; j++)
		{
			BitBlt(hdc, 0, 0, nWidth, j, hdcMem, 0, 0, SRCCOPY); 
			Sleep(nIntervalTime);
		}
	}
	else
	{
		for (j = 0; j <= nHeight; j++)
		{
			BitBlt(hdc, 0, 0, nWidth, j, hdcMem, 0, nHeight - j, SRCCOPY); 
			Sleep(nIntervalTime);
		}
	}
	BitBlt(hdc, 0, 0, nWidth, nHeight, hdcMem, 0, 0, SRCCOPY);
}

// 飞入与伸展 - 从下往上
//《Windows界面编程第十二篇 位图显示特效 飞入效果与伸展效果》
//http://blog.csdn.net/morewindows/article/details/8696726
void AnimateDraw_FlyingBottomToTop(HDC hdc, HDC hdcMem, int nWidth, int nHeight, UINT nIntervalTime = 2, BOOL bFade = TRUE)
{
	int j;
	if (bFade)
	{
		for (j = nHeight; j >= 0; j--)
		{
			BitBlt(hdc, 0, j, nWidth, nHeight - j, hdcMem, 0, j, SRCCOPY); 
			Sleep(nIntervalTime);
		}
	}
	else
	{
		for (j = nHeight; j >= 0; j--)
		{
			BitBlt(hdc, 0, j, nWidth, nHeight - j, hdcMem, 0, 0, SRCCOPY); 
			Sleep(nIntervalTime);
		}
	}
	BitBlt(hdc, 0, 0, nWidth, nHeight, hdcMem, 0, 0, SRCCOPY);
}

// 飞入与伸展 - 从左往右
//《Windows界面编程第十二篇 位图显示特效 飞入效果与伸展效果》
//http://blog.csdn.net/morewindows/article/details/8696726
void AnimateDraw_FlyingLeftToRight(HDC hdc, HDC hdcMem, int nWidth, int nHeight, UINT nIntervalTime = 2, BOOL bFade = TRUE)
{
	int i;
	if (bFade)
	{
		for (i = 0; i <= nWidth; i++)
		{
			BitBlt(hdc, 0, 0, i, nHeight, hdcMem, 0, 0, SRCCOPY); 
			Sleep(nIntervalTime);
		}
	}
	else
	{
		for (i = 0; i <= nWidth; i++)
		{
			BitBlt(hdc, 0, 0, i, nHeight, hdcMem, nWidth - i, 0, SRCCOPY); 
			Sleep(nIntervalTime);
		}
	}
	BitBlt(hdc, 0, 0, nWidth, nHeight, hdcMem, 0, 0, SRCCOPY);
}

// 飞入与伸展 - 从右往左
//《Windows界面编程第十二篇 位图显示特效 飞入效果与伸展效果》
//http://blog.csdn.net/morewindows/article/details/8696726
void AnimateDraw_FlyingRightToLeft(HDC hdc, HDC hdcMem, int nWidth, int nHeight, UINT nIntervalTime = 2, BOOL bFade = TRUE)
{
	int i;
	if (bFade)
	{
		for (i = nWidth; i >= 0; i--)
		{
			BitBlt(hdc, i, 0, nWidth - i, nHeight, hdcMem, i, 0, SRCCOPY); 
			Sleep(nIntervalTime);
		}
	}
	else
	{
		for (i = nWidth; i >= 0; i--)
		{
			BitBlt(hdc, i, 0, nWidth - i, nHeight, hdcMem, 0, 0, SRCCOPY); 
			Sleep(nIntervalTime);
		}
	}
	BitBlt(hdc, 0, 0, nWidth, nHeight, hdcMem, 0, 0, SRCCOPY);
}



LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int   s_nShow;
	static HDC   s_hdcMem;
	static int   s_nWidth, s_nHeight;

	switch (message)
	{
	case WM_CREATE:
		{
			DragAcceptFiles(hwnd, TRUE);   
			// 加载位图
			HBITMAP hBitmap;  
			hBitmap = (HBITMAP)LoadImage(NULL, "107.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);  
			if (hBitmap == NULL)  
			{  
				MessageBox(hwnd, "LoadImage failed", "Error", MB_ICONERROR);  
				exit(0);  
			}
			// 位图HDC
			HDC hdc = GetDC(hwnd);
			s_hdcMem = CreateCompatibleDC(hdc);
			SelectObject(s_hdcMem, hBitmap);
			ReleaseDC(hwnd, hdc);

			// 计算位图宽高
			BITMAP bm;
			GetObject(hBitmap, sizeof(bm), &bm);
			s_nWidth = bm.bmWidth;
			s_nHeight = bm.bmHeight;
			

			s_nShow = 0;
		}
		return 0;


    case WM_KEYDOWN:   
        switch (wParam)  
        {  
        case VK_ESCAPE: //按下Esc键时退出   
            SendMessage(hwnd, WM_DESTROY, 0, 0);  
            return 0;  
        }  
        break; 

	case WM_PAINT:
		{
			HDC             hdc;  
			PAINTSTRUCT     ps;  
			hdc = BeginPaint(hwnd, &ps);
			switch (s_nShow)
			{
			case 0:
				BitBlt(hdc, 0, 0, s_nWidth, s_nHeight, s_hdcMem, 0, 0, SRCCOPY);
				break;
			
				// 水平交错
			case 1:
				AnimateDraw_StaggeredHorizontal(hdc, s_hdcMem, s_nWidth, s_nHeight);
				break;
				// 垂直交错
			case 2:
				AnimateDraw_StaggeredVertical(hdc, s_hdcMem, s_nWidth, s_nHeight);
				break;
				
				// 水平百叶窗
			case 3:
				AnimateDraw_JalousieHorizontal(hdc, s_hdcMem, s_nWidth, s_nHeight);
				break;
				// 垂直百叶窗
			case 4:
				AnimateDraw_JalousieVertical(hdc, s_hdcMem, s_nWidth, s_nHeight);
				break;
				
				// 随机积木
			case 5:
				AnimateDraw_RandomBlocks(hdc, s_hdcMem, s_nWidth, s_nHeight);
				break;
				
				// 飞入 从上往下
			case 6:
				AnimateDraw_FlyingTopToBottom(hdc, s_hdcMem, s_nWidth, s_nHeight, 2, FALSE);
				break;
				// 飞入 从下往上
			case 7:
				AnimateDraw_FlyingBottomToTop(hdc, s_hdcMem, s_nWidth, s_nHeight, 2, FALSE);
				break;
				// 飞入 从左往右		
			case 8:
				AnimateDraw_FlyingLeftToRight(hdc, s_hdcMem, s_nWidth, s_nHeight, 2, FALSE);
				break;
				// 飞入 从右往左
			case 9:
				AnimateDraw_FlyingRightToLeft(hdc, s_hdcMem, s_nWidth, s_nHeight, 2, FALSE);
				break;

				// 伸展 从上往下
			case 10:
				AnimateDraw_FlyingTopToBottom(hdc, s_hdcMem, s_nWidth, s_nHeight);
				break;
				// 伸展 从下往上
			case 11:
				AnimateDraw_FlyingBottomToTop(hdc, s_hdcMem, s_nWidth, s_nHeight);
				break;
				// 伸展 从左往右		
			case 12:
				AnimateDraw_FlyingLeftToRight(hdc, s_hdcMem, s_nWidth, s_nHeight);
				break;
				// 伸展 从右往左
			case 13:
				AnimateDraw_FlyingRightToLeft(hdc, s_hdcMem, s_nWidth, s_nHeight);
				break;
			}
			if (s_nShow != 0)
			{
				s_nShow = 0;
				InvalidateRect(hwnd, NULL, FALSE);
			}
			EndPaint(hwnd, &ps);
		}
		return 0;


	case WM_COMMAND:
		if (LOWORD(wParam) >= 40001 && LOWORD(wParam) <= 40013)
		{
			s_nShow = LOWORD(wParam) - 40000;
			InvalidateRect(hwnd, NULL, TRUE);
			return 0;
		}
		break;


		// 文件拖拽第三步 DragQueryFile and DragQueryFile
	case WM_DROPFILES:
		{
			HDROP hDrop = (HDROP)wParam;
			UINT nFileNum = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0); // 拖拽文件个数
			char strFileName[MAX_PATH];
			DragQueryFile(hDrop, 0, strFileName, MAX_PATH);//获得拖曳的文件名
			DragFinish(hDrop);      //释放hDrop

			DeleteDC(s_hdcMem);
			// 加载位图
			HBITMAP hBitmap;  
			hBitmap = (HBITMAP)LoadImage(NULL, strFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);  
			// 位图HDC
			HDC hdc = GetDC(hwnd);
			s_hdcMem = CreateCompatibleDC(hdc);
			SelectObject(s_hdcMem, hBitmap);
			ReleaseDC(hwnd, hdc);
			
			// 计算位图宽高
			BITMAP bm;
			GetObject(hBitmap, sizeof(bm), &bm);
			s_nWidth = bm.bmWidth;
			s_nHeight = bm.bmHeight;
			
			InvalidateRect(hwnd, NULL, TRUE);
		}
		return 0; 


	case WM_DESTROY:
		DeleteDC(s_hdcMem);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

