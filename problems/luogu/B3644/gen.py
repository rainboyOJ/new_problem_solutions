#!/usr/bin/env python3
import sys
from cyaron import IO, randint

def main():
    io = IO(input_file=sys.stdout, disable_output=True)
    n = randint(1, 100)
    io.input_writeln(n)
    
    # 生成 1..n 的随机排列作为真实拓扑序
    p = list(range(1, n + 1))
    import random
    random.shuffle(p)
    pos = {p[i]: i for i in range(n)}
    
    # 只能从拓扑序靠前的连向靠后的，保证是 DAG
    adj = [[] for _ in range(n + 1)]
    for i in range(n):
        u = p[i]
        for j in range(i + 1, n):
            v = p[j]
            # 以一定概率连边
            if randint(1, 100) <= 25:
                adj[u].append(v)
                
    for u in range(1, n + 1):
        if adj[u]:
            line = " ".join(map(str, adj[u])) + " 0"
        else:
            line = "0"
        io.input_writeln(line)

if __name__ == "__main__":
    main()
