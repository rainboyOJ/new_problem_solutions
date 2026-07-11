from __future__ import annotations

from dataclasses import dataclass, field
from html import unescape
from html.parser import HTMLParser
import json
from pathlib import Path
import re
from typing import Any
from http.cookiejar import CookieJar
from urllib.error import URLError
from urllib.request import HTTPCookieProcessor, Request, build_opener


class FetchError(RuntimeError):
    """抓取失败但不一定阻止创建 skeleton。"""


@dataclass
class Sample:
    input: str
    output: str


@dataclass
class ProblemData:
    oj: str
    problem_id: str
    problem_dir_id: str
    source: str
    title: str = ""
    statement_md: str = ""
    samples: list[Sample] = field(default_factory=list)
    warnings: list[str] = field(default_factory=list)


@dataclass
class FetchResult:
    data: ProblemData
    fetched: bool
    warnings: list[str] = field(default_factory=list)


class ElementByIdParser(HTMLParser):
    """只提取某个 id 的标签内容，避免为了一个 script 强依赖 bs4。"""

    def __init__(self, target_id: str):
        super().__init__(convert_charrefs=False)
        self.target_id = target_id
        self._capture = False
        self._depth = 0
        self.parts: list[str] = []

    def handle_starttag(self, tag: str, attrs: list[tuple[str, str | None]]) -> None:
        attrs_dict = dict(attrs)
        if attrs_dict.get("id") == self.target_id:
            self._capture = True
            self._depth = 1
            return
        if self._capture:
            self._depth += 1

    def handle_endtag(self, tag: str) -> None:
        if self._capture:
            self._depth -= 1
            if self._depth <= 0:
                self._capture = False

    def handle_data(self, data: str) -> None:
        if self._capture:
            self.parts.append(data)

    def content(self) -> str:
        return "".join(self.parts).strip()


class BaseFetcher:
    name = ""
    aliases: tuple[str, ...] = ()
    site_prefixes: tuple[str, ...] = ()

    def match_name(self, oj: str) -> bool:
        lowered = oj.lower()
        return lowered == self.name or lowered in self.aliases

    def match_url(self, url: str) -> bool:
        return any(url.startswith(prefix) for prefix in self.site_prefixes)

    def parse_url(self, url: str) -> tuple[str, str]:
        raise NotImplementedError

    def build_data_from_id(self, oj: str, problem_id: str) -> ProblemData:
        raise NotImplementedError

    def fetch(self, oj: str, problem_id: str) -> FetchResult:
        data = self.build_data_from_id(oj, problem_id)
        data.warnings.append(f"{self.name} 第一版只生成 skeleton，暂未实现完整题面/样例抓取。")
        return FetchResult(data=data, fetched=False, warnings=list(data.warnings))

    def fetch_by_url(self, url: str) -> FetchResult:
        oj, problem_id = self.parse_url(url)
        result = self.fetch(oj, problem_id)
        result.data.source = url
        return result

    def http_get(self, url: str, timeout: int = 15) -> str:
        # 给 OJ 一个正常 UA，减少被默认 urllib UA 拦截的概率。
        data, charset = self.http_get_bytes(url, timeout=timeout)
        return data.decode(charset, errors="replace")

    def http_get_bytes(self, url: str, timeout: int = 15) -> tuple[bytes, str]:
        # 给 OJ 一个正常 UA，减少被默认 urllib UA 拦截的概率。
        request = Request(
            url,
            headers={
                "User-Agent": (
                    "Mozilla/5.0 (X11; Linux x86_64) "
                    "AppleWebKit/537.36 (KHTML, like Gecko) "
                    "Chrome/120.0 Safari/537.36"
                )
            },
        )
        try:
            opener = build_opener(HTTPCookieProcessor(CookieJar()))
            with opener.open(request, timeout=timeout) as response:
                charset = response.headers.get_content_charset() or "utf-8"
                return response.read(), charset
        except URLError as exc:
            raise FetchError(f"网络请求失败：{url}: {exc}") from exc


def extract_element_by_id(html: str, element_id: str) -> str:
    """优先使用 bs4；当前环境没有 bs4 时，用小型 HTMLParser fallback。"""

    try:
        from bs4 import BeautifulSoup  # type: ignore
    except Exception:
        parser = ElementByIdParser(element_id)
        parser.feed(html)
        return unescape(parser.content())

    soup = BeautifulSoup(html, "html.parser")
    element = soup.find(id=element_id)
    if element is None:
        return ""
    return element.decode_contents().strip()


def extract_json_script(html: str, element_id: str) -> dict[str, Any]:
    content = extract_element_by_id(html, element_id)
    if not content:
        raise FetchError(f"未找到 #{element_id} JSON 数据。")
    try:
        return json.loads(content)
    except json.JSONDecodeError as exc:
        raise FetchError(f"#{element_id} JSON 解析失败：{exc}") from exc


def markdown_section(title: str, content: str | None) -> str:
    if not isinstance(content, str) or not content.strip():
        return ""
    return f"## {title}\n\n{content.strip()}\n"


def normalize_space(text: str) -> str:
    return re.sub(r"\s+", " ", text).strip()


def safe_write_text(path: Path, content: str, *, overwrite: bool) -> bool:
    if path.exists() and not overwrite:
        return False
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(content, encoding="utf-8")
    return True
