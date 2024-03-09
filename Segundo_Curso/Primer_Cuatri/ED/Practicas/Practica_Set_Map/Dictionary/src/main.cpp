#include <iostream>
#include "Dictionary.h"

using namespace std;

typedef Dictionary::const_iterator const_Dic_it;
typedef std::vector<std::string>::const_iterator v_it;

/**
 * @brief Imprime un vector de strings.
 *
 * @param v el vector a imprimir.
*/
void ImprimeVectorString(const std::vector<std::string>& v) {
	
    for(v_it it = v.cbegin(); it != v.cend(); ++it)
    {
        cout << *it << endl;
    }	
}

/*******************************************************/
/*******************************************************/
/*******************************************************/
int main(int argc, char* argv[]) {
    
    Dictionary d(argv[1]);
    int length = atoi(argv[2]);
    
    
    cout << d << endl << endl;
    ImprimeVectorString(d.wordsOfLength(length));
    
    return 0;
}
