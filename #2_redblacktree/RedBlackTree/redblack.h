#ifndef REDBLACK_H
#define REDBLACK_H

const int black = 0;
const int red = 1;

#define	MAX_STRKEY_LEN	20

class Node {
public:
	Node(int bb, int k, int i, Node *ll, Node *rr) {
		b = bb, key = k; index = i, l = ll, r = rr;
	};
	int b;			// 노드 색깔
	int key;		// 키 값
	int index;		
	Node *l, *r;	// left right
};

class IntRBTree {
public:
	IntRBTree();
	Node *search(int search_key);
	void insert(int v, int index);
	void split(int v);
	void show(int v);
	Node *rotate(int v, Node *y);
	void showChild(Node *tmp);
private:
	Node *head, *z, *gg, *g, *p, *x;
};

#endif