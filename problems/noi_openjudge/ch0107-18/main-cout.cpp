#include <cstring>
#include <iostream>


char str1[1000];
char str2[1000];
int main(){
    std::cin >> str1;
    std::cin >> str2;

    if( strstr(str1,str2) != NULL){
        std::cout << str2 << " is substring of " << str1;
    }
    else if( strstr(str2,str1) != NULL){
        std::cout << str1 << " is substring of " << str2;
    }
    else
        std::cout << "No substring";

    return 0;
}
