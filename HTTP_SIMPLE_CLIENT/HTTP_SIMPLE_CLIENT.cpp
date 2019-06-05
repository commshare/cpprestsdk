// HTTP_SIMPLE_CLIENT.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "def.h"
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
//https://segmentfault.com/q/1010000002869889


//#if USE_SIMPLE_CLIENT
//int main(int argc, char* argv[])
//#else
int main_simple(int argc, char* argv[])
//#endif
{
    auto fileStream = std::make_shared<ostream>();
    // Open stream to output file.
    pplx::task<void> requestTask = fstream::open_ostream(U("results.html"))
                                       .then([=](ostream outFile) {
                                           *fileStream = outFile;
                                           // Create http_client to send the request.
                                           http_client client(U("http://www.bing.com/"));
                                           http_client localclient(U("http://localhost:8888"));
                                           printf("create client and send request  \n");
                                           return localclient.request(methods::GET);
                                       })
                                       .then([=](http_response response) {
                                           printf("Received response status code:%u\n", response.status_code());
                                           system("pause");
                                           return response.body().read_to_end(fileStream->streambuf());
                                       })
                                       .then([=](size_t) {
                                           printf("close file stream \n");
										 return fileStream->close(); });
    try
    {
        requestTask.wait();
    }
    catch (const std::exception& e)
    {
        printf("Error exception:%s\n", e.what());
        system("pause");
    }

    return 0;
}
