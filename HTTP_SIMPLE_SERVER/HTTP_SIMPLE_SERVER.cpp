// HTTP_SIMPLE_SERVER.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

//#include <iostream>
//
//int main()
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
//https : // segmentfault.com/q/1010000002869889


#include "cpprest/asyncrt_utils.h"
#include "cpprest/http_client.h"
#include "cpprest/http_listener.h"
#include "cpprest/json.h"
#include "cpprest/uri.h"
using namespace web::http::experimental::listener;
using namespace web::http;
using namespace web;

void handle_get(http_request message) { message.reply(status_codes::OK, U("Hello, World!")); };

void handle_post(http_request message) { message.reply(status_codes::NotFound); };

void handle_put(http_request message) { message.reply(status_codes::NotFound); };

void handle_delete(http_request message) { message.reply(status_codes::NotFound); };

#define TRACE(msg) std::wcout << msg
#define TRACE_ACTION(a, k, v) std::wcout << a << L" (" << k << L", " << v << L")\n"

int main(int argc, char** argv)
{
    uri_builder uri(U("http://localhost:8888"));
    http_listener listener(uri.to_uri());

    listener.support(methods::GET, handle_get);
    listener.support(methods::POST, handle_post);
    listener.support(methods::PUT, handle_put);
    listener.support(methods::DEL, handle_delete);

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
