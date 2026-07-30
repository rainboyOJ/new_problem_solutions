/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>

int main(){
    double a;
    int n;
    int i;
    scanf("%lf",&a);
    scanf("%d",&n);
    for (i=1;i<=n;i++){
        a = a*1.001;
    }
    printf("%0.4lf",a);
    return 0;
}
