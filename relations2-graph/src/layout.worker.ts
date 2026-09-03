/// <reference lib="webworker" />

import { runLayoutSync } from './layout-core';
import type { LayoutInput, LayoutMessage } from './types';

self.onmessage = (event: MessageEvent<LayoutInput>) => {
  try {
    const finalPositions = runLayoutSync(event.data, (positions) => {
      self.postMessage({ type: 'tick', positions } satisfies LayoutMessage);
    });
    self.postMessage({ type: 'done', positions: finalPositions } satisfies LayoutMessage);
  } catch (error) {
    self.postMessage({
      type: 'error',
      message: error instanceof Error ? error.message : '布局计算失败',
    } satisfies LayoutMessage);
  }
};
