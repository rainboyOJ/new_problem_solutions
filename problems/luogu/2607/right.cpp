#include <cstdio>
#include <iostream>

#define ll long long

using namespace std;

int n, pos;
ll ans, s[1000011];

struct edge{
	int u, v, nxt;
}a[2000011]; //链式前向星

int tot, fir[1000011];

int ui, vi, E; //断开边的两端点及其编号

bool suc; //是否找到环

bool vis[1000011]; 

bool used[1000011]; //之前的联通块是否已经覆盖这个点

ll f[1000011][2], g[1000011][2];

bool vis1[1000011], vis2[1000011];

void fg(int w){
	used[w] = 1;
	int now = fir[w];
	while(now){
		if(!used[a[now].v])
			fg(a[now].v);
		now = a[now].nxt;
	}
} //覆盖当前基环树（联通块）
void find_circle(int w, int fa){
	if(suc) return ;
	int now = fir[w];
	vis[w] = 1;
	while(now){
		if(!vis[a[now].v])
			find_circle(a[now].v, w);
		else if(a[now].v != fa){
			ui = a[now].u;
			vi = a[now].v;
			E = now;
			suc = true;
			return ;
		}
		now = a[now].nxt;
	}
}//找环

void New(int from, int to){
	a[++tot].u = from;
	a[tot].v = to;
	a[tot].nxt = fir[from];
	fir[from] = tot;
}//建边

void dfs1(int w){
	int now = fir[w];
	f[w][1] = s[w];
	vis1[w] = 1;
	while(now){
		if(!vis1[a[now].v] && (now^1) != E){
			dfs1(a[now].v);
			f[w][0] += max(f[a[now].v][0], f[a[now].v][1]);
			f[w][1] += f[a[now].v][0];
		}
		now = a[now].nxt;
	}
}//以ui为根的树形dp
void dfs2(int w){
	int now = fir[w];
	g[w][1] = s[w];
	vis2[w] = 1;
	while(now){
		if(!vis2[a[now].v] && (now^1) != E){
			dfs2(a[now].v);
			g[w][0] += max(g[a[now].v][0], g[a[now].v][1]);
			g[w][1] += g[a[now].v][0];
		}
		now = a[now].nxt;
	}
}//以vi为根的树形dp

int main(){
	tot = 1;
	ui = vi = 0; // 环上任意边的两点 
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%lld%d", &s[i], &pos);
		New(i, pos); New(pos, i);
	}
	for(int i = 1; i <= n; i++){
		if(used[i]) continue;
		fg(i); suc = false;
		find_circle(i, 0);
		dfs1(ui); // 求以ui为根节点的树形dp 
		dfs2(vi); // 求以vi为根节点的树形dp 
		ans += max(f[ui][0], g[vi][0]);
	}
	printf("%lld\n", ans);
	return 0;
}

