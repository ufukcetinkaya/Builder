#include <string>
#include <vector>
#include <ostream>
#include <iostream>
#include <sstream>
using namespace std;

//struct tag
//{
//    std::string name;
//    std::string text;
//    std::vector<tag> children;
//    std::vector<std::pair<std::string, std::string>> attributes;
//
//    friend std::ostream& operator<<(std::ostream& os, const tag& tag)
//    {
//        os << "<" << tag.name;
//
//        for (const auto& att : tag.attributes)
//            os << " " << att.first << "=\"" << att.second << "\"";
//
//        if (tag.children.empty() && tag.text.length() == 0)
//        {
//            os << "/>" << std::endl;
//        }
//        else
//        {
//            os << ">" << std::endl;
//
//            if (tag.text.length())
//                os << tag.text << std::endl;
//
//            for (const auto& child : tag.children)
//                os << child;
//
//            os << "</" << tag.name << ">" << std::endl;
//        }
//
//        return os;
//    }
//protected:
//
//    tag(std::string name, std::string text)
//        : name{std::move(name)},
//        text{std::move(text)}
//    {
//    }
//
//
//    tag(std::string name, std::vector<tag> children)
//        : name{std::move(name)},
//        children{std::move(children)}
//    {
//    }
//};
//
//struct p : tag
//{
//    explicit p(const std::string& text)
//        : tag{ "p", text }
//    {
//    }
//
//    p(std::initializer_list<tag> children)
//        : tag("p", children)
//    {
//    }
//
//};
//
//struct img : tag
//{
//    explicit img(const std::string& url)
//        : tag{ "img", "" }
//    {
//        attributes.emplace_back("src", url);
//    }
//};

struct arguments
{
    string name, type;
};

struct field
{
    string name, type;

    field(string name, string type)
	    : name{std::move(name)},
	      type{std::move(type)}
    {
    }

    friend ostream& operator<<(ostream& os, const field& obj)
    {
    	return os << obj.type << " " << obj.name << ";";
    }
};

struct Class
{
    string name;
    vector<field> fields;

    friend ostream& operator<<(ostream& os, const Class& obj)
    {
        os << "class " << obj.name << "\n{\n";
        for (auto&& field : obj.fields)
        {
            os << "  " << field << "\n";
        }
        return os << "};\n";
    }
};

class code_builder
{
    Class the_class_;
public:
    explicit code_builder(const string& class_name)
    {
        the_class_.name = class_name;
    }

    code_builder& add_field(const string& name, const string& type)
    {
        the_class_.fields.emplace_back(name, type);
        return *this;
    }

    code_builder& add_method(const string& name, const string& type)
    {
        the_class_.fields.emplace_back(name, type);
        return *this;
    }

    friend ostream& operator<<(ostream& os, const code_builder& obj)
    {
        return os << obj.the_class_;
    }
};


int main()
{
	const auto cb = code_builder{ "Person" }
	                .add_field("name", "string")
	                .add_field("age", "int");
    ostringstream oss;
    oss << cb;
    std::cout << oss.str() << std::endl;
    return 0;
}