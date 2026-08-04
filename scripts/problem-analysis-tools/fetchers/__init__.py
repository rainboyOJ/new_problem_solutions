"""Fetcher providers used by fetch_problem.py."""

from .base import FetchError, FetchResult, ProblemData, Sample
from .acwing import AcWingFetcher
from .atcoder import AtCoderFetcher
from .codeforces import CodeforcesFetcher
from .kattis import KattisFetcher
from .leetcodecn import LeetCodeCNFetcher
from .luogu import LuoguFetcher
from .shumeng import ShumengFetcher
from .usaco import USACOFetcher
from .vjudge import VJudgeFetcher


FETCHERS = [
    LuoguFetcher(),
    AtCoderFetcher(),
    KattisFetcher(),
    LeetCodeCNFetcher(),
    USACOFetcher(),
    CodeforcesFetcher(),
    ShumengFetcher(),
    VJudgeFetcher(),
    AcWingFetcher(),
]


__all__ = [
    "AcWingFetcher",
    "AtCoderFetcher",
    "CodeforcesFetcher",
    "FETCHERS",
    "FetchError",
    "FetchResult",
    "KattisFetcher",
    "LeetCodeCNFetcher",
    "LuoguFetcher",
    "ProblemData",
    "Sample",
    "ShumengFetcher",
    "USACOFetcher",
    "VJudgeFetcher",
]
