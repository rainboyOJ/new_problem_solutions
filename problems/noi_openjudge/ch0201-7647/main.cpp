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
int x;

int main(){
    scanf("%d%d%d",&a,&b,&c);
    int i;
    for(i=2;i<=1000005;i++){
        int t1 = a % i;
        int t2 = b % i;
        int t3 = c % i;
        if( t1 == t2 && t2 == t3 && t1 == t3){
            printf("%d\n",i);
            return 0;
        }
    }
    return 0;
}
