# USACO Problem Set Luogu Links Design

## Goal

Add a clickable Luogu problem link beside every USACO entry in `problem-sets/2026-cspj-summer-first-prize.md`, while preserving the existing USACO link, completion state, grouping, order, and training notes.

## Scope

Modify only:

- `problem-sets/2026-cspj-summer-first-prize.md`

Do not modify USACO or Luogu solution articles, other problem sets, rendering code, or existing user changes.

## Entry Format

Keep both problem sources on the checklist line:

```markdown
- [x] [[problem: usaco,1515]]（洛谷：[[problem: luogu,P12022]]）
  训练点：简单枚举，规则映射，稳定处理输入输出。
```

Use the existing full-width Chinese parentheses and `洛谷：` label consistently. Do not move the Luogu link to a separate line and do not replace the USACO link.

## Problem Mapping

Use these verified USACO-to-Luogu mappings:

```text
1515 P12022   1491 P11836   1467 P11667   1443 P11449   1419 P10274
1395 P10187   1371 P10131   1347 P9974    1299 P9121    1251 P8897
1227 P8266    1179 P8090    1131 P9937    1107 P9943    1109 P9945
1083 P9940    1084 P9941    1059 P9955    1060 P9956    1035 P9952
1011 P9949    1012 P9950    987 P9946     988 P9947     963 P5831
964 P5832     965 P5833

1516 P12023   1517 P12024   1492 P11837   1493 P11838   1468 P11668
1469 P11669   1444 P11450   1445 P11451   1420 P10275   1421 P10276
1396 P10188   1397 P10189   1372 P10132   1373 P10133   1348 P9975
1349 P9976    1323 P9183    1324 P9184    1325 P9185    1300 P9122
1301 P9123    1275 P9010    1276 P9011    1277 P9012    1252 P8898
1253 P8899    1228 P8267    1229 P8268    1203 P8183    1204 P8184
1205 P8185    1180 P8091    1181 P8092    1155 P7993    1156 P7994

1518 P12025   1494 P11839   1470 P11670   1446 P11452   1422 P10277
1374 P10134   1350 P9977    1326 P9186    1278 P9013    1279 P9014
1254 P8900    1206 P8186    1182 P8093    1158 P7990    1110 P7411
1087 P7300    1062 P7148    1038 P6281

1520 P12027   1472 P11672   1448 P11454   1424 P10279   1400 P10192
1352 P9979    1328 P9188    1256 P8902    1112 P7410    1016 P6150
```

The mapping selects the original contest division when Luogu contains multiple problems with the same title. In particular:

- USACO 1469 uses Bronze `P11669`; USACO 1470 uses Silver `P11670`.
- USACO 1107 uses Bronze `P9943`; USACO 1110 uses Silver `P7411`.
- USACO 1443 maps to `P11449`, whose Luogu title misspells the official title as `Roundabount Rounding`.
- USACO 1448 maps to `P11454`, whose Luogu title uses `Conveyer` instead of the official `Conveyor`.

## Verification

1. Confirm the USACO section still contains exactly 90 USACO problem references.
2. Confirm it contains exactly 90 Luogu problem references.
3. Confirm every listed USACO ID has exactly one Luogu link and every pair matches the mapping above.
4. Confirm checklist states, section order, training notes, and all content outside the USACO section are unchanged.
5. Run the repository tests that cover problem-set rendering and Markdown problem links.
6. Request or render `/problem-sets/2026-cspj-summer-first-prize` and confirm both links render for representative T1, T2, T3, and T4 entries.
