/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <bits/stdc++.h>
using namespace std;

int a,b,c;


int main(){
    scanf("%d %d %d",&a,&b,&c);
    int x_limit = c / a;
    int y_limit = c / b;
    int cnt=0;
    int i,j;
    for(i=0;i<=x_limit;i++){
        for(j=0;j<=y_limit;j++){
            if( a*i + b*j == c)
                cnt++;
        }
    }
    printf("%d\n",cnt);
    return 0;
}
