
//https://mariusbancila.ro/blog/2017/11/19/revisited-full-fledged-client-server-example-with-c-rest-sdk-2-10/
#include "def.h"
/*
Notice there are slight changes in the way output is formatted, both in the server and the client application. The rest
is mostly unchanged, except for the handling of JSON, that has changed significatly since version 1.1. Again, please see
the original post for an explanation of the code.

The output from running these client and server applications is shown below. On the left is the client output, and on
the right the server output.
*/
void display_json(json::value const& jvalue, utility::string_t const& prefix)
{
    std::wcout << prefix << jvalue.serialize() << std::endl;
}

pplx::task<http_response> make_task_request(http_client& client, method mtd, json::value const& jvalue)
{
    return (mtd == methods::GET || mtd == methods::HEAD) ? client.request(mtd, L"/restdemo")
                                                         : client.request(mtd, L"/restdemo", jvalue);
}

void make_request(http_client& client, method mtd, json::value const& jvalue)
{
    make_task_request(client, mtd, jvalue)
        .then([](http_response response) {
            if (response.status_code() == status_codes::OK)
            {
                return response.extract_json();
            }
            return pplx::task_from_result(json::value());
        })
        .then([](pplx::task<json::value> previousTask) {
            try
            {
                display_json(previousTask.get(), L"R: ");
            }
            catch (http_exception const& e)
            {
                std::wcout << e.what() << std::endl;
            }
        })
        .wait();
}

int full_client_main()
{
    http_client client(U("http://localhost:8888"));

    auto putvalue = json::value::object();
    putvalue[L"one"] = json::value::string(L"100");
    putvalue[L"two"] = json::value::string(L"200");

    std::wcout << L"\nPUT (add values)\n";
    display_json(putvalue, L"S: ");
    make_request(client, methods::PUT, putvalue);

    auto getvalue = json::value::array();
    getvalue[0] = json::value::string(L"one");
    getvalue[1] = json::value::string(L"two");
    getvalue[2] = json::value::string(L"three");

    std::wcout << L"\nPOST (get some values)\n";
    display_json(getvalue, L"S: ");
    make_request(client, methods::POST, getvalue);

    auto delvalue = json::value::array();
    delvalue[0] = json::value::string(L"one");

    std::wcout << L"\nDELETE (delete values)\n";
    display_json(delvalue, L"S: ");
    make_request(client, methods::DEL, delvalue);

    std::wcout << L"\nPOST (get some values)\n";
    display_json(getvalue, L"S: ");
    make_request(client, methods::POST, getvalue);

    auto nullvalue = json::value::null();

    std::wcout << L"\nGET (get all values)\n";
    display_json(nullvalue, L"S: ");
    make_request(client, methods::GET, nullvalue);

    return 0;
}