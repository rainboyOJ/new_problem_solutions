/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-02 13:56:35
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

// 定义最大范围，2e6 足够容纳 1e5 个区间的左右端点（最多 2e5 个点）
const int maxn = 2e6+5;
int n,m;
int a[maxn]; //差分数组：用于记录每个离散化坐标点的覆盖变化量

// 简单的结构体存储原始区间输入
struct range {
    int l,r;
};
vector<range> vec;


//oisnip_begindiscrete离散化_unique.cpp
/** * 步骤1：加入数据
* for (int x : nums) d.add(x);
* 步骤2：构建
* d.build();
* 步骤3：使用
* 去重后大小: :  d.size() 
* for (int x : nums) cout << x << " -> " << d.get(x) << endl;
*/
struct Discrete {
    std::vector<int> xs;

    // 清空数据，为多组测试用例做准备
    void clear() { xs.clear(); }

    // 1. 添加元素：将所有涉及到的坐标点加入待处理列表
    void add(int x) { xs.push_back(x); }

    // 2. 构建：排序并去重，建立数值到排名的映射
    void build() {
        std::sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
    }

    // 3. 查询 x 映射后的值 (默认从 1 开始)
    // 作用：将巨大的原始坐标 x 转换为较小的数组下标
    int get(int x) {
        return std::lower_bound(xs.begin(), xs.end(), x) - xs.begin() + 1;
    }

    //离散化后 映射的 最大的id（即有效点的总数）
    int get_max() {
        return xs.size();
    }
    
    // 3.1 查询 x 映射后的值 (从 0 开始)
    int get_zero(int x) {
        return std::lower_bound(xs.begin(), xs.end(), x) - xs.begin();
    }

    // 4. 反向查询：根据离散化后的值 k 找回 原值 (k 从 1 开始)
    int origin(int k) {
        return xs[k - 1];
    }
    
    // 获取去重后的元素总数
    int size() {
        return xs.size();
    }
} disc;
//oisnip_end

void init(){
    std::cin >> n;
    
    // 初始化差分数组，注意每次处理新用例都要清零
    // 提示：如果 T 很大且 maxn 很大，这里可以用 disc.get_max() 来局部清空以优化速度
    memset(a,0,sizeof(a));

    vec.clear();
    disc.clear(); // 清空离散化工具
    
    // --- 阶段 1: 读取输入并收集关键点 ---
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        int l,r;
        std::cin >> l >> r;
        
        // 核心逻辑：这里存入 r+1，因为差分是在区间结束的“下一位”进行减操作
        vec.push_back({l,r+1});
        
        // 将 l 和 r+1 加入离散化候选项
        disc.add(l);
        disc.add(r+1);
    }
    
    // --- 阶段 2: 构建离散化映射 ---
    disc.build();
    
    // --- 阶段 3: 执行差分操作 ---
    for(auto &ra : vec) {
        // 获取原始坐标对应的离散化下标（排名）
        int lid = disc.get(ra.l);
        int rid = disc.get(ra.r); // 这里 ra.r 已经是原输入的 r+1 了
        
        a[lid]++; // 区间开始，覆盖数 +1
        a[rid]--; // 区间结束的下一位，覆盖数 -1
    }

    // --- 阶段 4: 扫描线（前缀和）求最大值 ---
    int ans = 0;
    int overcnt = 0; // 当前这一层的重叠数量
    
    // 注意：这里的 n 是局部变量，遮蔽了全局的 n。
    // 它代表离散化后有效点的数量，写法很安全。
    int n = disc.get_max(); 
    
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        overcnt += a[i]; // 累加差分值，得到当前点的实际覆盖数
        if( ans < overcnt)
            ans = overcnt; // 更新最大值
    }
    std::cout << ans << "\n";

}

signed main () {
    // 关闭同步流，加速 I/O，防止 T 很大时输入输出超时
    ios::sync_with_stdio(false); cin.tie(0);
    int T;
    std::cin >> T;
    while (T--) {
        init();
    }
    
    return 0;
}
