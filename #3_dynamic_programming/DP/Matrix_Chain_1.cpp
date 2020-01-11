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

	//입력을 받을 것인지 기존의 matrix를 사용할 것인지 묻는다.
	char input;
	while (true) {
		cout << "입력을 받을 거면 i을 문제에 나와있는 값으로 진행할 거면 p를 입력해주세요. ";
		cin >> input;

		//직접 입력 받는 경우
		/*예제
		i
		5
		30 20 10 10 20 30
 		*/
		if (input == 'i') {
			cout << "행렬의 개수를 입력해주세요. ";
			cin >> n;

			cout << "p값을 입력해주세요.  ";
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

	//행렬 곱의 최적의 경우에서 총 곱셈의 수를 저장하는 배열dp와 최적의 순서를 가지는 마지막 곱셈하는 위치 k를 저장하는 str을 초기화 했습니다. 
	dp = new int*[n];
	str = new int*[n + 1];		//나중에 str형태로 출력하려고 str이라고 명명
	dpstr = new string*[n];
	for (int i = 0; i < n + 1; i++) {
		str[i] = new int[n + 1];
		if (i < n) {
			dp[i] = new int[n];
			dpstr[i] = new string[n];

			memset(dp[i], 0, sizeof(int)*n);	//메모리 공간을 0으로 초기화
		}
		memset(str[i], -1 , sizeof(int)*(n + 1));	//메모리 공간을 -1로 초기화
	}

	//1번문제 출력
	cout << endl << "========================================================================================" << endl << endl;
	cout << "1번, 모든 가능한 곱셈 순서는 총 몇가지 인가?" << endl << endl
		<< "numdp[n]은 i가 2부터 n - 2일 때까지 일 때 NUM[i]*NUM[n-i]의 합과 NUM[n-1] * 2의 합으로 이루어진다." << endl
		<< "점화식을 구하면 다음과 같다." << endl
		<< "NUM[n] = NUM[n-1] * 2 + 시그마(i = 2 ~ n-2) NUM[i] * [n-i]" << endl << endl;
	int num = getNum(n);
	cout << endl << "따라서 n이 " << n << "일 때, 행렬을 곱하는 경우는 총 " << num << "개 이다." << endl << endl;

	//2번문제 계산과정
	cout << "========================================================================================" << endl << endl
		<< "각 단계별 최적 곱셉 경우 계산과정" << endl << endl;

	int result = DP(matrix, n);
	cout << endl << "========================================================================================";
	cout << endl << "========================================================================================" << endl << endl;

	//2번문제 결과 출력
	cout << "주어진 행렬들의 곱의 순서는 최적일 때 '" << result << "' 번을 곱하고"
		<< endl << "다음과 같은 순서를 갖는다 " << endl;

	cout << "옆의 순서는 재귀를 이용했다: ";
	printOrder(0, n - 1);
	cout << endl << "옆의 순서는 DP를 이용했다: ";
	printOrderDP(n);

	cout << endl << endl << "순서를 구하는 경우에서 가장 최적의 곱을 갖게하는 min을 구한 상태에서 재귀를 이용하면 중복되는 경우가 없고, DP도 같은 점화식을 반복문으로 풀어서 서술한 것이기 때문에 둘의 시간 복잡도는 비슷하지만, DP의 경우에 차지하는 데이터 공간이 더 필요해서 공간복잡도면에서는 오히려 재귀가 낫다고 생각한다."
		<< endl << "특히나 곱셈의 순서를 구하는 경우에서 dp로 구해 놓은 행렬의 최적 곱을 갖게 하는 min(코드에서 str 배열)을 구한 상태에서 재귀를(반 재귀, 반 dp) 이용하면 중복이 없기 때문에 코드의 간결성과 메모리공간 복잡도 면에서도 재귀가 더 낫다고 생각한다."
		<< endl << "이 둘은 최적 행렬 곱을 갖게하는 min값을 저장한 int형 이중벡터 str을 이용했을 때의 결과이다." << endl;
	

	cout << endl <<endl<< "dpstr을 이용해서 DP를 돌리면서 이중 스트링 벡터에 값을 쌓아가면서 만든 결과: " << dpstr[0][n - 1] << endl
		<< "결과는 같게 나오지만 이중스트링 배열를 이용하기 때문에 재귀보다는 메모리 차지가 큰 편이다. 하지만 dp를 돌면서 한번에 값을 얻어내기 재귀 도는 시간을 단축할 수 있다."
		<< "위에 출력된 재귀와 dp는 우선적으로 DP를 돌고나서 최적 곱셈을 갖게하는 min을 저장한 integer 이중 배열을 갖고있어야 결과 값이 나온다. 따라서 이 방법이 공간이 넉넉하다면 더 효율적이다." ;

	cout << endl << endl << "========================================================================================";
	printDP(n);


	//동적으로 할당한 배열들 해제
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
	if (n == 1) return 0;		//default로 넣어놓은 n이 1, 2 인경우는 바로 값을 리턴합니다.
	else if (n == 2) return 1;

	int *numdp = new int[n];
	memset(numdp, 0, sizeof(int)*n);	//메모리 공간을 0으로 초기화

	//배열이 한개일 때 두개일 때는 먼저 초기화
	numdp[0] = 0;
	numdp[1] = 1;

	//numdp[n]은 i가 2부터 n - 2일 때까지 일 때 NUM[i]*NUM[n-i]의 합과 NUM[n-1] * 2의 합으로 이루어진다. 
	//점화식을 구하면 다음과 같다.
	// NUM[n] = NUM[n-1] * 2 + 시그마(i = 2 ~ n-2) NUM[i] * [n-i]

	// NUM[4] = NUM[3] * 2 + NUM[2] * NUM[2]
	// NUM[5] = NUM[4] * 2 + NUM[3] * NUM[2] + NUM[2] * NUM[3]

	//인덱스가 0부터 시작하기 때문에 1씩 빼서 계산됩니다.
	for (int i = 2; i < n; i++) {
		numdp[i] += (numdp[i - 1]) * 2;
		if (i == n - 1)	cout << "NUM[" << n << "] = NUM[" << i << "] * 2 ";

		for (int j = 1; j < i - 1; j++) {
			numdp[i] += (numdp[j] * numdp[i - j - 1]);
			if (i == n - 1)	cout << "+ NUM[" << j + 1 << "] * NUM[" << i - j << "]";
		}
	}

	return numdp[n - 1];	//n일 때의 곱셈의 개수를 리턴합니다.
}


int DP(const vector<int> &matrix, int n) {
	
	//dpstr의 대각선 n*n부분을 An행렬 이름들로 초기화한다. 
	for (int i = 0; i < n; i++) {
		dpstr[i][i] = "A" + to_string(i + 1);
	}


	for (int r = 0; r < n; r++) {			//총 배열의 수를 저장, 문제의 크기를 결정하는 변수
		for (int i = 0; i < n - r; i++) {
			int j = i + r;					//배열 n개에서 Ai부터 Aj까지 합을 구하고자 한다.

			if (i == j)						//i와 j가 같은 것은 한 행렬을 곱하려는 것이기 때문에 그대로 0
				continue;

			int mem;
			int min = 2147483647;			//min값을 int에서 가장 큰 값으로 설정함
			for (int k = i; k < j; k++) {
				int tmp = dp[i][k] + dp[k + 1][j] + matrix[i] * matrix[k + 1] * matrix[j + 1];
				//각 행렬 곱셉이 수행되는 상황들을 다 tmp에 담으면서 가장 작은 경우가 나올 때를 min에 기억한다.
				//n개의 행렬일 경우 n-1만큼 돌면서 모든 가능성을 판단한다

				if (min > tmp) {
					min = tmp;		//min은 가장 작은 tmp를 기억한다.
					mem = k;		//mem은 가장 작은 tmp를 가지는 k값을 기억한다.
				}
			}
			dp[i][j] = min;
			//각 단계에서의 최적의 경우의 계산과정을 출력한다.
			str[i][j] = mem;	//str은 가장 작은 min을 가지는 mem값을 전역변수로 기억한다. (재귀형 print문장)
			dpstr[i][j] = "(" + dpstr[i][mem] + " * "+ dpstr[mem + 1][j] + ")";		//최적의 곱을 갖게하는 mem을 이용해서 행렬 곱의 순서를 저장해나간다.

			cout << "A" << i + 1 << "~A" << j + 1 << "까지의 곱: "
				<< min << " = (A" << i + 1 << "~A" << mem + 1 << ")의 곱 + (A" << mem + 2 << "~A" << j + 1 << ")의 곱 + "
				<< "p" << i + 1 << "* p" << mem + 2 << "* p" << j + 2 << " = "
				<< dp[i][mem] << " + " << dp[mem + 1][j] << " + "
				<< matrix[i] << "*" << matrix[mem + 1] << "*" << matrix[j + 1] << endl << endl;
		}
	}

	return dp[0][n - 1];
}

void printDP(int n) {
	cout << endl << "========================================================================================";
	cout << endl << "n개의 배열을 Ai부터 Aj까지 곱할 때의 최적의 곱한 값을 구한 표이다." << endl;

	//dp로 구한 값들을 출력하여 보여준다.
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << "  [" << dp[i][j] << "]  ";
		}
		cout << endl;
	}
}

