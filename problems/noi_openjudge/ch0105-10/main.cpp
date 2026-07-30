/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>

int main(){
    int m,n;
    scanf("%d%d",&m,&n);
    int i,sum = 0;
    for(i=m;i<=n;i++){
        if( i % 17 == 0)
            sum += i;
    }
    printf("%d\n",sum);
    return 0;
}
