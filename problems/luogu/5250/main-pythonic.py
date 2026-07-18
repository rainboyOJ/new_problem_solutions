import sys

class Fenwick:
    def __init__(self, n):
        self.n = n
        self.tree = [0] * (n + 1)

    def add(self, pos, delta):
        while pos <= self.n:
            self.tree[pos] += delta
            pos += pos & -pos

    def prefix_sum(self, pos):
        total = 0
        while pos:
            total += self.tree[pos]
            pos -= pos & -pos
        return total

    def kth(self, rank):
        pos = 0
        step = 1 << (self.n.bit_length() - 1)
        while step:
            nxt = pos + step
            if nxt <= self.n and self.tree[nxt] < rank:
                pos = nxt
                rank -= self.tree[nxt]
            step >>= 1
        return pos + 1

def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    operations = list(zip(data[1::2], data[2::2]))
    lengths = sorted({length for _, length in operations})
    index = {length: i + 1 for i, length in enumerate(lengths)}

    bit = Fenwick(len(lengths))
    stock = set()
    answer = []

    for operation, length in operations:
        pos = index[length]
        if operation == 1:
            if length in stock:
                answer.append("Already Exist")
            else:
                stock.add(length)
                bit.add(pos, 1)
            continue

        if not stock:
            answer.append("Empty")
            continue

        if length in stock:
            chosen = length
        else:
            left_count = bit.prefix_sum(pos - 1)
            total = len(stock)
            left = lengths[bit.kth(left_count) - 1] if left_count else None
            right = lengths[bit.kth(left_count + 1) - 1] if left_count < total else None

            if right is None or left is not None and length - left <= right - length:
                chosen = left
            else:
                chosen = right

        answer.append(str(chosen))
        stock.remove(chosen)
        bit.add(index[chosen], -1)

    print("\n".join(answer))

if __name__ == "__main__":
    main()
