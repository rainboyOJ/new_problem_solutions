#include <cstring>
#include <iostream>
char str[500];
int main(){
    int cnt = 0;
    while(1){
        int ans = (std::cin >> str) ? 1 : -1;
        if( ans == EOF)
            break;
        int len = strlen(str);
        int i;
        for (i=0;i<len;i++){
            if( str[i] >= '0' && str[i] <= '9')
                cnt++;
        }
    }
    std::cout << cnt;
    return 0;
}
