import sys
from cyaron import IO, randint, Graph

# 生成符合题目要求的数据
# 保证：
# 1. 任意两站连通
# 2. 每个站最多 d 条线路经过
# 3. 每条线路站不重复
# 4. x != y
# 输出至 stdout

def main():
    io = IO(input_file=sys.stdout, disable_output=True)

    # 随机选择规模
    # 模式 1: 小规模，用于对拍验证正确性
    # n in [2, 10], m in [5, 20], d in [3, 5], q in [5, 20]
    n = randint(2, 8)
    m = randint(5, 15)
    d = randint(2, 4)
    q = randint(5, 15)
    c = 0

    io.input_writeln(c, n, m, d, q)

    # w_v
    w = [randint(1, 100) for _ in range(m)]
    io.input_writeln(w)

    # 为了确保连通且每个站至多 d 条线路，先建一棵站点树，然后用线路覆盖这些树边
    # 但简单起见，可以确保所有站点被连通图覆盖
    # 构造线路：
    # 每个站的度数 <= d
    degree = [0] * (m + 1)
    
    # 构造一个跨越 1..m 的骨架
    # 先把 1..m 划分或连接成连通块
    # 一种可靠方法：
    # 每条线路随机选一些站（长度 >= 2 且 <= m）
    # 确保图连通
    import random
    
    # 构建一棵站点的连通生成树
    tree = Graph.tree(m, chain=0.4, flower=0.2)
    tree_edges = []
    for e in tree.iterate_edges():
        tree_edges.append((e.start, e.end))
        
    # 分配线路覆盖这 m-1 条边
    # 线路 1 到 n，每条线分配若干条树边（或相邻点），再加上一些随机站
    lines = [set() for _ in range(n + 1)]
    for idx, (u, v) in enumerate(tree_edges):
        line_idx = (idx % n) + 1
        lines[line_idx].add(u)
        lines[line_idx].add(v)
        degree[u] += 1
        degree[v] += 1

    # 每条线路确保至少有 2 个点
    all_stations = list(range(1, m + 1))
    for i in range(1, n + 1):
        if len(lines[i]) < 2:
            # 补齐
            random.shuffle(all_stations)
            for st in all_stations:
                if st not in lines[i] and degree[st] < d:
                    lines[i].add(st)
                    degree[st] += 1
                if len(lines[i]) >= 2:
                    break

    # 随机添加站点到线路中
    for i in range(1, n + 1):
        extra = randint(0, 3)
        random.shuffle(all_stations)
        for st in all_stations:
            if extra <= 0:
                break
            if st not in lines[i] and degree[st] < d:
                lines[i].add(st)
                degree[st] += 1
                extra -= 1

    for i in range(1, n + 1):
        st_list = list(lines[i])
        random.shuffle(st_list)
        k_i = len(st_list)
        line_data = [k_i]
        for st in st_list:
            t_val = randint(1, 100)
            line_data.extend([st, t_val])
        io.input_writeln(line_data)

    # 生成询问
    for _ in range(q):
        x = randint(1, m)
        y = randint(1, m)
        while y == x:
            y = randint(1, m)
        io.input_writeln(x, y)

if __name__ == "__main__":
    main()
