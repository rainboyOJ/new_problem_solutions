#include <cstring>
#include <iostream>
#define maxn 500

int n;
char str[maxn];
char t1[10];
char t2[10];

int main(){
    std::cin >> str+1;
    std::cin >> t1+1;
    std::cin >> t2+1;
    int len = strlen(str+1);
    int i;
    for (i=1;i<=len;i++){
        if( str[i] == t1[1]){
            str[i] = t2[1];
        }
    }
    std::cout << str+1 << "\n";
    return 0;
}
