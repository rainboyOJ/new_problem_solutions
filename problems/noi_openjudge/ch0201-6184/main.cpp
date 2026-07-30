/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <bits/stdc++.h>
using namespace std;

int n,k;
int a[1005];

int main(){
    scanf("%d%d",&n,&k);
    int i,j;
    for(i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for(i=1;i<=n;i++){
        for(j=i+1;j<=n;j++){
            if( a[i]+a[j] == k)
            {
                printf("yes");
                return 0;
            }
        }
    }
    printf("no");
    return 0;
}
