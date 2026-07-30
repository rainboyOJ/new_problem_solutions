/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>


int main(){
    int n;
    scanf("%d",&n);
    double p = 1,q = 2;
    double sum = 0;
    int i;
    for (i=1;i<=n;i++){
        sum += q/p;
        double tq = q;
        q = q+p;
        p = tq;
    }
    printf("%0.4lf\n",sum);
    return 0;
}
