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
    int sum = 0;
    int min = 99999999;
    int i,t;
    scanf("%d",&n);
    for (i=1;i<=n;i++){
        scanf("%d",&t);
        if( sum < t)
            sum = t;
        if( min > t)
            min  =t;
    }
    printf("%d\n",sum-min);
    return 0;
}
