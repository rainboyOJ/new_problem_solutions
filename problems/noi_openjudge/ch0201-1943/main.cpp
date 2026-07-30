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
    int a,b,c;
    for(a=2;a<100;a++){
        for(b=a;b<100;b++){
            for(c=b;c<=100;c++){
                if( a*a +b*b == c*c){
                    printf("%d*%d + %d*%d = %d*%d\n",a,a,b,b,c,c);
                }
            }
        }
    }
    return 0;
}
