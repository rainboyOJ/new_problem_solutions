/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:51
 * update_at: 2026-10-06 09:51
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

typedef long long ll;

int n, c;
int on_lamps[105], off_lamps[105]; // 存储亮灯与灭灯约束
int on_cnt, off_cnt;

// 16 种奇偶组合对应的最少按压次数与前 6 盏灯的翻转图案（6 位二进制）
struct State {
    int press;   // 最少按压次数
    int pattern; // 前 6 盏灯的翻转图案，第 k 位为 1 表示第 k+1 盏灯被翻转
};

State states[16];
int state_cnt;

// 计算一组按钮奇偶对前 6 盏灯的翻转图案
int calc_pattern(int p1, int p2, int p3, int p4) {
    int mask = 0;
    for (int k = 0; k < 6; k++) {
        int flip = p1;
        if (k % 2 == 0) flip ^= p2; // 奇数号灯（k=0 对应灯号 1）
        else flip ^= p3;             // 偶数号灯
        if (k % 3 == 0) flip ^= p4;  // 3k+1 号灯（k=0,3 对应灯号 1,4）
        if (flip) mask |= 1 << k;
    }
    return mask;
}

// 预处理 16 种奇偶组合
void init_states() {
    state_cnt = 0;
    for (int p1 = 0; p1 <= 1; p1++)
    for (int p2 = 0; p2 <= 1; p2++)
    for (int p3 = 0; p3 <= 1; p3++)
    for (int p4 = 0; p4 <= 1; p4++) {
        states[state_cnt].press = p1 + p2 + p3 + p4;
        states[state_cnt].pattern = calc_pattern(p1, p2, p3, p4);
        state_cnt++;
    }
}

// 获取第 lamp 盏灯（1-based）的最终状态：初始全亮，被翻转则为 0
int lamp_state(int pattern, int lamp) {
    int pos = (lamp - 1) % 6;
    int flipped = (pattern >> pos) & 1;
    return 1 ^ flipped;
}

// 检查某个图案是否满足所有亮灯与灭灯约束
bool check(int pattern) {
    for (int i = 0; i < on_cnt; i++)
        if (lamp_state(pattern, on_lamps[i]) != 1) return false;
    for (int i = 0; i < off_cnt; i++)
        if (lamp_state(pattern, off_lamps[i]) != 0) return false;
    return true;
}

// 生成长度为 n 的灯状态字符串
string build_str(int pattern) {
    string s;
    s.resize(n);
    for (int i = 1; i <= n; i++)
        s[i - 1] = '0' + lamp_state(pattern, i);
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    init_states();

    cin >> n >> c;

    on_cnt = 0;
    while (true) {
        int x;
        cin >> x;
        if (x == -1) break;
        on_lamps[on_cnt++] = x;
    }

    off_cnt = 0;
    while (true) {
        int x;
        cin >> x;
        if (x == -1) break;
        off_lamps[off_cnt++] = x;
    }

    vector<string> ans;
    for (int i = 0; i < state_cnt; i++) {
        int press = states[i].press;
        int pattern = states[i].pattern;
        // 恰好按 c 次：最少次数不超过 c，且差值为偶数（多出来的次数成对抵消）
        if (press > c || (c - press) % 2 != 0) continue;
        if (!check(pattern)) continue;
        ans.push_back(build_str(pattern));
    }

    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end());

    if (ans.empty()) {
        cout << "IMPOSSIBLE\n";
    } else {
        for (size_t i = 0; i < ans.size(); i++)
            cout << ans[i] << "\n";
    }

    return 0;
}
