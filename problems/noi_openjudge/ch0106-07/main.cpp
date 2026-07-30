/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>

/* 对差值进行记数 ,a[1] = 1*/
int cnt[3005] = {0};

int main(){
    int n;
    scanf("%d",&n);
    int i;
    int a,b;
    scanf("%d",&a);
    for (i=2;i<=n;i++){
        scanf("%d",&b);
        int cha = b - a;
        if( cha < 0)
            cha = -cha;
        cnt[cha]++;
        a = b;
    }

    for(i=1;i<=n-1;i++){
        if( cnt[i] != 1){
            printf("Not jolly");
            return 0;
        }
    }
    printf("Jolly");
    return 0;
}
