/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>
int main(){
    int a,b;
    scanf("%d%d",&a,&b);
    if(( a < 60 && b >= 60) || ( b < 60 && a >= 60 ))
        printf("1");
    else
        printf("0");
    return 0;
}
