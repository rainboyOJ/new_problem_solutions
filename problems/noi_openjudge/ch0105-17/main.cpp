/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>

int main(){
    int k;
    int a=1,b=1,c;
    int i;
    scanf("%d",&k);
    if( k==1 || k == 2){
        printf("1");
        return 0;
    }

    for (i=3;i<=k;i++){
        c = a +b;
        a = b;
        b = c;
    }
    printf("%d\n",c);
    return 0;
}
