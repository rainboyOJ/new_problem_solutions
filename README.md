# rbook 题目库项目

这是一个基于 Fastify 的题目库网站，题目来源于 `problems/` 目录中的 Markdown 文件。项目同时提供：

- 网页浏览与检索（Pug + Bootstrap）
- RESTful API（供程序和 AI 调用）
- MCP 网关（`./mcp`，用于 AI 工具化调用）

## 1. 功能概览

- Markdown 题目渲染（Front Matter + 正文）
- 题解可视化辅助：Mermaid、Graphviz 源码块、Markdown 表格和图片
- 题目列表分页、OJ/标签筛选、搜索
- 题目详情页渲染
- API 接口：
  - `GET /api/problems`
  - `GET /api/problems/:oj/:id`
  - `GET /api/tags`
  - `GET /api/oj`
  - `GET /api`（API 文档页）
- 双链解析：`[[oj/problem_id]]`

## 2. 环境要求

- Node.js 22+
- npm
- Docker 24+（可选，用 Docker 部署时需要）
- Docker Compose 插件（可选，用 `docker compose` 部署时需要）

## 3. 启动网站服务

在项目根目录执行：

```bash
npm install
npm start
```

默认访问地址：

- 网站首页：`http://127.0.0.1:3000/`
- API 文档：`http://127.0.0.1:3000/api`

### 3.1 Push 前检查

`npm install` 会自动启用仓库内的 `.githooks/pre-push`。每次 push 前会运行：

```bash
npm run verify:push
```

检查包括依赖状态、自动化测试、关系图编译及产物一致性、全量内容索引，以及真实服务启动和健康接口。push 前工作区必须完全干净，推送引用必须指向当前 `HEAD`。检查失败时不会 push，并会输出失败阶段、命令、退出码和建议动作。

也可以显式调用 `project-pre-push-check` skill 运行同一检查并诊断失败原因。该 skill 默认不会修改文件。

## 4. 使用 Docker 安装与启动

项目已经提供 `Dockerfile` 和 `docker-compose.yml`。服务启动和收到 `SIGHUP` 时会扫描 `problems/` 与 `problem-sets/` 的 frontmatter，原子替换内存目录；Markdown 正文在首次请求时渲染，并进入最多 200 项的共享 LRU 缓存。

Docker 镜像会由 GitHub Actions 推送到 GHCR：

```text
ghcr.io/rainboyoj/new_problem_solutions:master
```

国内 VPS 如果拉取 `ghcr.io` 较慢，可以优先使用下面两个加速地址：

```text
ghcr.nju.edu.cn/rainboyoj/new_problem_solutions:master
gh-proxy.org/docker/ghcr.io/rainboyoj/new_problem_solutions:master
```

### 4.1 从 GHCR 拉取镜像

推荐顺序是先拉国内加速镜像，失败后再试原始 GHCR：

```bash
docker pull ghcr.nju.edu.cn/rainboyoj/new_problem_solutions:master
docker tag ghcr.nju.edu.cn/rainboyoj/new_problem_solutions:master problems-solution:deploy
```

如果 `ghcr.nju.edu.cn` 不可用，再试：

```bash
docker pull gh-proxy.org/docker/ghcr.io/rainboyoj/new_problem_solutions:master
docker tag gh-proxy.org/docker/ghcr.io/rainboyoj/new_problem_solutions:master problems-solution:deploy
```

最后 fallback 到原始 GHCR：

```bash
docker pull ghcr.io/rainboyoj/new_problem_solutions:master
docker tag ghcr.io/rainboyoj/new_problem_solutions:master problems-solution:deploy
```

如果 GHCR package 不是 Public，需要先登录：

```bash
docker login ghcr.io -u YOUR_GITHUB_USERNAME
```

密码使用 GitHub Personal Access Token，至少需要 `read:packages` 权限。

### 4.2 本地构建镜像

在项目根目录执行：

```bash
docker build -t problems-solution:deploy .
```

### 4.3 使用 Docker Compose 启动

```bash
docker compose up -d
```

默认配置会把本机 `./problems`、`./problem-sets` 和 `./.runtime` 只读挂载到容器，并把容器 `3000` 端口映射到本机 `127.0.0.1:3300`。

