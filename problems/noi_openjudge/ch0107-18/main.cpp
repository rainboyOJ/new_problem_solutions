/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>
#include <cstring>


char str1[1000];
char str2[1000];
int main(){
    scanf("%s",str1);
    scanf("%s",str2);

    if( strstr(str1,str2) != NULL){
        printf("%s is substring of %s",str2,str1);
    }
    else if( strstr(str2,str1) != NULL){
        printf("%s is substring of %s",str1,str2);
    }
    else
        printf("No substring");

    return 0;
}
