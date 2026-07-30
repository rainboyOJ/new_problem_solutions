/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>
#include <cstring>

double rate;
char str1[505];
char str2[505];

int main(){
    scanf("%lf",&rate);
    scanf("%s",str1+1);
    scanf("%s",str2+1);
    int i,cnt=0;
    int len = strlen(str1+1);
    for (i=1;i<=len;i++){
        if( str1[i] ==  str2[i]){
            cnt++;
        }
    }
    if( cnt*1.0 / len >= rate )
        printf("yes");
    else
        printf("no");
    return 0;
}
