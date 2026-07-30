/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>
int main(){
    double h;
    scanf("%lf",&h);
    double sum = -h;
    double fang = 0;
    int i;
    for (i=1;i<=10;i++){
        sum += 2*h;
        h = h /2;
    }
    printf("%g\n",sum);
    printf("%g",h);
    return 0;
}
