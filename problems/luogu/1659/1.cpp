/**
 * Author by Rainboy blog: https://blog.roj.ac.cn github : https://github.com/rainboylvx
 * date: 2025-12-14 09:04:01
 * oj: luogu-1659
 * title: [国家集训队] 拉拉队排练
 * description: manacher
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
const int maxn = 2e6+5;
ll mod = 19930726;
ll n,m,k;
char s[maxn];
ll cnt[maxn]; // cnt[i] 表示长度为的回文串的数量



// Manacher 模板（不使用 std::string）
struct Manacher {
    // 变换后长度上限：2*MAXN + 少量哨兵
    static const int SZ = maxn * 2 + 5;
    char t[SZ];    // 变换后的字符串：^ # a # b # ... # $
    int p[SZ];     // 半径数组（在 t 上的扩展长度）
    int m = 0;     // t 的实际长度（含终止符）

    // 构造变换串并计算 p[]
    // 输入：C 风格字符串 s（以 '\0' 结尾）
    void build(const char *s) {
        int n = (int)strlen(s);
        int k = 0;
        t[k++] = '&';   // 左哨兵，防止越界
        t[k++] = '#';
        for (int i = 0; i < n; ++i) {
            t[k++] = s[i];
            t[k++] = '#';
        }
        t[k++] = '^';   // 右哨兵
        t[k] = '\0';
        m = k;

        // 初始化半径数组
        memset(p,0,sizeof(p));

        // Manacher 主循环
        int center = 0, right = 0;
        for (int i = 1; i < m - 1; ++i) {
            int mirror = 2 * center - i;
            if (i < right) p[i] = min(right - i, p[mirror]);
            else p[i] = 1; // 长度至少是1

            // 暴力扩展：安全因为有哨兵
            while (t[i + p[i]] == t[i - p[i]]) ++p[i];

            int len = p[i] - 1;
            cnt[len]++;

            // 更新中心与右边界
            if (i + p[i] > right) {
                center = i;
                right = i + p[i];
            }
        }
    }

    // 获取最长回文子串，返回长度；通过引用参数 l,r 返回原串上的左闭右闭索引（0-based）
    int longest(int &l, int &r) const {
        int best_len = 0, best_center = 0;
        for (int i = 1; i < m - 1; ++i) {
            if (p[i]-1 > best_len) {
                best_len = p[i]-1;
                best_center = i;
            }
        }
        if (best_len == 0) { l = 0; r = -1; return 0; }
        // 将 t 中的位置映射回原串的索引
        l = (best_center - best_len) / 2;
        r = l + best_len - 1;
        return best_len;
    }
};

Manacher man;

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//
//     static char s[MAXN + 5];
//     if (scanf("%s", s) != 1) return 0;   // 读取一个单词（竞赛常用）
//     // 若需读取整行（含空格），使用 fgets 或 fgets + 去除末尾换行
//
//     Manacher man;
//     man.build(s);
//
//     int L, R;
//     int len = man.longest(L, R);
//     printf("%d\n", len);
//     if (len > 0) {
//         // 输出子串：注意 printf 的 %.*s 用法
//         printf("%.*s\n", len, s + L);
//     }
//     return 0;
// }
void init(){
    std::cin >> n >> k;
    cin >> s;
    man.build(s);
}

ll quick_pow(ll a,ll n) {
    ll base = a;
    ll ret =1;

    for( ;n ;n=n >> 1){
        if(n & 1)//取最低位, 是不是很像判断奇偶
            ret = ret * base % mod;
        base = base*base % mod;
    }

    return ret % mod;
}

signed main (int argc, char *argv[]) {
    ios::sync_with_stdio(false); cin.tie(0);
    init();

    for(int i = n;i-2 >= 0;i--) {
        cnt[i-2] += cnt[i];
        // std::cout << i << " " << cnt[i] <<endl;
    }

    ll ans = 1;
    for(int i = n;i >= 1;i--) {
        // 快速密
        if( i % 2 == 1) {
            if( k >= cnt[i]) {
                ans *= quick_pow(i,cnt[i]);
                ans %= mod;
                k-=cnt[i];
            }
            else if ( k != 0){
                ans *= quick_pow(i,k);
                ans %= mod;
                k = 0;
                break;
            }

        }
    }
    if( k != 0){
        std::cout << -1 << "\n";
    }
    else
        std::cout << ans << "\n";
    
    return 0;
}
