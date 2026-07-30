/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>
#include <cstring>

char str[100];

char _map1[] = "defghijklmnopqrstuvwxyzabc";
char _map2[] = "DEFGHIJKLMNOPQRSTUVWXYZABC";

int main(){
    int i,len;
    scanf("%s",str+1);
    len = strlen(str+1);

    //反过来
    int mid = len /2;
    for(i=1;i<=mid;i++){
        char t = str[i];
        str[i] = str[len+1-i];
        str[len+1-i]=  t;
    }
    // 大小写反转
    for (i=1;i<=len;i++){
        if( str[i] >='a' && str[i] <='z'){
            str[i] += 'A'-'a';
        }
        else {
            str[i] += 'a'-'A';
        }
    }
    /* 输出 */
    for (i=1;i<=len;i++){
        if( str[i] >='a' && str[i] <='z'){
            printf("%c",_map1[ str[i] - 'a']);
        }
        else {
            printf("%c",_map2[ str[i] - 'A']);
        }
    }
    return 0;
}
