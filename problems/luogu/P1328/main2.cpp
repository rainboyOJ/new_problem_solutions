#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200 + 10;
int n, na, nb, a[MAXN], b[MAXN], cnta, cntb;
// vs[x][y] = 1 表示甲出 x、乙出 y 时甲赢，0 表示甲输或平
int vs[5][5] = {{0,0,1,1,0},{1,0,0,1,0},{0,1,0,0,1},{0,0,1,0,1},{1,1,0,0,0}};
int main()
{
    cin >> n >> na >> nb;
    for(int i = 0; i < na; i++) cin >> a[i];
    for(int i = 0; i < nb; i++) cin >> b[i];
    for(int i = 0; i < n; i++)
    {
        // 周期循环：a[i%na] 取到第 i 轮 A 的出手
        cnta += vs[a[i % na]][b[i % nb]];
        cntb += vs[b[i % nb]][a[i % na]];
    }
    cout << cnta << " " << cntb << endl;
    return 0;
}

