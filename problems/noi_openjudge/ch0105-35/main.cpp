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
    double i,s = 1;
    double sum=1;
    for (i=1;i<=n;i++){
        s = s*i;
        sum += 1.0/s;
    }
    printf("%0.10f\n",sum);

    return 0;
}
