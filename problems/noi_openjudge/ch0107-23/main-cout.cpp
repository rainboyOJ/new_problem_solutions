#include <cstring>
#include <iostream>

char str[1000];
int cnt=0;
int main(){
    char t;
    while (std::cin >> std::noskipws >> t){
        str[++cnt] = t;
    }
    bool is_first_blank = true;
    int i;
    for (i=1;i<=cnt;i++){
        if( str[i] == ' ' && is_first_blank){
            std::cout << " ";
            is_first_blank = false;
        }
        else if ( str[i] != ' '){
            std::cout << (char)(str[i]);
            is_first_blank = true;
        }
    }
    return 0;
}