访问地址：

- 网站首页：`http://127.0.0.1:3300/`
- API 文档：`http://127.0.0.1:3300/api`

查看运行状态和日志：

```bash
docker compose ps
docker compose logs -f problems-solution
```

停止服务：

```bash
docker compose down
```

也可以不重新 tag，直接指定镜像地址启动：

```bash
IMAGE_REF=ghcr.nju.edu.cn/rainboyoj/new_problem_solutions:master docker compose up -d
```

### 4.4 不使用 Compose 直接运行

```bash
docker run --rm \
  -p 3000:3000 \
  -v "$PWD/problems:/app/problems:ro" \
  problems-solution:deploy
```

直接运行时访问：`http://127.0.0.1:3000/`

### 4.5 更新部署

使用 GHCR 镜像部署时，拉取新镜像后重启：

```bash
docker pull ghcr.nju.edu.cn/rainboyoj/new_problem_solutions:master
docker tag ghcr.nju.edu.cn/rainboyoj/new_problem_solutions:master problems-solution:deploy
docker compose up -d
```

本地构建部署时，代码或题目数据更新后重新构建并启动：

```bash
git pull
docker build -t problems-solution:deploy .
docker compose up -d
```

## 5. 使用 MCP（给 AI 调用）

MCP 服务位于 `./mcp`，它会调用上面的主站 API。

### 5.1 安装与启动

```bash
cd mcp
npm install
TARGET_API_BASE_URL=http://127.0.0.1:3000 npm start
```

默认监听：`http://127.0.0.1:3333`

### 5.2 MCP 提供的核心工具

- `search_problems`
- `get_problem_detail`

详细说明见：`mcp/README.md`

## 6. 题目解析工作流（给 AI 与手写题解使用）

本仓库提供以下本地 skill：

- `oj-problem-format-spec`：只规定题解 Markdown 的格式、目录结构、frontmatter、章节标题和代码嵌入方式。
- `oj-problem-analysis-writer`：负责写题目解析内容，完成辅助理解和对拍的 `brute.cpp`，并根据过程文档生成正式 `index.md`。
- `oj-problem-analysis-reviewer`：负责审查已有题解是否讲清楚，检查推导跳步、只贴代码、样例或可视化说明不足等质量问题。
- `oj-problem-relation-writer`：负责维护题目之间的 `pre` / `common` 关系字段，以及跨 OJ 的 `recommend` 推荐练习字段。
- `oj-sample-visualizer`：负责为单道题生成题目专用的样例可视化脚本和素材，例如 DP 表、网格、树 SVG、Graphviz dot。
- `project-pre-push-check`：执行完整的 push 前项目检查，并用中文定位失败阶段和原因。

这些 skill 位于：

```text
.agents/skills/oj-problem-format-spec/SKILL.md
.agents/skills/oj-problem-analysis-writer/SKILL.md
.agents/skills/oj-problem-analysis-reviewer/SKILL.md
.agents/skills/oj-problem-relation-writer/SKILL.md
.agents/skills/oj-sample-visualizer/SKILL.md
.agents/skills/project-pre-push-check/SKILL.md
```

### 6.1 标准题目目录

新题目只使用目录型结构：

```text
problems/<oj>/<problem_id>/
├── index.md
├── main.cpp
├── brute.cpp
├── gen.py
└── problem-analysis-workspace/
    ├── 01-problem-understanding.md
    ├── 02-observation-and-model.md
    ├── 03-solution-derivation.md
    ├── 04-correctness-and-edge-cases.md
    ├── 05-complexity-and-implementation.md
    ├── 06-final-index-draft.md
    └── duipai-report.md
```

正式电子书内容写入 `index.md`。`### 思路` 中引用 `brute.cpp` 帮助读者理解朴素做法：

```markdown
@include-code(./brute.cpp, cpp)
```

正式提交代码固定为 `main.cpp`，并在 `### 代码` 中使用：

```markdown
@include-code(./main.cpp, cpp)
```

`problem-analysis-workspace/` 是每道题的学习和推导过程目录，已通过 `.gitignore` 忽略，不作为最终电子书内容提交。`problem-relation-workspace/` 用于记录低置信度关系候选，也保持本地忽略。

