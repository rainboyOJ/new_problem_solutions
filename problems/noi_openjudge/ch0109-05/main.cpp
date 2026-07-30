/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>
using namespace std;

#define inf 0x7f7f7f7f

int n;
int min = inf;
int max= -inf;

int main(){
    int n;
    int i,t;
    scanf("%d",&n);
    for (i=1;i<=n;i++){
        scanf("%d",&t);
        if( min  > t) 
            min = t;
        if( max < t)
            max = t;
    }
    printf("%d",max-min);
    return 0;
}
