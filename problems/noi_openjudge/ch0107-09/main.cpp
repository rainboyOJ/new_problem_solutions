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
int idx = 1;

char _map[maxn];


int main(){
    char t;
    int i;
    for (i='a';i<='z';i++){
        _map[i] = i+1;
    }
    _map['z'] = 'a';
    for (i='A';i<='Z';i++){
        _map[i] = i+1;
    }
    _map['Z'] = 'A';
    while(1){
        int ans = scanf("%c",&t);
        if( t== '\n' || t == '\r' || ans == EOF)
            break;
        str[idx] = t;
        idx++;
    }
    idx--;
    for (i=1;i<=idx;i++){
        char c = str[i];
        if( ( c >='a' && c <='z') ||( c >='A' && c <='Z') )
            printf("%c",_map[c]);
        else
            printf("%c",c);
    }
    return 0;
}
