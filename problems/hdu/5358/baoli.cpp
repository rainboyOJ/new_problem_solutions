#include <bits/stdc++.h>
#include <cmath>
using namespace std;
typedef long long ll;
const int maxn = 1e5+6;
ll a[maxn];
int n;

ll range_sum(int l,int r){ return a[r] - a[l-1]; }

void init() {
    std::cin >> n;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> a[i];
        a[i] += a[i-1]; //前缀和
    }
}

ll log2(int l,int r) {
    ll sum = range_sum(l, r);
    return log(sum)/ log(2);
}

ll baoli() {
    ll ret = 0;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        for(int j = i;j <= n ;++j ) // j: 1->n
        {
            ret += (log2(i,j)+1) * (i+j);
        }
    }
    return ret;
}

int main (int argc, char *argv[]) {
    int T;
    std::cin >> T;
    while (T--) {
        init();
        cout << baoli() << endl;
        
    }
    
    return 0;
}