`index.md` frontmatter 中的 `description` 用一句话描述题解核心思路，供列表页、详情页、API、搜索和 AI 快速理解使用。新题解应填写非空内容；旧题解可以后续逐步补齐。`recommend` 用于记录仓库外或跨 OJ 的推荐练习，默认是 `recommend: []`，由 `oj-problem-relation-writer` 维护。

Luogu 的数字题目录统一使用 `P` 前缀，例如 `problems/luogu/P1001/`。主站、预览、API 和导航命令仍兼容输入纯数字 `1001`，并解析到规范的 `P1001`。

### 6.2 使用 skill 写题解

推荐流程：

1. 在 `problems/<oj>/<problem_id>/` 下准备 `main.cpp`。
2. 使用 `oj-problem-analysis-writer` 完成或修正 `brute.cpp`。
3. 让 AI 使用 `oj-problem-analysis-writer` 生成或补全 `problem-analysis-workspace/*.md`。
4. AI 根据 `06-final-index-draft.md` 和 `oj-problem-format-spec` 写入正式 `index.md`。
5. 如果要对拍，再准备或补全 `gen.py` 并运行对拍脚本。
6. 使用 `oj-problem-analysis-reviewer` 审稿，检查题意、推导、样例、可视化、复杂度和代码对应关系。
7. 人工检查 `index.md` 的题意、思路、复杂度和代码引用。

题解写作时必须评估是否需要可视化辅助。图论、树、DP、网格、搜索和复杂模拟题，优先使用 Mermaid、Graphviz、`tree_draw.py` 或 Markdown 表格解释样例数据和关键过程。详细规范见 [`docs/problem-visualization.md`](docs/problem-visualization.md)。

样例可视化不使用统一的万能解析器。推荐让 AI 使用 `oj-sample-visualizer`，在当前题目目录生成 `problem-analysis-workspace/viz_render.py`，再由这个题目专用脚本输出 SVG、dot 或 Markdown 表格。

示例提示：

```text
使用 oj-problem-analysis-writer，解析 problems/luogu/P1001/
根据 main.cpp 和过程文档生成 index.md
```

如果需要审查已有题解质量，使用：

```text
使用 oj-problem-analysis-reviewer，审稿 problems/luogu/P1001/
```

如果只需要创建或修正格式骨架，使用：

```text
使用 oj-problem-format-spec，规范 problems/luogu/P1001/index.md
```

### 6.3 随机数据、样例检查与对拍脚本

通用脚本放在：

```text
scripts/problem-analysis-tools/
```

随机数据生成：

```bash
python3 scripts/problem-analysis-tools/gen_random.py --pattern array -n 10 --min 1 --max 100
python3 scripts/problem-analysis-tools/gen_random.py --pattern tree -n 20
python3 scripts/problem-analysis-tools/gen_random.py --pattern graph -n 10 -m 15
python3 scripts/problem-analysis-tools/gen_random.py --pattern string -n 12 --charset abc
python3 scripts/problem-analysis-tools/gen_random.py --pattern permutation -n 10
```

对拍（给 Agent 和自动化使用，纯命令行）：

```bash
python3 scripts/problem-analysis-tools/duipai.py \
  --gen problems/luogu/P1001/gen.py \
  --user problems/luogu/P1001/main.cpp \
  --brute problems/luogu/P1001/brute.cpp \
  -n 200
```

人工交互式对拍：

```bash
cd problems/luogu/P1001
python3 ../../../scripts/problem-analysis-tools/duipai-human.py
```

样例运行器：

```bash
cd problems/luogu/P1001
python3 ../../../scripts/problem-analysis-tools/check_sample.py
```

也可以从项目根目录指定题目目录：

```bash
python3 scripts/problem-analysis-tools/check_sample.py problems/luogu/P1001
python3 scripts/problem-analysis-tools/check_sample.py problems/luogu/P1001 --source main.cpp --timeout 2
python3 scripts/problem-analysis-tools/check_sample.py problems/luogu/P1001 --timeout 1 --memory-mb 256
```

