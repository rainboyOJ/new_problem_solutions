import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

x1 = randint(-50, 50)
y1 = randint(-50, 50)
x2 = randint(-50, 50)
y2 = randint(-50, 50)
io.input_writeln(f"{x1} {y1} {x2} {y2}")

n = randint(1, 100)
io.input_writeln(n)

for _ in range(n):
    x = randint(-50, 50)
    y = randint(-50, 50)
    io.input_writeln(f"{x} {y}")
