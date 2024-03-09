#include <iostream>
#include "maxstack.h"

using namespace std;

int main(int argc, char *argv[]){

    //Run the current exercise
     maxstack stack;

     for(int i = 1; i < argc; i++){
         if (argv[i][0] == '.'){
             cout << stack.top() << endl;
             stack.pop();
         } else {
             pair <int,int> p;
             p.first=atoi(argv[i]);
             p.second=p.first;
             stack.push(p);
         }
     }
     return 0;
}