`check_sample.py` 会自动查找 `main.cpp`，没有时回退到 `1.cpp`。它会识别 `in/out`、`in1/out1`、`data/*.in` 与同名 `.out/.ans`；如果只有输入没有答案，会运行并标记为 `NO_ANSWER`。`--timeout` 控制时间限制，`--memory-mb` 控制内存判定线，内部默认额外给 16MB 保护余量。

对拍失败时会保存：

```text
problems/<oj>/<problem_id>/duipai-failed/
```

对拍记录默认写入：

```text
problems/<oj>/<problem_id>/problem-analysis-workspace/duipai-report.md
```

这些过程目录和失败样例目录已加入 `.gitignore`。

## 7. 工具使用

所有用户可直接运行的工具都支持：

```bash
<tool> --help
```

内部支撑库 `scripts/problem-tools/mylib/` 不作为用户命令使用。

也可以用 navi 作为交互式 cheatsheet。需要目录跳转能力时，推荐使用下面配置后的 `rbook-navi`，不要直接用 `command navi --path ...`：

```bash
rbook-navi
```

推荐在仓库目录内用 `git` 生成真实路径，然后把仓库脚本目录加入 `~/.zshrc` 的 `PATH`：

```bash
repo="$(git rev-parse --show-toplevel)"
cat >> ~/.zshrc <<EOF
export RBOOK_REPO="$repo"
export PATH="\$RBOOK_REPO/bin:\$RBOOK_REPO/scripts/navi:\$RBOOK_REPO/scripts/problem-analysis-tools:\$RBOOK_REPO/scripts/problem-tools:\$PATH"
source "\$RBOOK_REPO/scripts/navi/rbook-shell.zsh"
EOF
source ~/.zshrc
```

这样 `rbook`、`ptool`、`check_sample.py`、`r-cgdb.sh` 等脚本可以作为普通命令直接调用；`rbook-navi` 会打开本仓库 cheatsheet，并在当前 shell 执行选中的命令；`fetch_problem` 会在抓题后自动进入对应题目目录；`rbook_cd_problem` 可以用 `fzf` 选择 OJ 和题号目录后跳转。navi cheatsheet 中的命令会通过 `ptool` 或 shell 函数定位仓库根目录，避免在每条命令里重复写长路径。

人类开始写新题时推荐使用：

```bash
fetch_problem luogu P1001
fetch_problem https://www.luogu.com.cn/problem/P1001
```

它会调用底层 `fetch_problem.py` 创建题目结构，然后进入 `problems/<oj>/<problem_id>/`。如果是脚本、agent 或 CI，需要稳定输出，不需要改变当前目录，继续使用：

```bash
ptool fetch_problem luogu P1001 --json
```

已有题目目录跳转推荐使用：

```bash
rbook_cd_problem
rbook_cd_problem luogu
rbook_cd_problem luogu P1001
```

其中无参数和只传 OJ 的形式会用 `fzf` 选择目录。

完成一篇题解后，可以启动单题快速预览服务，不触发 `npm start` 前的全量题库扫描：

```bash
rbook preview
rbook preview --port 3100
```

它会自动选择最近修改的有效 `problems/**/index.md`，随后只监听这个题目目录。保存当前文章、题面、引用代码或图片后，所有已打开的预览页都会自动刷新。需要预览其他题目时，直接把浏览器地址改为对应的 `/problems/<oj>/<problem_id>/`；服务会切换唯一监听目录，并同步其他预览页。预览复用主站的 Markdown 渲染、题解模板、`problem.md` 弹窗、Mermaid、KaTeX 和客户端代码高亮。没有配置 `PATH` 时，也可以在仓库根目录运行：

```bash
npm run preview
```

网络选项仍可通过 `--host`、`--port/-p` 或 `HOST`、`PORT` 设置。完整说明见 [`docs/tools/rbook-preview.md`](docs/tools/rbook-preview.md)。

`ptool` 也可以直接在终端使用：

```bash
ptool list-problems
ptool check_sample problems/luogu/P1001
ptool --cd problems/luogu/P1001 old r-cgdb
```

`rbook-navi` 已由 `scripts/navi/rbook-shell.zsh` 提供，配置完成后直接使用：

```bash
rbook-navi
rbook-navi --query cd
rbook-navi --query duipai
rbook-navi --query sample
```

不要把 `rbook-navi` 配成 alias：

