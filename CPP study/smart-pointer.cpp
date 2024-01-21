#include <memory>
#include <iostream>

using namespace std;

void test2(weak_ptr<int[]>& sp, shared_ptr<int[]>& ssp) {
	shared_ptr<int[]> test2_sp(new int[1000000]);
	for (int i = 0; i < 10; i++) {
		test2_sp[i] = i * 100;
	}
	//sp = move(test2_sp);
	sp = test2_sp;
	ssp = test2_sp;
}

void test() {
	//unique_ptr<int[]> sn(new int[1000000]);
	////int* sn = new int[1000000];
	//for (int i = 0; i < 10; i++) {
	//	sn[i] = i;
	//}
	//for (int i = 0; i < 10; i++) {
	//	cout << sn[i] << endl;
	//}
	//int k = 0;
	//cin >> k;


	shared_ptr<int[]> ssp;
	weak_ptr<int[]> sp;
	int a;
	cin >> a;
	test2(sp, ssp);
	if (sp.expired()) {
		cout << "널입니다." << endl;
		return;
	}
	for (int i = 0; i < 10; i++) {
		cout << sp.lock()[i] << endl;
	}
	cin >> a;
}

int main() {
	test();

	int n;
	cin >> n;
}