/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
/* 
 * int      4
 * double   8
 * float    4
 * bool     1
 * char     1
 *
 * sizeof
 * */
#include <cstdio>

// sizeof 不是函数
// #define sizeof(int) 4
int main(){
    int a = sizeof(int);
    int b = sizeof(short);
    printf("%d %d",a,b);
    return 0;
}
