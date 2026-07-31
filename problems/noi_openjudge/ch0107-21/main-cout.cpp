#include <cstring>
#include <iostream>


char str[1000][100];
int main(){
    int i = 0;
    while(1){
        int ret = (std::cin >> str[++i]) ? 1 : -1;
        if ( ret == EOF)
            break;
    }
    i--;
    char *s1 = str[i-1];
    char *s2 = str[i];
    int j;
    for(j=1;j<=i-2;j++){
        if( strcmp(str[j],str[i-1]) == 0){
            std::cout << s2 << " ";
        }
        else
            std::cout << str[j] << " ";
    }
    return 0;
}
