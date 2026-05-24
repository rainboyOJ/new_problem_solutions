// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;

constexpr int MAXN = 1100000;            // 原始字符串最大长度
const int maxn = MAXN;

int l[MAXN*2+5];
int r[MAXN*2+5];

struct Node {
    int C;
    int L,R;
};
std::vector<Node> cr;
std::vector<Node> cr2;

bool cmp1(const Node &a ,const Node &b) {
    if( a.C != b.C) 
        return a.C < b.C;
    return a.R < b.R;
}

// Manacher 模板（不使用 std::string）
struct Manacher {
    // 变换后长度上限：2*MAXN + 少量哨兵
    static const int SZ = MAXN * 2 + 5;
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
        // for (int i = 0; i < m; ++i) p[i] = 0;
        memset(p,0,sizeof(p));

        // Manacher 主循环
        int center = 0, right = 0;
        for (int i = 1; i < m - 1; ++i) {
            int mirror = 2 * center - i;
            if (i < right) p[i] = min(right - i, p[mirror]);
            else p[i] = 1; // 长度至少是1

            // 暴力扩展：安全因为有哨兵
            while (t[i + p[i]] == t[i - p[i]]) ++p[i];

            // 更新中心与右边界
            if (i + p[i] > right) {
                center = i;
                right = i + p[i];


                Node tt;
                tt.C = i;
                tt.R = right;
                tt.L = center - (right-i);
                cr.push_back(tt);
            }
        }

        // 从左边到右边
        center = m-1;
        int left= m-1;
        for (int i = m-2; i >1 ; --i) {
            int mirror = 2 * center - i;
            if (i > left) p[i] = min(i-left, p[mirror]);
            else p[i] = 1; // 长度至少是1

            // 暴力扩展：安全因为有哨兵
            while (t[i + p[i]] == t[i - p[i]]) ++p[i];

            // 更新中心与左边界
            if (i - p[i] < left) {
                center = i;
                left = i - p[i];


                Node tt;
                tt.C = i;
                tt.R = center+(i-left);
                tt.L = left;
                // cout << "L = " << tt.L<< " ";
                // cout << "C = " << tt.C<< " ";
                // cout << "R = " << tt.R<< " \n";
                cr2.push_back(tt);
            }
        }
        // cout << "---left end ---\n";
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


struct myque {
    Node a[maxn];

    int head = 0, tail =0;
    void clear() {
        head = tail  = 0;
    }
    bool empty() {
        return tail == head;
    }

    void push(Node t) {
        a[tail++] = t;
    }

    void pop() { head++;}

    Node & front() {
        return a[head];
    }

    Node & back() {
        return a[tail-1];
    }
};

myque q;
int max_end[maxn];
int max_start[maxn];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    static char s[MAXN + 5];
    if (scanf("%s", s) != 1) return 0;   // 读取一个单词（竞赛常用）
    // 若需读取整行（含空格），使用 fgets 或 fgets + 去除末尾换行

    man.build(s);

    int L, R;
    int len = man.longest(L, R);
    // printf("%d\n", len);
    // if (len > 0) {
    //     // 输出子串：注意 printf 的 %.*s 用法
    //     printf("%.*s\n", len, s + L);
    // }
    // printf("\n");

    // 输出 字符
    // printf("%s\n",man.t);

    // 不需要对cr 进行排序,因为cr 一定是有序的

    //枚举 man.t 中的每个元素
    int cr_idx = 0;
    q.clear();
    for(int i = 1;i<= man.m-2;i++) {
        if( i% 2 == 0 ) continue;  // 只有 '#' 的时候才会计算

        // 队列里面添加元素
        while( cr_idx < cr.size() && cr[cr_idx].C <= i) {
            q.push(cr[cr_idx]);
            cr_idx++;
        }

        // 队列里面删除 不合法的元素 R <= i
        while( q.empty() == false &&q.front().R <= i) {
            q.pop();
        }
        
        if( q.empty() == false) {
            int _max_end =  i - q.front().C;
            // if( max_end < _max_end ) max_end = _max_end;
            max_end[i] = _max_end;
            // printf("%d -> max_end = %d\n",i,_max_end);
        }
    }

    // 为右到左去找
    cr_idx = 0;
    q.clear();
    for(int i = man.m-2;i>=1;i--) {
        if( i% 2 == 0 ) continue;  // 只有 '#' 的时候才会计算

        // 队列里面添加元素
        while( cr_idx < cr2.size() && cr2[cr_idx].C >= i) {

            // 末尾的元素,比新加入的元素更优秀
            if( !q.empty() && q.back().L < cr2[cr_idx].L)
                ;
            else
                q.push(cr2[cr_idx]);
            cr_idx++;
        }

        // 队列里面删除 不合法的元素 L >= i
        while( q.empty() == false &&q.front().L >= i) {
            q.pop();
        }
        
        // printf("i = %d\n",i);
        if( q.empty() == false) {
            // printf("Node (%d,%d,%d) \n",q.front().L,q.front().C,q.front().R);
            int _max_start =  q.front().C-i;
            max_start[i] = _max_start;
            // printf("%d -> max_start = %d\n",i,_max_start);
        }
    }

    
    // for(auto d : cr) {
    //     cout << "L = " << d.L<< " ";
    //     cout << "C = " << d.C<< " ";
    //     cout << "R = " << d.R<< " \n";
    // }
    // cout <<"---------- cr2 --------\n";
    // for(auto d : cr2) {
    //     cout << "L = " << d.L<< " ";
    //     cout << "C = " << d.C<< " ";
    //     cout << "R = " << d.R<< " \n";
    // }

    int ans = 0;
    for(int i = 2 ;i < man.m-2;i++){
        if( i % 2 == 0) continue;
        if( ans < max_start[i] +max_end[i]) 
            ans = max_start[i] +max_end[i];
    }
    printf("%d\n",ans);

    return 0;
}
