import re
import sys

SIZE = 8
ALL_ROWS = (1<<SIZE) -1

def queens(cols: int, d1 : int ,d2: int ):
    if cols == ALL_ROWS:
        yield ()
        return
    avail = ALL_ROWS & ~(cols | d1 | d2)
    while avail:
        bit = avail & -avail
        avail ^= bit
        for tail in queens(cols | bit, (d1 | bit) << 1, (d2 | bit) >> 1):
            yield (bit.bit_length() - 1,) + tail

def board(solution):
    return (
            " ".join('1' if solution[c] == r else '0' for c in range(SIZE))
            for r in range(SIZE)
            )
def solve():
    solutions = list(queens(0,0,0))
    out = []
    for no, solution in enumerate(solutions,1):
        out.append(f"No. {no}")
        out += board(solution)
        # print(*board(solution),sep="\n")
        # print()
        # print()

    print("\n".join(out))


    


if __name__ == "__main__":
    solve()
