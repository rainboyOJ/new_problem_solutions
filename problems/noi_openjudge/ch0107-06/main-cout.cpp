#include <cstring>
#include <iostream>
#define maxn 500

int n;
char str[maxn];

int main(){
    std::cin >> str+1;
    int i;
    int len = strlen(str+1);
    if( str[1] >= '0' && str[1] <='9'){
            std::cout << "no";
            return 0;
    }
    for (i=1;i<=len;i++){
        char c = str[i];
        if( (c >= 'a' && c <='z' ) || (c >='A' && c <='Z') || c== '_' || ( str[i] >= '0' && str[i] <='9'))
            ;
        else{
            std::cout << "no";
            return 0;
        }
    }
    std::cout << "yes";
    return 0;
}
