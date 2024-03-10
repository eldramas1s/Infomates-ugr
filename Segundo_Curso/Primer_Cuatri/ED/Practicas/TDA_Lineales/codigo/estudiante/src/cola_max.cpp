#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "maxqueue.h"

using namespace std;

int main(int argc, char *argv[]){

    // // Run the current exercise
    maxqueue queue;

    for(int i = 1; i < argc; i++) {
        if (argv[i][0] == '.') {
            cout << "caca";
            cout << queue.front() << endl;
            queue.pop();
        } else {
            pair <int,int>p;
            p.first=atoi(argv[i]);
            p.second=p.first;
            queue.push(p);
        }
    }
    return 0;
}
