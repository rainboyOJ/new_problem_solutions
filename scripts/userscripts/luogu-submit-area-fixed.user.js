// ==UserScript==
// @name         洛谷窄屏自适应提交区
// @namespace    http://tampermonkey.net/
// @version      1.0
// @description  窄屏时让提交区排在侧栏前面，语言选择和提交按钮固定在可视区，不用滚动
// @author       Rainboy
// @match        https://www.luogu.com.cn/problem/*
// @grant        none
// ==/UserScript==

(function() {
    const style = document.createElement('style');
    style.textContent = `
        /* 窄屏时提交区置顶 */
        @media (max-width: 1000px) {
            .sidebar-container.reverse.layout {
                display: flex !important;
                flex-direction: column !important;
            }
            .sidebar-container.reverse.layout .main {
                order: -1 !important;
            }
        }

        /* 提交按钮 + 语言选择 固定在可视区 */
        .sidebar-container .main .burger .body > .combo-wrapper.lang-select {
            position: sticky;
            top: 0;
            z-index: 100;
            background: var(--lfe-color--white, #fff);
            padding: 4px 0;
        }
        .sidebar-container .main .burger .body > button.solid {
            position: sticky;
            bottom: 0;
            z-index: 100;
            background: var(--lfe-color--white, #fff);
            margin-top: 0 !important;
        }
    `;
    document.head.appendChild(style);
})();
