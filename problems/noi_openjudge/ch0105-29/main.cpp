/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>

int main(){
    int n;
    scanf("%d",&n);
    if( n < 0){
        n = -n;
        printf("-");
    }

    bool is_first_zeor = true;
    while( n != 0){
        int ret = n % 10;
        n /= 10;
        if( ret == 0 && is_first_zeor )
            continue;
        is_first_zeor = 0;
        printf("%d",ret);
    }
    return 0;
}
