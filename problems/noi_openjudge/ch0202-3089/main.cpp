/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>

int fab(int n){
    if( n== 0 || n == 1)
        return 1;
    return fab(n-1)+fab(n-2);
}
int main(){
    int t;
    while(scanf("%d",&t) != EOF){
        int ans = fab(t);
        printf("%d\n",ans);
    }
    return 0;
}
