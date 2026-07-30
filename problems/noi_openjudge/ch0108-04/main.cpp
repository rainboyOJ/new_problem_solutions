/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>

int m,n;
int map[200][200];

bool is_ok(){
    int i,j;
    for (i=1;i<=n;i++){
        int cnt=0;
        for (j=1;j<=n;j++){
            if( map[i][j]) cnt++;
        }
        if( cnt % 2 != 0)
            return 0;
    }

    for (j=1;j<=n;j++){
        int cnt=0;
        for (i=1;i<=n;i++){
            if( map[i][j]) cnt++;
        }
        if( cnt % 2 != 0)
            return 0;

    }

    return 1;
}
int main(){
    scanf("%d",&n);
    int i,j;
    for (i=1;i<=n;i++){
        for (j=1;j<=n;j++){
            scanf("%d",&map[i][j]);
        }
    }

    if( is_ok()){
        printf("OK");
        return 0;
    }
    for (i=1;i<=n;i++){
        for (j=1;j<=n;j++){
            map[i][j] = !map[i][j];
            if( is_ok()){
                printf("%d %d\n",i,j);
                return 0;
            }
            map[i][j] = !map[i][j];
        }
    }
    printf("Corrupt");

    return 0;
}
