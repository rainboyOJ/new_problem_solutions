/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>
#include <cstring>

int n;


//进行操作
void getAns(int x){

    int cnt = 0; //计算用

    //找到第一个 符合条件的1
    int i;
    for(i=0;i<32;i++){
        if(  (x &(1<<i)) !=0 && ( x & (1<<(i+1))) == 0){
            //fined
            x = ( x | (1<<(i+1))); //第i+1位置1

            int t = ~((1<<(i+1))-1); // 1111000这种样式
            x = x & t; //后面全置0

            t = (1<<cnt)-1;
            x = x | t;
            break;
        }
        else if((x &(1<<i)) !=0)
            cnt++;
    }

    printf("%d\n",x);

}

int main(){
    
    while(1){
        scanf("%d",&n);
        if( n == 0)  break;

        getAns(n);


    }
    return 0;
}
