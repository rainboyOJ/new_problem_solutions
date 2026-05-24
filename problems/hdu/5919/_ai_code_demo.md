这是一个经典的 **可持久化线段树（Persistent Segment Tree，又称主席树）** 题目。

### 解题思路核心

1.  **问题转化**：

      * 题目要求在区间 $[L, R]$ 内，找到所有**不同数字**的**首次出现位置**。
      * 若一个位置 $i$ 是该数字在 $[L, R]$ 中的首次出现，通过预处理我们可以知道，这等价于：**该数字的上一次出现位置 $prev[i] < L$**。
      * 所以，我们需要寻找满足 $L \le i \le R$ 且 $prev[i] < L$ 的所有 $i$，计算它们的数量 $k$，然后找到第 $\lceil k/2 \rceil$ 小的 $i$。

2.  **构建主席树**：

      * 我们可以建立一棵以 **数组下标** 为值域的线段树。
      * **版本定义**：我们需要根据 $L$ 的变化来构建版本。
          * 定义 `root[L]` 表示当查询左端点为 $L$ 时的线段树状态。
          * 这就意味着 `root[L]` 这棵树里，包含了所有满足 $prev[i] < L$ 的下标 $i$。
      * **状态转移**：
          * `root[1]`：包含所有 $prev[i] < 1$（即 $prev[i]=0$，全局第一次出现）的下标。
          * 从 `root[L]` 到 `root[L+1]`：限制条件从 $prev[i] < L$ 变为 $prev[i] < L+1$。这意味着，我们多接纳了那些 $prev[i] = L$ 的下标。
          * 对于位置 $L$，它的下一个出现位置是 $next[L]$。显然，$next[L]$ 这个位置的 $prev$ 就是 $L$。
          * 所以：`root[L+1]` = 在 `root[L]` 的基础上，将位置 $next[L]$ 加入线段树。

3.  **查询步骤**：

      * 对于查询 $[L, R]$，我们使用版本 `root[L]`。
      * **第一步（算数量）**：在 `root[L]` 中查询区间 $[L, R]$ 的元素个数，记为 $k$。
          * 因为 `root[L]` 只包含 $prev < L$ 的点，且我们限制了查询范围 $[L, R]$，所以这就过滤出了所有符合条件的点。
      * **第二步（找中位数）**：我们需要找到这些点中第 $\lceil k/2 \rceil$ 小的下标。
          * 注意：`root[L]` 中包含了 $1 \dots L-1$ 的所有下标（因为它们的 $prev$ 肯定 $< L$）。
          * 所以我们在整棵树（值域 $1 \dots N$）中寻找第 $(L-1) + \lceil k/2 \rceil$ 小的元素，即为答案。

### C++ 代码实现

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

// 定义最大数组大小
const int MAXN = 200005;

// 主席树节点结构
struct Node {
    int l, r; // 左右子节点在数组中的索引
    int sum;  // 当前区间内存在的元素个数
} tree[MAXN * 40]; // 空间预估 N * logN * 2

int root[MAXN]; // 存储每个版本的根节点
int tot = 0;    // 节点分配计数器

int a[MAXN];       // 原数组
int next_pos[MAXN]; // next_pos[i] 表示 a[i] 下一次出现的位置
int last_pos[MAXN]; // 辅助数组，用于计算 next_pos

int n, m;

// 构建/更新线段树
// prev_node: 上一个版本的根节点
// node: 当前版本的根节点引用（会被赋值）
// l, r: 当前节点覆盖的区间范围
// pos: 需要插入的位置
void update(int prev_node, int &node, int l, int r, int pos) {
    node = ++tot;
    tree[node] = tree[prev_node]; // 复制上一个版本的信息
    tree[node].sum++;             // 当前节点计数 +1

    if (l == r) return;

    int mid = (l + r) >> 1;
    if (pos <= mid) {
        update(tree[prev_node].l, tree[node].l, l, mid, pos);
    } else {
        update(tree[prev_node].r, tree[node].r, mid + 1, r, pos);
    }
}

// 查询区间 [ql, qr] 内的元素个数
int query_sum(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return tree[node].sum;
    }
    int mid = (l + r) >> 1;
    int res = 0;
    if (ql <= mid) res += query_sum(tree[node].l, l, mid, ql, qr);
    if (qr > mid) res += query_sum(tree[node].r, mid + 1, r, ql, qr);
    return res;
}

// 查询线段树中第 k 小的下标
// 注意：是在整棵树范围内找第 k 个存在的下标
int query_kth(int node, int l, int r, int k) {
    if (l == r) return l;
    int mid = (l + r) >> 1;
    // 左子树存在的数量
    int left_count = tree[tree[node].l].sum;
    
    if (k <= left_count) {
        return query_kth(tree[node].l, l, mid, k);
    } else {
        return query_kth(tree[node].r, mid + 1, r, k - left_count);
    }
}

