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
int main(){
    int cnt = 0;
    while(1){
        int ans = scanf("%s",str);
        if( ans == EOF)
            break;
        int len = strlen(str);
        int i;
        for (i=0;i<len;i++){
            if( str[i] >= '0' && str[i] <= '9')
                cnt++;
        }
    }
    printf("%d",cnt);
    return 0;
}
