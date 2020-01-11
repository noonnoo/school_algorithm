#include <string>
#include <iostream>
#include <vector>
using namespace std;

int **dp;
int **str;
string **dpstr;

int getNum(int n);
void printDP(int n);
void printOrder(int i, int j);
void printOrderDP(int n);
int DP(const vector<int> &matrix, int n);

int main() {
	int n = 5;
	vector<int> matrix = { 10, 5, 20, 7, 15, 3 }; //10, 5, 20, 7, 15, 3 

	//�Է��� ���� ������ ������ matrix�� ����� ������ ���´�.
	char input;
	while (true) {
		cout << "�Է��� ���� �Ÿ� i�� ������ �����ִ� ������ ������ �Ÿ� p�� �Է����ּ���. ";
		cin >> input;

		//���� �Է� �޴� ���
		/*����
		i
		5
		30 20 10 10 20 30
 		*/
		if (input == 'i') {
			cout << "����� ������ �Է����ּ���. ";
			cin >> n;

			cout << "p���� �Է����ּ���.  ";
			matrix.clear();
			for (int i = 0; i <= n; i++) {
				int  tmp;
				cin >> tmp;
				matrix.push_back(tmp);
			}
			break;
		}
		else if (input == 'p') {
			break;
		}
		else {
			continue;
		}
	}

	//��� ���� ������ ��쿡�� �� ������ ���� �����ϴ� �迭dp�� ������ ������ ������ ������ �����ϴ� ��ġ k�� �����ϴ� str�� �ʱ�ȭ �߽��ϴ�. 
	dp = new int*[n];
	str = new int*[n + 1];		//���߿� str���·� ����Ϸ��� str�̶�� ���
	dpstr = new string*[n];
	for (int i = 0; i < n + 1; i++) {
		str[i] = new int[n + 1];
		if (i < n) {
			dp[i] = new int[n];
			dpstr[i] = new string[n];

			memset(dp[i], 0, sizeof(int)*n);	//�޸� ������ 0���� �ʱ�ȭ
		}
		memset(str[i], -1 , sizeof(int)*(n + 1));	//�޸� ������ -1�� �ʱ�ȭ
	}

	//1������ ���
	cout << endl << "========================================================================================" << endl << endl;
	cout << "1��, ��� ������ ���� ������ �� ��� �ΰ�?" << endl << endl
		<< "numdp[n]�� i�� 2���� n - 2�� ������ �� �� NUM[i]*NUM[n-i]�� �հ� NUM[n-1] * 2�� ������ �̷������." << endl
		<< "��ȭ���� ���ϸ� ������ ����." << endl
		<< "NUM[n] = NUM[n-1] * 2 + �ñ׸�(i = 2 ~ n-2) NUM[i] * [n-i]" << endl << endl;
	int num = getNum(n);
	cout << endl << "���� n�� " << n << "�� ��, ����� ���ϴ� ���� �� " << num << "�� �̴�." << endl << endl;

	//2������ ������
	cout << "========================================================================================" << endl << endl
		<< "�� �ܰ躰 ���� ���� ��� ������" << endl << endl;

	int result = DP(matrix, n);
	cout << endl << "========================================================================================";
	cout << endl << "========================================================================================" << endl << endl;

	//2������ ��� ���
	cout << "�־��� ��ĵ��� ���� ������ ������ �� '" << result << "' ���� ���ϰ�"
		<< endl << "������ ���� ������ ���´� " << endl;

	cout << "���� ������ ��͸� �̿��ߴ�: ";
	printOrder(0, n - 1);
	cout << endl << "���� ������ DP�� �̿��ߴ�: ";
	printOrderDP(n);

	cout << endl << endl << "������ ���ϴ� ��쿡�� ���� ������ ���� �����ϴ� min�� ���� ���¿��� ��͸� �̿��ϸ� �ߺ��Ǵ� ��찡 ����, DP�� ���� ��ȭ���� �ݺ������� Ǯ� ������ ���̱� ������ ���� �ð� ���⵵�� ���������, DP�� ��쿡 �����ϴ� ������ ������ �� �ʿ��ؼ� �������⵵�鿡���� ������ ��Ͱ� ���ٰ� �����Ѵ�."
		<< endl << "Ư���� ������ ������ ���ϴ� ��쿡�� dp�� ���� ���� ����� ���� ���� ���� �ϴ� min(�ڵ忡�� str �迭)�� ���� ���¿��� ��͸�(�� ���, �� dp) �̿��ϸ� �ߺ��� ���� ������ �ڵ��� ���Ἲ�� �޸𸮰��� ���⵵ �鿡���� ��Ͱ� �� ���ٰ� �����Ѵ�."
		<< endl << "�� ���� ���� ��� ���� �����ϴ� min���� ������ int�� ���ߺ��� str�� �̿����� ���� ����̴�." << endl;
	

	cout << endl <<endl<< "dpstr�� �̿��ؼ� DP�� �����鼭 ���� ��Ʈ�� ���Ϳ� ���� �׾ư��鼭 ���� ���: " << dpstr[0][n - 1] << endl
		<< "����� ���� �������� ���߽�Ʈ�� �迭�� �̿��ϱ� ������ ��ͺ��ٴ� �޸� ������ ū ���̴�. ������ dp�� ���鼭 �ѹ��� ���� ���� ��� ���� �ð��� ������ �� �ִ�."
		<< "���� ��µ� ��Ϳ� dp�� �켱������ DP�� ������ ���� ������ �����ϴ� min�� ������ integer ���� �迭�� �����־�� ��� ���� ���´�. ���� �� ����� ������ �˳��ϴٸ� �� ȿ�����̴�." ;

	cout << endl << endl << "========================================================================================";
	printDP(n);


	//�������� �Ҵ��� �迭�� ����
	for (int i = 0; i < n + 1; i++) {
		if (i < n) { 
			delete dp[i]; 
			delete[] dpstr[i];
		}
		delete[] str[i];
	}

	delete[] dp;
	delete[] dpstr;
	delete[] str;
}

