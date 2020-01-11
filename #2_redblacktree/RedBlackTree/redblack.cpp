#include "redblack.h"
#include <iostream>
using namespace std;

IntRBTree::IntRBTree() {
	z = new Node(black, 0, 0, 0, 0);	//z�� �ʱ�ȭ�ϴ� ���
	z->l = z; z->r = z;					//z�� ���� ������ �ڽĳ�� �Ѵ� z�� ����
	head = new Node(black, 0, 0, 0, z);	//z�� ������ �ڽ����� ���� head
}

Node *IntRBTree::search(int search_key)		//key�� ��带 ã��
{
	Node *x = head->r;		//0���� ����
	while (x != z) {		//x�� NIL�����ͳ�尡 �ƴϸ�
		if (x->key == search_key) return x;		//x�� Ű�� ã������ Ű�� ������ x ����
		x = (x->key > search_key) ? x->l : x->r;	//x�� Ű�� ã������ Ű���� ũ�� x�� ���� �ڽ� ����, ������ ������ �ڽĳ���
													//�ݺ����� ���Ƽ� ã�� Ű�� ���� x�� ã�Ƽ� ������ �� �ְ���
	}
	return NULL;	//���������� �������� ��ã���� ���ٴ� �ǹ̷� NULL�� �����Ѵ�.
}

void IntRBTree::insert(int v, int index)
{
	x = head; p = head; g = head;	//head������ ����
	while (x != z) {				//x�� �ʱ�ȭ ��尡 �ƴҶ� ��� �ݺ�
		gg = g; g = p; p = x;		//������带 �Ҿƹ��� ����, �Ҿƹ����� �θ����, �θ��带 �ڽĳ��� �ٲ�
		if (x->key == v) return;	//x�� Ű�� ���ε����� v�� ������ ��ȯ
		x = (x->key > v) ? x->l : x->r;		//x�� Ű�� v���� ũ�� x�� ���� �ڽĳ���, ������ ������ �ڽĳ��� �ٲ�
		if (x->l->b && x->r->b) this->split(v);		//(�ٲ�)x �ڽĳ���� ���� �����϶� ����
	}
	x = new Node(red, v, index, z, z);	//x�� ���ο� ��带 ����, �����̰� ���� ����Ű�� ���
	if (p->key > v) p->l = x;			//�θ��� Ű�� v���� ũ�� �θ��� ���ڽ����� x�� �����Ѵ�. 
	else p->r = x;						//�ƴϸ� �����ڽ����� x�� ����
	this->split(v); head->r->b = black;	//v�� �߽����� ����, ��Ʈ�� ���� ������ �ٲ۴�.
}

void IntRBTree::split(int v)
{
	x->b = red; x->l->b = black; x->r->b = black;		//x�� ���� ����, ���ڽ��� ��, �����ڽĵ� ��
	if (p->b) {											//�θ��� ���� �����̸�
		g->b = red;										//�Ҿƹ����� ���� ����
		if (g->key > v != p->key > v) p = this->rotate(v, g);		//�Ҿƹ����� Ű�� �θ��� Ű�� �Ѵ� v��Ű���� ũ�ų� �Ѵ� ���� ���� ��� �Ҿƹ��� �߽����� ȸ��
		x = this->rotate(v, gg);									//x�� �����Ҿƹ��� �������� ȸ���� ����� ��
		x->b = black;									//x�� ���� ������ ĥ��
	}
}

Node *IntRBTree::rotate(int v, Node *y)
{
	Node *gc, *c;								//�ڽİ� ���� ��带 ����
	c = (y->key > v) ? y->l : y->r;				//�ڽ��� ��� y�� Ű�� v���� ũ�� y�� ���ڽ�, �ƴϸ� �����ڽ�
	if (c->key > v) {							//�ڽĳ���� Ű�� v���� ũ��
		gc = c->l; c->l = gc->r; gc->r = c;		//���ڳ��� �ڽĳ���� ���ڽ�, �ڽĳ���� ���ڽ��� ���ڳ���� �����ڽ����� �Ҵ�, ������ �����ڽ��� �ڽĳ�带 �Ҵ�
	}
	else {										//�ƴϸ�
		gc = c->r; c->r = gc->l; gc->l = c;		//���ڳ��� �ڽ��� �����ڽ�, �ڽ��� �����ڽ��� ������ ���ڽ����� �Ҵ�, ������ ���ڽ��� �ڽĳ�带 �Ҵ���
	}
	if (y->key > v) y->l = gc;					//y�� Ű�� v���� Ŭ�� ���ڴ� y�� ���ڽ��� ��
	else y->r = gc;								//�ƴϸ� ���ڴ� y�� �����ڽ��� ��
	return gc;									//���ڳ�带 ��ȯ
}

void IntRBTree::show(int v)
{
	cout << v << endl;
	cout << "head: " << head->key << " ��: " << head->b <<endl;

	cout << "gg: " << gg->key << " ��: " << gg->b << endl;
	cout << "g: " << g->key << " ��: " << g->b << endl;
	cout << "p: " << p->key << " ��: " << p->b << endl;
	cout << "x: " << x->key << " ��: " << x->b << endl;
	cout << endl;

	cout << head->r->key << " ��: " << head->r->b << endl;
	Node *tmp = head->r;
	showChild(tmp);
}

void IntRBTree::showChild(Node * tmp)
{
	if (tmp == z)
		return;
	if (tmp->r != NULL) {
		cout << tmp->key << "������: " << tmp->r->key << " ��: " << tmp->r->b << endl;
		showChild(tmp->r);
	}
	if (tmp->l != NULL) {
		cout << tmp->key << "����: " << tmp->l->key << " ��: " << tmp->l->b << endl;
		showChild(tmp->l);
	}

	cout << endl;
}

