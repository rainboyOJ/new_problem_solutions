import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

t = 1
id_test = 0
io.input_writeln(f"{t} {id_test}")

n = randint(3, 8)
m = randint(2, 6)
c = 1
f = 1
io.input_writeln(f"{n} {m} {c} {f}")

for _ in range(n):
    row = "".join("1" if randint(0, 3) == 0 else "0" for _ in range(m))
    io.input_writeln(row)
