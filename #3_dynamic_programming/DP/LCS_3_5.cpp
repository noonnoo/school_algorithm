#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <stdlib.h>
using namespace std;

int getMax(int a, int b);
int recursion(string s1, string s2, string &str);
int DP(string s1, string s2);

int **dp;
string **dp_str;

int main() {
	LARGE_INTEGER StartCounter, EndCounter, liFrequency;
	QueryPerformanceFrequency(&liFrequency); // ���ļ�(1�ʴ� �����Ǵ� ī��Ʈ��)�� ���Ѵ�. �ð������� �ʱ�ȭ

	string s1 = "10111010100", s2 = "00111010110";

	//�Է°� �����ϱ�
	while (true) {
		char input;
		cout << "�Է��� ���� �Ÿ� i�� ���� 3�� �����ִ� ������ ������ �Ÿ� p�� �Է����ּ���. ";
		cin >> input;

		/*�Է� ���� ������
		i
		abcbdab bdcaba
		*/
		if (input == 'i') {
			cout << "���ڿ� s1�� s2�� 'abc bac' �� ���� ���·� �ۼ����ּ���: ";
			cin >> s1 >> s2;
			break;
		}
		else if (input == 'p') {
			break;
		}
		else {
			continue;
		}
	}

	//s1�� s2�� ���� ����
	int n1 = s1.length();
	int n2 = s2.length();
	int length;
	string str = "";

	dp = new int*[n1 + 1];							//dp���� ���� ����
	dp_str = new string*[n1 + 1];					//LCS�� ������ dp_str ���� ���� ����
	for (int i = 0; i < n1 + 1; i++) {
		dp_str[i] = new string[n2 + 1];
		dp[i] = new int[n2 + 1];
		memset(dp[i], 0, sizeof(int)*(n2 + 1));		//�޸� ������ 0���� �ʱ�ȭ
	}

	cout << endl << "================================================================================================================" << endl << endl
		<< "DP�� �������� �����ڵ带 �����Ͽ� �ۼ��߰�, DP�Լ����� n*n�� string ����� ���� LCS���ڿ����� ��� ����ϴ� ���·� �ۼ��ؼ� ����LCS�� ���߽��ϴ�."
		<< "�ڵ庰 �ڼ��� ������ �ּ��� �ۼ��Ͽ����ϴ�." << endl << endl
		<< "DP���� ���:" << endl << endl;


	QueryPerformanceCounter(&StartCounter); // �ڵ� ���� �� ī��Ʈ ����
	length = DP(s1, s2);
	QueryPerformanceCounter(&EndCounter); // �ڵ� ���� �� ī��Ʈ ����
	cout << "LCS�� ����: " << length << endl << "LCS ����: " << dp_str[s1.length()][s2.length()] << endl;
	printf("����ð� = %f ��\n", (double)(EndCounter.QuadPart - StartCounter.QuadPart) / (double)liFrequency.QuadPart);

	cout << endl << "================================================================================================================" << endl << endl
		<< "���ڿ� ���̸� ���ϴ� LCS�� �������� �����ڵ带 �����Ͽ� �ۼ��߰�, str�� ���۷��� ������ �Ű������� �༭ ������ ȣ���� �Լ��� str�� ����� str�� �����ϴ� ���·� �ۼ��ؼ� ����LCS�� ���߽��ϴ�."
		<< "�ڵ庰 �ڼ��� ������ �ּ��� �ۼ��Ͽ����ϴ�." << endl << endl
		<< "��� ���� ���:" << endl << endl;

	QueryPerformanceCounter(&StartCounter); // �ڵ� ���� �� ī��Ʈ ����
	length = recursion(s1, s2, str);
	QueryPerformanceCounter(&EndCounter); // �ڵ� ���� �� ī��Ʈ ����
	cout << "LCS�� ����: " << length << endl << "LCS ����: " << str << endl;
	printf("����ð� = %f ��\n", (double)(EndCounter.QuadPart - StartCounter.QuadPart) / (double)liFrequency.QuadPart);

	cout << endl << "================================================================================================================" << endl;


	cout << endl << endl << "�������� ���� �����ϰ� �������� dp���� �ð��� �����ϰ� �پ������� Ȯ���� �� �־����ϴ�."
		<< endl << "���ڿ��� ���� DP ����ð��� �� ū ��쵵 ��Ȥ �ִµ� �̴� ���ڿ� ���̰� ���� ��, recursion���� �ݺ��Ǵ� �κ��� �پ��� ������ ��Ϳ��� ������ ����ð��� ���� ������ ���̶�� �����մϴ�."
		<< endl << "���� ���ڿ��� ��� ����� ��Ϳ����� �ξ� �� �� �ð��� �ҿ���� �� �� �־����ϴ�."
		<< endl;

	//�������� �Ҵ��� �迭�� �������ش�.
	for (int i = 0; i < n1 + 1; i++) {
		delete[] dp[i];
		delete[] dp_str[i];
	}

	delete[] dp;
	delete[] dp_str;
}

