#include "redblack.h"
#include <iostream>
using namespace std;

IntRBTree::IntRBTree() {
	z = new Node(black, 0, 0, 0, 0);	//z는 초기화하는 노드
	z->l = z; z->r = z;					//z의 왼쪽 오른쪽 자식노드 둘다 z로 설정
	head = new Node(black, 0, 0, 0, z);	//z를 오른쪽 자식으로 갖는 head
}

Node *IntRBTree::search(int search_key)		//key로 노드를 찾음
{
	Node *x = head->r;		//0부터 시작
	while (x != z) {		//x가 NIL포인터노드가 아니면
		if (x->key == search_key) return x;		//x의 키와 찾으려는 키가 같으면 x 리턴
		x = (x->key > search_key) ? x->l : x->r;	//x의 키가 찾으려는 키보다 크면 x는 왼쪽 자식 노드로, 작으면 오른쪽 자식노드로
													//반복문을 돌아서 찾는 키와 같은 x를 찾아서 리턴할 수 있게함
	}
	return NULL;	//리프노드까지 내려가서 못찾으면 없다는 의미로 NULL을 리턴한다.
}

void IntRBTree::insert(int v, int index)
{
	x = head; p = head; g = head;	//head노드부터 시작
	while (x != z) {				//x가 초기화 노드가 아닐때 계속 반복
		gg = g; g = p; p = x;		//증조노드를 할아버지 노드로, 할아버지를 부모노드로, 부모노드를 자식노드로 바꿈
		if (x->key == v) return;	//x의 키가 새로들어오는 v와 같으면 반환
		x = (x->key > v) ? x->l : x->r;		//x의 키가 v보다 크면 x는 왼쪽 자식노드로, 작으면 오른쪽 자식노드로 바꿈
		if (x->l->b && x->r->b) this->split(v);		//(바뀐)x 자식노드의 색이 레드일때 분할
	}
	x = new Node(red, v, index, z, z);	//x에 새로운 노드를 생성, 레드이고 닐을 가리키는 노드
	if (p->key > v) p->l = x;			//부모의 키가 v보다 크면 부모의 왼자식으로 x를 지정한다. 
	else p->r = x;						//아니면 오른자식으로 x를 지정
	this->split(v); head->r->b = black;	//v를 중심으로 분할, 루트의 색을 블랙으로 바꾼다.
}

void IntRBTree::split(int v)
{
	x->b = red; x->l->b = black; x->r->b = black;		//x의 색은 레드, 왼자식은 블랙, 오른자식도 블랙
	if (p->b) {											//부모의 색이 레드이면
		g->b = red;										//할아버지의 색은 레드
		if (g->key > v != p->key > v) p = this->rotate(v, g);		//할아버지의 키와 부모의 키가 둘다 v의키보다 크거나 둘다 작지 않은 경우 할아버지 중심으로 회전
		x = this->rotate(v, gg);									//x는 증조할아버지 기준으로 회전한 결과가 됨
		x->b = black;									//x의 색을 블랙으로 칠함
	}
}

Node *IntRBTree::rotate(int v, Node *y)
{
	Node *gc, *c;								//자식과 손자 노드를 선언
	c = (y->key > v) ? y->l : y->r;				//자식은 노드 y의 키가 v보다 크면 y의 왼자식, 아니면 오른자식
	if (c->key > v) {							//자식노드의 키가 v보다 크면
		gc = c->l; c->l = gc->r; gc->r = c;		//손자노드는 자식노드의 왼자식, 자식노드의 왼자식은 손자노드의 오른자식으로 할당, 손자의 오른자식은 자식노드를 할당
	}
	else {										//아니면
		gc = c->r; c->r = gc->l; gc->l = c;		//손자노드는 자식의 오른자식, 자식의 오른자식은 손자의 왼자식으로 할당, 손자의 왼자식은 자식노드를 할당함
	}
	if (y->key > v) y->l = gc;					//y의 키가 v보다 클때 손자는 y의 왼자식이 됨
	else y->r = gc;								//아니면 손자는 y의 오른자식이 됨
	return gc;									//손자노드를 반환
}

void IntRBTree::show(int v)
{
	cout << v << endl;
	cout << "head: " << head->key << " 색: " << head->b <<endl;

	cout << "gg: " << gg->key << " 색: " << gg->b << endl;
	cout << "g: " << g->key << " 색: " << g->b << endl;
	cout << "p: " << p->key << " 색: " << p->b << endl;
	cout << "x: " << x->key << " 색: " << x->b << endl;
	cout << endl;

	cout << head->r->key << " 색: " << head->r->b << endl;
	Node *tmp = head->r;
	showChild(tmp);
}

void IntRBTree::showChild(Node * tmp)
{
	if (tmp == z)
		return;
	if (tmp->r != NULL) {
		cout << tmp->key << "오른쪽: " << tmp->r->key << " 색: " << tmp->r->b << endl;
		showChild(tmp->r);
	}
	if (tmp->l != NULL) {
		cout << tmp->key << "왼쪽: " << tmp->l->key << " 색: " << tmp->l->b << endl;
		showChild(tmp->l);
	}

	cout << endl;
}

