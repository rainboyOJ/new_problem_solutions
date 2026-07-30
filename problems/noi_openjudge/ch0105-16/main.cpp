/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>

int main(){
    int n,k;
    scanf("%d%d",&n,&k);
    int i;
    double lilv = 1+k*0.01;
    double fangjia= 200;
    for (i=1;i<=20;i++){
        if( n*i*1.0 >= fangjia){
            break;
        }
        fangjia = fangjia * lilv;
    }
    if( i <= 20){
        printf("%d",i);
    }
    else
        printf("Impossible");
    return 0;
}
