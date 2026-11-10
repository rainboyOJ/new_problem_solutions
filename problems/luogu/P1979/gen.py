import sys
from cyaron import IO, randint, choice

def generate():
    io = IO(input_file=sys.stdout, disable_output=True)

    n = randint(2, 4)
    m = randint(2, 4)
    q = randint(1, 3)

    io.input_writeln(f"{n} {m} {q}")

    valid_cells = []
    for i in range(1, n + 1):
        row = []
        for j in range(1, m + 1):
            val = 1 if randint(1, 10) <= 8 else 0
            row.append(val)
            if val == 1:
                valid_cells.append((i, j))
        io.input_writeln(row)

    if len(valid_cells) < 2:
        valid_cells = [(1, 1), (1, 2)]

    for _ in range(q):
        from random import sample
        c1, c2 = sample(valid_cells, 2)
        c3 = choice(valid_cells)
        ex, ey = c1
        sx, sy = c2
        tx, ty = c3
        io.input_writeln(f"{ex} {ey} {sx} {sy} {tx} {ty}")

if __name__ == "__main__":
    generate()
