// get.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//https://social.msdn.microsoft.com/Forums/windows/en-US/6f22c643-7a33-4581-9fbb-5462c1602f8b/windows-10-getversionex?forum=windowssdk
#include <iostream>

//通过peb方式获得系统版本信息
#include <stdio.h>
#include <winternl.h>

#include <Windows.h>

#if 0

DWORD Major;
DWORD Minor;
DWORD Build;

typedef NTSTATUS(WINAPI* _NtQueryInformationProcess)(_In_ HANDLE ProcessHandle,
                                                     _In_ PROCESSINFOCLASS ProcessInformationClass,
                                                     _Out_ PVOID ProcessInformation,
                                                     _In_ ULONG ProcessInformationLength,
                                                     _Out_opt_ PULONG ReturnLength);
_NtQueryInformationProcess NtQueryInformationProcess_;

DWORD GetProcessPEBAddress(HANDLE hProc)
{
    PROCESS_BASIC_INFORMATION peb;
    DWORD tmp;
    NtQueryInformationProcess_ =
        (_NtQueryInformationProcess)GetProcAddress(GetModuleHandle("ntdll.dll"), "NtQueryInformationProcess");
    NtQueryInformationProcess_(hProc, ProcessBasicInformation, &peb, sizeof(PROCESS_BASIC_INFORMATION), &tmp);
    return (DWORD)peb.PebBaseAddress;
}

void OSVersion(HANDLE handle)
{
    DWORD pebAddress = GetProcessPEBAddress(handle);
    DWORD OSMajorVersionAddress = pebAddress + 0x0a4;
    DWORD OSMinorVersionAddress = pebAddress + 0x0a8;
    DWORD OSBuildNumberAddress = pebAddress + 0x0ac;
    ReadProcessMemory(handle, (void*)OSMajorVersionAddress, &Major, sizeof(Major), 0);
    ReadProcessMemory(handle, (void*)OSMinorVersionAddress, &Minor, sizeof(Minor), 0);
    ReadProcessMemory(handle, (void*)OSBuildNumberAddress, &Build, sizeof(Build), 0);
}

int main()
{
    HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId());
    OSVersion(handle);

    printf("OS version - %d.%d.%d", Major, Minor, Build);

    getchar();
    return 0;
}

//通过RtlGetVersion api获得系统信息

LONG(WINAPI* pfnRtlGetVersion)(RTL_OSVERSIONINFOEXW*);
(FARPROC&)pfnRtlGetVersion = GetProcAddress(GetModuleHandle(_T("ntdll.dll")), "RtlGetVersion");
if (pfnRtlGetVersion)
{
    RTL_OSVERSIONINFOEXW ver = {0};
    ver.dwOSVersionInfoSize = sizeof(ver);

    if (pfnRtlGetVersion(&ver) == 0)
    {
        // Success, read results in `ver`
    }
    else
    {
        // RtlGetVersion failed
    }
}
else
{
    // RtlGetVersion was not found...
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

#endif