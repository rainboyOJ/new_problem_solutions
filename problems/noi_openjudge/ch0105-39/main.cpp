/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>


int main(){
    int sum = 0;
    int i,n;
    scanf("%d",&n);
    for (i=1;i<=n;i++){
        if( i % 7 == 0) continue;
        bool flag= false;
        int t= i;
        while( t != 0){
            int a = t % 10;
            if( a == 7){
                flag = 1;
                break;
            }
            t /= 10;
        }
        if( flag) continue;
        sum += i*i;
    }
    printf("%d\n",sum);
    return 0;
}
