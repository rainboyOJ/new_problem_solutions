/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 11:52
 * update_at: 2026-10-05 11:52
 */
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 1005;

int n;
int a[MAXN];
int stk[MAXN]; // 车站 C 模拟栈，stk[top] 为栈顶
int top;       // 栈顶指针，0 表示空栈

bool solvable() {
    int cur = 1; // 下一节还没进站的车厢编号
    for (int i = 1; i <= n; ++i) {
        int x = a[i];
        // 把 cur..x 依次入栈；x < cur 时无需入栈
        if (x >= cur) {
            for (int v = cur; v <= x; ++v) {
                stk[++top] = v;
            }
            cur = x + 1;
        }
        // 检查栈顶是否恰好为 x
        if (top == 0 || stk[top] != x) {
            return false;
        }
        --top; // 弹出 x
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n)) return 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    cout << (solvable() ? "YES" : "NO") << "\n";
    return 0;
}
