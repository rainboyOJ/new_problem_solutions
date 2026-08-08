#include <bits/stdc++.h>
using namespace std;


// f[i][h][t] = 表明前i个物品,在体积h,质量t的时候得到的最大值
// f[i][h][t] =max( f[i-1][h][t] , f[i-1][h-h[i]][t-t[i]] + k[i]
int f[55][505][505]; 
int h[505];
int t[505];
int k[505];
int H,T,n;
int main (int argc, char *argv[]) {
    std::cin >> H >> T;
    std::cin >> n;

    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> h[i] >> t[i] >> k[i];
    }

    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        for(int j = 0;j <= H ;++j ) // j: 0->H
        {
            for(int l = 0;l <= T ;++l ) // l: 0->T
            {
                f[i][j][l] = f[i-1][j][l];

                if( h[i] <= j && t[i] <= l)
                {
                    f[i][j][l] = max( f[i][j][l], f[i-1][j-h[i]][l-t[i]] + k[i]);
                }
            }
        }
    }
    std::cout << f[n][H][T] << "\n";
    
    return 0;
}