int getNum(int n) {
	if (n == 1) return 0;		//default�� �־���� n�� 1, 2 �ΰ��� �ٷ� ���� �����մϴ�.
	else if (n == 2) return 1;

	int *numdp = new int[n];
	memset(numdp, 0, sizeof(int)*n);	//�޸� ������ 0���� �ʱ�ȭ

	//�迭�� �Ѱ��� �� �ΰ��� ���� ���� �ʱ�ȭ
	numdp[0] = 0;
	numdp[1] = 1;

	//numdp[n]�� i�� 2���� n - 2�� ������ �� �� NUM[i]*NUM[n-i]�� �հ� NUM[n-1] * 2�� ������ �̷������. 
	//��ȭ���� ���ϸ� ������ ����.
	// NUM[n] = NUM[n-1] * 2 + �ñ׸�(i = 2 ~ n-2) NUM[i] * [n-i]

	// NUM[4] = NUM[3] * 2 + NUM[2] * NUM[2]
	// NUM[5] = NUM[4] * 2 + NUM[3] * NUM[2] + NUM[2] * NUM[3]

	//�ε����� 0���� �����ϱ� ������ 1�� ���� ���˴ϴ�.
	for (int i = 2; i < n; i++) {
		numdp[i] += (numdp[i - 1]) * 2;
		if (i == n - 1)	cout << "NUM[" << n << "] = NUM[" << i << "] * 2 ";

		for (int j = 1; j < i - 1; j++) {
			numdp[i] += (numdp[j] * numdp[i - j - 1]);
			if (i == n - 1)	cout << "+ NUM[" << j + 1 << "] * NUM[" << i - j << "]";
		}
	}

	return numdp[n - 1];	//n�� ���� ������ ������ �����մϴ�.
}


int DP(const vector<int> &matrix, int n) {
	
	//dpstr�� �밢�� n*n�κ��� An��� �̸���� �ʱ�ȭ�Ѵ�. 
	for (int i = 0; i < n; i++) {
		dpstr[i][i] = "A" + to_string(i + 1);
	}


	for (int r = 0; r < n; r++) {			//�� �迭�� ���� ����, ������ ũ�⸦ �����ϴ� ����
		for (int i = 0; i < n - r; i++) {
			int j = i + r;					//�迭 n������ Ai���� Aj���� ���� ���ϰ��� �Ѵ�.

			if (i == j)						//i�� j�� ���� ���� �� ����� ���Ϸ��� ���̱� ������ �״�� 0
				continue;

			int mem;
			int min = 2147483647;			//min���� int���� ���� ū ������ ������
			for (int k = i; k < j; k++) {
				int tmp = dp[i][k] + dp[k + 1][j] + matrix[i] * matrix[k + 1] * matrix[j + 1];
				//�� ��� ������ ����Ǵ� ��Ȳ���� �� tmp�� �����鼭 ���� ���� ��찡 ���� ���� min�� ����Ѵ�.
				//n���� ����� ��� n-1��ŭ ���鼭 ��� ���ɼ��� �Ǵ��Ѵ�

				if (min > tmp) {
					min = tmp;		//min�� ���� ���� tmp�� ����Ѵ�.
					mem = k;		//mem�� ���� ���� tmp�� ������ k���� ����Ѵ�.
				}
			}
			dp[i][j] = min;
			//�� �ܰ迡���� ������ ����� �������� ����Ѵ�.
			str[i][j] = mem;	//str�� ���� ���� min�� ������ mem���� ���������� ����Ѵ�. (����� print����)
			dpstr[i][j] = "(" + dpstr[i][mem] + " * "+ dpstr[mem + 1][j] + ")";		//������ ���� �����ϴ� mem�� �̿��ؼ� ��� ���� ������ �����س�����.

			cout << "A" << i + 1 << "~A" << j + 1 << "������ ��: "
				<< min << " = (A" << i + 1 << "~A" << mem + 1 << ")�� �� + (A" << mem + 2 << "~A" << j + 1 << ")�� �� + "
				<< "p" << i + 1 << "* p" << mem + 2 << "* p" << j + 2 << " = "
				<< dp[i][mem] << " + " << dp[mem + 1][j] << " + "
				<< matrix[i] << "*" << matrix[mem + 1] << "*" << matrix[j + 1] << endl << endl;
		}
	}

	return dp[0][n - 1];
}

