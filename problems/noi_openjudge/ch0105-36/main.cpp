/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>


int main(){
    double x;
    int n;
    scanf("%lf",&x);
    scanf("%d",&n);
    double t =1;
    double ans = 1;
    int i;
    for (i=1;i<=n;i++){
        t *=x;
        ans += t;
    }
    printf("%.2lf\n",ans);
    return 0;
}
