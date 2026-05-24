/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-22 19:13:56
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
int n,m;
int a[maxn];
ll pre[maxn];
ll f[maxn];
ll ans = 0;

void init(){

}

void dfs(int n,ll left){
    ll choose_w = m - left;
    ans = max(ans,choose_w);
    if( n == 0) return;


// > 2. 最优性剪枝: 如果当前已选质量 + 剩余所有砝码的总质量 $\le$ 当前已找到的最佳答案，直接回溯（因为不可能更新答案了）。
    if( choose_w + pre[n] <= ans) 
        return;


// > 3. 可行性剪枝: 如果当前已选质量 + 剩余所有砝码的总质量 $\le C$，那么直接把这些砝码全部加上，尝试更新最大值并回溯，无需再往下递归搜索每一个分支。
    if( choose_w + pre[n] <= m) {
        ans = max(ans,choose_w+ pre[n]);
        return;
    }


    dfs(n-1,left);
    if( left - a[n] > 0)
        dfs(n-1,left-a[n]);

}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    std::cin >> n >> m;
    int tot = 0;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> a[i];
        if( a[i] > m) break;
        pre[i] = pre[i-1] + a[i];
        tot++;
    }

    dfs(tot,m);
    std::cout << ans << "\n";


    
    return 0;
}
