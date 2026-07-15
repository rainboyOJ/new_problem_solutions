def main():
    number = input().strip()
    k = int(input())

    stack = []
    for digit in number:
        while k > 0 and stack and stack[-1] > digit:
            stack.pop()
            k -= 1
        stack.append(digit)

    if k > 0:
        stack = stack[:-k]

    answer = "".join(stack).lstrip("0")
    print(answer if answer else "0")


if __name__ == "__main__":
    main()
