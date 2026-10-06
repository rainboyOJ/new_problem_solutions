/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 02:18
 * update_at: 2026-10-06 02:18
 */
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 10005;

struct Ant {
    ll pos;   // 初始位置
    bool right; // true 为 R，false 为 L
} a[MAXN]; // 按输入顺序

struct State {
    ll pos;   // 直走 T 秒后的位置
    bool right; // 该轨迹自带方向
} final_state[MAXN];

int order[MAXN]; // 初始位置第 r 名对应的输入编号
int cnt_pos[MAXN]; // 计数辅助，按排名对应 final_state 的位置
ll pos_list[MAXN]; // 提取位置用于计数

int n;
ll L, T;

bool cmp_order(int x, int y) {
    return a[x].pos < a[y].pos;
}

bool cmp_state(const State &x, const State &y) {
    return x.pos < y.pos;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> L >> T >> n;
    for (int i = 0; i < n; i++) {
        char ch;
        cin >> a[i].pos >> ch;
        a[i].right = (ch == 'R');
    }

    // 计算每只蚂蚁直走 T 秒的轨迹（碰撞掉头等价于互换身份）
    for (int i = 0; i < n; i++) {
        final_state[i].pos = a[i].pos + (a[i].right ? T : -T);
        final_state[i].right = a[i].right;
    }

    // 按初始位置排序得到排名 → 编号的映射
    for (int i = 0; i < n; i++) order[i] = i;
    sort(order, order + n, cmp_order);

    // 按终态位置排序
    sort(final_state, final_state + n, cmp_state);

    // 统计终态位置出现次数，判断 Same
    for (int i = 0; i < n; i++) pos_list[i] = final_state[i].pos;
    for (int i = 0; i < n; i++) {
        cnt_pos[i] = 1;
        if (i > 0 && pos_list[i] == pos_list[i - 1]) cnt_pos[i] = cnt_pos[i - 1] + 1;
    }
    for (int i = n - 2; i >= 0; i--) {
        if (pos_list[i] == pos_list[i + 1]) cnt_pos[i] = cnt_pos[i + 1];
    }

    // 按输入编号顺序输出：先按排名填入结果，再按编号顺序打印
    string out[MAXN];
    for (int r = 0; r < n; r++) {
        int idx = order[r];
        ll p = final_state[r].pos;
        bool right = final_state[r].right;
        if (p < 0 || p > L) {
            out[idx] = "Down";
        } else if (cnt_pos[r] > 1) {
            out[idx] = to_string(p) + " Same";
        } else {
            out[idx] = to_string(p) + " " + (right ? "R" : "L");
        }
    }
    for (int i = 0; i < n; i++) {
        cout << out[i] << "\n";
    }

    return 0;
}
