// ATM_Simulator.cpp : Defines the entry point for the application.
//
#include "framework.h"
#include "ATM_Simulator.h"
#include<stdio.h>

#define MAX_LOADSTRING 100

#define IDB_INSERTCARD 54
#define IDB_DEPOSIT 55
#define IDB_TRANSFER 56
#define IDB_PINCHANGE 57
#define IDB_OTHERS 58
#define IDB_FASTCASH 59
#define IDB_CASHWITHDRAW 60
#define IDB_BALANCE 61
#define IDB_MiniTouchButton 62

int overBalance;
int depositAmount, withdrawAmount;
wchar_t BAL[50];
WCHAR PIN[5];
WCHAR loggedIn[5];
WCHAR tempPin_U1[5];
WCHAR tempPin_U2[5];
WCHAR tempPin_U3[5];
WCHAR tempPin_U4[5];

const int Buffer_Size = 5;
WCHAR DevanshPin[];
BOOL proceed = FALSE;
HWND hWnd;

HBITMAP hInsertCardImage;
HBITMAP hUserImage, hBackImage;

HWND hBack;
HWND hUserImageButton;
HWND UserName,Acc,Ty;
HWND InsertCardButton;
HWND hDisplayBal;
HWND hPin;


HWND hMoney;
//HWND hMiniDlg;

BOOL start = FALSE;
BOOL DEPOSIT = FALSE;
SYSTEMTIME str_t;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    InsertCard(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    DepositMoney(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    TransferMoney(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    NewPin(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Others(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    FastCash(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    CashWithdraw(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    BalanceInquiry(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK    MiniStatement(HWND, UINT, WPARAM, LPARAM);

//HWND MiniTouchButton;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPWSTR    lpCmdLine,_In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ATMSIMULATOR, szWindowClass, MAX_LOADSTRING);


    MyRegisterClass(hInstance);  // kanusha 

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ATMSIMULATOR));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0)>0)
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    //wParam and lParam
    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;
    
    wcex.cbSize         = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PESLOGO));
    wcex.hCursor        = LoadCursor(nullptr, IDC_HAND);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 9);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ATMSIMULATOR);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_PESLOGO));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable
                        
  hWnd = CreateWindowW(szWindowClass,szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
      CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

       hBackImage = (HBITMAP)LoadImageW(NULL, L"Images\\PES Building.bmp", IMAGE_BITMAP, 800, 600, LR_LOADFROMFILE);
       hBack = CreateWindowW(L"STATIC",NULL,WS_VISIBLE|WS_CHILD|SS_BITMAP,0,0,800,600,hWnd,NULL,NULL,NULL); 
       SendMessage(hBack,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hBackImage);

       hInsertCardImage = (HBITMAP)LoadImageW(NULL, L"Images\\insertCard.bmp", IMAGE_BITMAP, 190, 190, LR_LOADFROMFILE);

       InsertCardButton = CreateWindowW(L"BUTTON",L"",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_BITMAP,
           50,10,150,150,hWnd,(HMENU)IDB_INSERTCARD,(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),NULL);

       SendMessage(InsertCardButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hInsertCardImage);
  
   CreateWindowW(L"Static", L"Name : ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER ,535, 40, 60, 20, hWnd, NULL, NULL, NULL);
   CreateWindowW(L"Static", L"Account No. : ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,535, 70, 100, 20, hWnd, NULL, NULL, NULL);
   CreateWindowW(L"Static", L"Type : ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,535, 100, 60, 20, hWnd, NULL, NULL, NULL);
   

   HWND DepositTouchButton = CreateWindow(L"BUTTON",L"DEPOSIT",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,10,180,240,50,hWnd,(HMENU)IDB_DEPOSIT,(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),NULL);      
   HWND DepositButton = CreateWindow(L"BUTTON",L"O",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,10,10,30,30,DepositTouchButton,NULL,(HINSTANCE)GetWindowLong(DepositTouchButton, GWL_HINSTANCE),NULL);     
 
   HWND TransferTouchButton = CreateWindow(L"BUTTON",L"TRANSFER",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,10,280,240,50,hWnd,(HMENU)IDB_TRANSFER,(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),NULL);      
   HWND TransferButton = CreateWindow(L"BUTTON",L"O",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,10,10,30,30,TransferTouchButton,NULL,(HINSTANCE)GetWindowLong(TransferTouchButton, GWL_HINSTANCE),NULL);    

   HWND PinChangeTouchButton = CreateWindow(L"BUTTON",L"PIN CHANGE",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,10,380,240,50,hWnd,(HMENU)IDB_PINCHANGE,(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),NULL);      
   HWND PinChangeButton = CreateWindow(L"BUTTON",L"O",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,10,10,30,30,PinChangeTouchButton,NULL,(HINSTANCE)GetWindowLong(PinChangeTouchButton, GWL_HINSTANCE),NULL);      

   HWND OthersTouchButton = CreateWindow(L"BUTTON",L"LOGOUT",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,10,480,240,50,hWnd,(HMENU)IDB_OTHERS,(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),NULL);      
   HWND OthersButton = CreateWindow(L"BUTTON",L"O",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,10,10,30,30,OthersTouchButton,NULL,(HINSTANCE)GetWindowLong(OthersTouchButton, GWL_HINSTANCE),NULL);   
  
   HWND FastCashTouchButton = CreateWindow(L"BUTTON",L"FAST CASH  ",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,535,180,240,50,hWnd,(HMENU)IDB_FASTCASH,(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),NULL);      
   HWND FastCashButton = CreateWindow(L"BUTTON",L"O",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,195,10,30,30,FastCashTouchButton,NULL,(HINSTANCE)GetWindowLong(FastCashTouchButton, GWL_HINSTANCE),NULL);

   HWND CashWithdrawTouchButton = CreateWindow(L"BUTTON",L"CASH WITHDRAW",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,535,280,240,50,hWnd,(HMENU)IDB_CASHWITHDRAW,(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),NULL);      
   HWND CashWithdrawButton = CreateWindow(L"BUTTON",L"O",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,195,10,30,30,CashWithdrawTouchButton,NULL,(HINSTANCE)GetWindowLong(CashWithdrawTouchButton, GWL_HINSTANCE),NULL);

   HWND BalanceTouchButton = CreateWindow(L"BUTTON",L"BALANCE INQUIRY",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,535,380,240,50,hWnd,(HMENU)IDB_BALANCE,(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),NULL);   
   HWND BalanceButton = CreateWindow(L"BUTTON",L"O",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,195,10,30,30,BalanceTouchButton,NULL,(HINSTANCE)GetWindowLong(BalanceTouchButton, GWL_HINSTANCE),NULL);

   HWND MiniTouchButton = CreateWindow(L"BUTTON",L"MINI STATEMENT",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,535,480,240,50,hWnd,(HMENU)IDB_MiniTouchButton,(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),NULL);   
   HWND MiniButton = CreateWindow(L"BUTTON",L"O",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,195,10,30,30,MiniTouchButton,NULL,(HINSTANCE)GetWindowLong(MiniTouchButton, GWL_HINSTANCE),NULL);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}
//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {   
            int wmId = LOWORD(wParam);
            switch (wmId)
            {    
            case IDB_INSERTCARD:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_INSERTCARD), hWnd, InsertCard);
                break;

            case IDB_DEPOSIT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DEPOSIT), hWnd, DepositMoney);
                break;

            case IDB_TRANSFER:
                
                break;

            case IDB_PINCHANGE:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_NEWPIN), hWnd, NewPin);
                break;

            case IDB_OTHERS:
                if (start)
                {
                    DestroyWindow(hUserImageButton);
                    DestroyWindow(UserName);
                    DestroyWindow(Acc);
                    DestroyWindow(Ty);

                    start = FALSE;

                    hInsertCardImage = (HBITMAP)LoadImageW(NULL, L"Images\\insertCard.bmp", IMAGE_BITMAP, 190, 190, LR_LOADFROMFILE);
                    InsertCardButton = CreateWindowW(L"BUTTON",L"",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_BITMAP,50,10,150,150,hWnd,(HMENU)IDB_INSERTCARD,(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),NULL);
                    SendMessage(InsertCardButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hInsertCardImage);
                }
                else
                {
                    MessageBoxW(NULL, L"Please Log In First\nInsert Your Card", L"Attention !", MB_OK | MB_ICONERROR);
                }
                break;
            
            case IDB_FASTCASH:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_FASTCASH), hWnd, FastCash);
                break;

            case IDB_CASHWITHDRAW:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_WITHDRAWAL), hWnd, CashWithdraw);
                break;

            case IDB_BALANCE:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_BALANCE), hWnd, BalanceInquiry);
                break;

            case IDB_MiniTouchButton:
                //DialogBox(hInst, MAKEINTRESOURCE(IDD_MiniStatementDialog), hWnd, MiniStatement);
                break;

            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;

            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }            
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
/*INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        //MessageBoxW(hDlg, L"Hello", L"Title", MB_OK | MB_ICONEXCLAMATION);
        return (INT_PTR)TRUE;

    
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}*/
int n;

