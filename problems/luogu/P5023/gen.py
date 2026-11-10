import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 对拍规模：n, m 限制在 1 到 3 之间（brute 在 3x3 时 2^9=512 次判定）
n = randint(1, 3)
m = randint(1, 3)

io.input_writeln(f"{n} {m}")
