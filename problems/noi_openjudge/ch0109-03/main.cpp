/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>

int main(){
    int a,b;
    
    int c =0;
    int max = -1;
    int i;
    for(i=1;i<=7;i++){
        scanf("%d%d",&a,&b);

        if( a+b > 8){
            if( a+b -8 > max){
                max= a+b-8;
                c=i;
            }
        }
    }
	printf("%d",c);
    return 0;
}
