#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXM = 200005;
const long long INF = -2e18; // 极小值

// tree[i] 维护的是 [i - lowbit(i) + 1, i] 的最大值
long long tree[MAXM];
long long a[MAXM]; // 必须存储原数组，用于查询时降级处理
int M;
long long D;
int cnt = 0; // 当前数组长度

int lowbit(int x) {
    return x & -x;
}

// 单点更新：向后更新父节点
void update(int x, long long val) {
    // 首先更新原数组
    // 注意：如果是静态数组求RMQ，这里会有不同；
    // 但因为本题是Append模式，a[x]刚被填入，tree[x]会被初始化为val
    // 然后我们要去更新它的父节点
    
    // 初始化当前位置
    tree[x] = val; 
    
    // 这里的逻辑和标准BIT求和略有不同
    // 标准BIT是 +=，这里是不断取 max
    // 注意：因为我们是按顺序插入的，所以当 update(x) 时，
    // tree[x] 之前的节点都已经填好了。
    // 我们只需要把 x 的值汇报给后续的父节点即可。
    for (int i = x; i <= M; i += lowbit(i)) {
        tree[i] = max(tree[i], val);
    }
}

// 区间查询 [L, R]
long long query(int L, int R) {
    long long res = INF;
    while (R >= L) {
        // 核心逻辑：
        // 检查 tree[R] 覆盖的左边界是否在 L 里面
        // tree[R] 覆盖范围是 [R - lowbit(R) + 1, R]
        if (R - lowbit(R) + 1 >= L) {
            // 如果整个区间都在范围内，直接利用 tree 的值
            res = max(res, tree[R]);
            R -= lowbit(R); // 跳过这整段
        } else {
            // 如果 tree[R] 覆盖太远了（超出了 L），不能用 tree[R]
            // 只能用原数组 a[R] 这个单点，然后向前挪一步
            res = max(res, a[R]);
            R--;
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> M >> D;

    // 初始化 BIT 数组为极小值
    // 虽然不用 fill 也可以（因为是从左往右填），但为了安全
    fill(tree, tree + MAXM, INF);
    fill(a, a + MAXM, INF);

    long long t = 0; // 上一次查询结果

    for (int i = 0; i < M; i++) {
        char op;
        long long n;
        cin >> op >> n;

        if (op == 'A') {
            long long val = (n + t) % D;
            cnt++;
            a[cnt] = val; // 记录原值
            update(cnt, val); // 更新 BIT
        } else {
            int L = n;
            // 查询区间：[cnt - L + 1, cnt]
            if (cnt == 0) t = 0;
            else t = query(cnt - L + 1, cnt);
            cout << t << "\n";
        }
    }

    return 0;
}

