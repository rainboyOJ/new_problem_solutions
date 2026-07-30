/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>


int main(){
    int i,n;
    int cnt=0;
    scanf("%d",&n);
    for (i=1;i<=n;i++){
        int t= i;
        while( t != 0){
            int a = t % 10;
            if( a == 1){
                cnt++;
            }
            t /= 10;
        }
    }
    printf("%d\n",cnt);
    return 0;
}
