// HTTP_SIMPLE_SERVER.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "http_svr.h"
//#include <iostream>
//
// int main()
//{
//    std::cout << "Hello World!\n";
//}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧:
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
// https : // segmentfault.com/q/1010000002869889

namespace simple_svr
{


void sshandle_get(http_request message) { message.reply(status_codes::OK, U("Hello, World!")); };

void sshandle_post(http_request message) { message.reply(status_codes::NotFound); };

void sshandle_put(http_request message) { message.reply(status_codes::NotFound); };

void sshandle_delete(http_request message) { message.reply(status_codes::NotFound); };
} // namespace simple_svr

int main_simple_server(int argc, char** argv)
{
    uri_builder uri(U("http://localhost:8888"));
    http_listener listener(uri.to_uri());

    listener.support(methods::GET, simple_svr::sshandle_get);
    listener.support(methods::POST, simple_svr::sshandle_post);
    listener.support(methods::PUT, simple_svr::sshandle_put);
    listener.support(methods::DEL, simple_svr::sshandle_delete);

    try
    {
        listener.open().then([&listener]() { TRACE(L"\nstarting to listen\n"); }).wait();

        while (true)
            ;
    }
    catch (std::exception const& e)
    {
        std::wcout << e.what() << std::endl;
    }
    catch (...)
    {
        std::wcout << "Unknown exception" << std::endl;
    }

    return 0;
}

