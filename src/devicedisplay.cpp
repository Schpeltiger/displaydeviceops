#include <iostream>
#include <sstream>
#include <nan.h>

NAN_METHOD(getNumOfDisplays)
{
    info.GetReturnValue().Set(GetSystemMetrics(SM_CMONITORS));
}

NAN_METHOD(monitorWake)
{
    // Monitor wake - hack by moving mouse
    //SendMessage(thisWindow, WM_SYSCOMMAND, SC_MONITORPOWER, -1); apparently does not work in Win8 and above

    mouse_event(MOUSEEVENTF_MOVE, 100, 100, 0, 0);
}

NAN_METHOD(monitorSleep)
{
    SendMessage(GetConsoleWindow(), WM_SYSCOMMAND, SC_MONITORPOWER, 2);
}

NAN_METHOD(getLastInputTime)
{
    LASTINPUTINFO last_input;
    last_input.cbSize = sizeof(LASTINPUTINFO);
    GetLastInputInfo(&last_input);

    SYSTEMTIME st;
    GetSystemTime(&st);

    FILETIME ft;
    SystemTimeToFileTime(&st, &ft);

    ULARGE_INTEGER uli_time;

    uli_time.LowPart = ft.dwLowDateTime;
    uli_time.HighPart = ft.dwHighDateTime;

    uli_time.QuadPart -= (GetTickCount() - last_input.dwTime);

    ft.dwLowDateTime = uli_time.LowPart;
    ft.dwHighDateTime = uli_time.HighPart;

    FileTimeToSystemTime(&ft, &st);

    std::stringstream ss;
    ss << st.wMonth << "-" << st.wDay << "-" << st.wYear << " " << st.wHour << ":" << st.wMinute << ":" << st.wSecond;
 
    info.GetReturnValue().Set(Nan::New<v8::String>(ss.str()).ToLocalChecked());
}

NAN_METHOD(checkActiveDisplayState)
{
    DISPLAY_DEVICE ddAdapter;
    ddAdapter.cb = sizeof(DISPLAY_DEVICE);

    BOOL pfOn = FALSE;

    for (DWORD dwAdapterNum = 0; EnumDisplayDevices(NULL, dwAdapterNum, &ddAdapter, 0); dwAdapterNum++)
    {
        if ((ddAdapter.StateFlags & (DISPLAY_DEVICE_ATTACHED_TO_DESKTOP | DISPLAY_DEVICE_MIRRORING_DRIVER)) == DISPLAY_DEVICE_ATTACHED_TO_DESKTOP)
        {
            DISPLAY_DEVICE ddMonitor;
            ddMonitor.cb = sizeof(DISPLAY_DEVICE);
            for (DWORD dwMonitorNum = 0; EnumDisplayDevices(ddAdapter.DeviceName, dwMonitorNum, &ddMonitor, EDD_GET_DEVICE_INTERFACE_NAME); dwMonitorNum++)
            {
                if (ddMonitor.StateFlags & DISPLAY_DEVICE_ACTIVE)
                {
                    HANDLE hMonitor = CreateFile(ddMonitor.DeviceID, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
                    GetDevicePowerState(hMonitor, &pfOn);
                    CloseHandle(hMonitor);
                }
            }
        }
    }
    info.GetReturnValue().Set((int)pfOn);
}
 
NAN_MODULE_INIT(init)
{
    Nan::SetMethod(target, "getNumOfDisplays", getNumOfDisplays);
    Nan::SetMethod(target, "monitorWake", monitorWake);
    Nan::SetMethod(target, "monitorSleep", monitorSleep);
    Nan::SetMethod(target, "getLastInputTime", getLastInputTime);
    Nan::SetMethod(target, "checkActiveDisplayState", checkActiveDisplayState);
}
 
NODE_MODULE(devicedisplayops, init)