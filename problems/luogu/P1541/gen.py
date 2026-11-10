import sys
from cyaron import IO, randint, Vector

def generate():
    io = IO(input_file=sys.stdout, disable_output=True)

    # 随机生成卡片数量
    c1 = randint(0, 5)
    c2 = randint(0, 5)
    c3 = randint(0, 5)
    c4 = randint(0, 5)
    cards = [1] * c1 + [2] * c2 + [3] * c3 + [4] * c4
    from random import shuffle
    shuffle(cards)

    m = len(cards)
    if m == 0:
        cards = [1]
        m = 1

    n = sum(cards) + 1

    io.input_writeln(f"{n} {m}")

    scores = Vector.random(n, [0, 50])
    io.input_writeln(scores)

    io.input_writeln(" ".join(map(str, cards)))

if __name__ == "__main__":
    generate()
