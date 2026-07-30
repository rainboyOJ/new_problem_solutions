/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <bits/stdc++.h>
using namespace std;

int a[205];
int cnt[205]  ={0} ;
int n,m;

int main(){
    scanf("%d%d",&n,&m);
    int i,t;
    for(i=1;i<=n;i++){
        scanf("%d",&t);
        a[i] = t;
        cnt[t]++;
    }
    for(i=1;i<=n;i++){
        if(cnt[ a[i] ] < 2)
            printf("BeiJu\n");
        else
            printf("%d\n",cnt[a[i]]-1);
    }
    return 0;
}
