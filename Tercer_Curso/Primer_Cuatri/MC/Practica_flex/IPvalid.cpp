#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

bool isValidIP(const char* ip) {
    int ipl = strlen(ip);
    if (ipl == 0 || ipl > 15) return false; // Longitud mínima 7 (0.0.0.0) y máxima 15 (255.255.255.255)

    int num_segments = 0;
    char segment[4]; // Para almacenar cada segmento temporalmente
    int segIndex = 0;

    for (int i = 0; i <= ipl; ++i) {
        if (ip[i] == '.' || ip[i] == '\0') {
            if (segIndex == 0) return false; // Segmento vacío

            segment[segIndex] = '\0';
            int num = atoi(segment);
            if (num < 0 || num > 255) return false; // Segmento fuera de rango

            ++num_segments;
            segIndex = 0; // Reiniciar el índice del segmento

            if (num_segments > 4) return false; // Demasiados puntos
        } else if (ip[i] >= '0' && ip[i] <= '9') {
            if (segIndex >= 3) return false; // Segmento demasiado largo
            segment[segIndex++] = ip[i];
        } else {
            return false; // Caracter inválido
        }
    }

    return num_segments == 4; // Deben haber exactamente 4 segmentos (3 puntos)
}

int main() {
    char ip[20];
    cout << "Introduce una dirección IP: ";
    cin >> ip;

    if (isValidIP(ip)) {
        cout << "La dirección IP es válida.\n";
    } else {
        cout << "La dirección IP no es válida.\n";
    }

    return 0;
}