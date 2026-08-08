/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-02-01 17:05:24
 */
#include <bits/stdc++.h>
#include <functional>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
int n,m;
int a[maxn];
int r;

void init(){
    std::cin >> n;
    std::cin >> m;
    for(int i = 1;i <= n*m ;++i ) // i: 1->n
    {
        std::cin >> a[i];
    }
    r = a[1];
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    init();
    int cnt = n*m;
    std::sort(a+1,a+1+cnt,std::greater<int>());
    int pos;
    for(int i = 1;i <= cnt ;++i ) // i: 1->cnt
    {
        if( a[i] == r) {
            pos = i;
            break;
        }
    }

    int col = (pos-1)/ n + 1;

    int row = pos % n;
    if( row == 0) row = n;
    if( col % 2 == 0) {
        row = n+1 - row;
    }
    std::cout << col << " ";
    std::cout << row << "\n";
    // std::cout << row << " " << col << endl;
    
    return 0;
}
