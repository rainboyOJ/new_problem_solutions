#!/usr/bin/env python3
"""默认生成直接枚举赋值能处理的小树；--n、--mode 用于边界及性能数据。"""
import argparse
import os
import random
import sys
from cyaron import Graph, IO, randint

parser = argparse.ArgumentParser()
parser.add_argument('--n', type=int)
parser.add_argument('--tests', type=int, default=1)
parser.add_argument('--mode', choices=['random', 'chain', 'star', 'broom', 'binary'])
args = parser.parse_args()
random.seed(int(os.environ.get('DUPAI_SEED', '1463701')))
io = IO(input_file=sys.stdout, disable_output=True)
io.input_writeln(args.tests)
for _ in range(args.tests):
    n = args.n or randint(2, 6)
    mode = args.mode or ['random', 'chain', 'star', 'broom', 'binary'][randint(0, 4)]
    if mode == 'chain' and n > 801:
        parser.error('合法纯链最多 801 个点；更大的深树请用 broom')
    if mode == 'star':
        tree = Graph.tree(n, flower=1)
    elif mode == 'chain':
        tree = Graph.tree(n, chain=1)
    elif mode == 'binary':
        tree = Graph.tree(n, father_gen=lambda u: u // 2)
    elif mode == 'broom':
        stem = min(n - 1, 800)
        tree = Graph.tree(n, chain=stem / (n - 1), father_gen=lambda u: stem)
    else:
        tree = Graph.tree(n)
    parent = [0] * (n + 1)
    depth = [0] * (n + 1)
    for edge in tree.iterate_edges():
        parent[edge.end] = edge.start
    for u in range(2, n + 1):
        assert 1 <= parent[u] < u
        depth[u] = depth[parent[u]] + 1
    height = max(depth)
    assert height <= 800
    m = randint(height, min(n - 1, 800))
    io.input_writeln(n, m)
    io.input_writeln(parent[2:])
