import sys
from cyaron import IO, randint
import random

io = IO(input_file=sys.stdout, disable_output=True)

# 生成合法棋局测试点：n 种颜色，每种 m 个球
n = randint(2, 5)
m = randint(3, 10)
io.input_writeln(f"{n} {m}")

balls = []
for c in range(1, n + 1):
    balls.extend([c] * m)

random.shuffle(balls)

for i in range(n):
    col = balls[i * m : (i + 1) * m]
    io.input_writeln(" ".join(map(str, col)))
