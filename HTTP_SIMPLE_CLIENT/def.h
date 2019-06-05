#pragma once

#include "cpprest/filestream.h"
#include "cpprest/http_client.h"

using namespace utility;              // Common utilities like string conversions
using namespace web;                  // Common features like URIs.
using namespace web::http;            // Common HTTP functionality
using namespace web::http::client;    // HTTP client features
using namespace concurrency::streams; // Asynchronous streams


#include <cpprest/http_client.h>
#include <cpprest/json.h>
//#pragma comment(lib, "cpprest_2_10")
//
//using namespace web;
//using namespace web::http;
//using namespace web::http::client;
//
//#include <iostream>
//using namespace std;



int main_simple(int argc, char* argv[]);
int full_client_main();