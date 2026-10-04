/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:23
 * update_at: 2026-10-03 12:30
 */
// P9721 [EC Final 2022] Inversion —— 交互题
//
// 询问 ? l r 返回 p_l..p_r 中逆序对个数的奇偶性，要求在 4*10^4 次询问内还原排列。
//
// 核心恒等式：记 inv(l,r) 为 p_l..p_r 内逆序对个数的奇偶性（约定 l>=r 时 inv=0），
// 对 l<r 有
//     [p_l > p_r] = inv(l,r) ^ inv(l+1,r) ^ inv(l,r-1) ^ inv(l+1,r-1)
// 把 [l,r] 中的逆序对按“是否用到 p_l”“是否用到 p_r”分成四类即可得到这个式子，
// 于是任意两个位置的大小关系只需要 4 次询问（相邻的 inv 还能复用）。
//
// 做法：插入排序 + 二分查找。
//   依次把 p_1,p_2,...,p_n 插入一张有序表，保持当前前缀的相对大小关系。
//   插入 p_i 时二分定位它的名次，每次比较用上面的恒等式（j+1==i 时只需 1 次询问）。
//   同时维护 E[l] = inv(l, i-1)，即当前前缀中从位置 l 到末尾的逆序对奇偶。
//   定位出名次 r 之后，p_l > p_i 等价于 rank[l] >= r（名次都在同一前缀内比较），
//   所以可以在 O(n) 次“不花询问”的数组更新里把 E 从 inv(.,i-1) 推进到 inv(.,i)。
//   询问次数上界为 2 * sum_{i=1}^{n} ceil(log2 i) = 39906 <= 4*10^4。
//
// 本地对拍说明：真实评测只给 n，排列是隐藏的。verify.sh 会把
// “n 加上整个排列”一起重定向进来，程序检测到 stdin 是普通文件时进入本地模式，
// 自己按定义把交互器的答案预计算好，这样同一份代码既能交互提交也能本地对拍。
#include <bits/stdc++.h>
#include <poll.h>
#include <sys/stat.h>
using namespace std;

const int maxn = 2005;

int n;
bool local_mode = false;          // 是否处于本地对拍模式
long long ask_count = 0;          // 已经发出的询问次数
static unsigned char invtab[maxn][maxn]; // 本地模式下预先算好的交互器答案
static int perm_in[maxn];         // 本地模式下读入的隐藏排列

int rank_of[maxn];                // rank_of[x] = p_x 在当前前缀中的名次（从 0 开始）
int elem_at[maxn];                // elem_at[t] = 当前前缀中名次为 t 的元素下标
unsigned char E[maxn];            // E[l] = inv(l, 当前前缀末尾) 的奇偶

// 向交互器询问 [l,r] 内逆序对个数的奇偶性；l>=r 时答案必为 0，不必询问。
int ask(int l, int r) {
    if (l >= r) {
        return 0;
    }
    ask_count++; // 只有真正会发出去的询问才计数（两个模式下都不发 l>=r 的询问）
    if (local_mode) {
        return invtab[l][r];
    }
    cout << "? " << l << " " << r << endl; // endl 会刷新输出
    int ans;
    cin >> ans;
    return ans;
}

// 本地模式：直接按定义算出所有 inv(l,r) 的奇偶性，充当交互器。
// 固定 r，令 l 从 r-1 递减，用 cnt 维护 [l, r-1] 中比 p_r 大的元素个数。
void build_local_table() {
    for (int r = 1; r <= n; r++) {
        int cnt = 0;
        for (int l = r - 1; l >= 1; l--) {
            if (perm_in[l] > perm_in[r]) {
                cnt++;
            }
            invtab[l][r] = (unsigned char)(invtab[l][r - 1] ^ (cnt & 1));
        }
    }
}

// 判断是否应该在本地模式下运行：
// 数据被重定向自普通文件（verify.sh 的 “< in” 就是这种），或者管道里还留着后续数据。
bool detect_local_mode() {
    struct stat st;
    if (fstat(0, &st) == 0 && S_ISREG(st.st_mode)) {
        return true;
    }
#if defined(__unix__) || defined(__APPLE__)
    struct pollfd pfd;
    pfd.fd = 0;
    pfd.events = POLLIN;
    pfd.revents = 0;
    if (poll(&pfd, 1, 0) > 0 && (pfd.revents & POLLIN)) {
        return true;
    }
#endif
    // cin 自己的缓冲区里可能已经缓存了未消费的数据（非空白才算）。
    if (cin.rdbuf()->in_avail() > 0) {
        int c = cin.rdbuf()->sgetc();
        if (!isspace((unsigned char)c)) {
            return true;
        }
    }
    return false;
}

void read_data() {
    cin >> n;
    local_mode = detect_local_mode();
    if (local_mode) {
        for (int i = 1; i <= n; i++) {
            cin >> perm_in[i];
        }
        build_local_table();
    }
}

void solve() {
    for (int i = 1; i <= n; i++) {
        // 二分查找 p_i 的名次 r：最小的 r 使 elem_at[r] 对应的数比 p_i 大。
        // 名次的取值范围是 [0, i-1]（当前前缀共有 i-1 个元素）。
        int lo = 0, hi = i - 1;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            int j = elem_at[mid];
            int gt = ask(j, i) ^ ask(j + 1, i) ^ E[j] ^ E[j + 1];
            if (gt) {
                hi = mid;      // p_j > p_i，插入点不会在 mid 之后
            } else {
                lo = mid + 1;  // p_j < p_i，插入点至少在 mid+1
            }
        }
        int r = lo;

        // 更新 E：g 表示 [l, i-1] 中比 p_i 大的元素个数（mod 2）；
        // p_l > p_i <=> rank_of[l] >= r，所以不需要额外询问。
        int g = 0;
        for (int l = i - 1; l >= 1; l--) {
            if (rank_of[l] >= r) {
                g ^= 1;
            }
            E[l] ^= g;
        }
        E[i] = 0; // inv(i,i) = 0

        // 名次 >= r 的元素整体后移一位，再把 i 放到名次 r 上。
        for (int t = i - 2; t >= r; t--) {
            int j = elem_at[t];
            rank_of[j] = t + 1;
            elem_at[t + 1] = j;
        }
        elem_at[r] = i;
        rank_of[i] = r;
    }

    // 名次从 0 开始，所以 p_i = rank_of[i] + 1，直接按位置 1..n 输出。
    cout << "!";
    for (int i = 1; i <= n; i++) {
        cout << " " << rank_of[i] + 1;
    }
    cout << endl;

    if (local_mode) {
        fprintf(stderr, "# 本地模式：共模拟询问 %lld 次（上限 40000）\n", ask_count);
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    read_data();
    solve();
    return 0;
}
