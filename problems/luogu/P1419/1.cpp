/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * date: 2025-12-24 19:40:34
 * * 算法核心：二分答案 (Binary Search on Answer) + 单调队列优化 (Monotonic Queue Optimization)
 * 复杂度：O(N * log(Answer_Range / EPS))
 */
#include <bits/stdc++.h>
#include <iomanip>
#include <ios>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
int n,s,t;
int a[maxn];
double b[maxn], sum[maxn]; // b: 减去二分值后的数组, sum: b数组的前缀和

const double EPS = 1e-5; // 精度控制，用于实数二分结束条件

// 构造辅助数组 b 和前缀和 sum
// 核心思想：原式 (sum[i]-sum[j])/(i-j) >= est 
// 变形为：(sum[i]-sum[j]) >= est * (i-j)
// 移项得：(sum[i] - i*est) - (sum[j] - j*est) >= 0
// 这里的 b[k] = a[k] - est 其实就是把每个元素先减去平均值
// 只要找到一段区间和 >= 0，就说明平均值 >= est
void build_arr_b(double est) {
    for(int i = 1; i <= n; ++i) 
    {
        b[i] = a[i] - est;          // 每个元素减去猜测的平均值
        sum[i] = sum[i-1] + b[i];   // 计算新数组的前缀和
    }
}

// 辅助函数：计算区间和 (当前代码未直接使用，保留作为逻辑参考)
double sum_range(int l,int r) { return sum[r] - sum[l-1]; }

void init(){
    std::cin >> n;
    std::cin >> s >> t;
    for(int i = 1; i <= n; ++i) 
    {
        std::cin >> a[i];
    }
}

// 检查是否存在一个长度在 [S, T] 之间的子段，其平均值 >= est
bool check(double est) {

    build_arr_b(est); // 根据当前的猜测值 est 重构前缀和

    // 单调队列 q，存放的是下标 k
    // 队列性质：队列内的 sum[k] 单调递增
    // 队首 q.front() 始终是当前合法范围内 sum 值最小的那个下标
    deque<int> q; 

    // i 代表子段的【结束位置】
    // 子段范围是 [j+1, i]，其中 j 是我们在单调队列里维护的【前驱位置】(即 sum[j] 中的 j)
    // 长度限制：S <= i - j <= T  ==>  i - T <= j <= i - S
    for(int i = s; i <= n; ++i) 
    {
        // 1. 入队操作：尝试将新的候选前驱 (i-s) 加入队列
        // 只有当 i >= s 时，(i-s) 才能构成至少长度为 s 的区间，是一个合法的起点前驱
        int candidate = i - s;
        
        // 维护单调性：如果新来的 sum[candidate] 比队尾更小，
        // 那么队尾那些 sum 值大的元素永远不可能成为“最优解”（减数越小，结果越大），直接踢出
        while( !q.empty() && sum[q.back()] >= sum[candidate] )
            q.pop_back();
        
        q.push_back(candidate);

        // 2. 出队操作：移除“过期”的元素
        // 如果队首的下标 < i-t，说明以该下标为起点的段落长度 > t，超出了最大长度限制
        while( !q.empty() && q.front() < i-t )
            q.pop_front(); 

        // 3. 判定操作
        if( !q.empty() ) {
            // sum[i] - sum[q.front()] 表示以 i 结尾，以 q.front()+1 开始的区间和
            // 如果这个区间和 >= 0，说明平均值 >= est，check 成功
            if( sum[i] - sum[q.front()] >= 0 )
                return true;
        }
    }

    return false; // 遍历完所有可能并未找到，说明 est 偏大
}

// 二分查找答案
double bs_find(double l, double r) {
    while (r - l > EPS) { // 当区间足够小时停止
        double mid = (l + r) / 2;
        if( check(mid) )
            l = mid; // mid 可行，尝试更大的平均值 (答案在右边)
        else
            r = mid; // mid 不可行，答案在左边
    }
    return l;
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    init();

    // 确定二分范围：题目数据范围 -1e4 到 1e4
    double max_val = 1e4 + 5; 
    double min_val = -1e4 - 5;

    double ans = bs_find(min_val, max_val);

    cout << fixed << setprecision(3) << ans << "\n";

    return 0;
}