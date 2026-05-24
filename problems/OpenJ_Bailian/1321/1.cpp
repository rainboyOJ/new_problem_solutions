/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-23 19:12:10
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
int n,k;
int a[maxn];
int ans;

char board[10][10];

int col[20];

void put(int x,int y) {
    col[y] = 1;
    board[x][y] = 'x';
}
void unput(int x,int y) {
    col[y] = 0;
    board[x][y] = '#';
}
void print_chess() {
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        for(int j = 1;j <= n ;++j ) // j: 1->n
        {
            cout << board[i][j];
        }
        std::cout << "\n";
    }

}

void dfs(int dep,int left_chess) {
    if( left_chess == 0) {
        // print_chess();
        // cout << "--------\n";
        ans++;
        return;
    }
    if( dep > n ) { return; }

    // 不放
    dfs(dep+1,left_chess);

    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        if( board[dep][i] == '.') continue;
        if( col[i] == 0) {

            put(dep,i);
            dfs(dep+1,left_chess - 1);
            unput(dep,i);
        }
    }

}

void solve() {
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        for(int j = 1;j <= n ;++j ) // j: 1->n
        {
            cin >> board[i][j];
        }
    }
    ans = 0;
    dfs(1,k);
    std::cout << ans << "\n";
}
signed main () {
    ios::sync_with_stdio(false); cin.tie(0);

    while (1) {
        std::cin >> n >> k;
        if( n == -1 && k == -1) break;
        solve();
        
    }
    
    return 0;
}
