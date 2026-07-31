#include <cstring>
#include <iostream>

char s[1000];
char tmp[1000];

bool is_hui_wen(){
    int len =  strlen(tmp);
    int mid = len /2;
    int i,j;
    for (i=0;i<mid;i++){
        if( tmp[i] != tmp[len-i-1]){
            return false;
        }
    }
    return true;
}
int main(){
    std::cin >> s+1;
    int len = strlen(s+1);
    int i,j;
    for(i=2;i<=len;i++){
        for (j=1;j<=len-i+1;j++){
            memset(tmp,0,sizeof(tmp));
            strncpy(tmp,s+j,i);
            //std::cout << tmp << "\n";
            if( is_hui_wen())
                std::cout << tmp << "\n";
        }
    }
    return 0;
}
