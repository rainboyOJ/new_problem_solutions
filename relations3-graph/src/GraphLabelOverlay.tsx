import React from 'react';
export interface GraphLabel { id: string; text: string; left: number; top: number; width: number; height: number; priority?: number }
export function GraphLabelOverlay({ labels }: { labels: GraphLabel[] }) {
  return <div className="relations3-label-overlay" aria-hidden="true">{labels.map(label => <span key={label.id} data-label-id={label.id} className={label.priority! <= 1 ? 'is-center' : ''} style={{ width: label.width, height: label.height, zIndex: label.priority! <= 1 ? 2 : 1, transform: `translate3d(${label.left}px,${label.top}px,0)` }}>{label.text}</span>)}</div>;
}
