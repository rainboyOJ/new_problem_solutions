/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>
using namespace std;

int n,x;
int a[10005];
int main(){
    scanf("%d",&n);
    int i,j;
    for (i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    scanf("%d",&x);
    for (i=1;i<=n;i++){
        if( a[i] == x){
            printf("%d\n",i);
            return 0;
        }
    }
    printf("-1");
    return 0;
}
