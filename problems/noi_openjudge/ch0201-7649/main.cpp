/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <bits/stdc++.h>
using namespace std;

int main(){
    int i,j;
    int sum=0;
    int n;
    scanf("%d",&n);

    for(i=1;1;i++){ // 数量
        sum += i;
        if( sum < n) continue;
        for(j=1;j<=i;j++) { //自己家的门牌
            if( sum-(j*2) == n){
                printf("%d %d\n",j,i);
                return 0;
            }
        }
        
    }
    return 0;
}
