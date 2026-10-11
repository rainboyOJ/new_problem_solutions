#include <bits/stdc++.h>
using namespace std;

// main.cpp：P7072 直播获奖（CSP-J 2020）
// 思路：成绩只有 0~600，用 cnt[s] 统计已出分人数，
//       每出一个分就从高分往低分累加，找到累计人数 >= 计划获奖人数的第一个分数，即分数线。
// 复杂度：每次询问最多扫 601 个分数，总复杂度 O(n * 600)。

const int MAXN = 100005;
const int MAXS = 600; // 成绩上界（题面成绩 0~600）

int n;       // 选手总数
int w;       // 获奖百分比（w%）
int a[MAXN]; // a[i] = 第 i 个出分选手的成绩
int cnt[MAXS + 5]; // cnt[s] = 已出分选手中成绩恰为 s 的人数（值域小，直接开桶）

// 求即时分数线：从高分往低分累加人数，
// 累计到第 need 名时所在的分数就是第 need 名的成绩（并列同分自然都获奖）。
int get_line(int need) {
    int sum = 0;
    for (int score = MAXS; score >= 0; score--) {
        sum += cnt[score];
        if (sum >= need) {
            return score;
        }
    }
    return 0; // 兜底：全部为 0 分时返回 0
}

// 逐个加入成绩并输出当前分数线
void solve() {
    for (int i = 1; i <= n; i++) {
        cnt[a[i]]++;                 // 第 i 个选手出分，进桶
        int need = i * w / 100;      // 计划获奖人数 floor(i * w%)
        if (need < 1) {
            need = 1;                // 至少 1 人获奖（题面 max(1, ...)）
        }
        int line = get_line(need);   // 当前获奖分数线
        if (i > 1) {
            cout << ' ';             // 相邻整数间用一个空格分隔
        }
        cout << line;
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); // 关掉同步，加快读入（本题 n 可达 1e5，影响不大但属习惯写法）

    cin >> n >> w;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    solve();

    return 0;
}
