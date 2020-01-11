#define MAX_NUM 50

#include <iostream>
#include <vector>
#include <time.h>
using namespace std;

int **dp;
int **flag;

void DP(vector<vector<int>> &matrix, int n);
int getMax(int i, int j);
void printPath(vector<vector<int>> &matrix, int n);

int main() {
	int n = 4;
	vector<vector<int>> matrix = { {6, 7, 12, 5}, {5, 3, 11, 18}, {7, 17, 3, 3}, {8, 10, 14, 9} };
	
	srand(time(0));
	//������ matrix�� ����� ������, ���� ���� ����� ��������� �����Ѵ�.
	while (true) {
		char input;

		cout << "������ ������ 4*4 ������ ����� ����� �Ŷ�� y�� ���ο� ���� ����� ����� ���̶�� n�� �Է����ּ���." << endl;
		cin >> input;
		if (input == 'y') {
			break;
		}
		else if (input == 'n') {
			matrix.clear();
			char pm;
			cout << "��� ��ҿ� ������ ���� �Ÿ� -�� ����� ���� �Ÿ� +�� �Է����ּ���. " << endl;
			cin >> pm;

			cout << "����� column���� row���� n�� �Է����ּ���.  " << endl;
			cin >> n;

			for (int i = 0; i < n; i++) {
				vector<int> tmp;
				for (int j = 0; j < n; j++) {
					int t;
					if (pm == '-')
						t = rand() % MAX_NUM * 2 - MAX_NUM;		//�밢�� �������� ����Ǳ� ���ؼ��� ��� �� �������� �־�߸� �Ѵ�.
																//����� �ִٸ� ��� ���� 0�̾ƴ� �̻� �밢�� �������� ���� ����.
					else
						t = rand() % MAX_NUM;
					tmp.push_back(t);							//�������� ������� �� t�� tmp���Ϳ� ����
				}
				matrix.push_back(tmp);				//0�� �ƴҶ� tmp���͸� matrix ���Ϳ� ����
			}
			break;
		}
		else {
			continue;
		}
	}

	//k���� �̸��� �ְ� ������ ���� ��dp�� k�� ��� �Դ��� �����ϴ� flag ���� �迭 �� �ʱ�ȭ
	dp = new int*[n + 1];
	flag = new int*[n + 1];
	for (int i = 0; i <= n; i++) {
		dp[i] = new int[n + 1];
		flag[i] = new int[n + 1];
		memset(dp[i], 0, sizeof(int)*(n + 1));		//�޸� ������ 0���� �ʱ�ȭ
		memset(flag[i], 0, sizeof(int)*(n + 1));		//�޸� ������ 0���� �ʱ�ȭ
	}

	cout << endl << "================================================================================================================" << endl ;
	cout << endl << "����� ������ ���� �����Ǿ����ϴ�." << endl;		//n�� ���� ����� �����Ѵ�. matrix�� vector�� �������.
	//������ ����� ����Ѵ�. -�� | �� �ȿ� �ִ� ���� ��Ұ��̰�, ���� ���� ��ǥ�� ��Ÿ����.
	for (int i = -1; i < n; i++) {
		for (int j = -1; j < n; j++) {
			if (j == -1) {									//index�κ� �� ����ϱ� ���� ��������.
				cout << i + 1 << " | ";
				continue;
			}
			if (i == -1) {
				cout << j + 1 << "  ";
				continue;
			}
			cout << matrix[i][j] << " ";
		}
		if (i == -1) {										//�ε��� ����� �ٹٲ�
			cout << endl;
			for (int j = 0; j <= n; j++)
				cout << "---";
		}
		cout << endl;
	}

	cout << endl << "================================================================================================================" << endl 
		<< "================================================================================================================" << endl ;
	DP(matrix, n);		//DP�� �����Ų��.
	cout << endl << "��Ģ��� �������� ���� �� �ִ� �ִ� ���� " << dp[n][n] << "�Դϴ�." << endl << endl;	//dp[n][n]���� ��� ���� ����Ѵ�.
	cout << "�ִ��� ���� �������� �� ���� ���� ��η� �����Դϴ�." << endl;		//printpath�� ��θ� ����Ѵ�.
	printPath(matrix, n);

	cout << endl << "��δ� dp�� �����ϸ鼭 ��� ���⿡�� �Դ����� ����صδ� flag�� ���� �ٽ� �ö󰡼� ������� ���� �ݺ����� ���� ��θ� ����ϴ� printPath�Լ��� �̿��߰�, �ڼ��� �ڵ� ������ �ּ��� �ֽ��ϴ�." << endl;

	cout << endl << "================================================================================================================" << endl
		<< "================================================================================================================" << endl << endl;

	for (int i = 0; i < n + 1; i++) {		//�������� �Ҵ��� �޸𸮸� �������ش�.
		delete[] dp[i];
		delete[] flag[i];
	}

	delete[] dp;
	delete[] flag;
}

