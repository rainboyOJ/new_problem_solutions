import sys
from cyaron import IO, randint

def generate():
    io = IO(input_file=sys.stdout, disable_output=True)

    n = 1
    io.input_writeln(n)

    S = randint(2, 6)
    t = randint(1, 20)
    A = randint(1, S)
    B = randint(1, S)

    io.input_writeln(f"{S} {t} {A} {B}")

    for _ in range(S):
        # 构造矩形前三点：选中心 (cx, cy)，以及正交向量 (dx, dy) 和 (-dy, dx)
        cx = randint(20, 100)
        cy = randint(20, 100)
        w = randint(1, 10)
        h = randint(1, 10)

        # 轴对齐或简单矩形
        x1, y1 = cx, cy
        x2, y2 = cx + w, cy
        x3, y3 = cx, cy + h

        cost = randint(1, 30)
        io.input_writeln(f"{x1} {y1} {x2} {y2} {x3} {y3} {cost}")

if __name__ == "__main__":
    generate()
