/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>
#include <cstring>
int a[1000000] = {0};

int main(){
    a[0] = 1;
    int n;
    int i,j;
    int idx = 1;
    scanf("%d",&n);
    for (i=1;i<=n;i++){

        int jin = 0;
        for(j=0;j<idx;j++){
            int t= ( jin+a[j]+a[j]) % 10;
            jin = ( jin+a[j]+a[j]) / 10;
            a[j] = t;
        }
        if(jin){
            a[idx] = jin;
            idx++;
        }
    }
    for(i = idx-1;i>=0;i--)
        printf("%d",a[i]);
    return 0;
}
