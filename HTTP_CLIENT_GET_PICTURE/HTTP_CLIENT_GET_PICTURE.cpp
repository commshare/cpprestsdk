// HTTP_CLIENT_GET_PICTURE.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//https://www.cnblogs.com/highway-9/p/6021238.html

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
#include <cpprest/containerstream.h>
#include <cpprest/filestream.h>
#include <cpprest/http_client.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <regex>
#include <string>
#include <vector>

// 请求并解析url
bool get_result(const std::string& url, const std::string& pattern, std::vector<std::string>& vec)
{
    try
    {
	  //Converts to a platform dependent Unicode string type. 这是转unicode
        web::http::client::http_client client(web::uri(utility::conversions::to_string_t(url)));
		//获取服务端的应答
        web::http::http_response response = client.request(web::http::methods::GET).get();

        concurrency::streams::stringstreambuf buffer;
        response.body().read_to_end(buffer).get();
        std::string& str = buffer.collection();

        // 使用C++11提供的正则表达式库
        std::regex r(pattern);
        for (std::sregex_iterator iter(str.begin(), str.end(), r), end; iter != end; ++iter)
        {
            std::cout << iter->str() << std::endl;
            vec.emplace_back(iter->str());
        }
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
        return false;
    }

    return true;
}

// 获取图片
bool get_result(const std::string& url, std::string& picture)
{
    try
    {
        web::http::client::http_client client(web::uri(utility::conversions::to_string_t(url)));
        web::http::http_response response = client.request(web::http::methods::GET).get();

        concurrency::streams::stringstreambuf buffer;
        response.body().read_to_end(buffer).get();
        picture = buffer.collection();
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
        return false;
    }

    return true;
}

// 保存图片
bool write_to_file(const std::string& file_path, const std::string& data)
{
    try
    {
        std::ofstream file;
        file.open(file_path, std::ios::out | std::ios::binary);
        if (!file.good())
        {
            return false;
        }
        file.write(data.c_str(), data.size());
        file.close();
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
        return false;
    }

    return true;
}

int main()
{
    // [1] 请求每一页，将子页面的url保存在sub_url_vec里面
    std::vector<std::string> sub_url_vec;
    std::string pattern = "/desk/[0-9]+.htm";
    for (int i = 1; i <= 32; ++i)
    {
        // 创意主题
        std::string url = "http://www.51ztzj.com/dbizhi/category_27_" + std::to_string(i) + ".htm#content_anchor";
        std::cout << "Start get " << i << " page, url: " << url << std::endl;
        // 请求并解析url
        if (!get_result(url, pattern, sub_url_vec))
        {
            std::cout << "Get " << i << " page failed" << std::endl;
        }
    }

    // 最终的图片url：http://img.51ztzj.com//upload/image/20130220/2013022014_670x419.jpg
    // [2] 将子页面的图片url解析出来放入picture_url_vec
    std::vector<std::string> picture_url_vec;
    pattern = "http://img.51ztzj.com//upload/image/.+/.+_670x419.jpg";
    for (std::size_t i = 0; i < sub_url_vec.size(); ++i)
    {
        std::string url = "http://www.51ztzj.com" + sub_url_vec[i];
        std::cout << "Start get " << i + 1 << " sub page, url: " << url << std::endl;
        // 请求并解析url
        if (!get_result(url, pattern, picture_url_vec))
        {
            std::cout << "Get " << i + 1 << " sub page failed" << std::endl;
        }
    }

    // [3] 最后遍历picture_url_vec，然后一个一个的下载图片
    for (std::size_t i = 0; i < picture_url_vec.size(); ++i)
    {
        std::cout << "Start download " << i + 1 << " picture, url: " << picture_url_vec[i] << std::endl;
        std::string picture;
        // 获取图片
        if (!get_result(picture_url_vec[i], picture))
        {
            std::cout << "Download " << i + 1 << " picture failed" << std::endl;
        }

        std::string file_path = "./download/" + std::to_string(i) + ".jpg";
        // 保存图片
        if (!write_to_file(file_path, picture))
        {
            std::cout << "Write to file failed: " << i + 1 << std::endl;
        }
    }

    return 0;
}