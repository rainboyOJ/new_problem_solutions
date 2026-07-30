/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <bits/stdc++.h>
using namespace std;

int n;

int main(){
    scanf("%d",&n);
    int i,j,k;
    int ans=0;
    for (i=0;i<=n;i++){
        for (j=0;j<=n;j++){
            for (k=0;k<=n;k++){
                if( (i+j) % 2== 0&&
                        (j+k) % 3 == 0 &&
                        (i+j+k) % 5 == 0){
                    ans = max(ans, i+j+k);
                }
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