void printPath(vector<vector<int>> &matrix, int num) {
	int n = num;
	int m = num;
	vector<int> result;
	vector<pair<int, int>> row_col;

	if (num == 0)return;
	row_col.push_back(make_pair(n, m));		//���� ������ ��Ҹ� ���� result�� �ְ� ����
	result.push_back(matrix[n - 1][m - 1]);

	while (n != 1 || m != 1) {		//n�� m�� 1�� �ƴҶ� ���� ����
		if (flag[n][m] == 3 && n != 1 && m != 1) 		//flag[n][m]�� 3�̰�, n�� m�� 1�� �ƴϸ� (�밢������ �°��)
			result.push_back(matrix[--n - 1][--m - 1]);	//matrix[n-2][m-2] �� n-1,m-1�� ��Ұ��� result�� �ְ�, n,m���� 1�� ����. (matrix�� 0���� �����ϱ� ������ 1�� ����)
		else if (flag[n][m] == 1 && m != 1)				//flag[n][m]�� 1�̰�, m�� 1�� �ƴϸ� (���ʿ��� �°��)
			result.push_back(matrix[n - 1][--m - 1]);	//matrix[n-1][m-2] �� n,m-1�� ��Ұ��� result�� �ְ�, m������ 1�� ����.
		else if (flag[n][m] == 2 && n != 1)				//flag[n][m]�� 2�̰�, n�� 1�� �ƴϸ� (���ʿ��� �°��)
			result.push_back(matrix[--n - 1][m - 1]);	//matrix[n-2][m-1] �� n-1,m�� ��Ұ��� result�� �ְ�, n������ 1�� ����.
		else
			break;
		row_col.push_back(make_pair(n, m));
	}

	for (int i = result.size() - 1; i > 0; i--) {	//path�� �������� �� �ֱ� ������ �Ųٷ� ����Ѵ�.
		cout << result[i] << "(" << row_col[i].second << "," << row_col[i].first << ")" << " -> ";
	}
	cout << result[0] << "(" << num << "," << num << ")" << endl;
}

void DP(vector<vector<int>> &matrix, int n) {

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			dp[i][j] = matrix[i - 1][j - 1] + getMax(i, j);		//dp[i][j]�� dp[i][j-1], dp[i-1][j]�� ���� ū ���� matrix[i-1][j-1](i,j�� ���� matrix ��)�� ���Ѵ�.
		}
	}
}

int getMax(int i, int j) {		//dp[i][j]�� dp[i][j-1], dp[i-1][j]�� ���� ū ���� ���� ���� ã�� �Լ�
	int a = dp[i][j - 1];
	int b = dp[i - 1][j];
	int c = dp[i - 1][j - 1];

	if (a == b && b == c && a == 0 && i == j && i ==1)	//1,1�� �� 0����: ����, ����, �밢���� ��� 0 �̰�, i�� j�� ������ 1�� ���� 1,1 ��Ȳ
		return 0;
	else if (i == 1) {			//���� ���� ���� ��� --> ������ ���ʿ����ۿ� ����	: ù ��Ұ� �����̸� �Ʒ� ���ǹ����� null���� ������ ������ ���� �ɷ���
		flag[i][j] = 1;			//���� ū���� a�̸� flag�� i,j-1 ��, ���ʿ��� �Դٰ� ǥ��: 1
		return a;
	}
	else if (j == 1) {			//���� ���� ���� ���	 --> ������ �����ʿ����ۿ� ����
		flag[i][j] = 2;			//���� ū���� a�̸� flag�� i-1,j ��, ���ʿ��� �Դٰ� ǥ��: 2
		return b;
	}


	if (c >= a && c >= b) {		//�밢���� ���� �缭 �����̳� ���� ���� 0�� ��쿡, �밢������ ���� �����Ͽ� path�� ���δ�.
		flag[i][j] = 3;			//���� ū���� a�̸� flag�� i-1,j-1 ��, �밢������ �Դٰ� ǥ��: 3
		return c;
	}
	else if (a >= b && a >= c) {
		flag[i][j] = 1;			//���� ū���� a�̸� flag�� i,j-1 ��, ���ʿ��� �Դٰ� ǥ��: 1
		return a;
	}
	else if (b >= a && b >= c) {
		flag[i][j] = 2;			//���� ū���� a�̸� flag�� i-1,j ��, ���ʿ��� �Դٰ� ǥ��: 2
		return b;
	}

}