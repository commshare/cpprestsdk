
#include "http_svr.h"
// https://mariusbancila.ro/blog/2013/08/19/full-fledged-client-server-example-with-cpprest-sdk-110/
//看这个 https://mariusbancila.ro/blog/2017/11/19/revisited-full-fledged-client-server-example-with-c-rest-sdk-2-10/
namespace full_svr


{
#if 0
void display_json(json::value const& jvalue, utility::string_t const& prefix)
{
    std::wcout << prefix << jvalue.serialize() << std::endl;
}


  /*
  n this simple implementation the dictionary is a std::map. 
  Its content is not persisted to disk, it is reloaded each time the server starts.
  */
std::map<utility::string_t, utility::string_t> dictionary;
//http://cn.voidcc.com/question/p-uoiiighz-boe.html
typedef std::vector<std::pair<utility::string_t, json::value>> field_map;

/*
Let’s now look at the handlers. As mentioned earlier the GET method is a bit different than the others. A GET request
should return all the key-value pairs in the server’s dictionary. Its implementation looks like this:

handlers implementation */
void handle_get(http_request request)
{
    TRACE(L"\nhandle GET\n");

	
	//是不是库里没有的
  //  json::value::field_map answer;
    field_map answer; 
    for (auto const& p : dictionary)
    {
      //  answer.push_back(std::make_pair(json::value(p.first), json::value(p.second)));
        answer.push_back(std::make_pair(p.first, json::value(p.second))); 
    }
	//http://cn.voidcc.com/question/p-uoiiighz-boe.html
    request.reply(status_codes::OK, json::value::object(answer));
}


void handle_request(http_request request, std::function<void(json::value&, field_map&)> action)
{
    field_map answer;

    request.extract_json()
        .then([&answer, &action](pplx::task<json::value> task) {
            try
            {
			  //这里会有报错
                auto& const jvalue = task.get();

                if (!jvalue.is_null())
                {
                    action(jvalue, answer);
                }
            }
            catch (http_exception const& e)
            {
                std::wcout << e.what() << std::endl;
            }
        })
        .wait();

    request.reply(status_codes::OK, json::value::object(answer));
} 
void handle_post(http_request request)
{
    TRACE("\nhandle POST\n");

    handle_request(request, [](json::value& jvalue, field_map& answer) {
	    //数组 遍历
        for (auto const& e : jvalue.as_array())
        {
		    //数组中的每一项
            if (e.is_string())
            {
                auto key = e.as_string();
				//在服务端的字典里里找这个key，生成answer
                auto pos = dictionary.find(key);
                if (pos == dictionary.end())
                {
                    answer.push_back(make_pair(key, json::value(L"<nil>")));
                }
                else
                {
                    answer.push_back(make_pair(pos->first, json::value(pos->second)));
                }
            }
        }
    });
}
void handle_put(http_request request)
{
    TRACE("\nhandle PUT\n");

    handle_request(request, [](json::value& jvalue, field_map& answer) {
        for (auto const& e : jvalue.as_object())
        {
            if (e.second.is_string())
            {
                auto key = e.first;
                auto value = e.second.as_string();

                if (dictionary.find(key) == dictionary.end())
                {
                    TRACE_ACTION(L"added", key, value);
                    answer.push_back(make_pair(key, json::value(L"<put>")));
                }
                else
                {
                    TRACE_ACTION(L"updated", key, value);
                    answer.push_back(make_pair(key, json::value(L"<updated>")));
                }

                dictionary[key] = value;
            }
        }
    });
}

void handle_del(http_request request)
{
    TRACE("\nhandle DEL\n");

	//调用handle_request，传入lambda表达式 std::function<void(json::value&, field_map&)> action
    handle_request(request, [](json::value& jvalue, field_map& answer) {
        std::set<utility::string_t> keys;
        for (auto const& e : jvalue.as_array())
        {
            if (e.is_string())
            {
                auto key = e.as_string();

                auto pos = dictionary.find(key);
                if (pos == dictionary.end())
                {
                    answer.push_back(make_pair(key, json::value(L"<failed>")));
                }
                else
                {
                    TRACE_ACTION(L"deleted", pos->first, pos->second);
                    answer.push_back(make_pair(key, json::value(L"<deleted>")));
                    keys.insert(key);
                }
            }
        }

        for (auto const& key : keys)
            dictionary.erase(key);
    });
}
int svr_main(int argc, char** argv)
{
    http_listener listener(L"http://localhost/restdemo");

    listener.support(methods::GET, handle_get);
    listener.support(methods::POST, handle_post);
    listener.support(methods::PUT, handle_put);
    listener.support(methods::DEL, handle_del);

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

    return 0;
}
#else /// https://mariusbancila.ro/blog/2017/11/19/revisited-full-fledged-client-server-example-with-c-rest-sdk-2-10/

/*
I will not reiterate all the details described in the former article. However, in summary, the server maintains a
dictionary of values (both keys and values are strings). Through HTTP calls a client can retrieve the content of the
dictionary, add new values, update or delete existing ones.

客户端主要是对服务端的dictionary做读取/修改
*/
std::map<utility::string_t, utility::string_t> dictionary;

void display_json(json::value const& jvalue, utility::string_t const& prefix)
{
    std::wcout << prefix << jvalue.serialize() << std::endl;
}

void handle_get(http_request request)
{
    TRACE(L"\nhandle GET\n");

    auto answer = json::value::object();

    for (auto const& p : dictionary)
    {
        answer[p.first] = json::value::string(p.second);
    }

    display_json(json::value::null(), L"R: ");
    display_json(answer, L"S: ");

    request.reply(status_codes::OK, answer);
}

void handle_request(http_request request, std::function<void(web::json::value const&, web::json::value&)> action)
{
    auto answer = web::json::value::object();

    request.extract_json()
        .then([&answer, &action](pplx::task<web::json::value> task) {
            try
            {
                auto const& jvalue = task.get();
                display_json(jvalue, L"R: ");

                if (!jvalue.is_null())
                {
                    action(jvalue, answer);
                }
                else
                {
                    std::wcout << "jvalue.is_null() !!!!err!!!!" << std::endl;
                }
            }
            catch (http_exception const& e)
            {
                std::wcout << e.what() << std::endl;
            }
        })
        .wait();


    display_json(answer, L"S: ");

    request.reply(status_codes::OK, answer);
}

void handle_post(http_request request)
{
    TRACE("\nhandle POST\n");

    handle_request(request, [](json::value const& jvalue, json::value& answer) {
        for (auto const& e : jvalue.as_array())
        {
            if (e.is_string())
            {
                auto key = e.as_string();
                auto pos = dictionary.find(key);

                if (pos == dictionary.end())
                {
                    answer[key] = json::value::string(L"<nil>");
                }
                else
                {
                    answer[pos->first] = json::value::string(pos->second);
                }
            }
        }
    });
}

void handle_put(http_request request)
{
    TRACE("\nhandle PUT\n");

    handle_request(request, [](json::value const& jvalue, json::value& answer) {
        for (auto const& e : jvalue.as_object())
        {
            if (e.second.is_string())
            {
                auto key = e.first;
                auto value = e.second.as_string();

                if (dictionary.find(key) == dictionary.end())
                {
                    TRACE_ACTION(L"added", key, value);
                    answer[key] = json::value::string(L"<put>");
                }
                else
                {
                    TRACE_ACTION(L"updated", key, value);
                    answer[key] = json::value::string(L"<updated>");
                }

                dictionary[key] = value;
            }
        }
    });
}

void handle_del(http_request request)
{
    TRACE("\nhandle DEL\n");

    handle_request(request, [](json::value const& jvalue, json::value& answer) {
        std::set<utility::string_t> keys;
        for (auto const& e : jvalue.as_array())
        {
            if (e.is_string())
            {
                auto key = e.as_string();

                auto pos = dictionary.find(key);
                if (pos == dictionary.end())
                {
                    answer[key] = json::value::string(L"<failed>");
                }
                else
                {
                    TRACE_ACTION(L"deleted", pos->first, pos->second);
                    answer[key] = json::value::string(L"<deleted>");
                    keys.insert(key);
                }
            }
        }

        for (auto const& key : keys)
            dictionary.erase(key);
    });
}
}

/*
starting to listen

handle PUT
R: {"one":"100","two":"200"}
added (one, 100)
added (two, 200)
S: {"one":"<put>","two":"<put>"}

handle POST
R: ["one","two","three"]
S: {"one":"100","three":"<nil>","two":"200"}

handle DEL
R: ["one"]
deleted (one, 100)
S: {"one":"<deleted>"}

handle POST
R: ["one","two","three"]
S: {"one":"<nil>","three":"<nil>","two":"200"}

handle GET
R: null
S: {"two":"200"}

*/
int full_svr_main(int argc, char** argv)
{
    http_listener listener(L"http://localhost:8888/restdemo");

    listener.support(methods::GET, full_svr::handle_get);
    listener.support(methods::POST, full_svr::handle_post);
    listener.support(methods::PUT, full_svr::handle_put);
    listener.support(methods::DEL, full_svr::handle_del);

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

    return 0;
}

#endif
