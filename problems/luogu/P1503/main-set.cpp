/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-15 22:15
 * update_at: 2026-09-15 22:15
 *
 * P1503 鬼子进村
 * 解法：用 std::set 维护被摧毁的房子（断点）。
 *       查询 x 时用 upper_bound 找到右侧最近断点 R，再往前挪一格得到左侧断点 L，
 *       答案就是 R - L - 1。
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

const int maxn = 5e5 + 5;

int n, m;
bool destroyed[maxn]; // destroyed[i] 表示 i 号房子当前是否被摧毁
int stk[maxn], top_;  // 摧毁历史，R 操作按后进先出恢复
set<int> s;           // 存储所有被摧毁的房子编号

void read_data() {
    cin >> n >> m;
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(0);
    read_data();

    // 虚拟边界：0 和 n+1 永远是被摧毁的
    s.insert(0);
    s.insert(n + 1);

    for (int i = 1; i <= m; ++i) {
        string op;
        cin >> op;
        if (op == "D") {
            int x;
            cin >> x;
            destroyed[x] = true;
            s.insert(x);
            stk[++top_] = x;
        } else if (op == "R") {
            int x = stk[top_--];
            destroyed[x] = false;
            s.erase(x);
        } else { // Q
            int x;
            cin >> x;
            if (destroyed[x]) {
                cout << 0 << "\n";
            } else {
                // 右侧最近的断点
                set<int>::iterator it = s.upper_bound(x);
                int R = *it;
                --it; // 往前一格就是左侧最近的断点
                int L = *it;
                cout << R - L - 1 << "\n";
            }
        }
    }

    return 0;
}
