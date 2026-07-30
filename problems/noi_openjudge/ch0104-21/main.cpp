/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio> 
int main(){
    int n,x,y;
    scanf("%d%d%d",&n,&x,&y);
    int ans = y / x;
    if( y % x !=0)
        ans++;
    if( n - ans <0)
        printf("0");
    else
        printf("%d\n",n-ans);
    return 0;
}
