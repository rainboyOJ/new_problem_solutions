#include <cstring>
#include <iostream>


int n;
int line;
char a[400][400];
char str[100000];

void xchg(char &i,char &j){
    char t = i;
    i = j;
    j = t;
}

void rev(char s[]){
    int i;
    for (i=1;i<=n/2;i++){
        xchg(s[i], s[n-i+1]);
    }
}

void init(){
    std::cin >> n;
    std::cin >> str+1;
    int i,j;
    int len = strlen(str+1);
    line = len / n;
    for (i=1;i<=line;i++){
        for (j=1;j<=n;j++){
            a[i][j] = str[(i-1)*n+j];
        }
    }
    for (i=1;i<=line;i++){
        if( i % 2 == 0)
            rev(a[i]);
    }

    /*
     *for (i=1;i<=line;i++){
     *    for (j=1;j<=n;j++){
     *        std::cout << (char)(a[i][j]) << " ";
     *    }
     *    std::cout << "\n";
     *}
     */

}
int main(){
    init();
    int i,j;
    for (j=1;j<=n;j++){
        for (i=1;i<=line;i++){
            std::cout << (char)(a[i][j]);
        }
    }
    return 0;
}
