#!/usr/bin/env python
# -*- encoding: utf-8 -*-
"""
    heap.py
    ~~~~~
    Implementing a max-heap in Python

    :created: 2014-08-18 12:13:21 -0500
    :copyright: (c) 2014, Lambda Labs, Inc.
    :license: All Rights Reserved.
"""
from __future__ import print_function
import sys
from math import floor

def left_idx(idx):
    return 2 * idx + 1

def right_idx(idx):
    return 2 * idx + 2

def parent_idx(idx):
    return floor((idx - 1) / 2) if idx > 0 else 0

class Heap(object):
    """
    An array-based heap.
    """

    def __init__(self, values):
        self.values = values
        self.heap_size = len(values)

    def node_count(self):
        return self.heap_size

    def __repr__(self):
        return "<Heap number_items:%s>" % self.node_count()

    def __iter__(self):
        return iter(self.values)

    def valid_node(self, idx):
        return idx >= 0 and idx < self.node_count()

    def swap(self, a, b):
        av = self.values[a]
        self.values[a] = self.values[b]
        self.values[b] = av

    def decrement_key(self):
        self.heap_size -= 1

    def sort(self):
        root = 0
        while self.node_count():
            self.swap(root, self.node_count() - 1)
            self.decrement_key()
            self.max_heapify(root)
        return self.values

    def max_heapify(self, idx):
        l = left_idx(idx)
        r = right_idx(idx)
        largest = idx
        if self.valid_node(l) and self.values[l] > self.values[largest]:
            largest = l
        if self.valid_node(r) and self.values[r] > self.values[largest]:
            largest = r
        if largest != idx:
            self.swap(idx, largest)
            return self.max_heapify(largest)
        else:
            return self

def print_heap(h, idx):
    if idx == 0:
        print()
    sys.stdout.write("(")
    l = left_idx(idx)
    r = right_idx(idx)
    if h.valid_node(idx):
        sys.stdout.write("%s,%s\n" % (idx, h.values[idx]))
    if h.valid_node(l):
        print_heap(h, l)
    if h.valid_node(r):
        print_heap(h, r)
    sys.stdout.write(")")

# build a max-heap from the bottom up.
def max_heap(things):
    h = Heap(things)
    # from the least parent to the root.
    for idx in range((len(things) - 2) / 2, -1, -1):
        h.max_heapify(idx)
    return h

# ints -> sorted max heap
def heap_sort(ints):
    heap = max_heap(ints)
    return heap.sort()

def sint(x):
    try:
        return int(x)
    except:
        return None

if __name__ == '__main__':
    ints = [sint(x) for x in sys.stdin.read().split('\n') if sint(x) != None]
    print(ints)
    print(heap_sort(ints))
