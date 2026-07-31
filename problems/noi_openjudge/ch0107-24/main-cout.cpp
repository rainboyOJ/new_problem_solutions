#include <cstring>
#include <iostream>

char str[1000];
int main(){
    std::cin >> str;
    int len =  strlen(str);
    std::cout << len;
    
    while(1){
        int ret = (std::cin >> str) ? 1 : -1;
        if( ret == EOF) break;
        len =  strlen(str);
        std::cout << "," << len;
    }
    return 0;
}
