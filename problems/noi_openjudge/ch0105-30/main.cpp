/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>


int main(){
    int n,k;
    scanf("%d%d",&n,&k);
    if( n % 19 != 0){
        printf("NO");
        return 0;
    }
    int cnt = 0;
    while( n !=0){
        if( n % 10 == 3)
            cnt++;
        n /= 10;
    }
    if( cnt == k)
        printf("YES");
    else
        printf("NO");
    return 0;
}
