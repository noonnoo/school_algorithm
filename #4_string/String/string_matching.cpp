#include <iostream>
#include <fstream>
#include <windows.h>
#define MAX_FOUND 100000
using namespace std;

void naiveMatching(const char *str, const char *pattern);
int* preprocessing(const char *pattern);
void KMP(const char *str, const char *pattern);
void boyerMoorHorspool(const char *str, const char *pattern);
void printFoundIndex(int *arr, int num, const char *pattern);
void removeNonASCII(char * str, int leng);

LARGE_INTEGER StartCounter, EndCounter, liFrequency;// 시간 측정에 사용하기 위한 변수
bool printALL;

int main() {

	char *str;
	QueryPerformanceFrequency(&liFrequency); // 주파수(1초당 증가되는 카운트수)를 구한다. 시간측정의 초기화

	char fname1[] = "file1.txt";
	char fname2[] = "file2.txt";
	char fname3[] = "file3.txt";

	char pattern1[] = "Further Reading about Standards";
	char pattern2[] = "17650    20000818";
	char pattern3[] = "Sorcerer";

	cout << "정확한 시간 측정을 위해 print문들을 시간 재는 함수 밖에 빼려고 index를 모으는 배열을 만들었고, 이 찾은 배열의 최대 크기가 100000으로 설정되어있습니다." << endl
		<< "따라서 100000개 보다 많이 있는 문자열은 제대로된 값을 반환하지 못할 수 있으므로 MAX_FOUND값을 늘려주세요." << endl << endl;

	cout << "찾아낸 문자열의 인덱스를 모두 출력하고 싶으면  t를 입력 하고 아니면 f를 입력하세요. ";
	char tmp;
	cin >> tmp;
	if (tmp == 't')
		printALL = true;
	else
		printALL = false;

	cout << endl << endl << "=============================================================================================================" << endl << endl;

	for (int i = 0; i < 3; i++) {			//미리 설정해둔 파일과 검색하고 싶은 문자열에 대해 for문을 돌면서 문자열 검색을 시행한다.
		char *fname;
		char *pattern;

		switch (i) {
		case 0:
			fname = fname1;
			pattern = pattern1;
			break;
		case 1:
			fname = fname2;
			pattern = pattern2;
			break;

		case 2:
			fname = fname3;
			pattern = pattern3;
			break;
		default:
			fname = fname1;
			pattern = pattern1;
		}

		//read로 한번에 파일을 불러왔다.
		ifstream file(fname, ios::in | ios::binary | ios::ate);
		unsigned int leng = file.tellg();
		file.seekg(0, ios::beg);
		str = new char[leng];

		file.read(str, leng);
		file.close();

		//문자열을 다 불러오면 다음을 출력한다.
		cout << fname << "문자열 불러오기 완료,  총" << leng << "글자" << endl;


		//보이어무어에서는 특수문자가 있으면 돌아가지 않기때문에 ASCII코드가 아닌 문자를 지우는 작업을 미리한다.
		removeNonASCII(str, leng);


		//3가지 알고리즘을 실행한다.
		cout << endl << "-------------------------------------------------------------------------------------------------------------" << endl << endl;
		naiveMatching(str, pattern);

		cout << endl << "-------------------------------------------------------------------------------------------------------------" << endl << endl;
		KMP(str, pattern);

		cout << endl << "-------------------------------------------------------------------------------------------------------------" << endl << endl;
		boyerMoorHorspool(str, pattern);

		cout << endl << endl << "=============================================================================================================" << endl
			<< "=============================================================================================================" << endl << endl << endl ;

	}

	delete[] str;
	return 0;
}

