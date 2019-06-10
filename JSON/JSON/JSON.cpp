// JSON.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iomanip>
#include <iostream>
#include <filesystem>
#include <nlohmann/json.hpp>

#include "File.h"

// for convenience
using json = nlohmann::json;

#include <iostream>

//创建json对象
/*
{
  "pi": 3.141,
  "happy": true,
  "name": "Niels",
  "nothing": null,
  "answer": {
    "everything": 42
  },
  "list": [1, 0, 2],
  "object": {
    "currency": "USD",
    "value": 42.99
  }
}
*/
void createJson()
{
    /*
      {
        "answer": {
            "everyting": 42
        },
        "happy": true,
        "list": [
            1,
            0,
            2
        ],
        "name": "Niels",
        "nothing": null,
        "object": {
            "currency": "USD",
            "value": 42.99
        },
        "pi": 3.141
    }
    */
    // empty structure null
    json j;
    // add a number that is stored as double (note the implicit conversion of j to an object)
    j["pi"] = 3.141;
    // add a boolean that is stored as bool
    j["happy"] = true;

    // add a string that is stored as std::string
    j["name"] = "Niels";

    // add another null object by passing nullptr
    j["nothing"] = nullptr;

    // add another null object by passing nullptr
    j["nothing"] = nullptr;

    // add an object inside the object
    j["answer"]["everyting"] = 42;

    // add an array that is stored as std::vector (using an initializer list)
    j["list"] = {1, 0, 2};

    // add another object ,using an initializer list of pairs
    j["object"] = {{"currency", "USD"}, {"value", 42.99}};

    /////////////////////////j2和j3都跟j不一样吧TODO
    // https://blog.csdn.net/forrid/article/details/78867679
    // instead ,you could also write (which looks very similar to the json above)
    json j2 = {{"pi", 3.143},
               {"happy", true},
               {"NAME", "CHLL"},
               {"NOTHING", nullptr},
               {"ANSWER", {"EVERYTHINS"}, 42},
               {"list", {1, 0, 2}},
               {"object", {{"currency", "USD"}, {"value", 42.99}}}};
    std::cout << std::setw(4) << j << std::endl;
    std::cout << "=============================" << std::endl;

    std::cout << std::setw(4) << j2 << std::endl;
    json j3 = {"pi",
               3.143,
               "happy",
               true,
               "NAME",
               "CHLL",
               "NOTHING",
               nullptr,
               {"ANSWER", {"EVERYTHINS"}, 42},
               "list",
               {1, 0, 2},
               "object",
               {"currency", "USD", "value", 42.99}};
    std::cout << "=============================" << std::endl;
    std::cout << std::setw(4) << j3 << std::endl;

    ////////////序列化
    // 从字符串字面量创建对象
    /*
j4 {
"happy": true,
"pi": 3.141
}
    */
    json j4 = "{\"happy\": true, \"pi\": 3.141}"_json;
    // 最好是使用原始字符串字面量
    /*
j5{
"happy": true,
"pi": 3.141
}
    */
    auto j5 = R"({"happy": true, "pi": 3.141})"_json;
    // 显式地分析
    auto j6 = json::parse("{\"happy\": true, \"pi\": 3.141}");
    std::cout << "j4 " << std::setw(4) << j4 << std::endl;
    std::cout << "j5" << std::setw(4) << j5 << std::endl;
    std::cout << "j6" << std::setw(4) << j6 << std::endl;

    // 显式地转换至字符串
    std::string s = j6.dump();
    // 传入缩进空格数，使用良好的打印形式进行序列化
    std::cout << j6.dump(4) << std::endl;
}
/*https://www.json.cn/
{
    "project":   "client-logs",
    "region":   "henzhen",
    "logStore":   "com-web",
    "source":   "127.0.0.1",
    "encode" : 2,
    "content":[{
        "key1" :   "%E5%86%85%E5%AE%B91",
      "key2" :   "%E5%86%AE%B91",
     
        "key3" : "内容3"
    },{
        "key1" : "内容1",
        "key2" : "内容2",
        "key3" :   "%E5%86%85%E5%AE%B93"
    }]
}

*/
void create100()
{
    std::cout << "=============================" << std::endl;
    //   json j = json::parse("{ \  "project \" : \ "client-logs \",\ "region \" : \"henzhen \",\"logStore \" :
    //   \"com-web \",\"source \" : \"127.0.0.1 \",\ "encode" : 2,}");
    //    auto j5 = R"({"happy": true, "pi": 3.141})"_json;
    json raw = R"({ 
    "project":   "client-logs",
    "region":   "shenzhen",
    "logStore":   "com-web",
    "source":   "127.0.0.1",
    "encode" : 2,
    "content":[0,1,2]
})"_json;
    // std::cout <<"comj:"<< std::setw(4) << j << std::endl;
    std::cout << std::setw(4) << raw << std::endl;
}
void createarray()
{
    std::cout << "=============================" << std::endl;
    //创建一个空数组
    json empty_array_explicit = json::array();
    // 创建一个空对象的两种方式
    json empty_object_implicit = json({});
    json empty_object_explicit = json::object();

    // array是一个数组，可以用数字直接下标访问。
    json array = {"a", 6, "xin", 8};
    std::cout << "array[0]" << std::setw(4) << array[0] << std::endl;

    /*
    // add an object inside the object
j["answer"]["everyting"] = 42;

// add an array that is stored as std::vector (using an initializer list)
j["list"] = {1, 0, 2};

// add another object ,using an initializer list of pairs
j["object"] = {{"currency", "USD"}, {"value", 42.99}};
    */
    json j;
    // add a number that is stored as double (note the implicit conversion of j to an object)
    //会覆盖啊 TODO
    /*
"content": {
"5": "5",
"6": 42.99,
"7": "8"
},
    */
    j["content"] = {{"currency", "USD"}, {"value", 42.99}, {"nihao", "home"}};
    j["content"] = {{"1", "2"}, {"3", 42.99}, {"4", "5"}};
    j["content"] = {{"5", "5"}, {"6", 42.99}, {"7", "8"}};
    j["module"] = "china";
    std::cout << std::setw(4) << j << std::endl;

    std::cout << "=============================" << std::endl;
    //怎么变为了这个样子：   "1content": " [ \"one\", \"two\", \"three\" ]", ？？？？？？TODO
    j["1_content"] = R"( [ "one", "two", "three" ])";
    /*
        "2_content": "[\n  { \"op\": \"replace\", \"path\": \"/baz\", \"value\": \"boo\" },\n  { \"op\": \"add\",
       \"path\": \"/hello\", \"value\": [\"world\"] },\n  { \"op\": \"remove\", \"path\": \"/foo\"} \n]",
    */
    j["2_content"] = R"([
  { "op": "replace", "path": "/baz", "value": "boo" },
  { "op": "add", "path": "/hello", "value": ["world"] },
  { "op": "remove", "path": "/foo"} 
])";
    /*
    3 是这样的，看起来这个就符合要求
"3_content": [
{
"op": "replace",
"path": "/baz",
"value": "boo"
},
{
"op": "add",
"path": "/hello",
"value": [
"world"
]
},
{
"op": "remove",
"path": "/foo"
}
],
    */
    //这个也符号要求，j["2_content"] 的方法可以直接转为json的字符串
    j["3_content"] = json::parse(
        "[ { \"op\": \"replace\", \"path\": \"/baz\", \"value\": \"boo\" },\n  { \"op\": \"add\", \"path\": "
        "\"/hello\", \"value\": [\"world\"] },\n  { \"op\": \"remove\", \"path\": \"/foo\"} ]");
    /*
    GOOD!
    厉害了，这个符合要求
"4_content": [
{
"currency": "USD",
"nihao": "home",
"value": 42.99
},
{
"5": "5",
"6": 42.99,
"7": "8"
},
{
"5": "5",
"6": 42.99,
"7": "8"
}
],
    */
    json m1 = {{"currency", "USD"}, {"value", 42.99}, {"nihao", "home"}};
    json m2 = {{"1", "2"}, {"3", 42.99}, {"4", "5"}};
    json m3 = {{"5", "5"}, {"6", 42.99}, {"7", "8"}};
    //这样符合要求
    j["4_content"] = {m1, m3, m3};
    std::cout << std::setw(4) << j << std::endl;
}
void creatPatch()
{
    // a JSON value
    json j_original = R"({
  "baz": ["one", "two", "three"],
  "foo": "bar"
})"_json;

    // https://www.jianshu.com/p/69e57f2af904
    // a JSON patch (RFC 6902)
    json j_patch = R"([
  { "op": "replace", "path": "/baz", "value": "boo" },
  { "op": "add", "path": "/hello", "value": ["world"] },
  { "op": "remove", "path": "/foo"}
])"_json;
}
class Component
{
public:
    Component(std::string type) { name = type; }
    /*
 {
    "TIME": "china_2",
    "Type": "1_china"
},
    */
    void Serialize(json& outJson)
    {
        outJson["Type"] = std::to_string(++id) + "_" + name;
        outJson["TIME"] = name + "_" + std::to_string(++id);
    }
    static int id;

private:
  
