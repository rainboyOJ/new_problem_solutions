/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <bits/stdc++.h>
using namespace std;


int n,m;

int main(){
    scanf("%d%d",&n,&m);
    int i;
    for(i=1;i<m;i++){
        if( 
                n % i == 0 &&
                n % (m-i) == 0
                ){
            printf("%d\n",i);
            return 0;
        }
    }
    printf("-1");
    return 0;
}
