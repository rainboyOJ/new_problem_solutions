#include <cstring>
#include <iostream>

char s1[1005];
int main(){
    std::cin >> s1+1;
    int len = strlen(s1+1);
    int mid = len /2;
    int i;
    for(i=1;i<=mid;i++){
        if( s1[i] != s1[len+1-i]){
            std::cout << "no";
            return 0;
        }
    }
    std::cout << "yes";
    return 0;
}
