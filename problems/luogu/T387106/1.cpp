/**
 * Author by Rainboy blog: https://blog.roj.ac.cn github : https://github.com/rainboylvx
 * date: 2025-12-07 16:52:56
 * oj: luogu-T387106
 * title: 
 * description: 
 */
#include <bits/stdc++.h>
#include <random>
using namespace std;
typedef  long long ll;
const int maxn = 2e6+5;
int n,m;
int w[maxn];
int f[maxn];
int choose[105][maxn]; // choose[i][j] 表示前i个物品,在容量j的时候,有没有选 第i个物品

int cnt;
int ch_id[105];

void init(){
    std::cin >> n >> m;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> w[i];
    }

}

signed main (int argc, char *argv[]) {
    ios::sync_with_stdio(false); cin.tie(0);
    init();
    f[0] = 1; // 1 表示装满
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        for(int j = m;j >= w[i] ;--j ) // j: m->w
        {
            // if( f[j] == 0 && f[j-w[i]] == 1) {
            if( f[j-w[i]] == 1) {
                choose[i][j] = 1;
                f[j] = 1;
            } 
        }
    }
    // cout << f[m] << endl;

    int tm = m;

    for(int i = n;i>=1;i--) {
        if( tm ==0 || f[tm] == 0) break;
        if( choose[i][tm] == 1) {
            ch_id[++cnt] = i;
            tm -= w[i];
        }
    }

    if(f[tm] != 1) {
        cout <<"not found\n";
        return 0;
    }

    for(int i = cnt ;i>=1 ;i--) {
        int id = ch_id[i];
        // cout << id << endl;
        cout << "number:" << id << "  ";
        cout << "weight:"<< w[id] << "\n";

    }
    
    return 0;
}
