#include <cstring>
#include <iostream>

char str[100005];
int cnt[500] = {0};

int main(){
    std::cin >> &str[1];
    int len = strlen(&str[1]);
    int i,j;
    for (i=1;i<=len;i++){
        cnt[ str[i] ]++;
    }
    for (i=1;i<=len;i++){
        if( cnt[ str[i] ] == 1){
            std::cout << (char)(str[i]) << "\n";
            return 0;
        }
    }
    std::cout << "no";
    return 0;
}
