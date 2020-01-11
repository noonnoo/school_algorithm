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
	QueryPerformanceFrequency(&liFrequency); // 주파수(1초당 증가되는 카운트수)를 구한다. 시간측정의 초기화

	string s1 = "10111010100", s2 = "00111010110";

	//입력값 설정하기
	while (true) {
		char input;
		cout << "입력을 받을 거면 i을 문제 3에 나와있는 값으로 진행할 거면 p를 입력해주세요. ";
		cin >> input;

		/*입력 예제 교과서
		i
		abcbdab bdcaba
		*/
		if (input == 'i') {
			cout << "문자열 s1과 s2를 'abc bac' 와 같은 형태로 작성해주세요: ";
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

	//s1과 s2의 길이 구함
	int n1 = s1.length();
	int n2 = s2.length();
	int length;
	string str = "";

	dp = new int*[n1 + 1];							//dp공간 동적 생성
	dp_str = new string*[n1 + 1];					//LCS를 저장할 dp_str 공간 동적 생성
	for (int i = 0; i < n1 + 1; i++) {
		dp_str[i] = new string[n2 + 1];
		dp[i] = new int[n2 + 1];
		memset(dp[i], 0, sizeof(int)*(n2 + 1));		//메모리 공간을 0으로 초기화
	}

	cout << endl << "================================================================================================================" << endl << endl
		<< "DP는 교과서의 수도코드를 참고하여 작성했고, DP함수에서 n*n의 string 행렬을 만들어서 LCS문자열들을 모두 기억하는 형태로 작성해서 최종LCS를 구했습니다."
		<< "코드별 자세한 설명은 주석에 작성하였습니다." << endl << endl
		<< "DP실행 결과:" << endl << endl;


	QueryPerformanceCounter(&StartCounter); // 코드 수행 전 카운트 저장
	length = DP(s1, s2);
	QueryPerformanceCounter(&EndCounter); // 코드 수행 후 카운트 저장
	cout << "LCS의 길이: " << length << endl << "LCS 문장: " << dp_str[s1.length()][s2.length()] << endl;
	printf("수행시간 = %f 초\n", (double)(EndCounter.QuadPart - StartCounter.QuadPart) / (double)liFrequency.QuadPart);

	cout << endl << "================================================================================================================" << endl << endl
		<< "문자열 길이를 구하는 LCS는 교과서의 수도코드를 참고하여 작성했고, str을 레퍼런스 형태의 매개변수로 줘서 그전에 호출한 함수의 str에 변경된 str을 저장하는 형태로 작성해서 최종LCS를 구했습니다."
		<< "코드별 자세한 설명은 주석에 작성하였습니다." << endl << endl
		<< "재귀 실행 결과:" << endl << endl;

	QueryPerformanceCounter(&StartCounter); // 코드 수행 전 카운트 저장
	length = recursion(s1, s2, str);
	QueryPerformanceCounter(&EndCounter); // 코드 수행 후 카운트 저장
	cout << "LCS의 길이: " << length << endl << "LCS 문장: " << str << endl;
	printf("수행시간 = %f 초\n", (double)(EndCounter.QuadPart - StartCounter.QuadPart) / (double)liFrequency.QuadPart);

	cout << endl << "================================================================================================================" << endl;


	cout << endl << endl << "수행결과를 보면 동일하게 나오지만 dp에서 시간이 현저하게 줄어들었음을 확인할 수 있었습니다."
		<< endl << "문자열에 따라 DP 수행시간이 더 큰 경우도 간혹 있는데 이는 문자열 길이가 작을 때, recursion에서 반복되는 부분이 줄어들기 때문에 재귀에서 오히려 수행시간이 적게 나오는 것이라고 생각합니다."
		<< endl << "따라서 문자열이 길면 길수록 재귀에서는 훨씬 더 긴 시간이 소요됨을 알 수 있었습니다."
		<< endl;

	//동적으로 할당한 배열을 해제해준다.
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
	else if (s1[0] == s2[0]) {		//만약 s1의 첫번째 문자와 s2의 첫번째 문자가 같으면
		str += s1[0];				//str에 공통된 문자를 넣는다.
		return recursion(s1.substr(1, n - 1), s2.substr(1, m - 1), str) + 1;	//s1과 s2의 마지막 문자 하나씩을 자른 문자를 재귀로 돌리고 1을 더하여 리턴 
	}
	else {												//아니면
		string st1 = "", st2 = "";						//string temp 변수인 st1과 st2를 만든다. --> 그냥 str을 돌리면 재귀를 돌면서 반복되는 부분에서의 공통문자도 합쳐지기때문에, 공통문자가 아닐 때 새로 변수를 만들어서 중복으로 문자가 저장되는 것을 방지한다.
		int t1 = recursion(s1.substr(1, n - 1), s2, st1);		//s1의 앞을 자른 문자열과 s2를 넣고, str자리에 st1을 넣어서 재귀를 돌린다.
		int t2 = recursion(s1, s2.substr(1, m - 1), st2);		//s1과 s2의 앞을 자른 문자열을 넣고, str자리에 st2을 넣어서 재귀를 돌린다.

		if (t1 > t2) {			//t1이 t2보다 클 때
			str += st1;			//recursion으로 받아온 st1을 str에 합친다.
			return t1;
		}
		else {
			str += st2;			//recursion으로 받아온 st2를 str에 합친다.
			return t2;
		}
	}
}

int DP(string s1, string s2) {
	int n = s1.length();		//s1과 s2의 길이를 구해서 n과 m에 넣는다.
	int m = s2.length();

	for (int i = 1; i <= n; i++) {		//이중 for문을 돌면서 각각의 원소에 접근한다.
		for (int j = 1; j <= m; j++) {	//여기서 원소는 eij는 string1의 i번째 위치까지의 문자열과, string2의 j번째 위치까지의 문자열에 대한 LCS이다.
			if (s1.substr(i - 1, 1) == s2.substr(j - 1, 1)) {	//string1의 i번째 문자와 string2의 j번째 문자가 같으면 
				dp[i][j] = dp[i - 1][j - 1] + 1;				//dp에는 1을 더하고
				dp_str[i][j] = dp_str[i - 1][j - 1] + s1.substr(i - 1, 1);	//dp_str에는 그전의 문자열에 공통 문자를 추가한다.
			}
			else {												//아니라면
				dp[i][j] = getMax(dp[i - 1][j], dp[i][j - 1]);	//dp[i][j]는 dp[i][j-1]과 dp[i-1][j]중 큰 값을 대입한다. 
																//string1의 i까지 문자열과 string2의 j까지 문자열이 갖는 LCS는 i,j번째 문자가 같지 않으면 그전의 max값과 동일하기 때문
				if (dp[i - 1][j] == dp[i][j])					//dp[i][j-1]과 dp[i-1][j] 중 최대 값을 갖는 경우의 LCS문자열을 dp[i][j]에 넣는다.
					dp_str[i][j] = dp_str[i - 1][j];
				else
					dp_str[i][j] = dp_str[i][j - 1];
			}
		}
	}
	return dp[n][m];	//결과를 리턴한다.
}

int getMax(int a, int b) {		// 두 정수중 큰 수를 구하는 함수
	if (a > b)
		return a;
	else
		return b;
}