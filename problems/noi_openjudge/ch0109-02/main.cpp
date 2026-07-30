/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>
#include <cstring>

using namespace std;

int n;
int fen;
char name[1000];
int max=-1;
char t[1000];
int main(){
    scanf("%d",&n);
    int i,j;
    for (i=1;i<=n;i++){
        scanf("%d",&fen);
        scanf("%s",t);
        if( fen > max){
            max = fen;
            strcpy(name,t);
        }
    }
    printf("%s\n",name);
    return 0;
}
