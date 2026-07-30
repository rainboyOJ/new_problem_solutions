/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>

int m,n;
int map[200][200];
int main(){
    int i,j,sum=0;
    scanf("%d%d",&m,&n);
    for (i=1;i<=m;i++){
        for (j=1;j<=n;j++){
            scanf("%d",&map[i][j]);
            if( i == 1 || j == 1 || i == m || j==n){
                sum += map[i][j];
            }
        }
    }
    printf("%d\n",sum);
    return 0;
}
