/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>

int main(){
    int k;
    scanf("%d",&k);
    double sum = 0,kk = k;
    int i;
    for (i=1;1;i++){
        sum += 1.0/i;
        if( sum > k){
            printf("%d",i);
            return 0;
        }
    }
    return 0;
}
