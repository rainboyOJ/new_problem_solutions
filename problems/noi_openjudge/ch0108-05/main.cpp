/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>

int a[10][10];

int main(){
    int i,j;
    for (i=1;i<=5;i++){
        for (j=1;j<=5;j++){
            scanf("%d",&a[i][j]);
        }
    }
    for (i=1;i<=5;i++){
        int max = -1;
        int pos;
        for (j=1;j<=5;j++){
            if( a[i][j] > max ){
                max = a[i][j];
                pos = j;
            }
        }
        bool flag = true;
        for(j=1;j<=5;j++){
            if(a[j][pos] < max){
                flag = false;
                break;
            }
        }
        if( flag == true){
            printf("%d %d %d",i,pos,max);
            return 0;
        }
    }
    printf("not found");
    return 0;
}
