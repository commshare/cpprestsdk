#include "client_https.hpp"
#include <iostream>

using namespace std;

typedef SimpleWeb::Client<SimpleWeb::HTTPS> HttpsClient;

int simple_https_client()
{
  try
  {
      HttpsClient client("github.com",false);


      auto r1 = client.request("GET", "/");
      cout << r1->content.rdbuf() << endl;
  }
  catch //(std::exception* e)
      (boost::system::system_error &e)
  {
      cout << e.what() << endl;
  }
  return 0;
}