void naiveMatching(const char *str, const char *pattern) {
	int indexes[MAX_FOUND];
	int num = 0;
	int count = 0;

	QueryPerformanceCounter(&StartCounter); // 코드 수행 전 카운트 저장

	int n = strlen(str);
	int m = strlen(pattern);

	//주어진 문자열 처음부터 패턴 문자열 크기만큼 뺀 곳까지 패턴과 하나하나 대조하면서 매칭이 있는지 찾는다.
	for (int i = 0; i <= n - m; i++) {		
		int j;	//j는 pattern에서 돌 인덱스
		for (j = 0; j < m; j++) {
			if (pattern[j] != str[i + j]) 	//패턴 j위치가 str의 i+j와 같지 않다는 것은 해당 위치의 문자가 패턴이 아니라는 것이기 때문에 바로 for문을 빠져나온다.
				break;
		}

		if (j == m)							//j가 m인 것은 str에서 패턴이 찾아졌다는 말이므로 해당 인덱스를 인덱스 배열에 넣는다.
			indexes[num++] = i;
	}

	QueryPerformanceCounter(&EndCounter); // 코드 수행 후 카운트 저장

	//결과 출력
	cout << "다음은 naive matching에서 찾은 문자의 위치입니다." << endl;
	printFoundIndex(indexes, num, pattern);
	printf("수행시간 = %f 초\n", (double)(EndCounter.QuadPart - StartCounter.QuadPart) / (double)liFrequency.QuadPart);

	//cout << count << endl;

}

int* preprocessing(const char *pattern) {
	//패턴 속에 겹치는 패턴이 있으면 뒷쪽 있는 패턴과 비교하는 string이 매칭에 실패할 때 돌아갈 곳을 pi배열에 저장한다.
	
	int j = 0;		
	int k = -1;
	
	int m = strlen(pattern);		//m은 pattern의 문자 수
	int *pi = new int[m + 1];		//pi 배열에 돌아갈 곳을 저장한다.
	fill_n(pi, m + 1, -1);			//pi배열 초기화를 -1로 해놓는다.

	while (j < m) {					//문자열 수만큼 돌면서 pi배열을 완성한다.
		if (k == -1 || pattern[j] == pattern[k]) {		//k = -1이거나 j에서 패턴과 k에서 패턴이 겹치는 경우 
			j++;					//j와 k값을 1씩 늘린다.
			k++;
			pi[j] = k;				//pi[j]에 k를 대입한다.
		}
		else
			k = pi[k];				//k가 초기값 -1이 아니고, 패턴중 겹치는 문자가 없는 경우에 k를 pi[k]값으로 설정한다.
	}

	cout << "pi배열: ";
	for (int i = 0; i < m; i++)
		cout << pi[i] << " ";
	cout << endl << endl;

	return pi;
}

void KMP(const char *str, const char *pattern) {
	int indexes[MAX_FOUND];
	int num = 0;

	int i = 0;				//텍스트 문자열 포인터
	int j = 0;				//패턴 문자열 포인터
	int n = strlen(str);
	int m = strlen(pattern);

	//int skipnum = 0;

	int *pi = preprocessing(pattern);		//preprocessing을 통해 파이 배열을 받아온다. (교수님께서 pi배열 만드는건 상수시간이어서 시간 재는 것에 포함 안해도 무방하시다고 하셔서 뺐습니다.)

	QueryPerformanceCounter(&StartCounter); // 코드 수행 전 카운트 저장

 	while (i < n) {
		if (j == -1 || str[i] == pattern[j]) {	//j가 -1이거나() 패턴j와 str의 i가 같으면 i와 j를 1씩 늘려준다.
			i++; j++;
			//skipnum++;
		}
		else {
			j = pi[j];		//같은 문자가 없으면 pi배열의 값을 j에 넣는다.
		}

		if (j == m) {		//j가 m이라는 것은 패턴과 완전히 일치하는 부분이 나왔다는 것
			indexes[num++] = i - m;		//index에 넣어준다.
			j = pi[j];		//패턴 문자열 포인터를 초기화한다.
		}

	}

	QueryPerformanceCounter(&EndCounter); // 코드 수행 후 카운트 저장

	//결과 출력
	cout << "다음은 KMP 알고리즘에서 찾은 문자의 위치입니다." << endl;
	printFoundIndex(indexes, num, pattern);

	printf("수행시간 = %f 초\n", (double)(EndCounter.QuadPart - StartCounter.QuadPart) / (double)liFrequency.QuadPart);
	//cout << "총 " << skipnum << "만큼 패턴에서 스킵했습니다" << endl;

	delete[] pi;
}

