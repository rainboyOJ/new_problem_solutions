/**
 * Author by Rainboy blog: https://blog.roj.ac.cn github : https://github.com/rainboylvx
 * date: 2025-12-19 08:58:38
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
int n,m;
int deg[maxn]; //桶

const ll p = 131;
ll strhash(std::string s) {
    ll res = 1;
    for( auto c : s) res = res * p + c;
    return res;
}
ll mod = 1e6+1;
ll cnt_odd_deg  = 0;


// 并查集
int fa[maxn];
int find(int id) {
    if( id == fa[id]) return id;
    return fa[id] = find(fa[id]);
}

void merge(int x,int y) {
    int fx = find(x);
    int fy = find(y);
    if( fx != fy) fa[fx] = fy;
}

void init(){
    std::string s1,s2;
    while (cin >> s1 >> s2) {
        auto h1 = strhash(s1);
        auto h2 = strhash(s2);

        int id1 = h1 % mod;
        int id2 = h2 % mod;

        deg[id1]++;
        deg[id2]++;

        //合并到一个集合
        // std::cout << s1 << " ";
        // std::cout << s2 << "\n";
        merge(id1,id2);
    }

}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);

    for(int i = 0;i <= mod ;++i ) // i: 0->mod
    {
        fa[i] = i;
    }

    init();

    for(int i = 0;i <= mod ;++i ) // i: 1->n
    {
        if( deg[i] % 2 == 1) cnt_odd_deg++;
    }

    if( cnt_odd_deg !=0 && cnt_odd_deg !=2 ){
        cout << "Impossible" << endl;
        return 0;
    }

    
    int root = -1;
    //查找所有点的root 是一样的 
    for(int i = 0;i <= mod ;++i ) // i: 1->n
    {
        if( deg[i] != 0 ) {
            int ri =  find(i);
            if( root == -1) root = ri;

            if( ri != root) {
                cout << "Impossible" << endl;
                return 0;
            }
        }
    }
    cout << "Possible" << endl;
    return 0;
}
