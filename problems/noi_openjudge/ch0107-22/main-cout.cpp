#include <cstring>
#include <iostream>


char email[500];

int n;
char str1[500];
char str2[500];
char str3[500];

int main(){
    std::cin >> email;
    std::cin >> n;
    int i,j;
    int cnt=0;
    for (i=1;i<=n;i++){
        std::cin >> str1;
        std::cin >> str2;
        std::cin >> str3;


        if( strcmp(str3,email) == 0){
            cnt++;
            std::cout << str1 << " ";
            int len = strlen(str2);
            for (j=0;j< len;j++){
                char c  = str2[j];
                if( c >='a' && c <='z'){
                    std::cout << (char)(c+'A'-'a');
                }
                else if(  c >='A' && c <='Z')
                    std::cout << (char)(c+'a'-'A');
                else
                    std::cout << (char)(c);
            }
            std::cout << "\n";
        }
    }
    if(!cnt){
        std::cout << "empty";
    }
    return 0;
}
