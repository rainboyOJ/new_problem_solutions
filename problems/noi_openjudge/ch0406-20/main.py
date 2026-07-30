case_count = int(input())
for _ in range(case_count):
    device_count = int(input())
    devices = []
    bandwidths = set()
    for _ in range(device_count):
        data = list(map(int, input().split()))
        options = list(zip(data[1::2], data[2::2]))
        devices.append(options)
        bandwidths.update(bandwidth for bandwidth, _ in options)
    best = 0.0
    for bandwidth in bandwidths:
        total_price = 0
        for options in devices:
            prices = [price for option_bandwidth, price in options if option_bandwidth >= bandwidth]
            if not prices:
                break
            total_price += min(prices)
        else:
            best = max(best, bandwidth / total_price)
    print(f"{best:.3f}")
