/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 15:57
 * update_at: 2026-08-10 21:51
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

int n;
long long m;
string direction;
long long capacity[MAXN]; // capacity[i]：第 i 头奶牛桶的容量，也就是初始牛奶量

int pre_pos(int x) {
    if (x == 1) return n;
    return x - 1;
}

int next_pos(int x) {
    if (x == n) return 1;
    return x + 1;
}

char dir_at(int x) {
    return direction[x - 1];
}

// 对于 RL 中左边的 R 点，统计它左侧连续 R 链的容量和，不包含这个溢出点本身。
long long sum_left_r_chain(int pos) {
    long long sum = 0;
    int cur = pre_pos(pos);
    while (dir_at(cur) == 'R') {
        sum += capacity[cur];
        cur = pre_pos(cur);
    }
    return sum;
}

// 对于 RL 中右边的 L 点，统计它右侧连续 L 链的容量和，不包含这个溢出点本身。
long long sum_right_l_chain(int pos) {
    long long sum = 0;
    int cur = next_pos(pos);
    while (dir_at(cur) == 'L') {
        sum += capacity[cur];
        cur = next_pos(cur);
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    cin >> direction;

    long long answer = 0;
    for (int i = 1; i <= n; i++) {
        cin >> capacity[i];
        answer += capacity[i];
    }

    for (int i = 1; i <= n; i++) {
        int j = next_pos(i);
        if (dir_at(i) == 'R' && dir_at(j) == 'L') {
            long long left_loss = sum_left_r_chain(i);
            long long right_loss = sum_right_l_chain(j);

            answer -= min(left_loss, m);
            answer -= min(right_loss, m);
        }
    }

    cout << answer << '\n';
    return 0;
}
