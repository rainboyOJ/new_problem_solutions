# fetch_usaco_testdata.py

位置：

```text
scripts/problem-analysis-tools/fetch_usaco_testdata.py
```

作用：从 USACO 官方结果页找到 `Test data` 链接，下载 zip，并解压到题目目录的 `data/` 下。

## 基本用法

在 USACO 题目目录中直接运行：

```bash
python3 ../../../scripts/problem-analysis-tools/fetch_usaco_testdata.py
```

从仓库根目录指定题目目录或 cpid：

```bash
ptool fetch_usaco_testdata problems/usaco/1110
ptool fetch_usaco_testdata 1110
ptool fetch_usaco_testdata 'https://usaco.org/index.php?page=viewproblem2&cpid=1110'
ptool --cd problems/usaco/1110 fetch_usaco_testdata
```

下载后可以直接用现有样例检查工具跑本地数据：

```bash
ptool check_sample problems/usaco/1110 --timeout 3 --memory-mb 256
```

`check_sample.py` 已经支持 `data/*.in + data/*.out` 和 `data/*.in + data/*.ans`，所以 USACO 官方数据不需要额外转换。

## 覆盖策略

默认不覆盖已经存在的 `data/*.in` / `data/*.out`：

```bash
ptool fetch_usaco_testdata 1110
```

需要重新下载并覆盖时：

```bash
ptool fetch_usaco_testdata 1110 --force
```

只预览链接和将要写入的路径：

```bash
ptool fetch_usaco_testdata 1110 --dry-run
```

给脚本或 agent 使用 JSON 输出：

```bash
ptool fetch_usaco_testdata 1110 --json
```

## 链接解析

脚本不会硬编码测试数据 zip 文件名。它的流程是：

1. 打开 `viewproblem2&cpid=<id>` 题面页；
2. 从题面页解析比赛标题，例如 `USACO 2021 February Contest, Silver`；
3. 推导官方结果页，例如 `feb21results`；
4. 在结果页中定位同一个 `cpid`；
5. 读取紧跟着的 `Test data` 和 `Solution` 链接。

输出中会打印官方题解链接，解 USACO 题时建议先读官方 solution，再写自己的代码和题解。

## USACO 写题流程建议

USACO 官方题一般有完整测试数据。写这类题时优先使用：

```text
读题面 -> 读官方 solution -> 写 main.cpp -> 下载官方 testdata -> check_sample 跑全量数据
```

对拍仍然有价值，但不再是每道 USACO 题的默认必选项。下面这些情况再考虑对拍：

- 官方 testdata 下载失败；
- 官方数据通过了，但你对边界实现仍然不放心；
- 题解需要展示“暴力到正解”的推导，并且 `brute.cpp` 已经是可靠的小数据答案；
- 不是 USACO 题，或者没有官方完整数据。
