/*
 * Author(Ecks)
 * Project(FullscreenCursorLockEcks)
 * File(Win32Main.c)
 * Date(2 Jul 2024 - 9:05:07 pm)
 *
 * TODO(Ecks):
 *  - Less power-draw?
 *  - Perhaps a way to stop software that repeatedly un-clips the cursor?
 */
#if __WIN32__
#ifdef _MSC_VER
int _fltused=0;
#endif

#if __GNUC__
extern void ___chkstk_ms(void);
inline void ___chkstk_ms(void) {return;}
#else
extern void __chkstk(void);
inline void __chkstk(void) {return;}
#endif

#include <windows.h>
#include "libStdEcks/StdTypeEcks.h"

inline internal b32
win32RectEquals(RECT a, RECT b) {
  return ((a.left == b.left) &&
          (a.top == b.top) &&
          (a.right == b.right) &&
          (a.bottom == b.bottom));
}

internal void
win32ToggleCursorLockIfFullscreen(HWND hwnd) {
  DWORD wndStyle = GetWindowLongA(hwnd, GWL_STYLE);
  MONITORINFO monitorInfo = {}; monitorInfo.cbSize = sizeof(monitorInfo);
  GetMonitorInfo(MonitorFromWindow(hwnd, MONITOR_DEFAULTTOPRIMARY), &monitorInfo);
  RECT wndRect; GetClientRect(hwnd, &wndRect);
  
  if(win32RectEquals(wndRect, monitorInfo.rcMonitor) && !(wndStyle & WS_OVERLAPPEDWINDOW)) {
    ClipCursor(&monitorInfo.rcMonitor);
  }else {
    ClipCursor(0);
  }
  
  return;
}

internal void CALLBACK
hwndEventCallback(HWINEVENTHOOK eventHook,
                  DWORD event,
                  HWND hwnd,
                  LONG idObject,
                  LONG idChild,
                  DWORD eventThread,
                  DWORD eventTime) {
  switch(event) {
    case EVENT_OBJECT_LOCATIONCHANGE: {
      HWND focusedHwnd = GetForegroundWindow();
      if(focusedHwnd == hwnd) {
        win32ToggleCursorLockIfFullscreen(focusedHwnd);
      }
    }break;
    case EVENT_SYSTEM_FOREGROUND: {
      if(hwnd) {
        win32ToggleCursorLockIfFullscreen(hwnd);
      }
    }break;
  }
  return;
}

internal LRESULT CALLBACK
win32Callback(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  LRESULT result = false;
  switch(msg) {
    case WM_DESTROY:
    case WM_CLOSE: {
      PostQuitMessage(0);
    }break;
    
    default: {
      result = DefWindowProcA(hwnd, msg, wParam, lParam);
    }break;
  }
  
  return result;
}

b32
win32Start(void) {
  HINSTANCE inst; GetModuleHandleExA(0, 0, &inst);
  
  CreateMutexA(0, 1, "Global\\FullscreenCursorLockEcksMutex");
  if((GetLastError() != ERROR_ALREADY_EXISTS) &&
     SetWinEventHook(EVENT_SYSTEM_FOREGROUND,
                     EVENT_OBJECT_LOCATIONCHANGE,
                     0, hwndEventCallback,
                     0, 0, WINEVENT_OUTOFCONTEXT|WINEVENT_SKIPOWNPROCESS)) {
    HWND hwnd;
    WNDCLASSA wndcl = {
      0, win32Callback,
      0, 0, inst,
      0, 0, 0, 0, "FullscreenCursorLockEcksClass"
    };
    
    if(RegisterClassA(&wndcl) && (hwnd = CreateWindowExA(0,
                                                         wndcl.lpszClassName,
                                                         "FullscreenCursorLockEcks",
                                                         WS_OVERLAPPEDWINDOW,
                                                         CW_USEDEFAULT, CW_USEDEFAULT,
                                                         960, 540,
                                                         0, 0, inst, 0))) {
#if 0
      // TODO(Ecks): Implement shell icon to close from the taskbar?
      // NOTE(Ecks): 982bac74-97cc-4bf8-b610-03fcfccda70e
      GUID taskbarIconGUID = {0x982bac74, 0x97cc, 0x4bf8, {0xb6, 0x10, 0x03, 0xfc, 0xfc, 0xcd, 0xa7, 0x0e}};
      NOTIFYICONDATA taskbarIconData = {};
      taskbarIconData.cbSize = sizeof(taskbarIconData);
      taskbarIconData.hWnd = hwnd;
      taskbarIconData.guidItem = taskbarIconGUID;
      strCpy(taskbarIconData.szTip,
             strLen(FULLSCREEN_LOCK_ECKS_DEFAULT_TB_ICON_TIP),
             FULLSCREEN_LOCK_ECKS_DEFAULT_TB_ICON_TIP);
      
      taskbarIconData.uFlags = NIF_GUID|NIF_TIP;
      Shell_NotifyIconA(NIM_ADD, &taskbarIconData);
#endif
      MSG msg;
      while(GetMessageA(&msg, 0, WM_DESTROY, WM_CLOSE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    }
  }
  
  ClipCursor(0);
  ExitProcess(0);
  return 0;
}

#endif
