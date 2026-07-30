/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>
#include <cmath>

bool is_prime(int n){
    int i;
    for(i=2;i<=(int)sqrt(n);i++ ){
        if( n % i ==0)
            return 0;
    }
    return 1;
}


int main(){
    int n;
    scanf("%d",&n);
    int i;
    for (i=1;i<=n;i++){
        if( n % i == 0 && is_prime(i)){
            int a = n / i;
            if( is_prime(a)){
                printf("%d\n",a);
                return 0;
            }
        }
    }
    return 0;
}
