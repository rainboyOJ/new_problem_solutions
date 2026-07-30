/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>

int main(){
    int i;
    int n;
    scanf("%d",&n);
    int a=0,b=0,c=0;

    int t;
    for (i=1;i<=n;i++){
        scanf("%d",&t);
        if( t == 1)
            a++;
        if( t == 5)
            b++;
        if( t == 10)
            c++;
    }
    printf("%d\n",a);
    printf("%d\n",b);
    printf("%d\n",c);
    return 0;
}
