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
int main(){
    scanf("%s",str);
    int len =  strlen(str);
    printf("%d",len);
    
    while(1){
        int ret = scanf("%s",str);
        if( ret == EOF) break;
        len =  strlen(str);
        printf(",%d",len);
    }
    return 0;
}
