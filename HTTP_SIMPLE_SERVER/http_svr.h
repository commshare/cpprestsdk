#pragma once


#if 0
#include "cpprest/asyncrt_utils.h"
#include "cpprest/http_client.h"
#include "cpprest/http_listener.h"
#include "cpprest/json.h"
#include "cpprest/uri.h"
using namespace web::http::experimental::listener;
using namespace web::http;
using namespace web;



#define TRACE(msg) std::wcout << msg
#define TRACE_ACTION(a, k, v) std::wcout << a << L" (" << k << L", " << v << L")\n"


#endif


#include <cpprest/http_listener.h>
#include <cpprest/json.h>
  // cpprest140_2_10.lib
  //#pragma comment(lib, "cpprest140_2_10")

using namespace web;
using namespace web::http;
/* https://ruby-china.org/topics/16982
去年，微软开源了代码为 Casablanca 的 C++ REST SDK，目的主要是为了让C++ 编程时更加方便的消费 RESTful
服务。但最近它新增了一项功能：New experimental features such as HTTP Listener
library，正是这项功能的出现，我认为它会成为一个比较具有潜力的项目，简单的说，利用
Casablanca，可以搭建起一个原生代码与云计算服务之间的双向桥梁，轻轻松松的把那些用C、C++、Delphi 甚至是 VB
写的单机程序转变成 Web 服务，让单机时代的优秀创意在云计算时代重新闪亮！
*/
using namespace web::http::experimental::listener;

#include <iostream>
#include <map>
#include <set>
#include <string>
//using namespace std;


#define TRACE(msg) std::wcout << msg
#define TRACE_ACTION(a, k, v) std::wcout << a << L" (" << k << L", " << v << L")\n"


int main_simple_server(int argc, char** argv);
int full_svr_main(int argc, char** argv);