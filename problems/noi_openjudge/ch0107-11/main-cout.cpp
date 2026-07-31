#include <iostream>
/* 
 *  AC
 *  BB
 *
 * */
#include <cstring>

char str1[500];
char str2[500];
char str3[500];
int _map[500] = {0};
int _map2[500] = {0};

int main(){
    std::cin >> str1+1;
    std::cin >> str2+1;
    std::cin >> str3+1;
    int len = strlen(str1+1);
    int i,j;
    for (i=1;i<=len;i++){
        char c = str1[i];
        char d = str2[i];
        if(_map[c] == 0 && _map2[d] == 0 ){
            _map[c] = d;
            _map2[d] = c;
        }
        else if(_map[c] != 0 && _map[c] != d){
            std::cout << "Failed";
            return 0;
        }
        else if( _map2[d] != 0 && _map2[d] != c){
            std::cout << "Failed";
            return 0;
        }
    }
    for (i='A';i<='Z';i++){
        if( _map[i] == 0){
            std::cout << "Failed";
            return 0;
        }
    }
    len = strlen(str3+1);
    for (i=1;i<=len;i++){
        std::cout << (char)(_map[ str3[i]]);
    }
    return 0;

}