int recursion(string s1, string s2, string &str) {
	int n = s1.length();
	int m = s2.length();

	if (m == 0 || n == 0) {
		return 0;
	}
	else if (s1[0] == s2[0]) {		//���� s1�� ù��° ���ڿ� s2�� ù��° ���ڰ� ������
		str += s1[0];				//str�� ����� ���ڸ� �ִ´�.
		return recursion(s1.substr(1, n - 1), s2.substr(1, m - 1), str) + 1;	//s1�� s2�� ������ ���� �ϳ����� �ڸ� ���ڸ� ��ͷ� ������ 1�� ���Ͽ� ���� 
	}
	else {												//�ƴϸ�
		string st1 = "", st2 = "";						//string temp ������ st1�� st2�� �����. --> �׳� str�� ������ ��͸� ���鼭 �ݺ��Ǵ� �κп����� ���빮�ڵ� �������⶧����, ���빮�ڰ� �ƴ� �� ���� ������ ���� �ߺ����� ���ڰ� ����Ǵ� ���� �����Ѵ�.
		int t1 = recursion(s1.substr(1, n - 1), s2, st1);		//s1�� ���� �ڸ� ���ڿ��� s2�� �ְ�, str�ڸ��� st1�� �־ ��͸� ������.
		int t2 = recursion(s1, s2.substr(1, m - 1), st2);		//s1�� s2�� ���� �ڸ� ���ڿ��� �ְ�, str�ڸ��� st2�� �־ ��͸� ������.

		if (t1 > t2) {			//t1�� t2���� Ŭ ��
			str += st1;			//recursion���� �޾ƿ� st1�� str�� ��ģ��.
			return t1;
		}
		else {
			str += st2;			//recursion���� �޾ƿ� st2�� str�� ��ģ��.
			return t2;
		}
	}
}

int DP(string s1, string s2) {
	int n = s1.length();		//s1�� s2�� ���̸� ���ؼ� n�� m�� �ִ´�.
	int m = s2.length();

	for (int i = 1; i <= n; i++) {		//���� for���� ���鼭 ������ ���ҿ� �����Ѵ�.
		for (int j = 1; j <= m; j++) {	//���⼭ ���Ҵ� eij�� string1�� i��° ��ġ������ ���ڿ���, string2�� j��° ��ġ������ ���ڿ��� ���� LCS�̴�.
			if (s1.substr(i - 1, 1) == s2.substr(j - 1, 1)) {	//string1�� i��° ���ڿ� string2�� j��° ���ڰ� ������ 
				dp[i][j] = dp[i - 1][j - 1] + 1;				//dp���� 1�� ���ϰ�
				dp_str[i][j] = dp_str[i - 1][j - 1] + s1.substr(i - 1, 1);	//dp_str���� ������ ���ڿ��� ���� ���ڸ� �߰��Ѵ�.
			}
			else {												//�ƴ϶��
				dp[i][j] = getMax(dp[i - 1][j], dp[i][j - 1]);	//dp[i][j]�� dp[i][j-1]�� dp[i-1][j]�� ū ���� �����Ѵ�. 
																//string1�� i���� ���ڿ��� string2�� j���� ���ڿ��� ���� LCS�� i,j��° ���ڰ� ���� ������ ������ max���� �����ϱ� ����
				if (dp[i - 1][j] == dp[i][j])					//dp[i][j-1]�� dp[i-1][j] �� �ִ� ���� ���� ����� LCS���ڿ��� dp[i][j]�� �ִ´�.
					dp_str[i][j] = dp_str[i - 1][j];
				else
					dp_str[i][j] = dp_str[i][j - 1];
			}
		}
	}
	return dp[n][m];	//����� �����Ѵ�.
}

int getMax(int a, int b) {		// �� ������ ū ���� ���ϴ� �Լ�
	if (a > b)
		return a;
	else
		return b;
}