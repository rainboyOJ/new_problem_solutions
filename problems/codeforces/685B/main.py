import sys

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    n = int(input_data[0])
    q = int(input_data[1])
    
    fa = [0] * (n + 1)
    children = [[] for _ in range(n + 1)]
    
    # 读入父节点
    # input_data[2 : n + 1] 对应 p_2, ..., p_n
    for i in range(2, n + 1):
        p = int(input_data[i])
        fa[i] = p
        children[p].append(i)
    
    # BFS 生成拓扑序，避免递归
    bfs_order = [0] * n
    bfs_order[0] = 1
    head = 0
    tail = 1
    while head < tail:
        u = bfs_order[head]
        head += 1
        for v in children[u]:
            bfs_order[tail] = v
            tail += 1
            
    sz = [1] * (n + 1)
    heavy = [0] * (n + 1)
    ans = [0] * (n + 1)
    
    # 自底向上遍历
    for i in range(n - 1, -1, -1):
        u = bfs_order[i]
        heavy_v = 0
        heavy_sz = 0
        total_sz = 1
        for v in children[u]:
            s = sz[v]
            total_sz += s
            if s > heavy_sz:
                heavy_sz = s
                heavy_v = v
        sz[u] = total_sz
        heavy[u] = heavy_v
        
        if heavy_v == 0:
            ans[u] = u
        else:
            c = ans[heavy_v]
            # 2 * sz[c] < total_sz 说明上方连通块超过一半
            while (sz[c] << 1) < total_sz:
                c = fa[c]
            ans[u] = c
            
    # 回答查询
    out = []
    queries = input_data[n + 1 : n + 1 + q]
    for q_str in queries:
        v = int(q_str)
        out.append(str(ans[v]))
        
    sys.stdout.write("\n".join(out) + "\n")

if __name__ == '__main__':
    main()
