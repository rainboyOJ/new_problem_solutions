#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;
typedef  long long ll;
int n,m;
ll a[maxn]; // 原数组，存储每个数字的值

long long powers[11]; // 用于存储 10 的幂次方，powers[i] = 10^(i-1)

// 预处理 10 的幂次方
void precompute_powers() {
    powers[1] = 1;
    for (int i = 2; i <= 10; ++i) powers[i] = powers[i - 1] * 10;
}

// 获取数字 val 的第 D 位数字（个位是第1位）
inline int get_digit(long long val, int D) {
    return (val / powers[D]) % 10;
}

// ---- block 分块结构体
struct Block {
    ll block; // 块的大小，通常取 sqrt(n)
    ll t; // 块的总数量
    ll pos[maxn]; // pos[i] 表示原数组第 i 个元素所属的块编号
    ll st[maxn]; // st[i] 表示第 i 个块的起始下标
    ll ed[maxn]; // ed[i] 表示第 i 个块的结束下标

    ll addflag[maxn]; // 懒标记，这个题目里暂时没用到
    // cnt[i][d][p] 表示第 i 个块中，所有数字的第 d 位上，数字 p 出现的次数
    ll cnt[2005][11][10]; 

    // 初始化分块结构
    void init(){
        memset(cnt,0,sizeof(cnt)); // 清空统计数组，因为有多组数据
        block = sqrt(n); // 计算块大小
        t = n / block; // 计算完整块的数量
        if( n % block) t++; // 如果有剩余元素，块数量加 1
        
        // 确定每个块的起始和结束下标
        for(ll i = 1;i <= t ;++i ) // i: 1->t
        {
            st[i] = (i-1) * block + 1;
            ed[i] = i * block;
        }
        ed[t] = n; // 修正最后一个块的结尾下标为 n
        
        // 确定每个元素所属的块编号
        for(ll i = 1;i <= n ;++i ) // i: 1->n
        {
            pos[i] = (i-1) / block + 1;
        }

        // 初始化 cnt 数组，统计每个块内的信息
        for(ll i = 1;i <= t ;++i ) // i: 1->t
        {
            for(ll j = st[i];j <= ed[i] ;++j ) // j: 1->n
            {
                ll num = a[j]; // 使用 long long 防止溢出
                // 遍历数字 num 的每一位，更新 cnt 数组
                for(int d = 1;d <= 10;d ++) cnt[i][d][ get_digit(num, d)]++;
            }
        }
    }

    // 单点修改操作：将 a[L] 的值修改为 val
    // 这里 R 其实没用到，因为是单点修改，调用时传入 update(x, x, y)
    void update(ll L,ll R,ll val) {
        int idx = L; // 要修改的元素的下标
        int bidx = pos[L]; // 该元素所属的块编号

        // 1. 移除旧值的贡献
        // 遍历旧值 a[idx] 的每一位，在对应的 cnt 统计中减 1
        for(int d = 1;d <= 10;d++)
            cnt[bidx][d][get_digit(a[idx], d)]--;
            
        // 2. 更新原数组
        a[idx] = val;
        
        // 3. 添加新值的贡献
        // 遍历新值 val 的每一位，在对应的 cnt 统计中加 1
        for(int d = 1;d <= 10;d++)
            cnt[bidx][d][get_digit(val, d)]++;
    }

    // 区间查询操作：查询区间 [L, R] 内，第 d 位是 val 的数字有多少个
    long long query(ll L,ll R,int d,int val) {
        long long ret = 0;
        ll p = pos[L], q = pos[R]; // 计算区间两端所属的块编号
        
        if( p == q) {
            // 情况 1：查询区间在同一个块内
            // 直接暴力遍历区间 [L, R] 进行统计
            for(ll i = L;i <= R;i++) {
                if( get_digit(a[i], d) == val)
                    ret++;
            }
        }
        else {
            // 情况 2：查询区间跨越多个块
            
            // 统计中间完整的块
            for(ll i = p+1;i<=q-1;i++) {
                ret += cnt[i][d][val]; // 直接累加预处理好的统计信息
            }
            
            // 统计左侧不完整的散块
            for(ll i = L; i <= ed[p] ;i++) {
                if( get_digit(a[i], d) == val)
                    ret++;
            }
            
            // 统计右侧不完整的散块
            for(ll i = st[q];i <= R;i++) {
                if( get_digit(a[i], d) == val)
                    ret++;
            }
        }
        return ret;
    }
} myblock;


int main () {
    // 优化 I/O 操作，提高读写速度
    std::ios::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    
    precompute_powers(); // 程序开始时预处理 10 的幂次方

    int T;
    std::cin >> T; // 读取测试用例数量
    while (T--) {
        std::cin >> n >> m; // 读取数组大小和操作次数
        for(int i = 1;i <= n ;++i ) std::cin >> a[i]; // 读取原数组
        
        myblock.init(); // 初始化分块结构
        
        for(int i = 1;i <= m ;++i ) // i: 1->m 处理 m 次操作
        {
            char opt;
            std::cin >> opt; // 读取操作类型
            if( opt == 'Q') { // 查询操作
                int l,r,d,p;
                std::cin >> l >> r >> d >> p; // 读取查询参数
                cout << myblock.query(l, r,d,p) << "\n"; // 输出查询结果
            }
            else { // 修改操作
                int x,y;
                std::cin >> x >> y; // 读取修改参数
                myblock.update(x,x,y); // 执行单点修改
            }
        }
    }
    
    return 0;
}
