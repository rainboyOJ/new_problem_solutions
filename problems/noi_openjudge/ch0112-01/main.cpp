/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>

int a,b;
char c;

void init(){
    scanf("%d",&a);

    while(1){
        scanf("%c",&c);
        if( c != ' ')
            break;
    }

    scanf("%d",&b);
}

int suan(int a,int b,char c){
    if( c == '/')
        return a /b;
    if( c == '%')
        return a % b;
    if( c == '*')
        return a * b;
    if( c == '+')
        return a + b;
    if( c == '-')
        return a - b;
}

int main(){
    init();
    int ans = suan(a,b,c);
    printf("%d\n",ans);

    return 0;
}
