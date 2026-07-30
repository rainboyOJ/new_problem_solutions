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
    int t,n,i,c;
    t=1;
    while(t--){
        scanf("%d",&n);
        for (i=n;i>=1;i--){
            scanf("%d",&c);
            c *= i;
            printf("%d ",c);
        }
        scanf("%d",&c);
        if( n == 0){
            printf("0");
        }
        printf("\n");
    }
    return 0;
}
