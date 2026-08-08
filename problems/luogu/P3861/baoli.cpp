#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
int n;
const int mod = 998244353;
ll t;

ll ans;
ll rcd[20000];


void dfs(ll pre,ll num,int dep) {
    if( dep > 1) {
        ans+=1;
        // for(int i = 1;i < dep ;++i ) // i: 1->dep
        // {
        //     std::cout << rcd[i] << " x ";
        // }
        // std::cout << num << "\n";
    }

    for(ll i = pre+1; i<num ;i++)
    {

        // 不能拆分,不是因子
        if( num % i != 0) continue;

        // 剩余的元素不能超过当前(pre)
        if( num / i <= i) break;
        //优化
        if( i * i >= num) break;
        rcd[dep] = i;
        dfs(i,num / i,dep+1);
    }

}

int main (int argc, char *argv[]) {
    std::cin >> n;
    while (n--) {
        ans = 0;
        std::cin >> t;
        dfs(1,t,1);
        // std::cout << "ans =  "  ;
        std::cout << ans % mod << "\n";
    }

    
    return 0;
}
