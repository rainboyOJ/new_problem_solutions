#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 998244353;

long long n;
long long ans;
vector<long long> factors;

// 邻接表：adj[i] 存储 pair{子因子下标 d_idx, 剩余部分下标 rem_idx}
// 只有满足 factors[d_idx] * factors[d_idx] <= factors[i] 的 d_idx 才会存入
vector<pair<int, int>> adj[7000]; 

// 1. 获取所有因子
void get_factors(long long x) {
    factors.clear();
    for (long long i = 1; i * i <= x; ++i) {
        if (x % i == 0) {
            factors.push_back(i); // 这里包含 1，方便下标对应，但在 DFS 中我们会跳过
            if (i * i != x) {
                factors.push_back(x / i);
            }
        }
    }
    sort(factors.begin(), factors.end());
}

// 2. 预处理因子之间的整除关系 (构建图)
// 这一步能消除 DFS 中所有的取模和二分查找
void build_graph() {
    int m = factors.size();
    for (int i = 0; i < m; ++i) {
        adj[i].clear();
        // 我们只需要遍历到 sqrt(factors[i])，因为 DFS 中有剪枝要求
        // j 从 1 开始，跳过因子 1 (下标0)
        for (int j = 1; j < i; ++j) {
            long long f = factors[j];
            
            // 剪枝条件：f * f > current 也就是 factors[j]^2 > factors[i] 时停止
            // 因为 factors 是有序的，后面肯定更大
            if (f > factors[i] / f) break; // 防止溢出的写法，等价于 f*f > factors[i]
            
            if (factors[i] % f == 0) {
                long long rem = factors[i] / f;
                
                // 找到 rem 在 factors 中的下标
                //由于 rem 肯定是因子，且 rem >= f，我们可以用 lower_bound 快速找到
                // 实际上因为是在预处理，这里用 lower_bound 耗时可以接受
                int rem_idx = lower_bound(factors.begin(), factors.end(), rem) - factors.begin();
                
                // 存入：用因子 j (下标) 去除 i (下标)，剩余 rem_idx (下标)
                adj[i].push_back({j, rem_idx});
            }
        }
    }
}

// 3. 极速 DFS
// curr_idx: 当前剩余数值在 factors 中的下标
// min_idx:  下一个因子允许的最小下标 (保证严格递增)
void dfs(int curr_idx, int min_idx) {
    // 只要进入这里，说明前面的分解是合法的。
    // 此时 remaining (即 factors[curr_idx]) 本身作为一个因子，也是一种情况。
    // 这里需要判断：剩余的这个数是否满足“严格大于上一个因子”。
    // 这一点由调用方的 min_idx 保证。
    // 如果 curr_idx >= min_idx，说明剩余的数比上一个因子大（或相等，但我们传的是+1所以是严格大），合法。
    if (curr_idx >= min_idx) {
        ans++;
    }

    // 遍历预处理好的合法因子列表
    // adj[curr_idx] 里存的都是满足 d*d <= current 的真因子
    for (auto &edge : adj[curr_idx]) {
        int d_idx = edge.first;
        int rem_idx = edge.second;

        // 严格递增条件：选取的因子下标必须 >= min_idx
        if (d_idx < min_idx) continue;
        
        // 递归：不需要取模，不需要除法，直接传下标
        // 下一层要求的因子下标必须 >= d_idx + 1
        dfs(rem_idx, d_idx + 1);
    }
}

void solve() {
    cin >> n;
    ans = 0;
    
    // 1. 找因子
    get_factors(n);
    
    // 2. 建图 (预处理)
    build_graph();
    
    // 3. 搜索
    // 目标是分解 n (它是 factors 的最后一个元素，下标 size-1)
    // 最小因子下标要求从 1 开始 (跳过因子 1)
    dfs(factors.size() - 1, 1);
    
    // 答案减 1 (去掉 n 本身没被拆分的情况)
    cout << (ans - 1 + MOD) % MOD << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
