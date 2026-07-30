/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>
int a[20][20];
int n,x,y;
int main(){
    scanf("%d%d%d",&n,&x,&y);
    int i,j;
    for (i=1;i<=n;i++){
        printf("(%d,%d) ",x,i);
    }
    printf("\n");

    for (i=1;i<=n;i++){
        printf("(%d,%d) ",i,y);
    }
    printf("\n");
    
    for (i=1;i<=n;i++){
        for (j=1;j<=n;j++){
            if( i-j == x - y){
                printf("(%d,%d) ",i,j);
                break;
            }
        }
    }
    printf("\n");

    for (i=n;i>=1;i--){
        for (j=1;j<=n;j++){
            if( i+j == x + y){
                printf("(%d,%d) ",i,j);
                break;
            }
        }
    }
    printf("\n");
    return 0;
}
