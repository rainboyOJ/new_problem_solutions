/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>

int main(){
    int a,b;
    char c;
    scanf("%d%d",&a,&b);
    scanf("%c",&c);
    scanf("%c",&c);
    int ans ;
    if( c == '*')
        ans = a*b;
    else if( c == '/' && b == 0){
        printf("Divided by zero!");
        return 0;
    }
    else if( c == '/')
        ans = a/b;
    else if (c == '+')
        ans = a + b;
    else if (c == '-')
        ans = a - b;
    else {
        printf("Invalid operator!");
        return 0;
    }
    printf("%d\n",ans);

    return 0;
}
