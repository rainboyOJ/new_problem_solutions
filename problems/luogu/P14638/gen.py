#!/usr/bin/env python3
"""默认生成小规模对拍数据；可通过 --n、--q、--mode 构造边界和大数据。"""
import argparse
import os
import random
import sys
from cyaron import IO, Vector, randint
from cyaron.vector import VectorRandomMode

parser = argparse.ArgumentParser()
parser.add_argument('--n', type=int)
parser.add_argument('--q', type=int)
parser.add_argument('--mode', choices=['random', 'negative', 'positive', 'zero', 'alternating'])
args = parser.parse_args()
random.seed(int(os.environ.get('DUPAI_SEED', '1463801')))
n = args.n or randint(1, 40)
q = args.q or randint(1, 30)
if not (1 <= n <= 50000 and 1 <= q <= 1024):
    parser.error('要求 1<=n<=50000、1<=q<=1024')
mode = args.mode or ['random', 'negative', 'positive', 'zero', 'alternating'][randint(0, 4)]
if mode == 'negative':
    values = [row[0] for row in Vector.random(n, [(-100000, -1)], VectorRandomMode.repeatable)]
elif mode == 'positive':
    values = [row[0] for row in Vector.random(n, [(1, 100000)], VectorRandomMode.repeatable)]
elif mode == 'zero':
    values = [0] * n
elif mode == 'alternating':
    values = [100000 if i % 2 == 0 else -100000 for i in range(n)]
else:
    values = [row[0] for row in Vector.random(n, [(-100000, 100000)], VectorRandomMode.repeatable)]
queries = [(1, 1), (n, n), (1, n)]
for _ in range(max(0, q - len(queries))):
    left = randint(1, n)
    right = left if randint(0, 3) == 0 else randint(left, n)
    queries.append((left, right))
io = IO(input_file=sys.stdout, disable_output=True)
io.input_writeln(n)
io.input_writeln(values)
io.input_writeln(q)
for left, right in queries[:q]:
    io.input_writeln(left, right)
