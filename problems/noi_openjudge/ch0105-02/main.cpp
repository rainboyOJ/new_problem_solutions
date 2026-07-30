/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>

int main(){
    double t,sum = 0;
    int i;
    for(i=1;i<=12;i++){
        scanf("%lf",&t);
        sum += t; // => sum = sum +t
    }
    printf("$%0.2lf",sum / 12);
    return 0;
}
