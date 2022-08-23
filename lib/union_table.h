/**
 * @file union_table.h
 * @author Ayush Sinha
 * @brief Union table library for graph questions.
 * @version 0.1
 * @date 2022-08-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef UNION_TABLE_H
#define UNION_TABLE_H


class union_table {

    int numComponents;
    int __size;

    int* sz;
    int* id;

public:

    union_table() {
        numComponents = 0;
    }

    union_table(int __n) {
        numComponents = __size = __n;

        sz = new int[__n];
        id = new int[__n];

        for (int i = 0; i < __n; i++) {
            sz[i] = 1;
            id[i] = i;
        }

    }

    int find(int p) {

        // Find the root group for an element
        int root = p;
        while (root != id[root])
            root = id[root];


        // Appling path compression to a element
        while (p != root) {
            int next = id[p];
            id[p] = root;
            p = next;
        }

        return root;
    }

    bool is_connected(int p, int q) {
        return find(p) == find(q);
    }

    int component_size() {
        return numComponents;
    }

    int size(int p) {
        return sz[find(p)];
    }

    // Joins element p and element q to same group
    void unify(int p, int q) {
        int root_p = find(p);
        int root_q = find(q);

        // p and q already in same group.
        if (root_p == root_q) return;

        // Adding smaller group to a larger group
        if (sz[root_p] < sz[root_q]) {
            sz[root_q] += sz[root_p];
            id[root_p] = root_q;
        } else {
            sz[root_p] += sz[root_q];
            id[root_q] = root_p;
        }

        numComponents--;
    }


};


#endif

