/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 15:48
 * update_at: 2026-10-07 15:48
 */
// ROJ 1698 字符串匹配
// 题意：s 的子串 w 与 t 匹配 <=> 存在双射 f 把 w 的字符映到 t 的字符上，
//       即 w 与 t 的「相等关系结构」完全一致（哪些位置字符相同）。
// 做法：广义 KMP。把每个位置换成「到上一次出现同一字符的距离」，
//       按窗口长度裁剪后比较，距离超过窗口长度的位置统一记 0（表示窗口内首次出现）。
#include <cstdio>
#include <cstring>

typedef long long ll;

const int MAXN = 1000005; // n、m、C 的上界都是 1e6
// 各数组的值域都不超过 1e6，装得下 int，所以大容量数组统一用 int 省内存（不用 ll）

int n, m;             // s、t 的长度
int charset;          // 字符集大小 C，字符取 1..C
int s_dist[MAXN];     // s_dist[i] = i 到「s 中上一次出现 s[i] 的位置」的距离（没出现过则等于 i）
int t_dist[MAXN];     // t_dist[i] 同理，作用于 t
int t_sig[MAXN];      // t_sig[k] = t_dist[k] 按窗口长度 k 裁剪后的值，模式侧的裁剪是静态的
int fail_[MAXN];      // fail_[i] = t 的前 i 个字符在同构意义下的最长真 border 长度
int last_pos[MAXN];   // last_pos[x] = 字符 x 最近一次出现的位置，按组清零
int answer[MAXN];     // 本组所有匹配位置的首位下标，KMP 保证天然升序

// 输入总量可达 31MB，用自带缓冲的 fread 逐个读整数
static char in_buf[1 << 20];
static int in_len = 0;
static int in_pos = 0;

char next_char() {
    if (in_pos == in_len) {
        in_len = fread(in_buf, 1, sizeof in_buf, stdin);
        in_pos = 0;
        if (in_len == 0) return 0;
    }
    return in_buf[in_pos++];
}

int read_int() {
    char c = next_char();
    while (c && (c < '0' || c > '9')) c = next_char();
    int x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = next_char();
    }
    return x;
}

// 把一串字符读成「到上一次出现位置的距离」：dist[i] = i - last[x]，并更新 last[x]
void read_dist(int *dist, int len) {
    for (int i = 1; i <= len; i++) {
        int x = read_int();
        dist[i] = i - last_pos[x];
        last_pos[x] = i;
    }
    memset(last_pos, 0, sizeof(int) * (charset + 1)); // 只清字符集用到的范围
}

// 处理一组数据
void work() {
    n = read_int();
    m = read_int();
    read_dist(s_dist, n);
    read_dist(t_dist, m);

    // 模式侧第 k 位比较时，窗口长度恒为 k，所以裁剪是静态的：
    // t_dist[k] >= k 说明 t[k] 在 t 的前 k 位里是首次出现，记 0。
    t_sig[0] = 0;
    for (int k = 1; k <= m; k++) t_sig[k] = t_dist[k] < k ? t_dist[k] : 0;

    // 求失配数组：把 t 自己当文本，文本侧第 i+1 位按窗口长度 j+1 动态裁剪
    fail_[1] = 0;
    int j = 0;
    for (int i = 1; i < m; i++) {
        int d = t_dist[i + 1] < j + 1 ? t_dist[i + 1] : 0;
        while (j > 0 && d != t_sig[j + 1]) {
            j = fail_[j];
            d = t_dist[i + 1] < j + 1 ? t_dist[i + 1] : 0;
        }
        if (d == t_sig[j + 1]) j++;
        fail_[i + 1] = j;
    }

    // 在 s 上匹配：当前已匹配长度 j 时，s 侧第 i 位按窗口长度 j+1 动态裁剪
    int cnt = 0;
    j = 0;
    for (int i = 1; i <= n; i++) {
        int d = s_dist[i] < j + 1 ? s_dist[i] : 0;
        while (j > 0 && d != t_sig[j + 1]) {
            j = fail_[j];
            d = s_dist[i] < j + 1 ? s_dist[i] : 0;
        }
        if (d == t_sig[j + 1]) j++;
        if (j == m) {
            answer[++cnt] = i + 1 - m; // 匹配段是 [i-m+1, i]，首位下标从 1 开始
            j = fail_[j];
        }
    }

    printf("%d\n", cnt);
    for (int i = 1; i <= cnt; i++) printf("%d ", answer[i]);
    putchar('\n');
}

int main() {
    int T = read_int();
    charset = read_int();
    for (int tc = 1; tc <= T; tc++) work();
    return 0;
}
