/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>
int n;
int age[205]={0};
int main(){
    int i,t;
    scanf("%d",&n);
    for (i=1;i<=n;i++){
        scanf("%d",&t);
        age[t]++;
    }
    int a,b,sum;
    a = 0,b=18,sum=0;
    for(i=a;i<=b;i++){
        sum += age[i];
    }
    printf("%0.2lf%%\n",sum*1.0 / n * 100);
    a = 19,b=35,sum=0;
    for(i=a;i<=b;i++){
        sum += age[i];
    }
    printf("%0.2lf%%\n",sum*1.0 / n * 100);
    a = 36,b=60,sum=0;
    for(i=a;i<=b;i++){
        sum += age[i];
    }
    printf("%0.2lf%%\n",sum*1.0 / n * 100);
    a = 61,b=200,sum=0;
    for(i=a;i<=b;i++){
        sum += age[i];
    }
    printf("%0.2lf%%\n",sum*1.0 / n * 100);
    return 0;
}
