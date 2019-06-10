#pragma once

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <filesystem>
#include <windows.h>
#include "boost/filesystem.hpp" // includes all needed Boost.Filesystem declarations


class Path
{
public:
    Path() = default;

    explicit Path(const std::string& InFile)
    {
        char buf[1024];
        GetModuleFileNameA(NULL, buf, 1024);
        std::string ProgramPath(buf);

        std::replace(ProgramPath.begin(), ProgramPath.end(), '\\', '/');
        size_t pos = ProgramPath.find_last_of("/");
        ProgramPath = ProgramPath.substr(0, pos + 1);

        std::string assetPrefix;
#if ME_EDITOR
        assetPrefix = "../../";
#endif
        LocalPath = InFile;

        std::replace(LocalPath.begin(), LocalPath.end(), '\\', '/');

        size_t path = LocalPath.find(':');
        if (path != std::string::npos)
        {
            FullPath = LocalPath;
        }
        else
        {
            FullPath = ProgramPath + assetPrefix + LocalPath;
        }

        path = LocalPath.rfind("Assets");
        if (path != std::string::npos)
        {
            LocalPath = LocalPath.substr(path, LocalPath.size());
        }

#if ME_EDITOR
        if (!std::filesystem::exists(FullPath))
        {
            std::string tempPath = ProgramPath + assetPrefix + "Engine/" + LocalPath;
            if (std::filesystem::exists(tempPath))
            {
                FullPath = std::move(tempPath);
                assetPrefix = assetPrefix.append("Engine/");
            }
        }
#endif
       // if (std::filesystem::is_regular_file((FullPath)))
        if (boost::filesystem::is_regular_file(FullPath))
        {
            IsFile = true;
            pos = FullPath.find_last_of("/");
            Directory = FullPath.substr(0, pos + 1);
        }
        else
        {
            IsFolder = true;
            Directory = FullPath;
        }

#if ME_PLATFORM_UWP
        std::replace(LocalPath.begin(), LocalPath.end(), '/', '\\');
#endif
    }

    ~Path() {}
    bool IsFile = false;
    bool IsFolder = false;
    std::string FullPath;
    std::string LocalPath;
    std::string Directory;
};