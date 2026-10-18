import sys

type Graph = list[list[int]]

# dfs 遍历 u 能到达的点
def dfs(g:Graph,u:int ,s:set):
    if u in s:
        return
    s.add(u)
    for v in g[u]:
        dfs(g,v,s)

def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)  # 0 <= n < 31，单个整数
    k = next(data)

    # build graph
    g:Graph = [[] for _ in range(n+1)]
    for _ in range(k):
        u = next(data)  # x >= 0
        v = next(data)  # y < n
        g[u].append(v)


    nSet:list[set] = [set() for _ in range(10)]
    # nSet 记录每个数字可以到达的数字的集合
    for i in range(10):
        dfs(g,i,nSet[i])
    ans = 1

    for c in str(n):
        # 有 len 种可能的变化
        ans *= len(nSet[int(c)])
    print(ans)




if __name__ == "__main__":
    solve()
