import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 适度控制对拍规模，确保暴力能在 2s 内跑完（t 适度随机在 1 ~ 3000）
m = randint(0, 300)
s = randint(1, 100000)
t = randint(1, 3000)

io.input_writeln(f"{m} {s} {t}")
