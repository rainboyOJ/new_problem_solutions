/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>
#include <cstring>


char str[1000][100];
int main(){
    int i = 0;
    while(1){
        int ret = scanf("%s",str[++i]);
        if ( ret == EOF)
            break;
    }
    i--;
    char *s1 = str[i-1];
    char *s2 = str[i];
    int j;
    for(j=1;j<=i-2;j++){
        if( strcmp(str[j],str[i-1]) == 0){
            printf("%s ",s2);
        }
        else
            printf("%s ",str[j]);
    }
    return 0;
}
