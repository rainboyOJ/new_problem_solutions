import sys


def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    need, farmer_count = data[0], data[1]

    farmers = []
    pos = 2
    for _ in range(farmer_count):
        price, amount = data[pos], data[pos + 1]
        pos += 2
        farmers.append((price, amount))

    farmers.sort()

    answer = 0
    for price, amount in farmers:
        buy = min(need, amount)
        answer += buy * price
        need -= buy
        if need == 0:
            break

    print(answer)


if __name__ == "__main__":
    main()
