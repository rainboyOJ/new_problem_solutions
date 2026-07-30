/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>
#include <cstring>

char s1[1005];
int main(){
    scanf("%s",s1+1);
    int len = strlen(s1+1);
    int mid = len /2;
    int i;
    for(i=1;i<=mid;i++){
        if( s1[i] != s1[len+1-i]){
            printf("no");
            return 0;
        }
    }
    printf("yes");
    return 0;
}
