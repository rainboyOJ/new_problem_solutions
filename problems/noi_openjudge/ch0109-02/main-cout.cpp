#include <cstring>
#include <iostream>


int n;
int fen;
char name[1000];
int max=-1;
char t[1000];
int main(){
    std::cin >> n;
    int i,j;
    for (i=1;i<=n;i++){
        std::cin >> fen;
        std::cin >> t;
        if( fen > max){
            max = fen;
            strcpy(name,t);
        }
    }
    std::cout << name << "\n";
    return 0;
}
