#include <bits/stdc++.h>
using namespace std;

struct Block {
    int h;
    int c;
    int a;
};

int n;
vector<Block> blocks;
vector<int> choose_count; // choose_count[i] 表示第 i 种方块用了多少个
int answer = 0;

bool cmp_block(const Block &x, const Block &y) {
    return x.a < y.a;
}

bool check() {
    int cur_height = 0;
    for (int i = 0; i < n; i++) {
        cur_height += choose_count[i] * blocks[i].h;
        if (cur_height > blocks[i].a) {
            return false;
        }
    }
    return true;
}

int calc_height() {
    int height = 0;
    for (int i = 0; i < n; i++) {
        height += choose_count[i] * blocks[i].h;
    }
    return height;
}

// 暴力枚举每种方块用了多少次，叶子节点统一检查高度限制。
void dfs_choose(int dep) {
    if (dep == n) {
        if (check()) {
            int value = calc_height();
            if (answer < value) answer = value;
        }
        return;
    }

    for (int cnt = 0; cnt <= blocks[dep].c; cnt++) {
        choose_count[dep] = cnt;
        dfs_choose(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    blocks.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> blocks[i].h >> blocks[i].a >> blocks[i].c;
    }

    sort(blocks.begin(), blocks.end(), cmp_block);

    choose_count.assign(n, 0);
    dfs_choose(0);
    cout << answer << '\n';

    return 0;
}
