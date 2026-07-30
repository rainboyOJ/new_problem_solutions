/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>
int l,m;
int a[10005] = {0};
int main(){
    scanf("%d%d",&l,&m);
    int i,j;
    for (i=1;i<=m;i++){
        int s,t;
        scanf("%d %d",&s,&t);
        for (j=s;j<=t;j++){
            a[j] = 1;
        }
    }
    int cnt = 0;
    for (i=0;i<=l;i++){
        if(!a[i]) cnt++;
    }
    printf("%d\n",cnt);
    return 0;
}
