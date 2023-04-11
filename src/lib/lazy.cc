#include <regex>
#include <list>
#include <vector>
#include <functional>
#include <thread>
#include <future>
#include <any>
#include <map>
#include <unordered_map>
#include <fstream>
#include <iostream>

#define var auto
#define final const auto
#define fn function
#define ptr(x) x *
#define ref(x) &x
#define type_ref(x) x &

namespace lazy
{
    using namespace std;
    namespace tokenization
    {
        string to_string(map<string, regex> src)
        {
            string result;
            for (final[str, reg] : src)
            {
                result += "{ " + str + " : std::regex } ";
            }
            return result;
        }

        string to_string(map<string, string> src)
        {
            string result;
            for (final[str, str2] : src)
            {
                result += "{ '" + str + "' : '" + str2 + "' } ";
            }
            return result;
        }

        string to_string(list<string> src)
        {
            string result;
            for (final str : src)
            {
                result += "'" + str + "' ";
            }
            return result;
        }

        string to_string(list<pair<string, string>> src)
        {
            string result;
            for (final[str, str2] : src)
            {
                result += "{ '" + str + "' : '" + str2 + "' } ";
            }
            return result;
        }

        list<pair<string, string>> tokenize(list<pair<string, regex>> dict, string error_type_name, list<string> pre_tokens)
        {
            list<pair<string, string>> tokens;
            var is_type_resolved = bool();
            for (type_ref(final) pre_token : pre_tokens)
            {
                is_type_resolved = false;
                for (type_ref(final)[type_name, type_regex] : dict)
                {
                    if (regex_match(pre_token, type_regex))
                    {
                        tokens.push_back({type_name, pre_token});
                        is_type_resolved = true;
                        break;
                    }
                }
                if (!is_type_resolved)
                    tokens.push_back({error_type_name, pre_token});
            }
            return tokens;
        }

        list<string> split(regex regex, string src)
        {
            var iterator = sregex_token_iterator(src.begin(), src.end(), regex, -1);
            var token_li = list<string>({iterator, sregex_token_iterator()});
            token_li.remove_if([](string str)
                               { return str == ""; });
            return token_li;
        }

        list<string> detach(regex regex, string src)
        {
            var iterator = sregex_token_iterator(src.begin(), src.end(), regex, 0);
            return {iterator, sregex_token_iterator()};
        }

        list<string> detach(regex regex, list<string> srcs)
        {
            var result = list<string>();
            for (final src : srcs)
            {
                for (final component : detach(regex, src))
                {
                    result.push_back(component);
                }
            }
            return result;
        }
    }
    using namespace tokenization;
}