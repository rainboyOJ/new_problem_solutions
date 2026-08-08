//Author by [Rainboy](https://github.com/rainboylvx)
//date: 2026-06-21 15:46:24

#include <bits/stdc++.h>
using namespace std;

int n;

struct node {
    int id;
    int spend;
};

// a[i][j][k] 表示 第i行的编号为j的星球 的第k个前驱
node a[105][105][105];
int cnta[105][105]; // cnta[i][j] 表示 第i行的编号为j的星球 前驱的数量

// f[i][j] = min(pre_ij + link-ij)
int f[105][105];
int k[105];

// int cnt[105][105];

void init(){
    std::cin >> n;

    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        int level = i;
        std::cin >> k[i];

        // 编号为j的星球
        for(int j = 1 ;j <= k[i]; j++) {
            while(1) {
                int pre_id, spend;
                cin >> pre_id ;
                if( pre_id == 0) break;

                cnta[i][j]++;
                int now_tot = cnta[i][j];

                std::cin >> spend;
                a[level][j][ now_tot ].spend = spend;
                a[level][j][ now_tot ].id = pre_id ;

            }
        }

    }
}

int main (int argc, char *argv[]) {
    init();

    // memset(f,0x3f,sizeof(f));
    for(int i = 0;i <= 104 ;++i ) // i: 0->104
    {
        for(int j = 0;j <= 104 ;++j ) // j: 0->104
        {
            f[i][j] = 100 * 1000;
        }
    }
    f[0][1] = 0;

    // dp
    for(int i = 1 ; i<= n;i++) { // level
        for(int j = 1;j <= k[i];j++) { //编号为j的星球
            for(int cnt  = 1 ; cnt <= cnta[i][j] ;cnt++) {

                int spend = a[i][j][cnt].spend;
                int id = a[i][j][cnt].id;

                f[i][j] = min(f[i][j], f[i-1][id] + spend);
            }

            // printf("f[%d][%d] = %d\n",i,j,f[i][j]);

        }
    }

    int ans = 100 * 1000;
    for(int j = 1 ;j <= k[n];j++) {
        if( ans > f[n][j]) ans = f[n][j];
    }
    std::cout << ans << "\n";
    return 0;
}
