#include <cstring>
#include <iostream>

char str[500];
int idx=0;
int main(){
    char t;
    while(1){
        int ret = (std::cin >> std::noskipws >> t) ? 1 : -1;
        if( t == '\n' || t == '\r' || ret == EOF)
            break;
        str[++idx] = t;
    }
    int i;
    for (i=1;i<=idx;i++){
        if( str[i] >='a' &&  str[i] >='a' ){
            std::cout << (char)(str[i]+'A'-'a');
        }
        else
            std::cout << (char)(str[i]);
    }
    return 0;
}