```bash
alias rbook-navi='command navi --path "$RBOOK_REPO/scripts/navi"'
```

这种 alias 会让 navi 在子进程里执行命令，导致 `rbook_cd_problem: command not found`，也不能保留 `cd`。新的 `rbook-shell.zsh` 会自动清理旧 alias。

说明见 [`docs/tools/navi.md`](docs/tools/navi.md)。

### 7.1 题解分析工具

| 工具 | 位置 | 文档 |
| --- | --- | --- |
| `rbook preview` | `bin/rbook.js` | [`docs/tools/rbook-preview.md`](docs/tools/rbook-preview.md) |
| `check_sample.py` | `scripts/problem-analysis-tools/check_sample.py` | [`docs/tools/check_sample.md`](docs/tools/check_sample.md) |
| `check_problem.py` | `scripts/problem-analysis-tools/check_problem.py` | [`docs/tools/check_problem.md`](docs/tools/check_problem.md) |
| `check_relations.py` | `scripts/problem-analysis-tools/check_relations.py` | [`docs/tools/check_relations.md`](docs/tools/check_relations.md) |
| `list_tags.py` | `scripts/problem-analysis-tools/list_tags.py` | [`docs/tools/list_tags.md`](docs/tools/list_tags.md) |
| `new-problem` / `new-problem.py` | `scripts/problem-analysis-tools/new-problem.py` | [`docs/tools/new-problem.md`](docs/tools/new-problem.md) |
| `fetch_problem.py` | `scripts/problem-analysis-tools/fetch_problem.py` | [`docs/tools/fetch_problem.md`](docs/tools/fetch_problem.md) |
| `fetch_usaco_testdata.py` | `scripts/problem-analysis-tools/fetch_usaco_testdata.py` | [`docs/tools/fetch_usaco_testdata.md`](docs/tools/fetch_usaco_testdata.md) |
| `fetch_problem` | `scripts/navi/rbook-shell.zsh` | [`docs/tools/rbook-shell.md`](docs/tools/rbook-shell.md) |
| `rbook_cd_problem` | `scripts/navi/rbook-shell.zsh` | [`docs/tools/rbook-shell.md`](docs/tools/rbook-shell.md) |
| `problem_status.py` | `scripts/problem-analysis-tools/problem_status.py` | [`docs/tools/problem_status.md`](docs/tools/problem_status.md) |
| `gen_random.py` | `scripts/problem-analysis-tools/gen_random.py` | [`docs/tools/gen_random.md`](docs/tools/gen_random.md) |
| `tree_draw.py` | `scripts/problem-analysis-tools/tree_draw.py` | [`docs/tools/tree_draw.md`](docs/tools/tree_draw.md) |
| `viz_templates/` | `scripts/problem-analysis-tools/viz_templates/` | [`docs/tools/viz_templates.md`](docs/tools/viz_templates.md) |
| `duipai.py` | `scripts/problem-analysis-tools/duipai.py` | [`docs/tools/duipai.md`](docs/tools/duipai.md) |
| `duipai-human.py` | `scripts/problem-analysis-tools/duipai-human.py` | [`docs/tools/duipai-human.md`](docs/tools/duipai-human.md) |
| `shrink_failed.py` | `scripts/problem-analysis-tools/shrink_failed.py` | [`docs/tools/shrink_failed.md`](docs/tools/shrink_failed.md) |
| `data_tool.py` | `scripts/problem-analysis-tools/data_tool.py` | [`docs/tools/data_tool.md`](docs/tools/data_tool.md) |
| `ptool` | `scripts/navi/ptool` | [`docs/tools/ptool.md`](docs/tools/ptool.md) |
| `migrate-luogu-dir-prefix.py` | `scripts/migrate-luogu-dir-prefix.py` | [`docs/tools/migrate-luogu-dir-prefix.md`](docs/tools/migrate-luogu-dir-prefix.md) |

### 7.2 旧版写题辅助工具

总览见 [`docs/problem-tools.md`](docs/problem-tools.md)。

