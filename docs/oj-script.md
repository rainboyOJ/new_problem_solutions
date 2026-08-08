# oj.js 使用文档

`scripts/problem-tools/oj.js` 是在线题目抓取命令入口。它会调用本项目中的旧在线题目抓取代码：

```text
old_scripts/online_judge/index.js
```

这个脚本的作用是：根据 OJ 和题号生成对应题目目录，并在目录中创建 `index.md`。每次执行时都会交互询问是否下载原题题面；选择下载时，支持的下载器会额外创建 `problem.md`。

## 1. 安装

先安装项目依赖：

```bash
npm install
```

如果希望直接使用 `oj` 命令，安装写题工具软链：

```bash
./scripts/install-problem-tools.sh
```

确认 `~/.local/bin` 已在 `PATH` 中：

```bash
export PATH="$HOME/.local/bin:$PATH"
```

## 2. 基本用法

使用 OJ 名称和题号：

```bash
oj luogu P9094
oj codeforces 165E
oj OpenJ_Bailian 1651
oj hdu 1003
```

或者不安装软链，直接从项目根目录运行：

```bash
scripts/problem-tools/oj.js luogu P9094
```

使用题目 URL：

```bash
oj https://www.luogu.com.cn/problem/P9094
oj https://vjudge.net/problem/OpenJ_Bailian-1651
oj https://codeforces.com/contest/165/problem/E
```

不带参数时会显示用法：

```bash
oj
```

输出：

```text
Usage: node index.js [oj] [id]
```

每次运行都会先询问：

```text
是否下载对应的题面到 problem.md? [y/N]
```

输入 `y`、`yes`、`是`、`好` 或 `下载` 会下载题面；直接回车默认不下载。

## 3. 生成结果

命令会创建或复用下面的目录：

```text
problems/<oj>/<id>/
```

并生成：

```text
problems/<oj>/<id>/index.md
```

如果在交互中选择下载题面，并且当前下载器支持题面抓取，还会生成：

```text
problems/<oj>/<id>/problem.md
```

例如：

```bash
oj luogu P9094
```

会生成：

```text
problems/luogu/P9094/index.md
```

`index.md` 的模板来自：

```text
old_scripts/online_judge/template/default.njk
```

默认内容包含：

```markdown
---
oj: "luogu"
problem_id: "P9094"
title: "..."
date: ...
toc: true
tags: []
desc: ""
source: ...
---

[[TOC]]

## 题目解析

## 代码

@include-code(./1.cpp, cpp)
```

如果 `index.md` 已经存在，脚本不会覆盖，会输出：

```text
.../index.md 已存在
```

`problem.md` 同样不会覆盖已有文件。

## 4. 支持的来源

当前入口加载了这些抓取器：

```text
luogu
vjudge
codeforces
```

目前自动下载 `problem.md` 的实现支持 `luogu`。其他下载器会继续生成 `index.md`，不会生成题面文件。

其中 `vjudge` 抓取器负责一批通过 VJudge 页面访问的 OJ，例如：

```text
poj
hdu
atcoder
OpenJ_Bailian
CodeForces
```

注意大小写：`OpenJ_Bailian` 这类目录名建议按现有 `problems/` 里的写法传入。

## 5. 和当前目录无关

这个脚本目前不根据当前目录自动推导 `oj/id`。也就是说，在下面目录里运行：

```bash
cd problems/luogu/P9094
oj
```

不会自动等价于 `oj luogu P9094`，仍然会显示 usage。

必须显式传参：

```bash
oj luogu P9094
```

## 6. 依赖说明

`oj.js` 依赖 Node.js 和项目 npm 依赖。和这个脚本直接相关的依赖主要是：

```text
cheerio
ejs
nunjucks
js-yaml
glob
```

这些依赖已经写入本项目 `package.json`。如果脚本报 `ERR_MODULE_NOT_FOUND`，通常是没有执行过：

```bash
npm install
```

## 7. 常见问题

### 7.1 只显示 Usage

说明命令参数不完整。正确格式是：

```bash
oj <oj> <id>
```

或：

```bash
oj <problem-url>
```

### 7.2 index.md 已存在

这是正常保护行为。脚本不会覆盖已有题解，避免误删手写内容。

### 7.3 洛谷或 VJudge 抓取失败

这类抓取需要访问外网页面。如果网络不可用、目标站反爬、页面结构变化，脚本可能失败。可以稍后重试，或手动创建 `index.md`。

### 7.4 codeforces 可以生成，但标题为空

当前 `codeforces` 抓取器主要生成基础模板和 source 链接，不抓取页面标题。生成后可手动补充 `title`。