void printDP(int n) {
	cout << endl << "========================================================================================";
	cout << endl << "n���� �迭�� Ai���� Aj���� ���� ���� ������ ���� ���� ���� ǥ�̴�." << endl;

	//dp�� ���� ������ ����Ͽ� �����ش�.
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << "  [" << dp[i][j] << "]  ";
		}
		cout << endl;
	}
}

//���� ���� ����� min���� ������ str ���� �迭�� �̿��ؼ� ����� ����� �̴� ���
void printOrderDP(int n) {
	int index = 0;	
	string result = "";	//result�� ������� �����ϴ� string�̴�.
	vector<pair<bool, pair<int, int>>> ordertree;		//���ȣ���� ���� �ʱ� ������ min���� �����ϴ� i~k����, k+1~j�� �����ϸ鼭 i == k�� ����, k+1 == j�� ������ order�� �����ϰ� ����Ѵ�.

	//i�� j�� ��� Ai~ Aj�� ��Ÿ����, k�� ���س��ұ� ������ Ai~ak, Ak+1~Aj�� ���ؼ� Ʈ�����·� ������ ���ĳ��� �� �ִ�.
	int i = 0, j = n - 1;
	int k = str[i][j];

	//ù��° ��Ʈ���
	//�ڽ��� �ִ���(������ true ������ false) �����ϴ� ù��° �ε����� (i��, k��) Ȥ�� (k+1, j)���� �ι�° ����° �ε����� �����Ѵ�.
	if (i != j)
		ordertree.push_back(make_pair(1, make_pair(i, j)));
	else
		ordertree.push_back(make_pair(0, make_pair(i, j)));
	
	int count = 0;	//count�� ��ȣ�� ������ ������ ���������� ����� ���� �����̴�. while���� �� ������ count�� ���� ��ŭ ���� ��ȣ�� �߰��Ѵ�.
	while (index < ordertree.size()) {		//��� ��带 �� ��ġ���� �����Ѵ�. (Ʈ���� BFS�� ��ģ��. Ʈ���� ��� ���� �ڽ� 2���� ���ų� �ƿ��ڽ��� ���� �ʴ� �����̴�.)
		if (ordertree[index].first == true) {
			bool flag = false;	//flag�� ��ģ ��尡 ��� ������ �� true�� ���Եȴ�.
			i = ordertree[index].second.first;
			j = ordertree[index].second.second;
			k = str[i][j];
			result += "(";		//��带 ��ĥ �� ��ȣ�� ����.
			count++;
			if (i == k) {		//���� �ڽĳ�尡 ������ ���, ordertree�� ��带 �ְ�, �ش� ����� ����� result�� �ְ� flag�� true.
				ordertree.push_back(make_pair(false, make_pair(i, k)));
				result += "A" + to_string(i + 1);
				flag = true;
			}
			else {				//���� �ڽĳ�尡 ������ �ƴ� ���, ��带 ordertree�� �ְ� flag�� flase
				ordertree.push_back(make_pair(true, make_pair(i, k)));
				flag = false;
			}

			if (k + 1 == j) {	//������ �ڽĳ�尡 ������ ���, ordertree�� ��带 �ְ�, �ش� ����� ����� result�� �ְ� flag�� �̹� true���� ���� true.
				ordertree.push_back(make_pair(false, make_pair(k + 1, j)));
				result += "A" + to_string(k + 2);
				if (flag) flag = true;
			}
			else {				//������ �ڽĳ�尡 ������ �ƴ� ���, ��带 ordertree�� �ְ� flag�� flase
				ordertree.push_back(make_pair(true, make_pair(k + 1, j)));
				flag = false;
			}
			if (flag) {			//��ģ �ڽ� ��尡 ��� ������ �� �� ����� ���� ���ϴ� ����̹Ƿ� ��ȣ�� �ݴ´�.
				result += ")";
				count--;
			}

		}
		index++;				//�ε����� �÷��� ���� ���� �Ѿ��.
	}

	for (int i = 0; i < count; i++)		//�ݴ� ��ȣ�� ���� �ۼ��Ѵ�.
		result += ")";

	cout << result;				//����� ����Ѵ�.
}

void printOrder(int i, int j) {

	if (i == j)		//n���� ����� Ai~Aj�� ������ ������ ����� ���� ���� (Ai~Ak)(Ak+1~Aj)��� �� ��, k���� i���̸� 
		cout << "A" << i + 1;		// Ai�� ����Ѵ�.
	else {						//�ƴϸ� �Ʒ��� �����Ѵ�.
		cout << "(";			//k���� �������� ��ȣ�� ���� �ݴ´�.			
		printOrder(i, str[i][j]);		//����ؼ� ������ ����� ���� ���� i�� j�� ���� �� ������ ���ȣ���Ѵ�.
		printOrder(str[i][j] + 1, j);
		cout << ")";
	}

}

