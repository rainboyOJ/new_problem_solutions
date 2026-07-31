#include <cstring>
#include <iostream>

int n;
int s[2000];
int main(){
    std::cin >> n;
    int i,cnt=1,max=1;
    for (i=1;i<=n;i++){
        std::cin >> s[i];
    }
    for (i=2;i<=n;i++){
        if(s[i] == s[i-1]){
            cnt++;
        }
        else {
            if( max < cnt) max = cnt;
            cnt = 1;
        }
    }
    if( max < cnt) max = cnt;
    std::cout << max << "\n";
    return 0;
}
