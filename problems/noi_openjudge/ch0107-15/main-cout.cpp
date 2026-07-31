#include <cstring>
#include <iostream>

int n;
char str[500];
int main(){
    std::cin >> n;
    int i,j;
    for (i=1;i<=n;i++){
        std::cin >> str+1;
        int len = strlen(str+1);
        if( str[1] >='a' && str[1] <='z'){
            std::cout << (char)(str[1]+'A'-'a');
        }
        else
            std::cout << (char)(str[1]);

        for (j=2;j<=len;j++){
            if( str[j] >='A' && str[j] <='Z'){
                std::cout << (char)(str[j]+'a'-'A');
            }
            else
                std::cout << (char)(str[j]);

        }
        std::cout << "\n";
    }
    return 0;
}
