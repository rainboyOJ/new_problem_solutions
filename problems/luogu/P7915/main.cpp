/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 22:33
 * update_at: 2026-10-01 22:33
 */
// main.cpp：固定第一个选择后，把剩余序列分成两段，贪心构造字典序最小方案。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1000005;

int n;                 // n <= 5e5，int 足够
int a[MAXN];           // a[i]：给定序列，值域 1..n，int 足够
int first_pos[MAXN];   // first_pos[x]：数值 x 第一次出现的位置
int second_pos[MAXN];  // second_pos[x]：数值 x 第二次出现的位置

// 固定第一步取左端（choose_left_first=true）或右端（false）后，
// 尝试构造字典序最小的回文操作串，成功写入 answer 并返回 true。
bool build_answer(bool choose_left_first, string &answer) {
    int total = 2 * n;
    int first_value;
    int match_pos;
    char first_op, last_op;
    int l1, r1, l2, r2;

    if (choose_left_first) {
        first_value = a[1];
        match_pos = (first_pos[first_value] == 1) ? second_pos[first_value] : first_pos[first_value];
        first_op = 'L';
        last_op = 'L';
        l1 = 2;
        r1 = match_pos - 1;
        l2 = match_pos + 1;
        r2 = total;
    } else {
        first_value = a[total];
        match_pos = (first_pos[first_value] == total) ? second_pos[first_value] : first_pos[first_value];
        first_op = 'R';
        // 最后只剩一个元素时，L/R 都能取走；为了字典序取 L。
        last_op = 'L';
        l1 = 1;
        r1 = match_pos - 1;
        l2 = match_pos + 1;
        r2 = total - 1;
    }

    string left_ops, right_ops;
    left_ops.push_back(first_op);

    // 每步为回文前半部分取一个数（left_ops），并预定对称位置的匹配数（right_ops）。
    // 当前可取的前端只可能是左段左端 l1 或右段右端 r2；
    // 匹配数只可能是左段右端 r1 或右段左端 l2，共四种配对。
    // 为字典序最小，能让当前操作为 L 时优先选 L。
    for (int step = 1; step <= n - 1; step++) {
        bool done = false;

        if (l1 <= r1) {
            if (l1 < r1 && a[l1] == a[r1]) {
                // 配对：左段左端 <-> 左段右端，两个操作都是 L。
                left_ops.push_back('L');
                right_ops.push_back('L');
                l1++;
                r1--;
                done = true;
            } else if (l2 <= r2 && a[l1] == a[l2]) {
                // 配对：左段左端 <-> 右段左端，前半取 L、后半取 R。
                left_ops.push_back('L');
                right_ops.push_back('R');
                l1++;
                l2++;
                done = true;
            }
        }

        if (!done && l2 <= r2) {
            if (l1 <= r1 && a[r2] == a[r1]) {
                // 配对：右段右端 <-> 左段右端，前半取 R、后半取 L。
                left_ops.push_back('R');
                right_ops.push_back('L');
                r2--;
                r1--;
                done = true;
            } else if (l2 < r2 && a[r2] == a[l2]) {
                // 配对：右段右端 <-> 右段左端，两个操作都是 R。
                left_ops.push_back('R');
                right_ops.push_back('R');
                r2--;
                l2++;
                done = true;
            }
        }

        if (!done) {
            return false;
        }
    }

    if (l1 <= r1 || l2 <= r2) {
        return false;
    }

    answer = left_ops;
    // 后半部分是反向记录的，倒序拼回去才是实际操作顺序。
    for (int i = (int)right_ops.size() - 1; i >= 0; i--) {
        answer.push_back(right_ops[i]);
    }
    answer.push_back(last_op);
    return true;
}

// 求解单组测试数据：先试 L 开头，再试 R 开头，都失败输出 -1。
void solve_one() {
    cin >> n;
    int total = 2 * n;
    for (int i = 1; i <= n; i++) {
        first_pos[i] = second_pos[i] = 0;
    }

    for (int i = 1; i <= total; i++) {
        cin >> a[i];
        if (first_pos[a[i]] == 0) {
            first_pos[a[i]] = i;
        } else {
            second_pos[a[i]] = i;
        }
    }

    string answer;
    if (build_answer(true, answer)) {
        cout << answer << '\n';
        return;
    }
    if (build_answer(false, answer)) {
        cout << answer << '\n';
        return;
    }
    cout << -1 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        solve_one();
    }

    return 0;
}
