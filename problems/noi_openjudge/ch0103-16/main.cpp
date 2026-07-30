/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>
#include <cmath>

int main(){
    double xa,ya,xb,yb;
    scanf("%lf%lf%lf%lf",&xa,&ya,&xb,&yb);
    double ans = sqrt((xa-xb)*(xa-xb)+(ya-yb)*(ya-yb));
    printf("%0.3lf\n",ans);

    return 0;
}
