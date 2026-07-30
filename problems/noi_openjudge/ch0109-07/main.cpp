/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>
#include <cstring>

#define inf 0x7f7f7f7f

int n;
int a[200];
int max = -inf;
int main(){
    scanf("%d",&n);
    int i;
    for (i=1;i<=n;i++){
        scanf("%d",&a[i]);
        if( max  < a[i])
            max = a[i];
    }
    int sum = 0;
    for (i=1;i<=n;i++){
        if( max != a[i])
            sum += a[i];
    }
    printf("%d\n",sum);
    return 0;
}
