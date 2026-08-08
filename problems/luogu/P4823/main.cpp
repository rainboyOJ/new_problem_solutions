#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2005;

struct Dwarf {
    int a, b; // a 表示肩高，b 表示手臂长度
} d[MAXN];

int n, H;
long long total_a; // 所有小矮人肩高总和 T

bool cmp_dwarf(const Dwarf &lhs, const Dwarf &rhs) {
    return lhs.a + lhs.b < rhs.a + rhs.b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> d[i].a >> d[i].b;
        total_a += d[i].a;
    }
    cin >> H;

    // 按 a+b 从小到大排序。
    // 交换论证可以证明：如果两个人都要逃走，让 a+b 更小的人更早逃走不会更差。
    sort(d + 1, d + n + 1, cmp_dwarf);

    priority_queue<int> heap; // 已选小矮人的肩高，超限制时删掉最大的
    long long used = 0;       // 当前已选小矮人的肩高和

    for (int i = 1; i <= n; i++) {
        // 如果第 i 个小矮人作为当前顺序里最后一个逃走的人，
        // 那么已逃走肩高前缀 P 需要满足：
        // P <= T + a_i + b_i - H
        long long limit = total_a + d[i].a + d[i].b - H;
        if (limit < 0) {
            continue;
        }

        // 先尝试把当前小矮人加入答案集合。
        used += d[i].a;
        heap.push(d[i].a);

        // 如果当前前缀肩高和超过限制，
        // 贪心地删掉已选中肩高最大的那个人，最有利于保留更多人数。
        while (!heap.empty() && used > limit) {
            used -= heap.top();
            heap.pop();
        }
    }

    cout << (int) heap.size() << '\n';
    return 0;
}
