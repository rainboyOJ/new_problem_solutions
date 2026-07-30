/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
/* 
 *  AC
 *  BB
 *
 * */
#include <cstdio>
#include <cstring>

char str1[500];
char str2[500];
char str3[500];
int _map[500] = {0};
int _map2[500] = {0};

int main(){
    scanf("%s",str1+1);
    scanf("%s",str2+1);
    scanf("%s",str3+1);
    int len = strlen(str1+1);
    int i,j;
    for (i=1;i<=len;i++){
        char c = str1[i];
        char d = str2[i];
        if(_map[c] == 0 && _map2[d] == 0 ){
            _map[c] = d;
            _map2[d] = c;
        }
        else if(_map[c] != 0 && _map[c] != d){
            printf("Failed");
            return 0;
        }
        else if( _map2[d] != 0 && _map2[d] != c){
            printf("Failed");
            return 0;
        }
    }
    for (i='A';i<='Z';i++){
        if( _map[i] == 0){
            printf("Failed");
            return 0;
        }
    }
    len = strlen(str3+1);
    for (i=1;i<=len;i++){
        printf("%c",_map[ str3[i]]);
    }
    return 0;

}
