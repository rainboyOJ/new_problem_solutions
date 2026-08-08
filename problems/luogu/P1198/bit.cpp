#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXM = 200005;
const long long INF = -2e18; // 极小值，足够小即可

// tree[i] 维护 [i - lowbit(i) + 1, i] 的最大值
long long tree[MAXM];
long long a[MAXM]; // 原数组，用于查询时如果区间不匹配则降级查找
int M;
long long D;
int cnt = 0; // 当前数组实际长度

int lowbit(int x) {
    return x & -x;
}

// 修复后的 update：只做 max 更新，绝不覆盖
// 仅适用于 Append 模式（从左到右依次填充）
void update(int x, long long val) {
    for (int i = x; i <= M; i += lowbit(i)) {
        tree[i] = max(tree[i], val);
    }
}

// 区间查询 [L, R]
long long query(int L, int R) {
    long long res = INF;
    while (R >= L) {
        // 如果 tree[R] 覆盖的左边界没有越过 L，说明这一整段都在查询范围内
        if (R - lowbit(R) + 1 >= L) {
            res = max(res, tree[R]);
            R -= lowbit(R); // 跳过这一大段
        } else {
            // 如果 tree[R] 覆盖范围太长，超出了 L，就不能用 tree[R]
            // 只能使用原数组 a[R] 这个单点，然后向前挪一步
            res = max(res, a[R]);
            R--;
        }
    }
    return res;
}

int main() {
    // 优化 I/O
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> M >> D;

    // 初始化：tree 必须全部初始化为极小值
    fill(tree, tree + MAXM, INF);
    // a 数组其实不需要显式初始化为 INF，因为我们是按 cnt 指针读写的，但为了安全也可以初始化
    fill(a, a + MAXM, INF);

    long long t = 0; // 记录上一次查询结果

    for (int i = 0; i < M; i++) {
        char op;
        long long n; // 注意：输入的 n 可能是负数，且需要 long long
        cin >> op >> n;

        if (op == 'A') {
            // 题目公式：(n + t) % D
            long long val = (n + t) % D;
            cnt++;
            a[cnt] = val;     // 必须存原值
            update(cnt, val); // 更新 BIT
        } else {
            int L = n; // 这里 n 代表题目中的长度 L
            if (cnt == 0) {
                t = 0;
            } else {
                // 查询最后 L 个数 -> 区间 [cnt - L + 1, cnt]
                t = query(cnt - L + 1, cnt);
            }
            cout << t << "\n";
        }
    }

    return 0;
}
