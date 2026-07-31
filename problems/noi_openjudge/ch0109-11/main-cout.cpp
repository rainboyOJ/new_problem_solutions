#include <cstring>
#include <iostream>

int n;
char str[2000];
int main(){
    std::cin >> n;
    std::cin >> str+1;
    int len = strlen(str+1);
    int i,cnt=1;
    for (i=2;i<=len;i++){
        if( str[i] == str[i-1]){
            cnt++;
        }
        else {
            cnt = 1;
        }
        if( cnt >=n){
            std::cout << (char)(str[i]);
            return 0;
        }
    }
    std::cout << "No";
    return 0;
}