INT_PTR CALLBACK InsertCard(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:

        n = 5;
        CreateWindowW(L"Static", L"Enter PIN : ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,20, 70, 150, 20, hDlg, NULL, NULL, NULL);
        hPin = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, 180, 70, 40, 20,hDlg, NULL, NULL, NULL);

        return (INT_PTR)TRUE;

    case WM_COMMAND:
        
        WCHAR DevanshPin[]= L"Files\\Devansh Nigam\\PIN.txt";
        WCHAR SruthiPin[] = L"Files\\Sruthi M\\PIN.txt";
        WCHAR KanushaPin[] = L"Files\\Kanusha\\PIN.txt";
        WCHAR BossPin[] = L"Files\\Boss\\PIN.txt";
        const int Buffer_Size = 25;
        HANDLE hFileBalance = NULL;

        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDOK:

            int tempPin;
            
            GetWindowTextW(hPin, PIN, 5);
            //GetSystemTime(&str_t);
            
            HANDLE hFile;
            hFile = CreateFileW(DevanshPin,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

            char U1PIN[Buffer_Size];
            DWORD dwBytesRead;
            ReadFile(hFile,U1PIN, Buffer_Size, &dwBytesRead, NULL);
            tempPin=atoi(U1PIN); // most important
            swprintf_s(tempPin_U1, L"%d", tempPin);
            CloseHandle(hFile);


            hFile = CreateFileW(SruthiPin,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

            char U2PIN[Buffer_Size];
            dwBytesRead;
            ReadFile(hFile, U2PIN, Buffer_Size, &dwBytesRead, NULL);
            tempPin = atoi(U2PIN); // most important
            swprintf_s(tempPin_U2, L"%d", tempPin);
            CloseHandle(hFile);

            hFile = CreateFileW(KanushaPin,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

            char U3PIN[Buffer_Size];
            dwBytesRead;
            ReadFile(hFile, U3PIN, Buffer_Size, &dwBytesRead, NULL);
            tempPin = atoi(U3PIN); // most important
            swprintf_s(tempPin_U3, L"%d", tempPin);
            CloseHandle(hFile);


            hFile = CreateFileW(BossPin,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

            char U4PIN[Buffer_Size];
            dwBytesRead;
            ReadFile(hFile, U4PIN, Buffer_Size, &dwBytesRead, NULL);
            tempPin = atoi(U4PIN); // most important
            swprintf_s(tempPin_U4, L"%d", tempPin);
            CloseHandle(hFile);

            
            
            //char getBalance[20];
            //const int Buffer_Size = 25;

            if ((wcscmp(PIN,tempPin_U1) == 0))
            {
                UserName = CreateWindowW(L"Static", L"Devansh Nigam", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,600, 40, 150, 20, hWnd, NULL, NULL, NULL);

                Acc = CreateWindowW(L"Static", L"XXXXX68880", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,620, 70, 120, 20, hWnd, NULL, NULL, NULL);

                Ty = CreateWindowW(L"Static", L"SAVINGS", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,600, 100, 60, 20, hWnd, NULL, NULL, NULL);

                hUserImage = (HBITMAP)LoadImageW(NULL, L"Images\\DevanshNigam.bmp", IMAGE_BITMAP, 150,150,LR_LOADFROMFILE);
                hUserImageButton = CreateWindowW(L"BUTTON",L"",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_BITMAP,50,10,150,150,hWnd,NULL,(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),NULL);
                SendMessage(hUserImageButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hUserImage);

                WCHAR szFileName[] = L"Files\\Devansh Nigam\\Balance.txt";
                hFileBalance = CreateFileW(szFileName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
                wcscpy_s(loggedIn, PIN);
                start = TRUE;
                
                EndDialog(hDlg, LOWORD(wParam));
                DestroyWindow(InsertCardButton);

            }
            else if ((wcscmp(PIN, tempPin_U2) == 0))
            {
                /*overBalance = u8Balance;
                BAL[50];
                swprintf_s(BAL, L"%d", overBalance);*/

                UserName = CreateWindowW(L"Static", L"Sruthi M", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,600, 40, 150, 20, hWnd, NULL, NULL, NULL);

                Acc = CreateWindowW(L"Static", L"XXXXX59659", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,620, 70, 120, 20, hWnd, NULL, NULL, NULL);

                Ty = CreateWindowW(L"Static", L"SAVINGS", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,600, 100, 60, 20, hWnd, NULL, NULL, NULL);

                hUserImage = (HBITMAP)LoadImageW(NULL, L"Images\\sruthi.bmp", IMAGE_BITMAP, 150, 150,LR_LOADFROMFILE);
                hUserImageButton = CreateWindowW(L"BUTTON",L"",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_BITMAP,50,10,150,150,hWnd,NULL,(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),NULL);
                SendMessage(hUserImageButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hUserImage);

                WCHAR szFileName[] = L"Files\\Sruthi M\\Balance.txt";
                hFileBalance = CreateFileW(szFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                wcscpy_s(loggedIn, PIN);
                start = TRUE;
                

                EndDialog(hDlg, LOWORD(wParam));
                DestroyWindow(InsertCardButton);
            }
            else if ((wcscmp(PIN, tempPin_U3) == 0))
            {
                //overBalance = u7Balance;
                //BAL[50];
                //swprintf_s(BAL, L"%d", overBalance);
                UserName = CreateWindowW(L"Static", L"Kanusha R K", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,600, 40, 150, 20, hWnd, NULL, NULL, NULL);

                Acc = CreateWindowW(L"Static", L"XXXXX92724", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,620, 70, 120, 20, hWnd, NULL, NULL, NULL);

                Ty = CreateWindowW(L"Static", L"SAVINGS", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,600, 100, 60, 20, hWnd, NULL, NULL, NULL);

                hUserImage = (HBITMAP)LoadImageW(NULL, L"Images\\kanusha.bmp", IMAGE_BITMAP, 150, 150,LR_LOADFROMFILE);
                hUserImageButton = CreateWindowW(L"BUTTON",L"",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_BITMAP,50,10,150,150,hWnd,NULL,(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),NULL);
                SendMessage(hUserImageButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hUserImage);

                WCHAR szFileName[] = L"Files\\Kanusha\\Balance.txt";
                hFileBalance = CreateFileW(szFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                wcscpy_s(loggedIn, PIN);
                start = TRUE;
                

                EndDialog(hDlg, LOWORD(wParam));
                DestroyWindow(InsertCardButton);
            }
            else if ((wcscmp(PIN, tempPin_U4) == 0))
            {
                UserName = CreateWindowW(L"Static", L"Basanagouda", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,600, 40, 150, 20, hWnd, NULL, NULL, NULL);

                Acc = CreateWindowW(L"Static", L"XXXXX81960", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,620, 70, 120, 20, hWnd, NULL, NULL, NULL);

                Ty = CreateWindowW(L"Static", L"SAVINGS", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,600, 100, 60, 20, hWnd, NULL, NULL, NULL);

                hUserImage = (HBITMAP)LoadImageW(NULL, L"Images\\boss.bmp", IMAGE_BITMAP, 150, 150,LR_LOADFROMFILE);
                hUserImageButton = CreateWindowW(L"BUTTON",L"",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_BITMAP,50,10,150,150,hWnd,NULL,(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),NULL);
                SendMessage(hUserImageButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hUserImage);

                WCHAR szFileName[] = L"Files\\Boss\\Balance.txt";
                hFileBalance = CreateFileW(szFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                wcscpy_s(loggedIn, PIN);
                start = TRUE;
                

                EndDialog(hDlg, LOWORD(wParam));
                DestroyWindow(InsertCardButton);
            }
            else
            {                   
                int insertId = MessageBoxW(hDlg, L"Incorrect PIN !!", L"Attention !!", MB_ICONWARNING | MB_ABORTRETRYIGNORE);
                switch (insertId)
                {
                case IDABORT:
                case IDIGNORE:
                    EndDialog(hDlg, LOWORD(wParam));
                    ShowWindow(hWnd,1);
                    UpdateWindow(hWnd);

                    break;

                case IDRETRY:
                    SetWindowTextW(hPin, L"");
                    break;
                }
            }

            char szInBufferBal[Buffer_Size];
            dwBytesRead;
            ReadFile(hFileBalance, szInBufferBal, Buffer_Size, &dwBytesRead, NULL);
            overBalance = atoi(szInBufferBal); // most important
            CloseHandle(hFileBalance);



            break;

        case IDCANCEL2:
                n--;
                GetWindowTextW(hPin, PIN, n);
                SetWindowTextW(hPin, PIN);
            break;

        case IDCANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        }    
        break;
    }
    return (INT_PTR)FALSE;
}


INT_PTR CALLBACK DepositMoney(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        if (start)
        {
            CreateWindowW(L"Static", L"Enter Amount : ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,30, 70, 200, 20, hDlg, NULL, NULL, NULL);
            hMoney = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, 220, 70, 200, 20,hDlg, NULL, NULL, NULL);
        }
        else
        {
            MessageBoxW(NULL, L"Please Insert Your Card", L"Attention !", MB_OK | MB_ICONERROR);
            EndDialog(hDlg, LOWORD(wParam));
            ShowWindow(hWnd, 1);
            UpdateWindow(hWnd);
        }
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDOK:

            WCHAR Amount[50]; 
            wchar_t s[50];
            GetWindowTextW(hMoney, Amount, 50);
            for (int x = 0; x < wcslen(Amount); x++)
            {
                if (iswdigit(Amount[x]))
                {
                    // store peek as numeric
                    s[x] = Amount[x];
                    s[x+1] = '\0';
                    depositAmount = _wtoi(s);
                }
            }
            if (depositAmount > 0)
            {
                DEPOSIT = TRUE;
                /*DEPBAL[50];

                swprintf_s(DEPBAL, L"%d", depositAmount);*/
                
                overBalance += depositAmount;
                HANDLE hFile=NULL;
                if ((wcscmp(PIN,tempPin_U1) == 0))
                {
                    WCHAR szFileName[] = L"Files\\Devansh Nigam\\Balance.txt";
                    hFile = CreateFileW(szFileName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                }
                else if ((wcscmp(PIN, tempPin_U2) == 0))
                {
                    WCHAR szFileName[] = L"Files\\Sruthi M\\Balance.txt";
                    hFile = CreateFileW(szFileName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                }
                else if ((wcscmp(PIN, tempPin_U3) == 0))
                {
                    WCHAR szFileName[] = L"Files\\Kanusha\\Balance.txt";
                    hFile = CreateFileW(szFileName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                }   
                else if ((wcscmp(PIN,tempPin_U4) == 0))
                {
                    WCHAR szFileName[] = L"Files\\Boss\\Balance.txt";
                    hFile = CreateFileW(szFileName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                }
                
                const int Buffer_Size = 25;
                char szOutBuffer[Buffer_Size];
                DWORD dwBytesWritten;
                strncpy_s(szOutBuffer, "", Buffer_Size);
                WriteFile(hFile, "                  ", strlen(szOutBuffer), &dwBytesWritten, NULL);
                sprintf_s(szOutBuffer, "%d", overBalance);
                WriteFile(hFile, szOutBuffer, strlen(szOutBuffer), &dwBytesWritten, NULL);
                CloseHandle(hFile);

                /*BAL[50];

                swprintf_s(BAL, L"%d", overBalance);*/

                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
            }
            else
            {
                int msgId=MessageBoxW(NULL, L"Deposited Amount \ncannot be Zero(0)", L"Attention !", MB_OK | MB_ICONERROR);
                switch (msgId)
                {
                case IDOK:
                    SetWindowTextW(hMoney,L"");
                    break;
                }
                /*EndDialog(hDlg, LOWORD(wParam));
                ShowWindow(hWnd, 1);
                UpdateWindow(hWnd);*/
            }
            return (INT_PTR)TRUE;

        case IDCANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


INT_PTR CALLBACK CashWithdraw(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        if (start)
        {
            CreateWindowW(L"Static", L"Enter Amount : ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 30, 70, 200, 20, hDlg, NULL, NULL, NULL);
            hMoney = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, 220, 70, 200, 20, hDlg, NULL, NULL, NULL);
        }
        else
        {
            MessageBoxW(NULL, L"Please Insert Your Card", L"Attention !", MB_OK | MB_ICONERROR);
            EndDialog(hDlg, LOWORD(wParam));
            ShowWindow(hWnd, 1);
            UpdateWindow(hWnd);
        }
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDOK:

            WCHAR Amount[50];
            wchar_t s[50];
            GetWindowTextW(hMoney, Amount, 50);
            for (int x = 0; x < wcslen(Amount); x++)
            {
                if (iswdigit(Amount[x]))
                {
                    // store peek as numeric
                    s[x] = Amount[x];
                    s[x + 1] = '\0';
                    withdrawAmount = _wtoi(s);
                }
            }
            if (withdrawAmount > 0)
            {
                
                /*DEPBAL[50];

                swprintf_s(DEPBAL, L"%d", depositAmount);*/
                if (overBalance - withdrawAmount == 0)
                {
                    int msgId = MessageBoxW(NULL, L"Main Balance will \nbe Zero(0)", L"Attention !", MB_OK | MB_ICONERROR);
                    switch (msgId)
                    {
                    case IDOK:
                        withdrawAmount = 0;
                        break;
                    }

                }
                else if (overBalance - withdrawAmount < 0)
                {
                    int msgId = MessageBoxW(NULL, L"Main Balance cannot \nbe Negative", L"Attention !", MB_OK | MB_ICONERROR);
                    switch (msgId)
                    {
                    case IDOK:
                        withdrawAmount = 0;
                        break;
                    }
                }

                else
                {
                    overBalance -= withdrawAmount;
                    HANDLE hFile = NULL;
                    if ((wcscmp(PIN, tempPin_U1) == 0))
                    {


                        WCHAR szFileName[] = L"Files\\Devansh Nigam\\Balance.txt";
                        hFile = CreateFileW(szFileName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                    }
                    else if ((wcscmp(PIN, tempPin_U2) == 0))
                    {
                        //overBalance += depositAmount;

                        WCHAR szFileName[] = L"Files\\Sruthi M\\Balance.txt";
                        hFile = CreateFileW(szFileName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                    }
                    else if ((wcscmp(PIN, tempPin_U3) == 0))
                    {
                        /*u7Balance += depositAmount;
                        overBalance = u7Balance;*/
                        WCHAR szFileName[] = L"Files\\Kanusha\\Balance.txt";
                        hFile = CreateFileW(szFileName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                    }
                    else if ((wcscmp(PIN, tempPin_U4) == 0))
                    {
                        /*u6Balance += depositAmount;
                        overBalance = u6Balance;*/
                        WCHAR szFileName[] = L"Files\\Boss\\Balance.txt";
                        hFile = CreateFileW(szFileName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                    }

                    const int Buffer_Size = 25;
                    char szOutBuffer[Buffer_Size];
                    DWORD dwBytesWritten;
                    strncpy_s(szOutBuffer, "", Buffer_Size);
                    WriteFile(hFile, "                 ", strlen(szOutBuffer), &dwBytesWritten, NULL);
                    sprintf_s(szOutBuffer, "%d", overBalance);
                    WriteFile(hFile, szOutBuffer, strlen(szOutBuffer), &dwBytesWritten, NULL);
                    CloseHandle(hFile);

                    /*BAL[50];

                    swprintf_s(BAL, L"%d", overBalance);*/

                    EndDialog(hDlg, LOWORD(wParam));
                    return (INT_PTR)TRUE;
                }
            }
            else
            {
                int msgId = MessageBoxW(NULL, L"Withdrawal Amount \ncannot be Zero(0)", L"Attention !", MB_OK | MB_ICONERROR);
                switch (msgId)
                {
                case IDOK:
                    SetWindowTextW(hMoney, L"");
                    break;
                }
                /*EndDialog(hDlg, LOWORD(wParam));
                ShowWindow(hWnd, 1);
                UpdateWindow(hWnd);*/
            }
            return (INT_PTR)TRUE;

        case IDCANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK FastCash(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        if (start)
        {
            return (INT_PTR)TRUE;
        }
        else
        {
            MessageBoxW(NULL, L"Please Insert Your Card", L"Attention !", MB_OK | MB_ICONERROR);
            EndDialog(hDlg, LOWORD(wParam));
            ShowWindow(hWnd, 1);
            UpdateWindow(hWnd);
        }
        return (INT_PTR)TRUE;

    case WM_COMMAND:

        withdrawAmount = 0;
        int wmId = LOWORD(wParam);
        if (wmId == ID200)
        {
            withdrawAmount = 200;
        }
        if (wmId == ID500)
        {
            withdrawAmount = 500;
        }
        if (wmId == ID700)
        {
            withdrawAmount = 700;
        }
        if (wmId == ID1000)
        {
            withdrawAmount = 1000;
        }
        if (wmId == ID1200) 
        { 
            withdrawAmount = 1200;
        }
        if (wmId == ID1500)
        {
            withdrawAmount = 1500;
        }
        if (wmId == ID2000)
        {
            withdrawAmount = 2000;
        }
        if (wmId == ID2200)
        {
            withdrawAmount = 2200;
        }
        if (wmId == ID2500)
        {
            withdrawAmount = 2500;
        }
        if (wmId == IDCANCEL)
        {
           EndDialog(hDlg, LOWORD(wParam));
           return (INT_PTR)TRUE;
        }


        if (overBalance - withdrawAmount == 0)
        {
            int msgId = MessageBoxW(NULL, L"Main Balance will \nbe Zero(0)", L"Attention !", MB_OK | MB_ICONERROR);
            switch (msgId)
            {
            case IDOK:
                withdrawAmount = 0;
                break;
            }

        }
        else if (overBalance - withdrawAmount < 0)
        {
            int msgId = MessageBoxW(NULL, L"Main Balance cannot \nbe Negative", L"Attention !", MB_OK | MB_ICONERROR);
            switch (msgId)
            {
            case IDOK:
                withdrawAmount = 0;
                break;
            }
        }
        else
        {
            overBalance -= withdrawAmount;
            HANDLE hFile = NULL;
            if ((wcscmp(PIN, tempPin_U1) == 0))
            {
                WCHAR szFileName[] = L"Files\\Devansh Nigam\\Balance.txt";
                hFile = CreateFileW(szFileName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            }
            else if ((wcscmp(PIN, tempPin_U2) == 0))
            {
                //overBalance += depositAmount;

                WCHAR szFileName[] = L"Files\\Sruthi M\\Balance.txt";
                hFile = CreateFileW(szFileName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            }
            else if ((wcscmp(PIN, tempPin_U3) == 0))
            {
                /*u7Balance += depositAmount;
                overBalance = u7Balance;*/
                WCHAR szFileName[] = L"Files\\Kanusha\\Balance.txt";
                hFile = CreateFileW(szFileName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            }
            else if ((wcscmp(PIN, tempPin_U4) == 0))
            {
                /*u6Balance += depositAmount;
                overBalance = u6Balance;*/
                WCHAR szFileName[] = L"Files\\Boss\\Balance.txt";
                hFile = CreateFileW(szFileName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            }

            const int Buffer_Size = 25;
            char szOutBuffer[Buffer_Size]="  ";
            DWORD dwBytesWritten;
            strncpy_s(szOutBuffer, "                    ", Buffer_Size);
            WriteFile(hFile, szOutBuffer, strlen(szOutBuffer), &dwBytesWritten, NULL);
            sprintf_s(szOutBuffer, "%d", overBalance);
            
            WriteFile(hFile, szOutBuffer, strlen(szOutBuffer), &dwBytesWritten, NULL);
            CloseHandle(hFile);

            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }

        break;
    }
    return (INT_PTR)FALSE;
}


/*INT_PTR CALLBACK PinChange(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        if (start)
        {
         //   CreateWindowW(L"Static", L"Enter Current Pin : ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 30, 60, 200, 20, hDlg, NULL, NULL, NULL);
           // hCurrentPin = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, 220, 70, 200, 20, hDlg, NULL, NULL, NULL);

            CreateWindowW(L"Static", L"Enter New Pin : ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 30, 100, 200, 20, hDlg, NULL, NULL, NULL);
            hNewPin1 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, 220, 100, 200, 20, hDlg, NULL, NULL, NULL);

//            CreateWindowW(L"Static", L"Re-Enter New Pin : ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 30,120, 200, 20, hDlg, NULL, NULL, NULL);
 //           hNewPin2 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, 220, 120, 200, 20, hDlg, NULL, NULL, NULL);
        }
        else
        {
            MessageBoxW(NULL, L"Please Insert Your Card", L"Attention !", MB_OK | MB_ICONERROR);
            EndDialog(hDlg, LOWORD(wParam));
            ShowWindow(hWnd, 1);
            UpdateWindow(hWnd);
        }
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDOK:
            GetWindowTextW(hCurrentPin, PIN, 5);
            GetWindowTextW(hNewPin1, NewPin1, 5);
            GetWindowTextW(hNewPin2, NewPin2, 5);
            res = wcscmp(NewPin1, NewPin2);
            if (res == 0)
            {
                if (wcscmp(NewPin1, PIN) == 0)
                {
                    int insertId = MessageBoxW(hDlg, L"Current Pin and New Pint\nCannot Be Same !!", L"Attention !!", MB_ICONINFORMATION | MB_ABORTRETRYIGNORE);
                    switch (insertId)
                    {
                    case IDABORT:
                    case IDIGNORE:
                        EndDialog(hDlg, LOWORD(wParam));
                        ShowWindow(hWnd, 1);
                        UpdateWindow(hWnd);

                        break;

                    case IDRETRY:
                        SetWindowTextW(hCurrentPin, L"");
                        SetWindowTextW(hNewPin1, L"");
                        SetWindowTextW(hNewPin2, L"");
                        break;
                }
                if ((wcscmp(PIN, tempPin_U1) == 0))
                {
                    WCHAR szFileName[] = L"Files\\Devansh Nigam\\PIN.txt";
                    hFile = CreateFileW(szFileName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                }
                else if ((wcscmp(PIN, tempPin_U2) == 0))
                {
                    WCHAR szFileName[] = L"Files\\Sruthi M\\PIN.txt";
                    hFile = CreateFileW(szFileName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                }
                else if ((wcscmp(PIN, tempPin_U3) == 0))
                {
                    WCHAR szFileName[] = L"Files\\Kanusha\\PIN.txt";
                    hFile = CreateFileW(szFileName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                }
                else if ((wcscmp(PIN, tempPin_U4) == 0))
                {
                    WCHAR szFileName[] = L"Files\\Boss\\PIN.txt";
                    hFile = CreateFileW(szFileName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                }


                char szOutBuffer[Buffer_PIN];
                DWORD dwBytesWritten;
                strncpy_s(szOutBuffer, "", Buffer_PIN);
                WriteFile(hFile, "                  ", strlen(szOutBuffer), &dwBytesWritten, NULL);
                sprintf_s(szOutBuffer, "%d", hNewPin1);
                WriteFile(hFile, szOutBuffer, strlen(szOutBuffer), &dwBytesWritten, NULL);
                CloseHandle(hFile);

                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
                break;
            }
        case IDCANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        }
        break;
    }
    return (INT_PTR)FALSE;
}*/



int p = 65;
/*INT_PTR CALLBACK MiniStatement(HWND hMiniDlg,UINT message,WPARAM wParam,LPARAM lParam)
{    
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        if (start)
        {
            CreateWindowW(L"STATIC", L"[LAST 05 TRANSACTIONS]", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,40, 40, 200, 20, hMiniDlg, NULL, NULL, NULL);

            if (DEPOSIT)
            {
                //\n03 April 2020 13:43 hrs"

                CreateWindowW(L"STATIC", L""/*DEPBAL*///, WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,40, p, 200, 40, hMiniDlg, NULL, NULL, NULL);
               // p = p + 45;
            //}
            /*CreateWindowW(L"STATIC", L"Deposited : Rs. 13400\n03 April 2020 13:43 hrs", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,
                40, 65, 200, 40, hMiniDlg, NULL, NULL, NULL);
            CreateWindowW(L"STATIC", L"Withdrawal : Rs. 15020\n01 April 2020 9:31 hrs", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,
                40, 110, 200, 40, hMiniDlg, NULL, NULL, NULL);
            CreateWindowW(L"STATIC", L"Withdrawal : Rs. 19560\n31 March 2020 21:12 hrs", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,
                40, 155, 200, 40, hMiniDlg, NULL, NULL, NULL);
            CreateWindowW(L"STATIC", L"Deposited : Rs. 18530\n28 March 2020 11:08 hrs", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,
                40, 200, 200, 40, hMiniDlg, NULL, NULL, NULL);
            CreateWindowW(L"STATIC", L"Balance Is : Rs. 9030\n23 March 2020 20:11 hrs", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,
                40, 245, 200, 40, hMiniDlg, NULL, NULL, NULL);*/
        /*}
        else
        {
            MessageBoxW(NULL, L"Please Insert Your Card", L"Attention !", MB_OK | MB_ICONERROR);
            EndDialog(hMiniDlg, LOWORD(wParam));
            ShowWindow(hWnd, 1);
            UpdateWindow(hWnd);
        }
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {                       
            EndDialog(hMiniDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}*/

INT_PTR CALLBACK BalanceInquiry(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        if (start)
        {
            CreateWindowW(L"Static", L"Current Balance", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,150, 80, 170, 20, hDlg, NULL, NULL, NULL);

            HANDLE hDisplayBal=NULL;

            if ((wcscmp(PIN, tempPin_U1) == 0))
            {
                WCHAR szFileName[] = L"Files\\Devansh Nigam\\Balance.txt";
                hDisplayBal = CreateFileW(szFileName, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            }
            else if ((wcscmp(PIN, tempPin_U2) == 0))
            {
                WCHAR szFileName[] = L"Files\\Sruthi M\\Balance.txt";
                hDisplayBal = CreateFileW(szFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            }
            else if ((wcscmp(PIN, tempPin_U3) == 0))
            {
                WCHAR szFileName[] = L"Files\\Kanusha\\Balance.txt";
                hDisplayBal = CreateFileW(szFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            }
            else if ((wcscmp(PIN, tempPin_U4) == 0))
            {
                WCHAR szFileName[] = L"Files\\Boss\\Balance.txt";
                hDisplayBal = CreateFileW(szFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            }
            
            const int Buffer_Size = 25;
            char szInBuffer[Buffer_Size];
            DWORD dwBytesRead;
            DWORD dwBytesWritten;       
            WriteFile(hDisplayBal, L"", strlen(""), &dwBytesWritten, NULL);
            ReadFile(hDisplayBal,szInBuffer, Buffer_Size, &dwBytesRead, NULL);
            int booo = atoi(szInBuffer);
            wcscpy_s(BAL, L"");
            //strncpy_s(BAL, "", 50);
            swprintf_s(BAL, L"%d", booo);
            CloseHandle(hDisplayBal);
            CreateWindowW(L"Static",BAL, WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,130, 110, 200, 70, hDlg, NULL, NULL, NULL);
        }
        else
        {
            MessageBoxW(NULL, L"Please Insert Your Card", L"Attention !", MB_OK | MB_ICONERROR);
            EndDialog(hDlg, LOWORD(wParam));
            ShowWindow(hWnd, 1);
            UpdateWindow(hWnd);
        }
        return (INT_PTR)TRUE;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


HWND hCurrentPin = NULL, hNewPin1 = NULL, hNewPin2 = NULL; HANDLE hFile = NULL;
WCHAR NewPin1[5]=L"23", NewPin2[5]=L"23";    int res =-2,res1=-1,res2=-2;
HANDLE hPINFILE = NULL;
int wmId = -1;

INT_PTR CALLBACK NewPin(HWND hDlgPin, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        if (start)
        {
            CreateWindowW(L"STATIC", L"Enter Your Current Pin : ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 22, 30, 160, 20, hDlgPin, NULL, NULL, NULL);
            hCurrentPin= CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER|ES_NUMBER, 181, 30, 40, 20, hDlgPin, NULL, NULL, NULL);

            CreateWindowW(L"STATIC", L"Enter Your New Pin : ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 22, 60, 160, 20, hDlgPin, NULL, NULL, NULL);
            hNewPin1 = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER | ES_NUMBER, 181, 60, 40, 20, hDlgPin, NULL, NULL, NULL);

            CreateWindowW(L"STATIC", L"Re-Enter New Pin : ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 22, 90, 160, 20, hDlgPin, NULL, NULL, NULL);
            hNewPin2 = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER | ES_NUMBER, 181, 90, 40, 20, hDlgPin, NULL, NULL, NULL);
        }
        else
        {
            MessageBoxW(NULL, L"Please Enter Pin First\nBy Inserting Your Card !", L"Attention !", MB_OK | MB_ICONERROR);
            EndDialog(hDlgPin, LOWORD(wParam));
            ShowWindow(hWnd, 1);
            UpdateWindow(hWnd);
        }
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDOK:
            GetWindowTextW(hNewPin1, NewPin1, 5);
            GetWindowTextW(hNewPin2, NewPin2, 5);
            res = wcscmp(NewPin1, NewPin2);
            res1 = wcscmp(PIN, NewPin1);
            res2 = wcscmp(PIN, NewPin2);   
            if ((wcscmp(loggedIn, tempPin_U1) == 0))
            {
                WCHAR szFileName[] = L"Files\\Devansh Nigam\\PIN.txt";
                hPINFILE = CreateFileW(szFileName, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            }
            else if ((wcscmp(loggedIn, tempPin_U2) == 0))
            {
                WCHAR szFileName[] = L"Files\\Sruthi M\\PIN.txt"; 
                hPINFILE = CreateFileW(szFileName, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            }
            else if ((wcscmp(loggedIn, tempPin_U3) == 0))
            {
                WCHAR szFileName[] = L"Files\\Kanusha\\PIN.txt"; 
                hPINFILE = CreateFileW(szFileName, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            }
            else if ((wcscmp(loggedIn, tempPin_U4) == 0))
            {
                
                WCHAR szFileName[] = L"Files\\Boss\\PIN.txt";
                hPINFILE = CreateFileW(szFileName, GENERIC_WRITE|GENERIC_READ, FILE_SHARE_WRITE|FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            }
            
            }
            DWORD dwBytesWritten;
                if (res1== 0 || res2 == 0)
                {
                    int insertId = MessageBoxW(hDlgPin, L"Current Pin and New Pint\nCannot Be Same !!", L"Attention !!", MB_ICONINFORMATION | MB_ABORTRETRYIGNORE);
                    switch (insertId)
                    {
                    case IDABORT:
                    case IDIGNORE:
                        EndDialog(hDlgPin, LOWORD(wParam));
                        ShowWindow(hWnd, 1);
                        UpdateWindow(hWnd);

                        break;

                    case IDRETRY:
                        SetWindowTextW(hCurrentPin, L"");
                        SetWindowTextW(hNewPin1, L"");
                        SetWindowTextW(hNewPin2, L"");
                        break;
                    }
                }
                else if (res == 0 && res1!=0 && res2!=0)
                {
                    wchar_t s[50];
                    int NEWPIN;
                    for (int x = 0; x < wcslen(NewPin1); x++)
                    {
                        if (iswdigit(NewPin1[x]))
                        {
                            // store peek as numeric
                            s[x] = NewPin1[x];
                            s[x + 1] = '\0';
                            NEWPIN = _wtoi(s);
                        }
                    }
                    const int Buffer_Size = 15;
                    char szOutBuffer[Buffer_Size];
                    DWORD dwBytesWritten;
                    strncpy_s(szOutBuffer, "", Buffer_Size);
                    WriteFile(hPINFILE, "                  ", strlen(szOutBuffer), &dwBytesWritten, NULL);
                    sprintf_s(szOutBuffer, "%d",NEWPIN);
                    WriteFile(hPINFILE, szOutBuffer, strlen(szOutBuffer), &dwBytesWritten, NULL);
                    CloseHandle(hPINFILE);
                    EndDialog(hDlgPin, LOWORD(wParam));
                    ShowWindow(hWnd, 1);
                    UpdateWindow(hWnd);

                }
                else if (res==-1)
                {
                    int insertId = MessageBoxW(hDlgPin, L"New Pins \nDoes Not Match!!", L"Attention !!", MB_ICONINFORMATION | MB_ABORTRETRYIGNORE);
                    switch (insertId)
                    {
                    case IDABORT:
                    case IDIGNORE:
                        EndDialog(hDlgPin, LOWORD(wParam));
                        ShowWindow(hWnd, 1);
                        UpdateWindow(hWnd);

                        break;

                    case IDRETRY:
                        SetWindowTextW(hCurrentPin, L"");
                        SetWindowTextW(hNewPin1, L"");
                        SetWindowTextW(hNewPin2, L"");
                        break;
                    }

                    
                }
                //return (INT_PTR)TRUE;
               
                break;

        case IDCANCEL:
            EndDialog(hDlgPin, LOWORD(wParam));
            ShowWindow(hWnd, 1);
            UpdateWindow(hWnd);

            break;
        }
        return (INT_PTR)FALSE;
    }

