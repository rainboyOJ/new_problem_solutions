/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>
#include <cstring>
#define maxn 500

int n;
char str[maxn];
char t1[10];
char t2[10];

int main(){
    scanf("%s",str+1);
    scanf("%s",t1+1);
    scanf("%s",t2+1);
    int len = strlen(str+1);
    int i;
    for (i=1;i<=len;i++){
        if( str[i] == t1[1]){
            str[i] = t2[1];
        }
    }
    printf("%s\n",str+1);
    return 0;
}