//최적 곱의 경우의 min값을 저장한 str 이중 배열을 이용해서 행렬의 결과를 뽑는 경우
void printOrderDP(int n) {
	int index = 0;	
	string result = "";	//result는 결과값을 저장하는 string이다.
	vector<pair<bool, pair<int, int>>> ordertree;		//재귀호출을 하지 않기 때문에 min값을 갖게하는 i~k까지, k+1~j를 추적하면서 i == k인 지점, k+1 == j인 지점을 order에 저장하고 출력한다.

	//i와 j는 행렬 Ai~ Aj를 나타내고, k를 구해놓았기 때문에 Ai~ak, Ak+1~Aj를 구해서 트리형태로 값들을 펼쳐나갈 수 있다.
	int i = 0, j = n - 1;
	int k = str[i][j];

	//첫번째 루트노드
	//자식이 있는지(있으면 true 없으면 false) 저장하는 첫번째 인덱스와 (i값, k값) 혹은 (k+1, j)값을 두번째 세번째 인덱스로 저장한다.
	if (i != j)
		ordertree.push_back(make_pair(1, make_pair(i, j)));
	else
		ordertree.push_back(make_pair(0, make_pair(i, j)));
	
	int count = 0;	//count는 괄호의 열림과 닫힘을 정상적으로 만들기 위한 변수이다. while문을 다 돌리고 count가 남은 만큼 닫힌 괄호를 추가한다.
	while (index < ordertree.size()) {		//모든 노드를 다 펼치고나면 종료한다. (트리는 BFS로 펼친다. 트리의 모든 노드는 자식 2개를 갖거나 아예자식을 갖지 않는 리프이다.)
		if (ordertree[index].first == true) {
			bool flag = false;	//flag는 펼친 노드가 모두 리프일 때 true를 갖게된다.
			i = ordertree[index].second.first;
			j = ordertree[index].second.second;
			k = str[i][j];
			result += "(";		//노드를 펼칠 때 괄호를 연다.
			count++;
			if (i == k) {		//왼쪽 자식노드가 리프인 경우, ordertree에 노드를 넣고, 해당 노드의 행렬을 result에 넣고 flag는 true.
				ordertree.push_back(make_pair(false, make_pair(i, k)));
				result += "A" + to_string(i + 1);
				flag = true;
			}
			else {				//왼쪽 자식노드가 리프가 아닌 경우, 노드를 ordertree에 넣고 flag는 flase
				ordertree.push_back(make_pair(true, make_pair(i, k)));
				flag = false;
			}

			if (k + 1 == j) {	//오룬쪽 자식노드가 리프인 경우, ordertree에 노드를 넣고, 해당 노드의 행렬을 result에 넣고 flag가 이미 true였을 때만 true.
				ordertree.push_back(make_pair(false, make_pair(k + 1, j)));
				result += "A" + to_string(k + 2);
				if (flag) flag = true;
			}
			else {				//오른쪽 자식노드가 리프가 아닌 경우, 노드를 ordertree에 넣고 flag는 flase
				ordertree.push_back(make_pair(true, make_pair(k + 1, j)));
				flag = false;
			}
			if (flag) {			//펼친 자식 노드가 모두 리프일 때 두 행렬을 먼저 곱하는 경우이므로 괄호를 닫는다.
				result += ")";
				count--;
			}

		}
		index++;				//인덱스를 늘려서 다음 노드로 넘어간다.
	}

	for (int i = 0; i < count; i++)		//닫는 괄호를 마저 작성한다.
		result += ")";

	cout << result;				//결과를 출력한다.
}

void printOrder(int i, int j) {

	if (i == j)		//n개의 행렬의 Ai~Aj의 곱에서 최적의 결과가 나올 때를 (Ai~Ak)(Ak+1~Aj)라고 할 때, k값이 i값이면 
		cout << "A" << i + 1;		// Ai를 출력한다.
	else {						//아니면 아래를 수행한다.
		cout << "(";			//k값을 기준으로 괄호를 열고 닫는다.			
		printOrder(i, str[i][j]);		//계속해서 최적의 결과가 나올 때의 i와 j가 같아 질 때까지 재귀호출한다.
		printOrder(str[i][j] + 1, j);
		cout << ")";
	}

}

