/**
 * Author by Rainboy blog: https://blog.roj.ac.cn github : https://github.com/rainboylvx
 * date: 2025-12-21 16:21:31
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
int n,p,s;
int w[maxn],v[maxn];
int min_file = 1e9;
int max_file = 0;
int tot;

void init(){
    std::cin >> n >> p >> s;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> w[i] >> v[i];
        if( min_file > w[i]) min_file = w[i];
        if( max_file < w[i]) max_file = w[i];
        tot += v[i];
    }
}

int f[1005];
int dp(int port) {
    memset(f,0,sizeof(f));
    for(int i =1;i<=n;i++){
        if( w[i] > port ) continue; 
        for(int j = s;j>= w[i];j--) {
            f[j] = max(f[j],f[j-w[i]] + v[i]);
        }
    }
    return f[s];
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    init();

    if( p == 0) {
        std::cout << 0 << "\n";
        return 0;
    }
    if( p > tot ) {
        std::cout << "No Solution!" << "\n";
        return 0;
    }

    // 枚举接口
    for(int i = min_file ; i<=max_file ;i++) {
        int res = dp(i);
        if( res >=p ) {
            std::cout << i << "\n";
            return 0;
        }
    }

    std::cout << "No Solution!" << "\n";

    
    return 0;
}
