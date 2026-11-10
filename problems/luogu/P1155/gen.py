import sys
import random
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 控制对拍规模：n 在 3 到 8 之间
n = randint(3, 8)
p = list(range(1, n + 1))
random.shuffle(p)

io.input_writeln(n)
io.input_writeln(" ".join(map(str, p)))
