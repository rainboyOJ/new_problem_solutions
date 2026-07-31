#include <cstring>
#include <iostream>

double rate;
char str1[505];
char str2[505];

int main(){
    std::cin >> rate;
    std::cin >> str1+1;
    std::cin >> str2+1;
    int i,cnt=0;
    int len = strlen(str1+1);
    for (i=1;i<=len;i++){
        if( str1[i] ==  str2[i]){
            cnt++;
        }
    }
    if( cnt*1.0 / len >= rate )
        std::cout << "yes";
    else
        std::cout << "no";
    return 0;
}
