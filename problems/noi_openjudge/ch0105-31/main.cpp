/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>

int a[50005] = {0};
int main(){
    int n,m;
    int i,j;
    scanf("%d%d",&n,&m);

    for (i=2;i<=m;i++){
        for(j=i;j<=n;j+=i){
            a[j] = !a[j];
        }
    }
    for (i=1;i<=n;i++){
        if( !a[i]){
            printf("%d",i);
            break;
        }
    }
    for( i++; i<=n;i++){
        if( !a[i]){
            printf(",%d",i);
        }
    }
    return 0;
}
