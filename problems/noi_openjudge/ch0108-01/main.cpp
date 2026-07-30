/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>

int a[10][10];

int main(){
    int i,j;

    for (i=1;i<=5;i++){
        for (j=1;j<=5;j++){
            scanf("%d",&a[i][j]);
        }
    }
    int t1,t2;
    scanf("%d%d",&t1,&t2);
    for (i=1;i<=5;i++){
        int t;
        t = a[t1][i];
        a[t1][i] = a[t2][i];
        a[t2][i] = t;
    }

    for (i=1;i<=5;i++){
        for (j=1;j<=5;j++){
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
    return 0;
}
