#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam);

HHOOK hMouseHook;

void MouseHooking() {
    hMouseHook = SetWindowsHookExA(WH_MOUSE_LL, MouseHookProc, NULL, 0);
    if (hMouseHook == NULL) {
        MessageBox(NULL, L"Failed to install mouse hook!", L"Error", MB_ICONERROR);
    }
}

LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        MSLLHOOKSTRUCT* hMouseStruct = (MSLLHOOKSTRUCT*)lParam; //сравниваем события, чтобы задетектить mouseevent.
        if (hMouseStruct != NULL) {
            if (hMouseStruct->flags == 1) { //проверяем флаг move.
                printf("Detect! \n");
            }
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    AllocConsole(); 

    if (freopen("CONOUT$", "w", stdout) == nullptr) 
        MessageBox(NULL, L"Failed to redirect standard output!", L"Error", MB_OK);
    MouseHooking(); //хук мышки
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

   
    UnhookWindowsHookEx(hMouseHook);
    return static_cast<int>(msg.wParam);
}
