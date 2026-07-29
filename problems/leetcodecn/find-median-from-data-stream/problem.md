# 295 数据流的中位数

## 题目描述
中位数是有序整数列表中的中间值。如果列表的大小是偶数，则没有中间值，中位数是两个中间值的平均值。

设计一个支持以下两种操作的数据结构：
- `void addNum(int num)` - 将数据流中的整数添加到数据结构中。
- `double findMedian()` - 返回目前所有元素的中位数。

**示例 1：**
```text
输入：addNum(1), addNum(2), findMedian() → 1.5, addNum(3), findMedian() → 2.0
```

**提示：**
- 最多会对 `addNum`、`findMedian` 进行 $5 \times 10^4$ 次调用。
