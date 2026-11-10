import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 控制 m <= 300 保证 priority_queue 在毫秒级内完成
n = randint(1, 50)
m = randint(0, 300)
q = randint(0, 20)
v = randint(2, 20)
u = randint(1, v - 1)
t = randint(1, 10)

io.input_writeln(f"{n} {m} {q} {u} {v} {t}")

a = [randint(0, 1000) for _ in range(n)]
io.input_writeln(" ".join(map(str, a)))
