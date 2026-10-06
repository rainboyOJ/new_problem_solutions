/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:12
 * update_at: 2026-10-06 09:12
 */
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 20005;         // 原始文本长度上限
const int MAXM = 2 * MAXN + 5;  // Manacher 插字符后的串长上限

char raw[MAXN];       // 原始文本，按读入顺序保存（含空格、标点、换行）
int raw_len;
char letter[MAXN];    // 过滤出的纯字母串，统一转小写
int pos[MAXN];        // pos[k] = letter[k] 在 raw 中的下标
int letter_cnt;

char t[MAXM];         // 插入 '#' 分隔符后的 Manacher 串，两端放哨兵 '^' 与 '$'
int p[MAXM];          // p[i] = 以 t[i] 为中心的回文半径

// 把纯字母串插成 ^#a#b#...#$ 的形式，返回新串长度。
int build_manacher_string() {
    int n = 0;
    t[n++] = '^';
    for (int i = 0; i < letter_cnt; i++) {
        t[n++] = '#';
        t[n++] = letter[i];
    }
    t[n++] = '#';
    t[n++] = '$';
    return n;
}

// 在字母串上跑 Manacher，返回最长回文长度，并写回字母串中的起止下标。
int manacher(int &best_l, int &best_r) {
    int m = build_manacher_string();
    p[0] = 0;  // p[0] 对应哨兵 '^'，不会被访问
    int center = 0;  // 当前回文覆盖最右的对称中心
    int right = 0;   // 当前回文覆盖到的最右边界
    int max_len = 0;
    int best_start = 0;

    for (int i = 1; i < m - 1; i++) {
        if (i < right) {
            // 利用对称性取初始半径，再暴力向两边扩展
            int mirror = 2 * center - i;
            p[i] = min(right - i, p[mirror]);
        } else {
            p[i] = 0;
        }
        while (t[i + 1 + p[i]] == t[i - 1 - p[i]]) {
            p[i]++;
        }
        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }
        // 严格大于保证等长时取字母串中最靠前的回文
        if (p[i] > max_len) {
            max_len = p[i];
            best_start = (i - p[i]) / 2;  // 映射回字母串中的起始下标
        }
    }
    best_l = best_start;
    best_r = best_start + max_len - 1;
    return max_len;
}

void solve() {
    char ch;
    while (raw_len < MAXN - 1 && cin.get(ch)) {
        raw[raw_len++] = ch;
    }

    // 提取字母并记录其在原始文本中的下标，字母统一转小写用于匹配
    for (int i = 0; i < raw_len; i++) {
        if ((raw[i] >= 'A' && raw[i] <= 'Z') || (raw[i] >= 'a' && raw[i] <= 'z')) {
            char c = raw[i];
            if (c >= 'A' && c <= 'Z') {
                c = c - 'A' + 'a';
            }
            letter[letter_cnt] = c;
            pos[letter_cnt] = i;
            letter_cnt++;
        }
    }

    if (letter_cnt == 0) {
        cout << 0 << "\n";
        return;
    }

    int best_l = 0;
    int best_r = 0;
    int max_len = manacher(best_l, best_r);

    int out_start = pos[best_l];
    int out_end = pos[best_r];
    cout << max_len << "\n";
    cout.write(raw + out_start, out_end - out_start + 1);
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
