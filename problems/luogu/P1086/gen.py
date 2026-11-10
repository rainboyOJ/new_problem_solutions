import sys
import random
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

m = randint(1, 10)
n = randint(1, 10)
k = randint(0, 150)
io.input_writeln(m, n, k)

# 生成互不相同的花生数
total_cells = m * n
num_peanuts = randint(0, min(total_cells, 20))
values = random.sample(range(1, 501), num_peanuts) if num_peanuts > 0 else []

grid = [[0] * n for _ in range(m)]
positions = random.sample([(i, j) for i in range(m) for j in range(n)], num_peanuts)

for idx, (r, c) in enumerate(positions):
    grid[r][c] = values[idx]

for r in range(m):
    io.input_writeln(" ".join(map(str, grid[r])))
