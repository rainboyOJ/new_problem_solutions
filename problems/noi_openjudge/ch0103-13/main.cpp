/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>

int main(){
    int a;
    scanf("%d",&a);
    int a1 = a % 10;
    a = a /10;
    int a2 = a % 10;
    a = a /10;
    printf("%d%d%d",a1,a2,a);
    return 0;
}
