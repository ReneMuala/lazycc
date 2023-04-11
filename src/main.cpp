#include "lib/lazy.cc"

using namespace lazy;

/// implementation of a simple parser
int main()
{
    var entrada = "int a= 1+2;";

    // cout << entrada << endl;

    var entrada_sem_espaco = split(regex(R"(\s+)"), entrada);

    var lexemas = detach(regex(R"(\w+|\+|\=|.+)"), entrada_sem_espaco);

    // for (var lex : lexemas)
    // {
    //     cout << lex << ",";
    // }

    var dicionario = list<pair<string, regex>>{
        {"palavra reservada", regex(R"(int)")},
        {"numero", regex(R"(\d+)")},
        {"delimitador", regex(R"(;)")},
        {"identificador", regex(R"(\w+)")},
    };

    var tokens = tokenize(dicionario, "erro", lexemas);

    cout << to_string(tokens) << endl;
}