/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <bits/stdc++.h>
using namespace std;

int n;
int a[105];

bool vis[10005] = {0};


int main(){
    scanf("%d",&n);
    int i,j,k;
    for(i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    sort(a+1,a+n+1);
    int cnt = 0;
    for(i=3;i<=n;i++){
        for(j=1;j<=i-2;j++){
            for(k=j+1;k<=i-1;k++){
                if( a[j]+a[k] == a[i]){
                    vis[i] = 1;
                }
            }
        }
    }
    for(i=1;i<=10000;i++){
        if( vis[i])
            cnt++;
    }
    printf("%d\n",cnt);
    return 0;
}
