/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-02 21:28:11
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
int n,m;
int h[maxn];
// 桶：buckets[i] 存储的是 离散化后排名为 i 的所有树的原始下标
vector<int> buckets[maxn];
// 头指针：head[i] 表示 buckets[i] 当前处理到了第几个元素
// 代替 pop_front，实现 O(1) 的伪删除
int head[maxn];

//oisnip_begindiscrete离散化_unique.cpp
/**  
* 步骤1：加入数据
*   for (int x : nums) d.add(x);
* 步骤2：构建
*   d.build();
* 步骤3：使用
*   去重后大小: :  d.size() 
*   for (int x : nums) cout << x << " -> " << d.get(x) << endl;
*/
struct Discrete {
    std::vector<int> xs;

    inline void clear() { xs.clear(); }

    // 1. 添加元素
    void add(int x) { xs.push_back(x); }

    // 2. 构建：排序并去重
    void build() {
        std::sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
    }

    // 3. 查询 x 映射后的值 (默认从 1 开始)
    // 如果找不到，返回的数值可能会超出范围，具体视 lower_bound 行为而定
    int get(int x) {
        return std::lower_bound(xs.begin(), xs.end(), x) - xs.begin() + 1;
    }

    //  可能得找不到对应的值
    int get_maybe(int x) {
        // 直接使用 lower_bound 查找迭代器
        auto it = std::lower_bound(xs.begin(), xs.end(), x);
        
        // 1. 检查是否到达末尾 (所有数都比 x 小)
        // 2. 检查找到的值是否严格等于 x (lower_bound 只是找 >= 的)
        if (it == xs.end() || *it != x) {
            return -1;
        }
        
        // 转换为 1-based 下标返回
        return it - xs.begin() + 1;
    }

    // 3.2 查询 x 映射后的最大的值 (从 1 开始)
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
    disc.clear();
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        buckets[i].clear();
        head[i] = 0;
    }
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> h[i];
        disc.add(h[i]);
    }
    disc.build();
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    while ( std::cin >> n >> m ) {
        init();

        // -> 将树的下标放入对应的桶中
        // 注意：这里我们正序遍历 (1 -> n)，放入桶中也是有序的 (小 -> 大)
        // 配合 head 指针从 0 开始自增，天然满足“取最左边”的要求
        for (int i = 1; i <= n; ++i) {
            // 因为 h[i] 一定在 uniq_h 里，这里直接二分找下标
            int id = disc.get(h[i]);
            buckets[id].push_back(i); // 放入高度为h[i[ 对应的下标
        }

        // 处理询问
        for(int i = 1;i <= m ;++i ) // i: 1->m
        {
            int q;
            std::cin >> q;
            int id = disc.get_maybe(q);
            // 情况1: 这个高度根本没出现过
            if( id == -1) {
                std::cout << -1 << "\n";
                continue;
            }

            // 情况2: 这个高度出现过，但是桶里的鸟都被打完了
            // head[id] 已经指到了 vector 的末尾
            if( head[id] >= buckets[id].size())
            {
                std::cout << -1 << "\n";
                continue;
            }

            // 情况3: 击中！
            std::cout << buckets[id][head[id]] << "\n";
            // 指针后移，相当于“删除”了这只鸟
            head[id]++;

        }
    }
    
    return 0;
}