| 工具 | 位置 | 文档 |
| --- | --- | --- |
| `b` | `scripts/problem-tools/b` | [`docs/tools/problem-tools-b.md`](docs/tools/problem-tools-b.md) |
| `duipai.py` | `scripts/problem-tools/duipai.py` | [`docs/tools/problem-tools-duipai.md`](docs/tools/problem-tools-duipai.md) |
| `one-duipai.py` | `scripts/problem-tools/one-duipai.py` | [`docs/tools/problem-tools-one-duipai.md`](docs/tools/problem-tools-one-duipai.md) |
| `test-data.py` | `scripts/problem-tools/test-data.py` | [`docs/tools/problem-tools-test-data.md`](docs/tools/problem-tools-test-data.md) |
| `randint.py` | `scripts/problem-tools/randint.py` | [`docs/tools/problem-tools-randint.md`](docs/tools/problem-tools-randint.md) |
| `input2dot.py` | `scripts/problem-tools/input2dot.py` | [`docs/tools/problem-tools-input2dot.md`](docs/tools/problem-tools-input2dot.md) |
| `dot2png.py` | `scripts/problem-tools/dot2png.py` | [`docs/tools/problem-tools-dot2png.md`](docs/tools/problem-tools-dot2png.md) |
| `luogu.py` | `scripts/problem-tools/luogu.py` | [`docs/tools/problem-tools-luogu.md`](docs/tools/problem-tools-luogu.md) |
| `oj` | `scripts/problem-tools/oj.js` | [`docs/tools/problem-tools-oj.md`](docs/tools/problem-tools-oj.md) |
| `r-lldb` | `scripts/problem-tools/lldb.sh` | [`docs/tools/problem-tools-r-lldb.md`](docs/tools/problem-tools-r-lldb.md) |
| `r-cgdb` | `scripts/problem-tools/r-cgdb.sh` | [`docs/tools/problem-tools-r-cgdb.md`](docs/tools/problem-tools-r-cgdb.md) |
| `nvimsizer` | `scripts/problem-tools/nvimsizer.sh` | [`docs/tools/problem-tools-nvimsizer.md`](docs/tools/problem-tools-nvimsizer.md) |
| `transfer` | `scripts/problem-tools/transfer.sh` | [`docs/tools/problem-tools-transfer.md`](docs/tools/problem-tools-transfer.md) |
| `r-list-all-scripts.py` | `scripts/problem-tools/r-list-all-scripts.py` | [`docs/tools/problem-tools-r-list-all-scripts.md`](docs/tools/problem-tools-r-list-all-scripts.md) |

## 8. 项目结构

```text
.
├── app.js                 # Fastify 应用构建入口
├── bin/www                # 网站启动脚本
├── lib/                   # 核心模块（题目管理、markdown 渲染等）
├── routes/                # 页面路由与 API 路由
├── views/                 # Pug 模板
├── public/                # 静态资源
├── problems/              # 题目 Markdown 数据（本地数据源）
├── scripts/problem-tools/ # 写题辅助脚本
├── scripts/problem-analysis-tools/ # 题解分析、随机数据与对拍脚本
├── .agents/skills/        # 本仓库使用的本地 AI skills
├── mcp/                   # MCP 网关服务
└── docs/                  # 设计与计划文档
```

## 9. 常用命令

### 根项目

```bash
npm test
npm start
```

题目解析工具：

```bash
python3 scripts/problem-analysis-tools/gen_random.py --pattern array -n 5
python3 scripts/problem-analysis-tools/check_sample.py problems/luogu/P1001
python3 scripts/problem-analysis-tools/duipai.py --gen problems/luogu/P1001/gen.py --user problems/luogu/P1001/main.cpp --brute problems/luogu/P1001/brute.cpp -n 200
```

源码阅读路径见：`docs/source-guide.md`

VPS + GitHub 自动部署教程见：`docs/deployment/vps-github-auto-deploy.md`

写题辅助脚本安装与使用见：`docs/problem-tools.md`

### MCP 子项目

```bash
cd mcp
npm test
npm start
npm run start:stdio
```

## 10. 开发说明

- 题目数据来自 `problems/`，启动时会扫描并用于检索。
- 如需扩展 AI 能力，优先在 `mcp/src/tools/` 下新增工具。
- API 变更后，请同步更新：
  - `views/api.pug`
  - `mcp/README.md`
