/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>
#include <cstring>

char str[1000];
int cnt=0;
int main(){
    char t;
    while( scanf("%c",&t)!=EOF ){
        str[++cnt] = t;
    }
    bool is_first_blank = true;
    int i;
    for (i=1;i<=cnt;i++){
        if( str[i] == ' ' && is_first_blank){
            printf(" ");
            is_first_blank = false;
        }
        else if ( str[i] != ' '){
            printf("%c",str[i]);
            is_first_blank = true;
        }
    }
    return 0;
}
