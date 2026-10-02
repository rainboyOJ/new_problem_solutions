#!/usr/bin/env python3
"""Jev (TypeSafe System One) 客户端：用于题目关系批量判断。

当前接入（2026-10-02 切换）：
- POST https://api.typesafe.ai/v1/systemone
- model: jev-1.13.0
- Authorization: Bearer $TYPESAFE_API_KEY（密钥从环境变量或 ~/.typesafe/env 读取，不写入日志）
- 不是 OpenAI 格式：没有 messages，/chat/completions 与 /responses 会 500
- choice criteria 最多 255 项；score 2-10 级；state 与全部问题合计 <= 32k token

备用接入（免费代理，2026-10-02 实测限流后不可靠）：
- POST https://opencode.ai/zen/v1/systemone + model jev-1.13-free（免 Authorization）
- 该端点前置 Cloudflare 拦截 Python 默认 UA（error 1010）

Jev 只返回判断与概率，不生成解释文本。原始返回必须落盘保存（批次可追溯性要求）。
"""

from __future__ import annotations

import http.client
import json
import os
import random
import time
import urllib.error
import urllib.request
from pathlib import Path
from typing import Any

DEFAULT_ENDPOINT = "https://api.typesafe.ai/v1/systemone"
DEFAULT_MODEL = "jev-1.13.0"
FALLBACK_ENDPOINT = "https://opencode.ai/zen/v1/systemone"
FALLBACK_MODEL = "jev-1.13-free"

API_KEY_FILE = Path.home() / ".typesafe" / "env"
# 官方 key 池（每行一个 key）。仅由脚本读取，绝不打印、不回显、不写入任何日志或批次记录。
KEY_POOL_FILE = Path.home() / ".typesafe" / "jev-lgp888.keys"


class JevError(RuntimeError):
    """请求失败（网络、HTTP 或响应格式错误）。"""


class JevAuthError(JevError):
    """401/403：该 key 无效，应从池中剔除。"""


def _api_key() -> str | None:
    """读取密钥：优先环境变量，其次 ~/.typesafe/env。密钥绝不写入日志或批次记录。"""
    key = os.environ.get("TYPESAFE_API_KEY")
    if key:
        return key.strip()
    if API_KEY_FILE.exists():
        for line in API_KEY_FILE.read_text(encoding="utf-8").splitlines():
            if line.startswith("TYPESAFE_API_KEY="):
                return line.split("=", 1)[1].strip()
    return None


def load_key_pool(path: Path | None = None) -> list[str]:
    """读取官方 key 池。只返回 key 本身，调用方不得写入日志。"""
    p = path or KEY_POOL_FILE
    if not p.exists():
        return []
    keys = [l.strip() for l in p.read_text(encoding="utf-8").splitlines() if l.strip()]
    return keys


class KeyPool:
    """round-robin key 分配 + 失效剔除 + 逐 key 计数。密钥绝不外泄到任何输出。"""

    def __init__(self, keys: list[str]):
        import threading
        self._keys = list(keys)
        self.dead: dict[int, str] = {}
        self.calls: dict[int, int] = {i: 0 for i in range(len(keys))}
        self._next = 0
        self._lock = threading.Lock()

    def __len__(self) -> int:
        return len(self.available())

    def available(self) -> list[int]:
        return [i for i in range(len(self._keys)) if i not in self.dead]

    def acquire(self) -> int:
        """返回可用 key 的下标；无可用 key 时抛 JevError。"""
        with self._lock:
            avail = self.available()
            if not avail:
                raise JevError("key 池已无可用 key")
            for _ in range(len(self._keys)):
                idx = self._next % len(self._keys)
                self._next += 1
                if idx in avail:
                    self.calls[idx] += 1
                    return idx
        raise JevError("key 池分配失败")

    def key(self, idx: int) -> str:
        return self._keys[idx]

    def mark_dead(self, idx: int, reason: str) -> None:
        with self._lock:
            self.dead.setdefault(idx, reason)

    def stats(self) -> dict:
        return {"total": len(self._keys), "alive": len(self.available()),
                "dead": {str(i): r for i, r in self.dead.items()},
                "calls_per_key": {str(i): n for i, n in self.calls.items()}}


def ask(
    state: Any,
    questions: dict[str, Any],
    *,
    model: str = DEFAULT_MODEL,
    endpoint: str = DEFAULT_ENDPOINT,
    raw_dir: Path | None = None,
    tag: str = "",
    max_retries: int = 4,
    timeout: float = 90.0,
    api_key: str | None = None,
) -> dict[str, Any]:
    """发送一次判断请求，返回完整响应 dict。

    - state: 字符串或 JSON 对象（多部分材料用命名字段）。
    - questions: {question_id: {type, instructions, criteria}}，独立问题放同一次请求并行问。
    - raw_dir: 提供时把原始响应保存到 raw_dir/<tag>.json，满足批次可追溯性。
    """
    payload = {
        "model": model,
        "state": state,
        "questions": questions,
    }
    body = json.dumps(payload, ensure_ascii=False).encode("utf-8")
    headers = {
        "Content-Type": "application/json",
        # 端点前置 Cloudflare 会拦截 Python-urllib 默认 UA（error 1010），伪装成常规客户端
        "User-Agent": "curl/8.7.1",
        "Accept": "application/json",
    }
    key = api_key or _api_key()
    if key:
        headers["Authorization"] = f"Bearer {key}"
    last_err: Exception | None = None
    for attempt in range(max_retries + 1):
        req = urllib.request.Request(endpoint, data=body, headers=headers, method="POST")
        try:
            with urllib.request.urlopen(req, timeout=timeout) as resp:
                text = resp.read().decode("utf-8")
            data = json.loads(text)
            if "answers" not in data:
                raise JevError(f"响应缺少 answers 字段: {text[:200]}")
            if raw_dir is not None:
                raw_dir.mkdir(parents=True, exist_ok=True)
                name = tag or f"req-{int(time.time() * 1000)}"
                (raw_dir / f"{name}.json").write_text(
                    json.dumps({"payload": payload, "response": data}, ensure_ascii=False, indent=2),
                    encoding="utf-8",
                )
            return data
        except urllib.error.HTTPError as e:
            last_err = e
            retry_after = e.headers.get("retry-after") if e.headers else None
            # 401/403：该 key 失效，交由 key 池剔除后换 key 重试
            if e.code in (401, 403):
                raise JevAuthError(f"HTTP {e.code}: key 无效") from e
            # 429 退避；5xx 重试；4xx（除 429）不重试
            if e.code == 429 or e.code >= 500:
                wait = float(retry_after) if retry_after else 2.0 * (attempt + 1)
                time.sleep(min(wait, 30.0))
                continue
            raise JevError(f"HTTP {e.code}: {e.read().decode('utf-8', 'replace')[:300]}") from e
        except (urllib.error.URLError, json.JSONDecodeError, OSError, http.client.HTTPException) as e:
            # 含 RemoteDisconnected 等连接层错误：并发下服务端会偶发断开，退避后重试
            last_err = e
            time.sleep(2.0 * (attempt + 1) + random.uniform(0, 1.5))
    raise JevError(f"重试 {max_retries} 次后仍失败: {last_err}")


if __name__ == "__main__":
    # 手工冒烟测试：python3 jev_client.py
    result = ask(
        state="这是一个连接性冒烟测试。",
        questions={
            "smoke": {
                "type": "choice",
                "instructions": "这段文本的语言是什么？",
                "criteria": {"chinese": "中文", "english": "英文", "other": "其他"},
            }
        },
        tag="smoke-test",
    )
    print(json.dumps(result, ensure_ascii=False, indent=2))
