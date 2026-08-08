//随机数据生成
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6;

std::random_device rd;
std::default_random_engine __rnd(rd());

// 预先定义的随机数生成器 https://en.cppreference.com/w/cpp/numeric/random
std::mt19937 mtrnd(rd());

// 每一次产生指定范围内的随机数
// std::uniform_int_distribution
// https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution

//生成[l,r]之间的随机整数
int rnd(int l,int r) {
    return __rnd() % (r-l+1) + l;
}

// 洗牌,用于产生n个不重复的随机数
// 例如： [1,n] 区间随机排列
struct myShuffle {
    int a[maxn];
    int idx;
    myShuffle(int n) :idx(0)
    {
        for(int i = 0;i<=n;i++) a[i] = n;
        std::shuffle(a+1,a+n+1,mtrnd);
    }

    int get() {
        return a[++idx];
    }
};

int parent[maxn];
int main() {
    // int n = rnd(15,100);// 一个n个点的树
    int n = 10;

    cout << n << " ";
    cout << n << endl;
    for(int i  = 2;i <= n;i++) {
        int p = rnd(1,i-1);
        cout << p << " " << i << endl;
        parent[i] = p;
    }

    while(1) {
        int p1 = rnd(1,n);
        int p2 = rnd(1,n);
        if( p2 < p1) std::swap(p2,p1);
        if( p1 == p2) continue;
        //重边
        if( parent[p2] == p1 ) continue;
        cout << p1 << " " << p2 << endl;
        break;
    }

    return 0;
}

