# agy CLI 本机实测记录

版本：`agy` 1.4.7（`/home/rainboy/.local/bin/agy`），账号已登录，配置在 `~/.gemini/antigravity-cli/settings.json`。
下列每条都在本机跑过，日期 2026-10-26。官方文档与本文冲突时，以本文为准，并重新验证。

## 基本调用

```bash
# 最小调用
agy -p="只回答 ok" --output-format json
# 返回
{"conversation_id":"…","status":"SUCCESS","response":"ok\n","duration_seconds":2.97,
 "num_turns":1,"usage":{"input_tokens":6767,"output_tokens":1,"thinking_tokens":0,"total_tokens":6768}}
```

- `-p`/`--print` 必须写成 `-p=值` 紧贴的形式。写成 `-p "文本" --output-format json` 时，`--print` 会把紧跟的 `--output-format` 当成提示词，然后报错：`--print took "--output-format" as its prompt`。
- **stdin 不能当提示词**。`printf '…' | agy --print` 会打印帮助；`printf '…' | agy -p --output-format json` 报上面那个错。别再试重定向，用 `-p=值`。
- 返回字段：`conversation_id`、`status`、`response`、`duration_seconds`、`num_turns`、`usage`、`denied_actions`（有工具被拒时出现）、`structured_output`（用 `--json-schema` 时出现）、`error`（失败时出现）。

## 模型

**本项目只允许使用 `gemini-3.8-flash-high`，其他模型一律禁止**（见 SKILL.md 的「模型：只准用一个」）。

`agy models` 会列出当前账号可用的全部模型，但这份列表**不是可选清单**：除 `gemini-3.8-flash-high` 外的任何 id 都不许用。

- 每次调用都显式写 `-m gemini-3.8-flash-high`；不要依赖 `settings.json` 里的默认模型。
- 不要传 `--effort`。既然固定一个模型，就不需要碰它。

## 时间限制

- `--print-timeout` 接受 `90s`、`15m` 形式（两者都验过）。默认 `0s` 表示一直等到这一轮结束——**必须显式设置**，否则可能挂很久。
- 外层再包 `timeout`：`--print-timeout` 只管 agy 内部的这一轮。
- 实测耗时波动很大，见 SKILL.md 的表；续接会话的追问出现过 151 s。

## 权限（最容易踩的地方）

`agy` 1.4.7 在无头模式下，任何需要人工确认的工具都会被**软拒绝**，并往 stderr 打一行：

```
jetski: no output produced — a tool required the "command" permission that headless mode cannot prompt for,
so it was auto-denied. Add an allow-rule under permissions.allow in settings.json (e.g. command(<target>)).
Alternatively, re-run with --dangerously-skip-permissions to auto-approve all tools.
```

要点：

1. **这种情况下 `status` 仍然是 `SUCCESS`，但 `response` 是空字符串**，同时 `denied_actions` 非空（例如 `[{"action":"command","display_name":"RunCommand"}]`）。只看 `status` 会以为成功。
2. **`permissions.allow` 白名单在本版本无效**。实测往 `settings.json` 注入 `"permissions":{"allow":["command(wc)"]}`（以及 `command(timeout)`、`run_command`、`command(*)`），重跑仍被拒；且 agy 退出后重写 `settings.json`，把整个 `permissions` 键丢掉。注入前后的文件 diff 证明它被清掉了。
3. 唯一可用的放行方式是 `--dangerously-skip-permissions`，它批准**全部**工具，包括 `write_to_file`、`replace_file_content`、`run_command`。
4. 放行后 agy 实际执行命令时会自带 `timeout` 前缀，例如请求"统计行数"它跑的是 `timeout 10 wc -l < file`。按二进制名做白名单的想法天然不可靠。
5. 只读工具（`view_file` / `grep_search` / `list_dir`）在**不**放行时也能用，所以纯粹的"读一个文件回答问题"不需要 `-w`。
6. 但让它**自己**去大文件里找一节，它会选择 `run_command`（`sed`/`head`）而不是 `view_file`，于是退出码 3。对策是把片段内联进提示词。
7. `--mode plan` 不解决这个问题：plan 模式下它改文件仍会尝试 `RunCommand` 并被拒（文件确实没被改，安全但白跑一轮）。
8. `trustedWorkspaces` 不影响命令权限（受信工作区里照样被拒）。

## 结构化输出

```bash
agy -p="…" --output-format json --json-schema '{"type":"object","properties":{"ok":{"type":"boolean"}},"required":["ok"]}'
```

- 返回里多出 `json_schema` 与 `structured_output` 两个字段；`response` 里仍然是一段自然语言（可能包含一个 JSON 代码块）。
- **`structured_output` 可能不是答案**。实测：正文明确写 `ok: false（未使用 -1）`，而 `structured_output` 填的是 `{"ok":true,"reason":"已读取文件并判断…输出 ok 与 reason"}`——它把"任务复述"当成了答案。所以判定一律看 `response`。
- 用 `--json-schema` 的只读任务本身不需要 `-w`（验过），别因为看到权限报错就误以为 schema 必须放开权限。

## 多轮会话

```bash
# 第一次
agy -p="记住一个数: 41" --output-format json          # 记下 conversation_id
# 追问
agy --conversation <conversation_id> -p="刚才的数加 1 是多少" --output-format json
# 也可以用 -c 续接"最近一次"会话
```

验过上下文确实保留（回答 `42`，`num_turns:2`）。

## 常驻会话协议（stream-json）

官方文档写的 NDJSON 协议在本机可用，事件形状与文档一致：

```bash
printf '{"event":"user","message":{"content":"只回答 ok"}}\n' \
  | agy --input-format stream-json --output-format stream-json
```

输出事件序列：

| 事件 | 内容 |
| --- | --- |
| `init` | `conversation_id`、`init.cwd`、`init.tools`（全部工具名）、`init.permission_mode`（`request-review`） |
| `step_update` | `step_index`、`state`（`ACTIVE`/`DONE`）、`step_type`（`user_input`/`agent_response`/`tool`）；`agent_response` 带 `text_delta`，`tool` 带 `tool_name` 与 `tool_info.parameters` |
| `result` | 终态对象，字段同 `--output-format json` 的返回 |

`step_update` 的 `tool_info.parameters` 能看到它到底想跑什么命令（例如 `{"CommandLine":"timeout 10 wc -l < …"}`），排查被拒原因时很有用。

## 工作区与其他文件

- cwd 就是工作区；`--add-dir` 可追加目录。
- 项目级配置：`.antigravity/mcp_config.json`（MCP）、`.antigravityignore`（排除路径，类似 `.gitignore`）。
- 会话记录落在 `~/.gemini/antigravity-cli/conversations/`，日志 `cli.log`。提示词内容会进这些文件，不要贴密钥。
- 子命令：`agent`/`agents`、`models`、`mcp`、`plugin`、`changelog`、`update`、`remote-control`、`install`、`mic-serve`。

## 复验清单（怀疑行为变了就跑这几条）

```bash
agy --version                                   # 版本
agy models                                      # 模型列表
agy -p="只回答 ok" --output-format json          # 基本通路与延迟
agy -p="运行 wc -l <某个文件> 只输出数字" --output-format json   # 是否还需要 -w（看 denied_actions）
```
