import sys
import random
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 对拍规模：控制 L <= 1500，确保 brute 不越界
L = randint(20, 1500)
S = randint(1, 10)
T = randint(S, 10)
M = randint(1, min(L - 2, 30))

# 随机生成 M 个在 (0, L) 互不相同的石子坐标
all_pos = list(range(1, L))
random.shuffle(all_pos)
stones = sorted(all_pos[:M])

io.input_writeln(L)
io.input_writeln(f"{S} {T} {M}")
io.input_writeln(" ".join(map(str, stones)))
