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

LARGE_INTEGER StartCounter, EndCounter, liFrequency;// �ð� ������ ����ϱ� ���� ����
bool printALL;

int main() {

	char *str;
	QueryPerformanceFrequency(&liFrequency); // ���ļ�(1�ʴ� �����Ǵ� ī��Ʈ��)�� ���Ѵ�. �ð������� �ʱ�ȭ

	char fname1[] = "file1.txt";
	char fname2[] = "file2.txt";
	char fname3[] = "file3.txt";

	char pattern1[] = "Further Reading about Standards";
	char pattern2[] = "17650    20000818";
	char pattern3[] = "Sorcerer";

	cout << "��Ȯ�� �ð� ������ ���� print������ �ð� ��� �Լ� �ۿ� ������ index�� ������ �迭�� �������, �� ã�� �迭�� �ִ� ũ�Ⱑ 100000���� �����Ǿ��ֽ��ϴ�." << endl
		<< "���� 100000�� ���� ���� �ִ� ���ڿ��� ����ε� ���� ��ȯ���� ���� �� �����Ƿ� MAX_FOUND���� �÷��ּ���." << endl << endl;

	cout << "ã�Ƴ� ���ڿ��� �ε����� ��� ����ϰ� ������  t�� �Է� �ϰ� �ƴϸ� f�� �Է��ϼ���. ";
	char tmp;
	cin >> tmp;
	if (tmp == 't')
		printALL = true;
	else
		printALL = false;

	cout << endl << endl << "=============================================================================================================" << endl << endl;

	for (int i = 0; i < 3; i++) {			//�̸� �����ص� ���ϰ� �˻��ϰ� ���� ���ڿ��� ���� for���� ���鼭 ���ڿ� �˻��� �����Ѵ�.
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

		//read�� �ѹ��� ������ �ҷ��Դ�.
		ifstream file(fname, ios::in | ios::binary | ios::ate);
		unsigned int leng = file.tellg();
		file.seekg(0, ios::beg);
		str = new char[leng];

		file.read(str, leng);
		file.close();

		//���ڿ��� �� �ҷ����� ������ ����Ѵ�.
		cout << fname << "���ڿ� �ҷ����� �Ϸ�,  ��" << leng << "����" << endl;


		//���̾����� Ư�����ڰ� ������ ���ư��� �ʱ⶧���� ASCII�ڵ尡 �ƴ� ���ڸ� ����� �۾��� �̸��Ѵ�.
		removeNonASCII(str, leng);


		//3���� �˰����� �����Ѵ�.
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

	QueryPerformanceCounter(&StartCounter); // �ڵ� ���� �� ī��Ʈ ����

	int n = strlen(str);
	int m = strlen(pattern);

	//�־��� ���ڿ� ó������ ���� ���ڿ� ũ�⸸ŭ �� ������ ���ϰ� �ϳ��ϳ� �����ϸ鼭 ��Ī�� �ִ��� ã�´�.
	for (int i = 0; i <= n - m; i++) {		
		int j;	//j�� pattern���� �� �ε���
		for (j = 0; j < m; j++) {
			if (pattern[j] != str[i + j]) 	//���� j��ġ�� str�� i+j�� ���� �ʴٴ� ���� �ش� ��ġ�� ���ڰ� ������ �ƴ϶�� ���̱� ������ �ٷ� for���� �������´�.
				break;
		}

		if (j == m)							//j�� m�� ���� str���� ������ ã�����ٴ� ���̹Ƿ� �ش� �ε����� �ε��� �迭�� �ִ´�.
			indexes[num++] = i;
	}

	QueryPerformanceCounter(&EndCounter); // �ڵ� ���� �� ī��Ʈ ����

	//��� ���
	cout << "������ naive matching���� ã�� ������ ��ġ�Դϴ�." << endl;
	printFoundIndex(indexes, num, pattern);
	printf("����ð� = %f ��\n", (double)(EndCounter.QuadPart - StartCounter.QuadPart) / (double)liFrequency.QuadPart);

	//cout << count << endl;

}

int* preprocessing(const char *pattern) {
	//���� �ӿ� ��ġ�� ������ ������ ���� �ִ� ���ϰ� ���ϴ� string�� ��Ī�� ������ �� ���ư� ���� pi�迭�� �����Ѵ�.
	
	int j = 0;		
	int k = -1;
	
	int m = strlen(pattern);		//m�� pattern�� ���� ��
	int *pi = new int[m + 1];		//pi �迭�� ���ư� ���� �����Ѵ�.
	fill_n(pi, m + 1, -1);			//pi�迭 �ʱ�ȭ�� -1�� �س��´�.

	while (j < m) {					//���ڿ� ����ŭ ���鼭 pi�迭�� �ϼ��Ѵ�.
		if (k == -1 || pattern[j] == pattern[k]) {		//k = -1�̰ų� j���� ���ϰ� k���� ������ ��ġ�� ��� 
			j++;					//j�� k���� 1�� �ø���.
			k++;
			pi[j] = k;				//pi[j]�� k�� �����Ѵ�.
		}
		else
			k = pi[k];				//k�� �ʱⰪ -1�� �ƴϰ�, ������ ��ġ�� ���ڰ� ���� ��쿡 k�� pi[k]������ �����Ѵ�.
	}

	cout << "pi�迭: ";
	for (int i = 0; i < m; i++)
		cout << pi[i] << " ";
	cout << endl << endl;

	return pi;
}

void KMP(const char *str, const char *pattern) {
	int indexes[MAX_FOUND];
	int num = 0;

	int i = 0;				//�ؽ�Ʈ ���ڿ� ������
	int j = 0;				//���� ���ڿ� ������
	int n = strlen(str);
	int m = strlen(pattern);

	//int skipnum = 0;

	int *pi = preprocessing(pattern);		//preprocessing�� ���� ���� �迭�� �޾ƿ´�. (�����Բ��� pi�迭 ����°� ����ð��̾ �ð� ��� �Ϳ� ���� ���ص� �����Ͻôٰ� �ϼż� �����ϴ�.)

	QueryPerformanceCounter(&StartCounter); // �ڵ� ���� �� ī��Ʈ ����

 	while (i < n) {
		if (j == -1 || str[i] == pattern[j]) {	//j�� -1�̰ų�() ����j�� str�� i�� ������ i�� j�� 1�� �÷��ش�.
			i++; j++;
			//skipnum++;
		}
		else {
			j = pi[j];		//���� ���ڰ� ������ pi�迭�� ���� j�� �ִ´�.
		}

		if (j == m) {		//j�� m�̶�� ���� ���ϰ� ������ ��ġ�ϴ� �κ��� ���Դٴ� ��
			indexes[num++] = i - m;		//index�� �־��ش�.
			j = pi[j];		//���� ���ڿ� �����͸� �ʱ�ȭ�Ѵ�.
		}

	}

	QueryPerformanceCounter(&EndCounter); // �ڵ� ���� �� ī��Ʈ ����

	//��� ���
	cout << "������ KMP �˰��򿡼� ã�� ������ ��ġ�Դϴ�." << endl;
	printFoundIndex(indexes, num, pattern);

	printf("����ð� = %f ��\n", (double)(EndCounter.QuadPart - StartCounter.QuadPart) / (double)liFrequency.QuadPart);
	//cout << "�� " << skipnum << "��ŭ ���Ͽ��� ��ŵ�߽��ϴ�" << endl;

	delete[] pi;
}

void computeJump(const char *pattern, int jump[]) {

	int m = strlen(pattern);		//pattern�� ���� ����

	for (int i = 0; i < 128; i++)
	{
		jump[i] = m;					//��Ÿ ���ڵ鿡 ���ؼ��� m��ŭ �پ�Ѱ� �Ѵ�.
	}

	for (int i = 0; i < m - 1; i++)
	{
		jump[pattern[i]] = m - i - 1;	//pattern�� �ִ� ���ڿ��� m-i-1��ŭ ������ �� �ְ� �����Ѵ�.
	}
}	

void boyerMoorHorspool(const char *str, const char *pattern) {
	int indexes[MAX_FOUND];
	int num = 0;
	int count = 0;
	//int jump_num = 0;

	int jump[130];
	computeJump(pattern, jump);		//computeJump�� jump�迭�� �޾ƿ´�. jump�迭�� ����� �ð� ���� ����ð��̾ ���� �ð���°Ϳ� ������ �ʿ䰡 ���ٰ� �ϼż� �ð� ��µ� ���� �ʾҽ��ϴ�.

	QueryPerformanceCounter(&StartCounter); // �ڵ� ���� �� ī��Ʈ ����

	int n = strlen(str);
	int m = strlen(pattern);
	int i = 0;								//i�� str�� ������ ������ index�̴�. jump�� ������ ���� jump�Ѵ�.
	while (i <= n - m) {
		int j = m - 1;						//j�� pattern���� ������ ���� �Ⱦ� ������ ����
		int k = i + m - 1;					//k�� str�� pattern�� ����ŭ ���� �κ� ���� �Ⱦ� ������ ����

		while (j > -1 && pattern[j] == str[k]) {	//j�� -1���� Ŭ ��, ������ j���ڿ� str�� k���ڰ� ������ while���� �Ѹ鼭 j�� k�� �ٿ�����.
			j--;
			k--;
		}

		if (j == -1) {						//���� while���� ������ j�� -1�̶�� ���� ������ ��� ��ġ�ߴٴ� �̾߱��̹Ƿ�
			indexes[num++] = i;				//indexes�迭�� i�� �ִ´�.
		}
		

		i = i + jump[str[i + m - 1]];		//���� �迭�� �ִ¸�ŭ �ε����� ���ؼ� �����Ѵ�.
		//jump_num++;							//���� ����ߴ��� ����
	}

	QueryPerformanceCounter(&EndCounter); // �ڵ� ���� �� ī��Ʈ ����

	//��� ���
	cout << "������ ���̾� ���� ȣ��Ǯ���� ã�� ������ ��ġ�Դϴ�." << endl;
	printFoundIndex(indexes, num, pattern);

	printf("����ð� = %f ��\n", (double)(EndCounter.QuadPart - StartCounter.QuadPart) / (double)liFrequency.QuadPart);

	//cout << "�� " << jump_num << "�� �����߽��ϴ�" << endl;
}


//���ϰ�, �߰ߵ� index�� �����ϰ� �ִ� arr, arr�� ũ���� num�� �Ű������� �޾Ƽ� ã�� ������ ����Ѵ�.
//��� ������ ����ð��� �ݿ����� �ʰ� ���� �Լ��� ®���ϴ�.
void printFoundIndex(int *arr, int num, const char *pattern) {
	cout << endl << num << "�������� ���� ���� " << pattern << "�� �߰ߵǾ����ϴ�." << endl << "������ ";

	if (printALL) {
		for (int i = 0; i < num; i++)
			cout << arr[i] << "  ";

		cout << "��ġ���� ã�������ϴ�." << endl << endl;
	}

}

void removeNonASCII(char * str, int leng) {		//���̾� ����� ���ڿ��� �ƽ�Ű�ڵ尡 �ƴ� �ڵ尡 ������ ����� �۵����� �����Ƿ� �ƽ�Ű�ڵ尡 �ƴ� ���ڸ� �����߽��ϴ�.
	for (int i = 0; i < leng; i++) {
		if (str[i] < 0 || str[i] > 127) {
			str[i] = ' ';
		}
	}

	cout << "�ؽ�Ʈ ���� �� ASCII �ƴ� ���ڸ� ���鹮�ڷ� ��ü�ϱ� �Ϸ�" << endl;
}