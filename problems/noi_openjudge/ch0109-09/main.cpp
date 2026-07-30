/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>
#include <cmath>
int n;
int cnt[10005] = {0};
int main(){
    scanf("%d",&n);
    int max=-1;
    int i,t;
    for (i=1;i<=n;i++){
        scanf("%d",&t);
        cnt[t]++;
        if( max < t)
            max =t;
    }
    for (i=0;i<=max;i++){
        printf("%d\n",cnt[i]);
    }
    return 0;
}
