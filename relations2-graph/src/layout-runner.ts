import { runLayoutSync } from './layout-core';
import type { LayoutInput, LayoutMessage, PositionMap } from './types';

export type LayoutTick = (positions: PositionMap) => void;

export class LayoutRunner {
  private worker: Worker | null = null;
  private generation = 0;

  run(input: LayoutInput, onTick: LayoutTick, onDone: LayoutTick, onError: (message: string) => void): void {
    this.cancel();
    const generation = ++this.generation;

    if (typeof Worker === 'undefined') {
      this.runOnMainThread(input, generation, onTick, onDone, onError);
      return;
    }

    try {
      const worker = new Worker(new URL('./layout.worker.ts', import.meta.url), { type: 'module' });
      this.worker = worker;
      let finished = false;
      worker.onmessage = (event: MessageEvent<LayoutMessage>) => {
        if (generation !== this.generation) return;
        const message = event.data;
        if (message.type === 'tick' && message.positions) onTick(message.positions);
        if (message.type === 'done' && message.positions) {
          finished = true;
          worker.terminate();
          this.worker = null;
          onDone(message.positions);
        }
        if (message.type === 'error') {
          finished = true;
          worker.terminate();
          this.worker = null;
          onError(message.message || '布局计算失败');
        }
      };
      worker.onerror = () => {
        if (finished || generation !== this.generation) return;
        finished = true;
        worker.terminate();
        this.worker = null;
        this.runOnMainThread(input, generation, onTick, onDone, onError);
      };
      worker.postMessage(input);
    } catch {
      this.runOnMainThread(input, generation, onTick, onDone, onError);
    }
  }

  cancel(): void {
    this.generation += 1;
    this.worker?.terminate();
    this.worker = null;
  }

  private runOnMainThread(
    input: LayoutInput,
    generation: number,
    onTick: LayoutTick,
    onDone: LayoutTick,
    onError: (message: string) => void,
  ): void {
    window.setTimeout(() => {
      if (generation !== this.generation) return;
      try {
        const positions = runLayoutSync(input, onTick);
        if (generation === this.generation) onDone(positions);
      } catch (error) {
        if (generation === this.generation) onError(error instanceof Error ? error.message : '布局计算失败');
      }
    }, 0);
  }
}
