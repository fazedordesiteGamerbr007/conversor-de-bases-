// Conversor de bases: binário (2), octal (8), decimal (10),
// hexadecimal (16) e base 64
// Compilar: g++ conversor.cpp -o conversor

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

const int QTD_BASES = 5;
const int BASES[QTD_BASES] = {2, 8, 10, 16, 64};
const string NOMES[QTD_BASES] = {"Binario", "Octal", "Decimal", "Hexadecimal", "Base 64"};

// Dígitos usados até a base 16 (aceita maiúscula ou minúscula na entrada)
const string DIGITOS_ATE_16 = "0123456789ABCDEF";

// Dígitos da base 64: tabela padrão do Base64 (A=0, B=1, ..., /=63).
// Aqui maiúscula e minúscula são dígitos diferentes.
const string DIGITOS_BASE64 =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

// Valor numérico de um caractere na base informada. Retorna -1 se não for válido.
int valorDoDigito(char c, int base) {
    size_t posicao;
    if (base == 64) {
        posicao = DIGITOS_BASE64.find(c);
    } else {
        posicao = DIGITOS_ATE_16.find(toupper(c));
    }
    if (posicao == string::npos || (int)posicao >= base) return -1;
    return (int)posicao;
}

// Converte um texto escrito na base informada para um número.
// Retorna false se tiver dígito inválido ou se o número for grande demais.
bool paraNumero(const string& texto, int base, unsigned long long& resultado) {
    if (texto.empty()) return false;

    const unsigned long long MAXIMO = ~0ULL; // maior valor que cabe na variável
    resultado = 0;

    for (char c : texto) {
        int digito = valorDoDigito(c, base);
        if (digito < 0) return false;                               // dígito inválido
        if (resultado > (MAXIMO - digito) / base) return false;     // estouraria o limite
        resultado = resultado * base + digito;
    }
    return true;
}

// Converte um número para texto na base informada (divisões sucessivas).
string paraTexto(unsigned long long numero, int base) {
    const string& digitos = (base == 64) ? DIGITOS_BASE64 : DIGITOS_ATE_16;
    if (numero == 0) return string(1, digitos[0]);

    string texto;
    while (numero > 0) {
        texto = digitos[numero % base] + texto; // o resto vira o próximo dígito
        numero /= base;
    }
    return texto;
}

int main() {
    while (true) {
        cout << "\n=== CONVERSOR DE BASES ===\n";
        cout << "Em qual base esta o numero?\n";
        for (int i = 0; i < QTD_BASES; i++) {
            cout << "  " << i + 1 << " - " << NOMES[i] << " (base " << BASES[i] << ")\n";
        }
        cout << "  0 - Sair\n";
        cout << "Opcao: ";

        string opcao;
        if (!(cin >> opcao) || opcao == "0") break;

        if (opcao.size() != 1 || opcao[0] < '1' || opcao[0] > '0' + QTD_BASES) {
            cout << "Opcao invalida.\n";
            continue;
        }
        int origem = opcao[0] - '1'; // posição nos vetores (0 a 4)

        cout << "Digite o numero em " << NOMES[origem] << ": ";
        string texto;
        if (!(cin >> texto)) break;

        unsigned long long numero;
        if (!paraNumero(texto, BASES[origem], numero)) {
            cout << "Numero invalido para a base " << BASES[origem]
                 << " (ou grande demais).\n";
            continue;
        }

        cout << "\nResultado:\n";
        for (int i = 0; i < QTD_BASES; i++) {
            cout << "  " << NOMES[i] << ": " << paraTexto(numero, BASES[i]) << "\n";
        }
    }

    cout << "Ate mais!\n";
    return 0;
}
