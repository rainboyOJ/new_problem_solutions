export const GRAPH_THEME = {
  canvas: '#000011', surface: '#0b1020', input: '#151d30', border: '#263247',
  text: '#e6edf7', muted: '#a6b2c5', overviewEdge: '#94a3b8', pre: '#fbbf24',
  next: '#7db5ff', common: '#5eead4', centerRing: '#f8fafc', hoverRing: '#fbbf24',
} as const;

export function getGraphCategoryColor(input: string): string {
  const value = (input || '').trim();
  if (!value) return '#7db5ff';
  const hex = value.match(/^#([0-9a-f]{6})$/i);
  if (!hex) return '#7db5ff';
  const n = Number.parseInt(hex[1], 16);
  const r = n >> 16, g = (n >> 8) & 255, b = n & 255;
  const max = Math.max(r, g, b), min = Math.min(r, g, b);
  const lift = max < 150 ? 150 - max : 0;
  return `rgb(${Math.min(255, r + lift)},${Math.min(255, g + lift)},${Math.min(255, b + lift)})`;
}
