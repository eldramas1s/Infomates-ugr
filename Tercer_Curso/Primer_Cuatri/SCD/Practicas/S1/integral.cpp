#include <iostream>
#include <iomanip>
#include <vector>
#include <thread>
#include <chrono>
#include <climits>
using namespace std;
using namespace std::chrono;

const long m = 1024*1024*1024;

double f(double x){
    return 4/(1+x*x);
}

void calcular_integral_hebras_intercalado(int i, int num_hebras, vector<double>& resultados){
    double suma = 0.0;
    for (long j = i; j<m; j+=num_hebras){
        const double xj = (double)(j+0.5)/m;
        suma+=f(xj);
    }
    resultados[i]=suma;
}

int main(){
    int num_hebras = 8;
    const double pi = 3.14159265358978312;
    double suma = 0;
    vector<double> resultados(num_hebras, 0.0);

    thread hebras[num_hebras];

    time_point<steady_clock> instante_inicio = steady_clock::now();

    for (int j = 0; j<num_hebras; ++j){
        hebras[j] = thread (calcular_integral_hebras_intercalado, j, num_hebras,ref(resultados)); 
    }

    for (int j=0; j<num_hebras; ++j){
        hebras[j].join();
    }
    for (int j = 0; j<num_hebras;++j){
        suma +=resultados[j]; 
    }
    
    suma = suma/m;

    time_point<steady_clock> instante_final = steady_clock::now();

    duration<float,micro> duracion_micros = instante_final - instante_inicio;

    cout << "La actividad ha tardado: "
         << duracion_micros.count() << " microsegundos." << endl;

    cout << "El resultado es : " << setprecision(100) << suma << endl; 

    return 0;
}
