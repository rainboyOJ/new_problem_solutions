#!/usr/bin/env python3
# gen.py：ROJ 1417 最大利润的对拍数据生成器，无输入，stdout 即一组数据。
# duipai.py 通过环境变量 DUPAI_SEED / DUPAI_CASE_ID 提供种子。
import os
import random
import sys

from cyaron import IO, randint

seed = int(os.environ.get("DUPAI_SEED", os.environ.get("DUPAI_CASE_ID", "0")))
if len(sys.argv) > 1:
    seed = int(sys.argv[1])
random.seed(seed)

io = IO(input_file=sys.stdout, disable_output=True)

kind = random.choice(["random", "random", "up", "down", "flat", "v", "extreme"])
n = random.choice([2, 2, 3, 5, 10, 50, 200, 1000])

if kind == "up":
    arr = sorted(randint(1, 10**9) for _ in range(n))          # 严格不减，答案在两端
elif kind == "down":
    arr = sorted((randint(1, 10**9) for _ in range(n)), reverse=True)  # 一路下跌，答案为负
elif kind == "flat":
    v = randint(1, 10**9)
    arr = [v] * n                                              # 全同价，答案为 0
elif kind == "v":
    arr = [randint(1, 10**9) for _ in range(n)]
    arr[random.randrange(n)] = 1                               # 插入一个最小值 1
    arr[random.randrange(n)] = 10**9                           # 插入一个最大值 1e9
elif kind == "extreme":
    arr = [random.choice([1, 10**9]) for _ in range(n)]        # 只有边界值
else:
    arr = [randint(1, 10**9) for _ in range(n)]

io.input_writeln(n)
for v in arr:
    io.input_writeln(v)
