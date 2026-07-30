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
    scanf("%lf",&x);
    if (  x < 5){
        printf("%0.3lf",-x+2.5);
    }
    else if( x < 10)
        printf("%0.3lf",2-1.5*(x-3)*(x-3));
    else 
        printf("%0.3lf",x/2-1.5);
    return 0;
}
