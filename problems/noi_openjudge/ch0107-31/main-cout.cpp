#include <cstring>
#include <iostream>

char s[1005];
int main(){
    std::cin >> s+1;
    int cnt = 1;
    int len = strlen(s+1);
    int i;
    for (i=2;i<=len+1;i++){
        if( s[i] == s[i-1]){
            cnt++;
        }
        else {
            std::cout << cnt;
            std::cout << (char)(s[i-1]);
            cnt = 1;
        }
    }
    return 0;
}
