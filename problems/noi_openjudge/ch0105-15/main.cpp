/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>

int main(){
    int r,m,y;
    scanf("%d%d%d",&r,&m,&y);
    double lilv = 1+ r*0.01;
    double result = m;
    int i;
    for (i=1;i<=y;i++){
        result = result*lilv;
    }
    printf("%d\n",(int)result);
    return 0;
}
