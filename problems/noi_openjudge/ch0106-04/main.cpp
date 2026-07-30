/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>
int a[105];
int n;
int main(){
    scanf("%d",&n);
    int i;
    for (i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for (i=n;i>=1;i--){
        printf("%d ",a[i]);
    }
    return 0;
}
