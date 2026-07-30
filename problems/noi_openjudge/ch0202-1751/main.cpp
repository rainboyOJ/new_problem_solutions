/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>
#include <cmath>
int n;
int cnt = 0;
void dfs(int f,int a){
    int i,end= (int)sqrt(a);
    for(i=f;i<=end;i++){
        if( a % i ==0){
            int ret = a / i;
            if ( ret >= i){
                cnt++;
                dfs(i,ret);
            }
        }
    }
}
int main(){
    int i,t;
    scanf("%d",&n);
    for (i=1;i<=n;i++){
        scanf("%d",&t);
        cnt = 0;
        dfs(2,t);
        printf("%d\n",cnt+1);
    }
    return 0;
}
