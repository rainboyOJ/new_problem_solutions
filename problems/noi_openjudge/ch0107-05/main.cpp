/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>
#include <cstring>
char str[500];
int idx = 1;

int main(){
    char t;
    while( scanf("%c",&t) != EOF){
        if( t == '\n' || t == '\r')
            break;
        str[idx] = t;
        idx++;
    }
    idx--;
    int i;
    for (i=1;i<idx;i++){
        //printf("%c %d\n",str[i],str[i]);
        printf("%c",str[i]+str[i+1]);
    }
    printf("%c",str[1]+str[idx]);
    return 0;
}
