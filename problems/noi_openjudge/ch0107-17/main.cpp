/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>
#include <cstring>

char content[2000];
char str1[1000];
char str2[1000];
int idx1=0;
int idx2=0;
int main(){
    char t; 
    // 读取所有的内容
    while( scanf("%c",&t) != EOF){
        content[++idx1]= t;
    }
    idx1 = 0;
    int all_len = strlen(content+1);
    int i,j=0;
    for (i=1;i<=all_len;i++){
        char c = content[i];
        if( c == '\n' || c == '\r')
            break;
        else if(c != ' ') {
            if( c >='A' && c <='Z')
                str1[++j] = c+'a'-'A';
            else
                str1[++j] = c;
        }
    }
    str1[j]  ='\0';

    // 略过剩下的 \n \r
    for(;1;i++){
        if( content[i] == '\n' ||  content[i] == '\r' )
            ;
        else
            break;
    }

    j=0;
    for(;i<=all_len;i++){
        char c = content[i];
        if( c == '\n' || c == '\r')
            break;
        else if(c != ' ') {
            if( c >='A' && c <='Z')
                str2[++j] = c+'a'-'A';
            else
                str2[++j] = c;
        }
    }
    str2[j] = '\0';

    int ans =  strcmp(str1,str2);
    if( ans == 0)
        printf("YES");
    else 
        printf("NO");
    return 0;
}
