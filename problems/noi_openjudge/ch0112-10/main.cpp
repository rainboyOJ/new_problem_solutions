/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>

bool is_prime(int x){
    int i;
    for (i=2;i<x;i++){
        if( x % i == 0)
            return 0;
    }
    return 1;
}
int main(){
    int n;
    scanf("%d",&n);
    int i,cnt = 0;
    for (i=3;i<=n-2;i++){
        if( is_prime(i) && is_prime(i+2)){
            cnt++;
            printf("%d %d\n",i,i+2);
        }
    }
    if( !cnt)
        printf("empty");
    return 0;
}
