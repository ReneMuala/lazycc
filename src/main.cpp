#include "lib/lazy.cc"

using namespace lazy;

/// implementation of a simple parser
int main()
{
    var entrada = R"(
        int x = 2;
    )";

    final dicionario = unordered_map<string, regex>({
        {"numero", regex(R"(\d)")},
        {"operador", regex(R"([=\+-\*/])")},
        {"palavra reservada", regex(R"(void|int)")}, {"delimitador", regex(R"([\(\)\[\];{}])")},
        {"identificador", regex(R"(\w+)")},
    });

    final entrada_sem_espacos = split(regex(R"(\s+)"), entrada);

    var lexema = detach(regex(R"(\d+(\.\d+)?|\w+|[\(\){}]|.+)"), entrada_sem_espacos);

    final tokens = tokenize(dicionario, "desconhecido", lexema);

    cout << to_string(tokens) << endl;
}