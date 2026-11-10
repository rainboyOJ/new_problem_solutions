#!/usr/bin/env python3
import sys
import random
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

n = randint(1, 9)
root = randint(1, n)
io.input_writeln(n, root)
io.input_writeln([randint(1, 10) for _ in range(n)])

# 构造一棵以 root 为根的树：order[0] 是根，其余点随机挑前面某个点当父亲
perm = [i for i in range(1, n + 1) if i != root]
random.shuffle(perm)
order = [root] + perm
for i in range(1, n):
    p = order[random.randint(0, i - 1)]
    io.input_writeln(p, order[i])

io.input_writeln(0, 0)
