/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:13
 * update_at: 2026-10-05 12:13
 */

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef long long ll;

const int MAXN = 10005; // n <= 10^4

ll A[MAXN]; // A[i]：第 i 个函数的二次项系数
ll B[MAXN]; // B[i]：第 i 个函数的一次项系数
ll C[MAXN]; // C[i]：第 i 个函数的常数项

// 堆元素：一个候选函数值，以及它来自哪个函数、对应哪个自变量。
// idx 是数组下标，n <= 10^4，用 int 即可。
struct Node {
    ll value;
    int idx;
    ll x;
};

// 小根堆的比较：函数值小的优先，值相同时函数编号小的优先（顺序不影响答案）。
struct Cmp {
    bool operator()(const Node &p, const Node &q) const {
        if (p.value != q.value) {
            return p.value > q.value;
        }
        return p.idx > q.idx;
    }
};

priority_queue<Node, vector<Node>, Cmp> heap; // 保存每个函数"指针"位置上的候选值

// 计算第 i 个函数在 x 处的取值 F_i(x) = A_i*x^2 + B_i*x + C_i。
ll calc(int i, ll x) {
    return A[i] * x * x + B[i] * x + C[i];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m;
    cin >> n >> m;

    // 系数全为正，F_i(x+1) - F_i(x) = A_i*(2x+1) + B_i > 0，
    // 所以每个函数在 x >= 1 上严格递增，可看成 n 条有序链做多路归并。
    for (int i = 1; i <= n; i++) {
        cin >> A[i] >> B[i] >> C[i];
        Node first;
        first.value = calc(i, 1);
        first.idx = i;
        first.x = 1;
        heap.push(first);
    }

    // 弹出 m 次堆顶即为前 m 小的函数值；每弹出一个，就把该函数的下一个候选压回堆。
    for (ll k = 1; k <= m; k++) {
        Node top = heap.top();
        heap.pop();

        if (k > 1) {
            cout << ' ';
        }
        cout << top.value;

        ll nxt = top.x + 1;
        Node next_node;
        next_node.value = calc(top.idx, nxt);
        next_node.idx = top.idx;
        next_node.x = nxt;
        heap.push(next_node);
    }
    cout << '\n';

    return 0;
}
