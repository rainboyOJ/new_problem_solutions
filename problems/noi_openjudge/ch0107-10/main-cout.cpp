#include <cstring>
#include <iostream>
#define maxn 500

int n;
char str[maxn];
int idx=1;

char mi[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char ming[] = "VWXYZABCDEFGHIJKLMNOPQRSTU";

int main(){
    char t;
    int i;
    while(1){
        std::cin >> std::noskipws >> t;
        if( t == '\n' || t == '\r' || t == EOF)
            break;
        str[idx] = t;
        idx++;
    }
    idx--;

    for(i=1;i<=idx;i++){
        char c = str[i];
        if( c >= 'A' && c <= 'Z'){
            std::cout << (char)(ming[ c-'A']);
        }
        else
            std::cout << (char)(c);
    }
    return 0;
}
