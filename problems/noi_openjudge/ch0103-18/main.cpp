/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
/* 
 * an = a1 +(n-1)*(a2-a1)
 * */
#include <cstdio>

int main(){
    int a1,a2,n;
    scanf("%d%d",&a1,&a2);
    scanf("%d",&n);
    int ans = a1+(n-1)*(a2-a1);
    printf("%d\n",ans);
    return 0;
}
