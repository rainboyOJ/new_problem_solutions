#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
const int maxe = 2e6+5;
struct linklist{
    struct edge{
        int u,v,w,next;
    };
    edge e[maxe];
    int h[maxe];
    int cnt=0;
    linklist(){
        memset(h,-1,sizeof(h));
    }
    void add(int u,int v,int w) {
        cnt++;
        e[cnt].u = u;
        e[cnt].v = v;
        e[cnt].w =w;
        e[cnt].next = h[u];
        h[u] = cnt;
    }
    void add2(int u,int v,int w){
        add(u,v,w);
        add(v,u,w);
    }
} e;

int m,n;
int a[maxn];
int rd[maxn];

bool in_a(int s,int t){
    for(int j=1;j<=t;j++){
        if(s==a[j]){
            return true;
        }
    }
    return false;
}

void init(){
    cin >> n >> m;
    for(int i=1;i<=m;i++){
        memset(a,0,sizeof(a));
        int t;
        cin >> t;
        for(int j=1;j<=t;j++){
            cin >> a[j];
        }
        for(int j=a[1];j<=a[t];j++){
            if(in_a(j,t)==false){
                for(int k=1;k<=t;k++){
                    e.add(a[k],j,1);
                    rd[j]++;
                }
            }
        }
    }
}

queue<int> q;
int ans[maxn];

void topsort() {
    for(int i = 1;i <= n ;++i ){
        if( rd[i] == 0) q.push(i);
    }
    while( !q.empty()){
        int u = q.front();
        q.pop();
        for(int i = e.h[u]; ~i;i = e.e[i].next) 
        {
            int v = e.e[i].v;
            rd[v]--;
            if(ans[u]+1>ans[v]){
                ans[v]=ans[u]+1;
            }
            if( rd[v] == 0)
                q.push(v);
        }
    }
}

int main(){
    init();
    topsort();
    int max1=-1;
    for(int i=1;i<=n;i++){
        max1=max(max1,ans[i]);
    }
    cout << max1+1;
    return 0;
}
