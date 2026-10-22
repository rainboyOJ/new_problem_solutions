import sys


type Edge = tuple[int,int,int]


class DSU:

    def __init__(self,size):
        self.parent  = [i for i in range(size+1)]

    def find(self,u:int):
        if self.parent[u] == u:
            return u
        self.parent[u] = self.find(self.parent[u])
        return self.parent[u]


    def merge(self,x,y):
        fx = self.find(x)
        fy = self.find(y)
        if fy != fx:
            self.parent[fx] = fy
            return True # 合并成功
        return False


def kruskal(n:int,edges):
    dsu = DSU(n)
    edges.sort(key = lambda edge : edge[2])
    ans = 0
    select = 0
    for u,v,w in edges:
        if dsu.merge(u,v):
            ans += w
            select+=1
            if select == n-1:
                return ans
    return -1



def solve(data):
    a = next(data)
    b = next(data)
    graph_martix = [ [next(data) for _ in range(b) ] for j in range(b) ]
    edges:list[Edge] = []

    # 超级源点

    source = b+1
    # 若礼物 b 又没有优惠边，它就成孤立点，MST 选不满 n-1 条边，返回 -1。
    for i in range(1,b+1):
        edges.append((source,i,a))
    for i in range(1,b+1):
        for j in range(1,b+1):
            if i >= j:
                continue
            price = graph_martix[i-1][j-1]
            if price == 0 :
                continue
            edges.append((i,j,price))

    # 修复：原来写 kruskal(b,edges)，但图里有 b+1 个点（礼物 1..b 加虚拟源点 b+1）。
    # DSU 只开到 b，find(b+1) 会直接 IndexError。点数必须传含源点的 source。
    ans = kruskal(source,edges)
    print(ans)




if __name__ == "__main__":
    data = iter(map(int, sys.stdin.buffer.read().split()))
    solve(data)
