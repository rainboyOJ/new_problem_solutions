/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-16 19:57
 * update_at: 2026-07-16 19:57
 */

#include <bits/stdc++.h>
#include <random>
#include <limits>
using namespace std;


template<typename T = long long,int N = 500005>
struct FHQ
{

    // ============ 数据
    int root;

    struct Node {
        int l,r;
        int size,fix;
        T val;
    };
    // 使用内存池 替代
    Node tr[N];
    int tr_idx = 0;
    int get() { return ++tr_idx;}

    std::mt19937 rnd;
    // ============ 数据
    // 定义极值，用于表示“没找到”
    // 如果是 long long 题目，请确保 T 是 long long
    const T INF_MAX = std::numeric_limits<T>::max();
    const T INF_MIN = std::numeric_limits<T>::min();

    // ============ 构造函数
    FHQ() {
        // root = 0;
        rnd.seed(233);
        // 也可以用下面的方式初始化随机数种子
        // rnd.seed(std::random_device()());
        init();
    }

    // --- 1. 多组数据必备 (Clear & Init) ---

    void init() {
        root = 0;
        tr_idx = 0;
        // 哨兵清理：防止 tr[0] 脏数据污染 size 计算
        tr[0].l = tr[0].r = tr[0].size = 0;
        tr[0].val = 0;
    }

    void clear() {
        init();
    }

    int size() const {
        return tr[root].size;
    }

    bool empty() const {
        return size() == 0;
    }

    // ============ 核心操作

    int new_node(T v) {
        int id = get();
        // tr[idx].ch[0]  = tr[idx].ch[1] = 0;
        tr[id].l = tr[id].r = 0; // 与上面等价
        tr[id].size = 1;
        tr[id].fix = rnd();
        tr[id].val = v;
        return id;
    }

    void update(int u ) {
        int l = tr[u].l;
        int r = tr[u].r;
        tr[u].size = tr[l].size + tr[r].size + 1;
    }

    // --- 这里的两个函数是 FHQ-Treap 的灵魂 ---

    /**
     * 分裂 (Split) - 按数值 v 分裂
     * 含义：将树 u 切成两棵树 x 和 y。
     * 功能:
     *      1. 使得 x 指向 u 中所有节点值 <= v 的节点组成的树
     *      2. 使得 y 指向 u 中所有节点值 > v 的节点组成的树
     * x 树：所有节点值 <= v
     * y 树：所有节点值 > v
     * 注意：x 和 y 是通过引用传回的
     * 注: 经过我的各种写法,发现最好的写法就是下面的这个,不要在修改了 by rainboy 2025-11-17
     */
    void split(int u,int v,int &x,int &y) {
        // 边界: 如果 u 是空树，那么 x 和 y 都是空树
        if( !u ) { x = y = 0; return; }
        if( tr[u].val <= v ) {
            x = u;
            // 剩下的问题是：u 的右子树里，可能还有 <= v 的，也可能有一部分 > v 的
            // 所以我们递归处理 u 的右子树
            split(tr[u].r,v,tr[u].r,y);
        } else {
            // 当前节点 > v，说明当前节点及其右子树都属于 y
            y = u;
            // 递归处理 u 的左子树
            split(tr[u].l,v,x,tr[u].l);
        }
        update(u); // 更新 u 的 size , 因为 u 的左右子树可能发生了变化
    }

    /**
     * 合并 (Merge)
     * 含义：将两棵树 x 和 y 合并成一棵树，并返回新根。
     * 前提：x 中所有节点的值 必须 <= y 中所有节点的值 (即有序)
     * 技巧：利用随机优先级 pri 来决定谁做父节点，从而保持平衡
     */
    int merge(int x,int y) {
        // 边界其中一个是空树,空树是单位元:如果有一棵树是空的，那么合并结果就是另一棵树
        if( !x || !y ) return x + y;

        // 谁的优先级高，谁就做父节点(取决于你是大根堆还是小根堆，这里用大根堆)
        if( tr[x].fix > tr[y].fix ) {
            tr[x].r = merge(tr[x].r,y);
            update(x); // 更新 x 的 size , 因为 x 的右子树可能发生了变化
            return x;
        } else {
            tr[y].l = merge(x,tr[y].l);
            update(y);
            return y;
        }
    }

    // --- 常用操作封装 (心智负担最低的写法) ---

    /**
     * 插入 (Insert)
     * 含义：将值 v 插入到树中
     * 注: 这个是最好的插入, 如果使用BST的插入,需要旋转,那就是普通Treap
     */
    void insert(T v) {
        int x,y;
        // 先按 v 分裂，把树切成 (<=v) 和 (>v) 两部分
        // 注: split <=v ,因为 新的节点放到相同的v的后面
        split(root,v,x,y);
        root = merge(merge(x,new_node(v)),y);
    }

