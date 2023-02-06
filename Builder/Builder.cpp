#include <iostream>
#include <string>
#include <vector>
#include <ostream>
#include <sstream>
using namespace std;

template <typename Range, typename Value = typename Range::value_type>
    string join(Range const& elements, const char *const delimiter)
{
        ostringstream os;
        auto b = begin(elements), e = end(elements);

        if (b != e) 
        {
            copy(b, prev(e), std::ostream_iterator<Value>(os, delimiter));
            b = prev(e);
        }
        if (b != e) 
        {
            os << *b;
        }

        return os.str();
}

enum file_type
{
	file_cpp = 0,
    file_h
};

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

struct method
{
	string name, type;
    vector<arguments> args;

    method(string name, string type, vector<arguments> arguments)
	    : name{std::move(name)},
	      type{std::move(type)},
          args{std::move(arguments)}
    {
    }

    friend ostream& operator<<(ostream& os, const method& obj)
    {
        vector<string> strings;
    	os << "\n\t" << obj.type << " " << obj.name << "(";
        for (const auto& ar : obj.args)
        {
            string s = ar.type + " " + ar.name;
            strings.emplace_back(s);
        }
        os << join(strings, ", ");
        os << ")";
        os << ";\n";
		//os << "\t{\n\t}";

        return os;
    }
};

struct Class
{
    string name;
    vector<field> fields;
    vector<method> methods;

    friend ostream& operator<<(ostream& os, const Class& obj)
    {
        os << "class " << obj.name << "\n{\n";
        for (auto&& field : obj.fields)
        {
            os << "\t" << field << "\n";
        }

        for (auto&& method : obj.methods)
        {
	        os << "\t" << method << "\n";
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

    code_builder& add_field(const string& name, const string& type, const vector<arguments>& args)
    {
        the_class_.fields.emplace_back(name, type);
        the_class_.methods.emplace_back(name, type, args);
        return *this;
    }

    friend ostream& operator<<(ostream& os, const code_builder& obj)
    {
        return os << obj.the_class_;
    }
};


int main()
{
    const arguments args = {"test", "string"};
    vector<arguments> ar;
    ar.emplace_back(args);
    ar.emplace_back(args);
	const auto cb = code_builder{ "Person" }
	                .add_field("name", "string", ar)
	                .add_field("age", "int", ar);
    ostringstream oss;
    oss << cb;
    std::cout << oss.str() << std::endl;

    /*string elements[] = { "aap", "noot", "mies" };

    typedef vector<string> strings;

    
    ostringstream oss;
    oss << join(strings(elements, elements + 3), ", ");;
    std::cout << oss.str() << std::endl;*/
    
    return 0;
}