void computeJump(const char *pattern, int jump[]) {

	int m = strlen(pattern);		//pattern의 문자 개수

	for (int i = 0; i < 128; i++)
	{
		jump[i] = m;					//기타 문자들에 대해서는 m만큼 뛰어넘게 한다.
	}

	for (int i = 0; i < m - 1; i++)
	{
		jump[pattern[i]] = m - i - 1;	//pattern에 있는 문자열은 m-i-1만큼 점프할 수 있게 설정한다.
	}
}	

void boyerMoorHorspool(const char *str, const char *pattern) {
	int indexes[MAX_FOUND];
	int num = 0;
	int count = 0;
	//int jump_num = 0;

	int jump[130];
	computeJump(pattern, jump);		//computeJump로 jump배열을 받아온다. jump배열을 만드는 시간 또한 상수시간이어서 굳이 시간재는것에 포함할 필요가 없다고 하셔서 시간 재는데 넣지 않았습니다.

	QueryPerformanceCounter(&StartCounter); // 코드 수행 전 카운트 저장

	int n = strlen(str);
	int m = strlen(pattern);
	int i = 0;								//i는 str을 훑으며 지나갈 index이다. jump할 시점이 오면 jump한다.
	while (i <= n - m) {
		int j = m - 1;						//j는 pattern에서 마지막 부터 훑어 내려올 변수
		int k = i + m - 1;					//k는 str의 pattern의 수만큼 더한 부분 부터 훑어 내려올 변수

		while (j > -1 && pattern[j] == str[k]) {	//j가 -1보다 클 때, 패턴의 j문자와 str의 k문자가 같으면 while문을 둘면서 j와 k를 줄여간다.
			j--;
			k--;
		}

		if (j == -1) {						//위의 while문을 돌고나온 j가 -1이라는 것은 패턴이 모두 일치했다는 이야기이므로
			indexes[num++] = i;				//indexes배열에 i를 넣는다.
		}
		

		i = i + jump[str[i + m - 1]];		//점프 배열에 있는만큼 인덱스를 더해서 점프한다.
		//jump_num++;							//점프 몇번했는지 세기
	}

	QueryPerformanceCounter(&EndCounter); // 코드 수행 후 카운트 저장

	//결과 출력
	cout << "다음은 보이어 무어 호스풀에서 찾은 문자의 위치입니다." << endl;
	printFoundIndex(indexes, num, pattern);

	printf("수행시간 = %f 초\n", (double)(EndCounter.QuadPart - StartCounter.QuadPart) / (double)liFrequency.QuadPart);

	//cout << "총 " << jump_num << "번 점프했습니다" << endl;
}


//패턴과, 발견된 index를 저장하고 있는 arr, arr의 크기인 num을 매개변수로 받아서 찾은 내용을 출력한다.
//출력 내용은 수행시간에 반영되지 않게 따로 함수로 짰습니다.
void printFoundIndex(int *arr, int num, const char *pattern) {
	cout << endl << num << "군데에서 문자 패턴 " << pattern << "이 발견되었습니다." << endl << "패턴이 ";

	if (printALL) {
		for (int i = 0; i < num; i++)
			cout << arr[i] << "  ";

		cout << "위치에서 찾아졌습니다." << endl << endl;
	}

}

void removeNonASCII(char * str, int leng) {		//보이어 무어에서 문자열에 아스키코드가 아닌 코드가 있으면 제대로 작동하지 않으므로 아스키코드가 아닌 문자를 제거했습니다.
	for (int i = 0; i < leng; i++) {
		if (str[i] < 0 || str[i] > 127) {
			str[i] = ' ';
		}
	}

	cout << "텍스트 파일 중 ASCII 아닌 문자를 공백문자로 대체하기 완료" << endl;
}