    std::string name;
};
int Component::id = 0;
/*
d

[
{
    "Components": [
        {
            "Type": "1_china"
        },
        {
            "Type": "1_usa"
        },
        {
            "Type": "1_english"
        }
    ],
    "Name": "zhangbin"
}
]

*/
void createVecor(json& d)
{
    json thing;
    thing["Name"] = "zhangbin";
    json& componentsJson = thing["Components"];

    std::vector<Component> sss;
    sss.push_back(Component("china"));
    sss.push_back(Component("usa"));
    sss.push_back(Component("english"));
    auto comps = sss;
    for (auto comp : comps)
    {
        json compJson;
        comp.Serialize(compJson);
        /*
        从vector来自动变为数组
[
{
"TIME": "china_2",
"Type": "1_china"
},
{
"TIME": "usa_4",
"Type": "3_usa"
},
{
"TIME": "english_6",
"Type": "5_english"
}
],
        */
        componentsJson.push_back(compJson);
    }
    std::cout << "===========thing==================" << std::endl;
    /*
//{
//"Components": [
//{
//    "Type": "1_china"
//},
//{
//    "Type": "2_usa"
//},
//{
//    "Type": "3_english"
//}
//],
//"Name": "zhangbin"
//}
    */
    std::cout << std::setw(4) << thing << std::endl;
    d.push_back(thing);
    d.push_back(thing);
}
Path FilePath;
void save(std::string fileName, json &world)
{
  
    //void Scene::Save(std::string fileName, Transform * root)
    {
        FilePath = Path(fileName);

        File worldFile(FilePath);
       
		

        worldFile.Write(world.dump(4));
        std::cout << world.dump(4) << std::endl;
    }
}
int main()
{
    std::cout << "Hello World!\n";
    createJson();
    create100();
    createarray();
    std::cout << "=============================" << std::endl;
    /*
[
{
"Components": [
    {
        "Type": "1_china"
    },
    {
        "Type": "1_usa"
    },
    {
        "Type": "1_english"
    }
],
"Name": "zhangbin"
},
{
"Components": [
    {
        "Type": "1_china"
    },
    {
        "Type": "1_usa"
    },
    {
        "Type": "1_english"
    }
],
"Name": "zhangbin"
}
]
    */
    json ddd;
    createVecor(ddd);
    std::cout << std::setw(4) << ddd << std::endl;
    json d;
    d["content"] = ddd;
    std::cout << "=============================" << std::endl;
    /*
{
"content": [
{
    "Components": [
        {
            "Type": "1_china"
        },
        {
            "Type": "1_usa"
        },
        {
            "Type": "1_english"
        }
    ],
    "Name": "zhangbin"
},
{
    "Components": [
        {
            "Type": "1_china"
        },
        {
            "Type": "1_usa"
        },
        {
            "Type": "1_english"
        }
    ],
    "Name": "zhangbin"
}
]
}
    */
    std::cout << std::setw(4) << d << std::endl;
	//E:\netttttt\http\zhangbincpprestsdk\WIN32\Release下面，跟exe同目录
    save("ssave.txt",d);
    system("pause");
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧:
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
