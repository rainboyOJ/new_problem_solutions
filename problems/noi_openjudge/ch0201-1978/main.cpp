/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <bits/stdc++.h>
using namespace std;

int a,b,c,d;
/* 是不是高峰 */
bool is_gaofeng(int day ,int hight_day,int cycle){
    if( day % cycle == hight_day % cycle)
        return 1;
    return 0;
}

int main(){
    scanf("%d%d%d%d",&a,&b,&c,&d);
    int i;
    for(i=d+1;1;i++){
        if(
is_gaofeng(i, a, 23) &&
is_gaofeng(i, b, 28) &&
is_gaofeng(i, c, 33) 
                )
        {
            printf("%d\n",i-d);
            return 0;
        }
    }
    return 0;
}
