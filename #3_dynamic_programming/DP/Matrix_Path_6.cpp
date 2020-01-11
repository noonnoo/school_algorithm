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
	//기존의 matrix를 사용할 것인지, 새로 랜덤 행렬을 만들것인지 결정한다.
	while (true) {
		char input;

		cout << "기존에 설정된 4*4 교과서 행렬을 사용할 거라면 y를 새로운 랜덤 행렬을 사용할 것이라면 n를 입력해주세요." << endl;
		cin >> input;
		if (input == 'y') {
			break;
		}
		else if (input == 'n') {
			matrix.clear();
			char pm;
			cout << "행렬 요소에 음수를 넣을 거면 -를 양수만 넣을 거면 +를 입력해주세요. " << endl;
			cin >> pm;

			cout << "행렬의 column수와 row수인 n을 입력해주세요.  " << endl;
			cin >> n;

			for (int i = 0; i < n; i++) {
				vector<int> tmp;
				for (int j = 0; j < n; j++) {
					int t;
					if (pm == '-')
						t = rand() % MAX_NUM * 2 - MAX_NUM;		//대각선 방향으로 진행되기 위해서는 요소 중 음수값이 있어야만 한다.
																//양수만 있다면 요소 값이 0이아닌 이상 대각선 움직임이 거의 없다.
					else
						t = rand() % MAX_NUM;
					tmp.push_back(t);							//랜덤으로 만들어진 수 t를 tmp벡터에 넣음
				}
				matrix.push_back(tmp);				//0이 아닐때 tmp벡터를 matrix 벡터에 넣음
			}
			break;
		}
		else {
			continue;
		}
	}

	//k까지 이르는 최고 점수를 저장 할dp와 k가 어디서 왔는지 저장하는 flag 동적 배열 및 초기화
	dp = new int*[n + 1];
	flag = new int*[n + 1];
	for (int i = 0; i <= n; i++) {
		dp[i] = new int[n + 1];
		flag[i] = new int[n + 1];
		memset(dp[i], 0, sizeof(int)*(n + 1));		//메모리 공간을 0으로 초기화
		memset(flag[i], 0, sizeof(int)*(n + 1));		//메모리 공간을 0으로 초기화
	}

	cout << endl << "================================================================================================================" << endl ;
	cout << endl << "행렬은 다음과 같이 구성되었습니다." << endl;		//n에 따라 행렬을 구성한다. matrix는 vector로 만들었다.
	//구성된 행렬을 출력한다. -와 | 의 안에 있는 값이 요소값이고, 밖의 값은 좌표를 나타낸다.
	for (int i = -1; i < n; i++) {
		for (int j = -1; j < n; j++) {
			if (j == -1) {									//index부분 을 출력하기 위해 나누었다.
				cout << i + 1 << " | ";
				continue;
			}
			if (i == -1) {
				cout << j + 1 << "  ";
				continue;
			}
			cout << matrix[i][j] << " ";
		}
		if (i == -1) {										//인덱스 출력후 줄바꿈
			cout << endl;
			for (int j = 0; j <= n; j++)
				cout << "---";
		}
		cout << endl;
	}

	cout << endl << "================================================================================================================" << endl 
		<< "================================================================================================================" << endl ;
	DP(matrix, n);		//DP를 실행시킨다.
	cout << endl << "규칙대로 움직여서 얻을 수 있는 최대 값은 " << dp[n][n] << "입니다." << endl << endl;	//dp[n][n]으로 결과 값을 출력한다.
	cout << "최대의 값을 얻으려고 할 때는 다음 경로로 움직입니다." << endl;		//printpath로 경로를 출력한다.
	printPath(matrix, n);

	cout << endl << "경로는 dp를 실행하면서 어느 방향에서 왔는지를 기록해두는 flag를 따라 다시 올라가서 출발지로 오면 반복문을 나와 경로를 출력하는 printPath함수를 이용했고, 자세한 코드 설명은 주석에 있습니다." << endl;

	cout << endl << "================================================================================================================" << endl
		<< "================================================================================================================" << endl << endl;

	for (int i = 0; i < n + 1; i++) {		//동적으로 할당한 메모리를 해제해준다.
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
	row_col.push_back(make_pair(n, m));		//가장 마지막 요소를 먼저 result에 넣고 시작
	result.push_back(matrix[n - 1][m - 1]);

	while (n != 1 || m != 1) {		//n과 m이 1이 아닐때 까지 진행
		if (flag[n][m] == 3 && n != 1 && m != 1) 		//flag[n][m]이 3이고, n과 m이 1이 아니면 (대각선에서 온경우)
			result.push_back(matrix[--n - 1][--m - 1]);	//matrix[n-2][m-2] 즉 n-1,m-1의 요소값을 result에 넣고, n,m값을 1씩 뺀다. (matrix는 0부터 시작하기 때문에 1씩 빼줌)
		else if (flag[n][m] == 1 && m != 1)				//flag[n][m]이 1이고, m이 1이 아니면 (왼쪽에서 온경우)
			result.push_back(matrix[n - 1][--m - 1]);	//matrix[n-1][m-2] 즉 n,m-1의 요소값을 result에 넣고, m값에서 1을 뺀다.
		else if (flag[n][m] == 2 && n != 1)				//flag[n][m]이 2이고, n이 1이 아니면 (위쪽에서 온경우)
			result.push_back(matrix[--n - 1][m - 1]);	//matrix[n-2][m-1] 즉 n-1,m의 요소값을 result에 넣고, n값에서 1을 뺀다.
		else
			break;
		row_col.push_back(make_pair(n, m));
	}

	for (int i = result.size() - 1; i > 0; i--) {	//path가 역순으로 들어가 있기 때문에 거꾸로 출력한다.
		cout << result[i] << "(" << row_col[i].second << "," << row_col[i].first << ")" << " -> ";
	}
	cout << result[0] << "(" << num << "," << num << ")" << endl;
}

