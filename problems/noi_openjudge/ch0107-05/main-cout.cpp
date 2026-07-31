#include <cstring>
#include <iostream>
char str[500];
int idx = 1;

int main(){
    char t;
    while (std::cin >> std::noskipws >> t){
        if( t == '\n' || t == '\r')
            break;
        str[idx] = t;
        idx++;
    }
    idx--;
    int i;
    for (i=1;i<idx;i++){
        //std::cout << (char)(str[i]) << " " << (int)(str[i]) << "\n";
        std::cout << (char)(str[i]+str[i+1]);
    }
    std::cout << (char)(str[1]+str[idx]);
    return 0;
}
