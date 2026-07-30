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
    int i,t;
    scanf("%d",&n);
    for (i=1;i<=n;i++){
        scanf("%d",&t);
        sum +=t;
    }
    printf("%d ",sum);
    printf("%0.5lf",sum*1.0/n);
    return 0;
}