void DP(vector<vector<int>> &matrix, int n) {

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			dp[i][j] = matrix[i - 1][j - 1] + getMax(i, j);		//dp[i][j]와 dp[i][j-1], dp[i-1][j]중 가장 큰 값을 matrix[i-1][j-1](i,j일 때의 matrix 값)에 더한다.
		}
	}
}

int getMax(int i, int j) {		//dp[i][j]와 dp[i][j-1], dp[i-1][j]중 가장 큰 값을 갖는 수를 찾는 함수
	int a = dp[i][j - 1];
	int b = dp[i - 1][j];
	int c = dp[i - 1][j - 1];

	if (a == b && b == c && a == 0 && i == j && i ==1)	//1,1일 때 0리턴: 왼쪽, 위쪽, 대각선이 모두 0 이고, i와 j가 같은데 1인 경우는 1,1 상황
		return 0;
	else if (i == 1) {			//가장 위쪽 행인 경우 --> 무조건 왼쪽에서밖에 못옴	: 첫 요소가 음수이면 아래 조건문에서 null값을 가져기 때문에 따로 걸러줌
		flag[i][j] = 1;			//가장 큰값이 a이면 flag에 i,j-1 즉, 왼쪽에서 왔다고 표시: 1
		return a;
	}
	else if (j == 1) {			//가장 왼쪽 열인 경우	 --> 무조건 오른쪽에서밖에 못옴
		flag[i][j] = 2;			//가장 큰값이 a이면 flag에 i-1,j 즉, 위쪽에서 왔다고 표시: 2
		return b;
	}


	if (c >= a && c >= b) {		//대각선을 먼저 재서 왼쪽이나 위쪽 값이 0일 경우에, 대각선에서 먼저 오게하여 path를 줄인다.
		flag[i][j] = 3;			//가장 큰값이 a이면 flag에 i-1,j-1 즉, 대각선에서 왔다고 표시: 3
		return c;
	}
	else if (a >= b && a >= c) {
		flag[i][j] = 1;			//가장 큰값이 a이면 flag에 i,j-1 즉, 왼쪽에서 왔다고 표시: 1
		return a;
	}
	else if (b >= a && b >= c) {
		flag[i][j] = 2;			//가장 큰값이 a이면 flag에 i-1,j 즉, 위쪽에서 왔다고 표시: 2
		return b;
	}

}