    /**
     * 删除 (Delete)
     * 含义：将值 v 从树中删除
     * 注: 这个是最好的删除, 与插入一样
     */
    void del(T v) {
        int x, y, z;
        // 1. 把树按 v 分裂 -> x(<=v), z(>v)
        split(root, v, x, z);
        // 2. 把 x 按 v-1 分裂 -> x(<v), y(==v)
        split(x, v - 1, x, y);

        // 此时 y 树里全是值为 v 的节点。
        // 如果要删除所有 v，直接忽略 y 即可。
        // 如果只删除一个 v：
        if (y) // y不是空树
        {
            // 合并 y 的左右孩子，相当于把 y 的根节点丢弃了
            y = merge(tr[y].l, tr[y].r);
        }

        // 3. 全部装回去
        root = merge(merge(x, y), z);
    }

    /**
     * 查询排名 (Rank), split 风格
     * 含义：查询值 v 在树中的排名
     * 注意:v-1 的依赖 T 的类型,如果是浮点数,可能会有精度问题
     */
    int rank_with_split(T v) {
        int x,y;
        split(root,v-1,x,y);
        int ans = tr[x].size + 1;
        root = merge(x,y);
        return ans;
    }
    /**
     * 查询排名 (Rank), bst风格,比split风格快
     * 含义：查询值 v 在树中的排名
     * 注意:v-1 的依赖 T 的类型,如果是浮点数,可能会有精度问题
     */
    T rank(int v) const {
        // 传统的 BST 查询方式, 不依赖 split/merge
        int u = root;
        T ans = 0; // 记录比 v 小的节点数量
        while(u) {
            if( tr[u].val < v) {
                // 当前节点比 v 小, 左子树所有节点也都比 v 小
                ans += tr[tr[u].l].size + 1;
                u = tr[u].r; // 去右子树继续找
            }
            else { // tr[u].val >= v
                // 当前节点不小于 v, 答案在左子树
                u = tr[u].l;
            }
        }
        return ans + 1; // 排名是 "比我小的个数 + 1"
    }


    /**
     * 查询第 k 小 (Kth),bst 风格
     * 含义：查询树中第 k 小的值
     */
    T kth(int k) const {
        int u = root;
        while( true ) {
            int l_size = tr[tr[u].l].size;
            if( k <= l_size ) u = tr[u].l;
            else if( k == l_size + 1 ) return tr[u].val;
            else k -= l_size + 1,u = tr[u].r;
        }
    }

    /**
     * 查询前驱 (Predecessor)
     * 含义：查询值 v 在树中的前驱 (小于v的最大值)
     */
    T pre(T v) {
        // T ans = -2147483647; // 假设为 int 类型的最小值, 表示未找到
        T ans = std::numeric_limits<T>::min(); // 更通用的写法
        int u = root;
        while (u) {
            if (tr[u].val < v) {
                // 当前节点是 v 的一个潜在前驱, 记录下来
                ans = tr[u].val;
                // 尝试在右子树中寻找更大的前驱
                u = tr[u].r;
            } else {
                // 当前节点值 >= v, 前驱一定在左子树
                u = tr[u].l;
            }
        }
        return ans;
    }

    /**
     * 查询后继 (Successor)
     * 含义：查询值 v 在树中的后继 (大于v的最小值)
     */
    T succ(T v) {
        int u = root;
        // T ans = 2147483647; // 假设为 int 类型的最大值, 表示未找到
        T ans = std::numeric_limits<T>::max(); // 更通用的写法
        while (u) {
            if (tr[u].val > v) {
                // 当前节点是 v 的一个潜在后继, 记录下来
                ans = tr[u].val;
                // 尝试在左子树中寻找更小的后继
                u = tr[u].l;
            } else {
                // 当前节点值 <= v, 后继一定在右子树
                u = tr[u].r;
            }
        }
        return ans;
    }

     // --- 4. STL 风格查询接口 ---

    /**
     * lower_bound: 寻找第一个 >= v 的值
     * 返回值: 找到的值，如果没找到返回 INF_MAX
     */
    T lower_bound(T v) {
        return succ(v-1); // 等价于 succ(v-1)
    }

    /**
     * upper_bound: 寻找第一个 > v 的值 (等同于 succ)
     * 返回值: 找到的值，如果没找到返回 INF_MAX
     */
    T upper_bound(T v) {
        return succ(v);
    }


};

FHQ fhq;

int main() {

    int n;
    std::cin >> n;
    int opt,val,ans;
    while (n--) {
        std::cin >> opt >> val;
        if( opt == 1) {
            fhq.insert(val);
        }
        else if( opt == 2) {
            fhq.del(val);
        }
        else if( opt == 3) {
            auto ans = fhq.rank(val);
            std::cout << ans <<endl;
        }
        else if( opt == 4) {
            auto ans = fhq.kth(val);
            std::cout << ans <<endl;
        }
        else if( opt == 5) {
            auto ans = fhq.pre(val);
            std::cout << ans <<endl;
        }
        else if( opt == 6) {
            auto ans = fhq.succ(val);
            std::cout << ans <<endl;
        }

    }


    return 0;
}
