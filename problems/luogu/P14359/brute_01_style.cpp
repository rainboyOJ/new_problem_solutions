// brute_01_style.cpp：01 序列风格暴力，先枚举每个候选区间选或不选。
#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<int> a;
vector<int> prefix_xor; // prefix_xor[i] = a[1] ^ ... ^ a[i]

struct Segment {
    int l;
    int r;
};

vector<Segment> seg;
vector<int> choose_seg; // choose_seg[i] = 0/1，表示第 i 个候选区间不选/选
int answer;

bool intersect(const Segment &x, const Segment &y) {
    return max(x.l, y.l) <= min(x.r, y.r);
}

bool check() {
    for (int i = 0; i < (int)seg.size(); i++) {
        if (choose_seg[i] == 0) continue;
        for (int j = i + 1; j < (int)seg.size(); j++) {
            if (choose_seg[j] == 0) continue;
            if (intersect(seg[i], seg[j])) {
                return false;
            }
        }
    }
    return true;
}

int calc_answer() {
    int cnt = 0;
    for (int i = 0; i < (int)seg.size(); i++) {
        if (choose_seg[i] == 1) cnt++;
    }
    return cnt;
}

void dfs_choose(int dep) {
    if (dep == (int)seg.size()) {
        if (check()) {
            int value = calc_answer();
            if (answer < value) answer = value;
        }
        return;
    }

    // 第 dep 个候选区间的 01 选择：0 不选，1 选。
    for (int i = 0; i <= 1; i++) {
        choose_seg[dep] = i;
        dfs_choose(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    a.assign(n + 1, 0);
    prefix_xor.assign(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        prefix_xor[i] = prefix_xor[i - 1] ^ a[i];
    }

    for (int l = 1; l <= n; l++) {
        for (int r = l; r <= n; r++) {
            int value = prefix_xor[r] ^ prefix_xor[l - 1];
            if (value == k) {
                seg.push_back({l, r});
            }
        }
    }

    choose_seg.assign(seg.size(), 0);
    answer = 0;
    dfs_choose(0);

    cout << answer << '\n';
    return 0;
}
