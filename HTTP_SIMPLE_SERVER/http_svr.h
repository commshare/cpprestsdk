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
ȥ�꣬΢��Դ�˴���Ϊ Casablanca �� C++ REST SDK��Ŀ����Ҫ��Ϊ����C++ ���ʱ���ӷ�������� RESTful
���񡣵������������һ��ܣ�New experimental features such as HTTP Listener
library����������ܵĳ��֣�����Ϊ�����Ϊһ���ȽϾ���Ǳ������Ŀ���򵥵�˵������
Casablanca�����Դ��һ��ԭ���������Ƽ������֮���˫���������������ɵİ���Щ��C��C++��Delphi ������ VB
д�ĵ�������ת��� Web �����õ���ʱ�������㴴�����Ƽ���ʱ������������
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