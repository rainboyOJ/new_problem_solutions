#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, p;
int a[105];
int dp[105]; // dp[i] 表示以 a[i] 开头的最长非递减子序列长度
vector<int> path; // 记录当前路径

// 预处理 DP
void calc_dp() {
    for (int i = n - 1; i >= 0; i--) {
        dp[i] = 1;
        for (int j = i + 1; j < n; j++) {
            if (a[j] >= a[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
}

struct Node {
    int val; // 具体的数值
    int id;  // 原数组中的下标
};

// 比较函数：数值小的优先；数值相同，下标小的优先（虽然去重后下标次要，但排序需稳定）
bool cmp(const Node& x, const Node& y) {
    if (x.val != y.val) return x.val < y.val;
    return x.id < y.id;
}

// DFS 搜索
// last_idx: 上一个选取的元素下标（-1表示还没选）
// target_len: 本次搜索的目标长度
void dfs(int last_idx, int target_len) {
    if (p == 0) return; // 已经找够 P 个，直接退出

    int cur_len = path.size();
    if (cur_len == target_len) {
        // 找到了一个符合长度的序列，打印
        for (int i = 0; i < cur_len; i++) {
            cout << path[i] << (i == cur_len - 1 ? "" : " ");
        }
        cout << endl;
        p--;
        return;
    }

    // 收集所有可能的下一个候选项
    vector<Node> candidates;
    int start = last_idx + 1;
    
    for (int i = start; i < n; i++) {
        // 1. 满足非递减性质
        if (last_idx != -1 && a[i] < a[last_idx]) continue;
        
        // 2. 满足长度可行性（剪枝）
        // 如果从 i 开始的最长长度 + 当前已有长度 < 目标长度，则不能选 i
        if (dp[i] + cur_len < target_len) continue;

        candidates.push_back({a[i], i});
    }

    // 按数值排序，保证字典序最小
    sort(candidates.begin(), candidates.end(), cmp);

    // 遍历候选项
    for (int i = 0; i < candidates.size(); i++) {
        if (p == 0) return;

        // 去重：如果当前值的数值和上一个候选项相同，则跳过
        // 因为排序过，相同的数值是相邻的，且因为我们优先选了下标小的（在sort中隐含或自然顺序），
        // 如果下标小的那个能搜出结果，下标大的那个搜出的结果必然是重复的或者被包含的。
        // 这里的去重是为了防止同一层级选了数值相同的不同元素导致输出重复的序列。
        if (i > 0 && candidates[i].val == candidates[i-1].val) continue;

        // 递归
        path.push_back(candidates[i].val);
        dfs(candidates[i].id, target_len);
        path.pop_back(); // 回溯
    }
}

int main() {
    // 优化IO
    ios::sync_with_stdio(false);
    cin.tie(0);

    while (cin >> n >> p) {
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        calc_dp();

        // 外层循环：枚举长度
        for (int len = 1; len <= n; len++) {
            if (p == 0) break;
            path.clear();
            dfs(-1, len);
        }
        
        cout << endl; // 每个 case 后输出空行
    }
    return 0;
}

