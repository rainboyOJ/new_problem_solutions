/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>
#include <cstring>

int n;

int fac(int n){
    if( n ==2 || n==1)
        return 1;

    return fac(n-1)+fac(n-2);
}

int main(){
    scanf("%d",&n);
    int i,t;
    for(i=1;i<=n;i++){
        scanf("%d",&t);
        int ans = fac(t);
        printf("%d\n",ans);
    }
    return 0;
}
