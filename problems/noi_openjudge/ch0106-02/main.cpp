/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>

int n=10,h;
int a[10+5];

int main(){
    int i;
    for (i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    scanf("%d",&h);
    h += 30;
    int cnt = 0;
    for (i=1;i<=n;i++){
        if( h >= a[i]){
            cnt++;
        }
    }
    printf("%d",cnt);

    return 0;
}
