# Tree Analyzer

A C++ program for analyzing a tree data structure using a parent array. The program supports operations like finding children, height, level, LCA (Least Common Ancestor), leaf nodes, subtree traversal, and more.

## Features
- Add parent-child relationships
- Query parent, children, and leaf nodes
- Compute node levels and subtree sizes
- Find Least Common Ancestor (LCA)
- Get all nodes at a given level
- Determine the path between two nodes

## Sample Commands
- `P x` — prints parent of node x  
- `C x` — prints children of node x  
- `L x` — prints level of node x  
- `A x y` — finds LCA of x and y  
- `F x y` — finds path from x to y  
- `N x` — lists all nodes in subtree rooted at x  
- `H x` — height of node x  
- `E level` — all nodes at a certain level

## How to Run
```bash
g++ main.cpp -o tree-analyzer
./tree-analyzer < input.txt
