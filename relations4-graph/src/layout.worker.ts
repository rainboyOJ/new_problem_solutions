import { createLayout, type LayoutInput } from './layout';
self.onmessage = (event: MessageEvent<LayoutInput>) => {
  try { self.postMessage({ positions: createLayout(event.data) }); }
  catch (error) { self.postMessage({ error: error instanceof Error ? error.message : '布局失败' }); }
};
