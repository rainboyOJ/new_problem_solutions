#!/usr/bin/env python3
# Author: 2026-10-09 08:30

import sys

def solve() -> None:
    data = sys.stdin.read().split()
    if not data:
        return
    
    iterator = iter(data)
    
    n_str = next(iterator, None)
    if n_str is None:
        return
    n = int(n_str)
    
    a_vals = []
    for _ in range(n):
        a_vals.append(int(next(iterator)))
        
    b_vals = []
    for _ in range(n):
        b_vals.append(int(next(iterator)))
        
    class Job:
        def __init__(self, id_val, a, b):
            self.id = id_val
            self.a = a
            self.b = b
            if self.a <= self.b:
                self.group = 1
            else:
                self.group = 2
                
    jobs = []
    for i in range(n):
        jobs.append(Job(i + 1, a_vals[i], b_vals[i]))
        
    def get_key(job):
        if job.group == 1:
            return (job.group, job.a, -job.b)
        else:
            return (job.group, -job.b, job.a)
            
    jobs.sort(key=get_key)
    
    t_a = 0
    t_b = 0
    for job in jobs:
        t_a += job.a
        t_b = max(t_b, t_a) + job.b
        
    print(t_b)
    print(" ".join(str(job.id) for job in jobs))

if __name__ == '__main__':
    solve()