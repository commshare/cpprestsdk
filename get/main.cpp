//_CRT_SECURE_NO_WARNINGS //: error C4996:  'GetVersionExW': 被声明为已否决
// 1.Project Properties > Configuration Properties > C/C++ > General > SDL checks关掉
#include "windows_version.h"
//./app.manifest.xml
#include <iostream>
#include <stdio.h>
int testrtc_main()
{
    std::string ver = rtc::rtc_win::getosver();
    std::cout << ver << std::endl;
    getchar();
    return 0;
}
// https://github.com/uemuraj/tanzaku/blob/63ea6637d7a3ab987659a63f08e39f504c7a6c21/windows-load-proc/maincpp.cpp
#define _WIN32_WINNT _WIN32_WINNT_WIN8
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

//
// DLL 関数を動的に利用するためのヘルパ
//
template<class ReturnType, class... ArgumentTypes>
class ProcAddress
{
    typedef ReturnType(__stdcall* ADDRESS)(ArgumentTypes...);

    HMODULE m_module;
    ADDRESS m_address;

public:
    ProcAddress(LPCSTR lib, LPCSTR proc)
    {
        m_module = ::LoadLibraryA(lib);
        m_address = (ADDRESS)::GetProcAddress(m_module, proc);
    }

    // コピー禁止のため以下は delete と指定するが...
    ProcAddress(const ProcAddress& ref) = delete;
    ProcAddress& operator=(const ProcAddress&) = delete;

    // このコンストラクタは delete 指定できない、実際には使わなくてもコンパイルエラーとなってしまう
    ProcAddress(ProcAddress&& ref) { static_assert(false); }

    ~ProcAddress() { ::FreeLibrary(m_module); }

    operator bool() { return m_address != nullptr; }

    ReturnType operator()(ArgumentTypes... args) { return (*m_address)(args...); }
};

//
// DLL 関数を動的に利用するためのヘルパ
//
template<class ReturnType, class... ArgumentTypes>
ProcAddress<ReturnType, ArgumentTypes...> LoadProcAddress(LPCSTR lib, LPCSTR proc)
{
    return ProcAddress<ReturnType, ArgumentTypes...>(lib, proc);
}


int whatmain()
{
    auto RtlGetVersion = LoadProcAddress<LONG, OSVERSIONINFOEXW*>("ntdll", "RtlGetVersion");

    if (RtlGetVersion)
    {
        OSVERSIONINFOEXW info = {sizeof info};

        return RtlGetVersion(&info);
    }

    return 1;
}


#include "Environment.h"

std::string getwintime()
{
    SYSTEMTIME st = {0};
    GetLocalTime(&st); //获取当前时间 可精确到ms
    char buffer[80] = {0};
    int len = sprintf_s(buffer,
                        80,
                        "%d-%02d-%02d %02d:%02d:%02d.%03d\n",
                        st.wYear,
                        st.wMonth,
                        st.wDay,
                        st.wHour,
                        st.wMinute,
                        st.wSecond,
                        st.wMilliseconds);
    if (-1 == len)
    {
        return std::string();
    }
    return std::move(std::string(buffer));
}
int main()
{
    FoundationKit::Environment ev;
    std::string os = ev.GetOSVersion();
    auto name = ev.GetMachineName();
    std::cout << os << std::endl;
    std::cout << name << std::endl;
    std::cout << getwintime() << std::endl;
    
    getchar();
    return 0;
}
