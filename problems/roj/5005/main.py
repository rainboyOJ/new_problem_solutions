import sys

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    n = int(input_data[0])
    total_sum = 0
    for i in range(1, n + 1):
        total_sum += i
    print(total_sum)

if __name__ == '__main__':
    main()