void solve(int case_num) {
    scanf("%d%d", &n, &m);
    
    // 初始化
    tot = 0;
    for (int i = 0; i <= n; i++) {
        last_pos[i] = n + 1; // 默认下一次出现位置为 n+1
        root[i] = 0;
    }

    // 读入数组
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    // 预处理 next_pos 数组
    // 从后往前扫，记录每个元素下一次出现的位置
    map<int, int> val_last_idx; 
    for (int i = n; i >= 1; i--) {
        if (val_last_idx.count(a[i])) {
            next_pos[i] = val_last_idx[a[i]];
        } else {
            next_pos[i] = n + 1;
        }
        val_last_idx[a[i]] = i;
    }

    // 构建主席树
    // root[L] 表示：对于查询左边界为 L 的情况，树中包含所有 prev[i] < L 的位置 i
    
    // 1. 先构建 root[1]。包含所有全局第一次出现的元素（即 prev[i] = 0 < 1）
    //    这些元素就是从前往后扫，每个值第一次出现的下标。
    //    利用刚才计算 next 的逻辑，我们可以通过 val_last_idx 里的最后状态获取第一次出现的下标？
    //    或者更简单的方法：我们按照 L 从 1 到 n 递推构建。
    
    // 重新规划构建逻辑：
    // root[1] 应该包含所有 i，满足 prev[i] < 1 (即 prev[i] == 0)。
    // root[L+1] = root[L] + { 满足 prev[i] == L 的下标 i }
    // 满足 prev[i] == L 的下标 i 其实就是 next_pos[L]。
    
    // 为了构建 root[1]，我们需要先把所有 prev[i]==0 的点插进去。
    // 这等价于：从空树开始，插入所有“第一次出现的位置”。
    // 也可以理解为：对 next_pos 构建。
    
    // 实际上更方便的写法是：
    // 初始化 root[1]：插入所有从左往右数第一次出现的数字位置。
    // 我们可以复用 val_last_idx (现在存的是每个数第一次出现的下标)
    
    // 必须清空 map 重新来一遍找“第一次”
    val_last_idx.clear();
    for (int i = 1; i <= n; i++) {
        if (val_last_idx.find(a[i]) == val_last_idx.end()) {
            // 这是 a[i] 第一次出现
            update(root[1], root[1], 1, n, i);
            val_last_idx[a[i]] = 1; 
        }
    }
    
    // 递推构建剩余版本
    // 从 root[L] 转移到 root[L+1]：
    // 意味着查询区间的左端点向右移动了一格，原来的左端点 L 变成了“过去”。
    // 那么原本 prev 为 L 的那个点 (即 next_pos[L])，现在满足 prev < L+1 了，需要加入树中。
    for (int i = 1; i < n; i++) {
        if (next_pos[i] <= n) {
            update(root[i], root[i+1], 1, n, next_pos[i]);
        } else {
            root[i+1] = root[i]; // 如果没有下一次出现，树结构不变
        }
    }

    printf("Case #%d:", case_num);
    
    int last_ans = 0;
    for (int i = 0; i < m; i++) {
        int l_prime, r_prime;
        scanf("%d%d", &l_prime, &r_prime);
        
        // 解密
        int l = (l_prime + last_ans) % n + 1;
        int r = (r_prime + last_ans) % n + 1;
        if (l > r) swap(l, r);
        
        // 核心查询逻辑
        // 1. 在 root[l] 版本中，查询 [l, r] 区间有多少个点
        //    这些点就是该区间内所有不同数字的首次出现位置
        int k_cnt = query_sum(root[l], 1, n, l, r);
        
        // 2. 题目要求第 ceil(k / 2) 个
        int target_k = (k_cnt + 1) / 2;
        
        // 3. 找到树中第 (l - 1 + target_k) 小的下标
        //    原因：root[l] 中包含了下标 1 到 l-1 的所有点（因为它们 prev < l 显然成立）
        //    我们只需要区间 [l, r] 里的第 target_k 个，加上前面的 l-1 个偏移量，
        //    就是在整棵树里的排名。
        int ans_idx = query_kth(root[l], 1, n, (l - 1) + target_k);
        
        last_ans = ans_idx;
        printf(" %d", last_ans);
    }
    printf("\n");
}

int main() {
    int t;
    if (scanf("%d", &t) == 1) {
        for (int i = 1; i <= t; i++) {
            solve(i);
        }
    }
    return 0;
}
```