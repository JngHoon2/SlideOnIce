#include <iostream>
#include "ioHandler.h"
using namespace std;

int main(){
    initTerminal();
    
    int i = 0;

    while(true){
        clearScreen();
        cout << i << endl;
        cout.flush();
        
        int key = getKeyPress();
        if(key == 65){
            i++;
        } else if(key == 66) {
            i--;
        } else if(key == 27) {
            break;
        }
    }

    restoreTerminal();
    return 0;
}