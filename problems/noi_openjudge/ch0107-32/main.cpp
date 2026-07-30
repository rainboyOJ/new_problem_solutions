/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>
#include <cstring>

char s[1005];
int main(){
    scanf("%s",s+1);
    int cnt = 1;
    int len = strlen(s+1);
    int i;
    for (i=1;i<=len+1;i++){
        if( s[i] >='a' && s[i] <='z')
            s[i] = s[i] +'A'-'a';
    }
    
    for (i=2;i<=len+1;i++){
        if( s[i] == s[i-1]){
            cnt++;
        }
        else {
            printf("(%c,%d)",s[i-1],cnt);
            cnt = 1;
        }
    }
    return 0;
}
