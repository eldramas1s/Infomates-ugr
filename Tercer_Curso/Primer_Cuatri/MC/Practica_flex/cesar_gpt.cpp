#include <iostream>
#include <cstring>

using namespace std;

void cifrarCesar(char* texto, int desplazamiento) {
    int len = strlen(texto);
    for (int i = 0; i < len; ++i) {
        if (texto[i] >= 33 && texto[i] <= 126) {
            texto[i] = ((texto[i] - 33 + desplazamiento) % 94) + 33;
        }
    }
}

void descifrarCesar(char* texto, int desplazamiento) {
    int len = strlen(texto);
    for (int i = 0; i < len; ++i) {
        if (texto[i] >= 33 && texto[i] <= 126) {
            texto[i] = ((texto[i] - 33 - (desplazamiento % 94) + 94) % 94) + 33;
        }
    }
}

int main() {
    char texto[256];
    int desplazamiento;

    cout << "Introduce el texto a cifrar: ";
    cin.getline(texto, 256);

    cout << "Introduce el desplazamiento: ";
    cin >> desplazamiento;

    cifrarCesar(texto, desplazamiento);
    cout << "Texto cifrado: " << texto << "\n";

    descifrarCesar(texto, desplazamiento);
    cout << "Texto descifrado: " << texto << "\n";

    return 0;
}