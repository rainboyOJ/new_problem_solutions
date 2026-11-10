import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 暴力对拍规模控制在 k <= 3，保证暴力可以在时限内跑出
k = randint(1, 3)
n = randint(1, 10**randint(1, 10))

io.input_writeln(f"{n} {k}")
