/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-02 12:39:43
 */
#include <bits/stdc++.h>
#include <vector>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 1e4+5;
int n,m;
int a[maxn];

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

    void clear() {
        xs.clear();
    }
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
} discx,discy;
//oisnip_end

struct Rect {
    int x1,y1,x2,y2;
    int val;
};
Rect rects[30];

void init(){
    std::cin >> n;
    discx.clear();
    discy.clear();
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        cin >> rects[i].x1;
        cin >> rects[i].y1;
        cin >> rects[i].x2;
        cin >> rects[i].y2;
        cin >> rects[i].val;

        discx.add(rects[i].x1);
        discx.add(rects[i].x2);

        discy.add(rects[i].y1);
        discy.add(rects[i].y2);
    }

    discx.build();
    discy.build();

}
bool include_area(int rectid ,int x1,int y1,int x2,int y2) {

    Rect & r = rects[rectid];
    return r.x1 <= x1 && r.x2 >= x2 && r.y1 <= y1 && r.y2 >= y2;

}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    int T;
    std::cin >> T;
    int caseid = 0;
    while (T--) {
        ll tot = 0;
        std::cout << "Case " << ++caseid  << ": ";
        init();

        for(int i = 0 ;i < discx.xs.size()-1; i++ ) {
            for(int j = 0 ;j < discy.xs.size()-1; j++ ) {

                int sx = discx.xs[i];
                int ex = discx.xs[i+1];

                int sy = discy.xs[j];
                int ey = discy.xs[j+1];

                ll area = (ll)(ex-sx) * (ey - sy);
                if( area == 0 ) continue;

                int maxVal = 0;
                for(int k = 1 ;k <=n;k++) {
                    if( include_area( k, sx,sy,ex,ey) )
                        maxVal = std::max(maxVal,rects[k].val);
                }

                tot += maxVal * area;
            }
        }
        std::cout << tot << "\n";
    }
    
    return 0;
}
