/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>

int main(){
    int a[101];
    int n,m;
    int i;
    scanf("%d",&n);
    for (i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    scanf("%d",&m);
    int cnt =0;
    for (i=1;i<=n;i++){
        if( a[i] == m)
            cnt++;
    }
    printf("%d",cnt);
    return 0;
}
