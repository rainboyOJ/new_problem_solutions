#include <cstring>
#include <iostream>

char str[5000];
int idx = 0;

char tmp[105];
char max_word[105];
char min_word[105];


int flag  = 1;
int next_word(){
    while(1){
        if(str[flag] != ' ' )
            break;
        flag++;
    }

    if( flag == idx+1){
        return -1;
    }

    int cnt = 0;
    while(1) {
        if( str[flag] == ' ' || flag == idx+1){
            tmp[cnt] = '\0';
            return 0;
        }
        else {
            tmp[cnt++] = str[flag];
            flag++;
        }
    }

    return 0;
}

int main(){
    char t;
    while (std::cin >> std::noskipws >> t){
        if( t == ',')
            t = ' ';
        else if ( t == '\n' || t == '\r')
            break;
        str[++idx] = t;
    }

    int max_w = -1,min_w = 999999;

    while(1){
        if( next_word() == -1){
            break;
        }
        //std::cout << tmp << "\n";
        int len = strlen(tmp);

        if( max_w  < len){
            max_w = len ;
            strcpy(max_word,tmp);
        }

        if( min_w  > len){
            min_w = len ;
            strcpy(min_word,tmp);
        }
    }
    std::cout << max_word << "\n";
    std::cout << min_word;
    return 0;
}
