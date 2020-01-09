// Circuit-2.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <iomanip>
#include <thread>
#include <time.h>
#include <vector>
#include <fstream>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
namespace mp = boost::multiprecision;
void circuit(unsigned int n, unsigned int q, unsigned int depth);
void circuit_thread(unsigned int n, unsigned int q, unsigned int depth, unsigned int i);
unsigned int count(mp::cpp_int x);
mp::cpp_int func(const mp::cpp_int& x, const unsigned int& q);
void showTime();
ofstream outputfile("Circuit.txt");


clock_t start_time;

int main()
{
	std::vector<std::thread> threads;
	unsigned int n, q, d;

	std::cout << "n = ";
	std::cin >> n;
	std::cout << "q = ";
	std::cin >> q;
	std::cout << "depth = ";
	std::cin >> d;

	start_time = clock();
	showTime();
	std::cout << "Main start" << std::endl;
	for (unsigned int i = 0; i < n + 1; i++)
	{
		/*
		if (i % 500 == 0 && i != 0)
		{
			showTime();
			std::cout << "n = " << i * 2 + 1 << " : now running..." << std::endl;
		}
		*/
		circuit(i, q, d);
	}
	showTime();
	std::cout << "Main end" << std::endl;
	system("pause");

	return 0;
}

void circuit(unsigned int n, unsigned int q, unsigned int depth)
{
	unsigned int N_init = n * 2 + 1;
	mp::cpp_int m, N;
	std::vector <mp::cpp_int> S(depth);

	for (unsigned int i = 1; i < q + 1; i++)
	{
		circuit_thread(n, q, depth, i);
	}
}

void circuit_thread(unsigned int n, unsigned int q, unsigned int depth, unsigned int i)
{
	unsigned int N_init = n * 2 + 1;
	unsigned int Q = i * 2 + 1;
	unsigned int k;
	unsigned long long l;
	mp::cpp_int N = N_init;
	mp::cpp_int m;
	std::vector <mp::cpp_int> S(depth);


	for (unsigned int d = 0; d < depth; d++)
	{
		k = count((Q - 2) * N + 1);
		m = N;

		for (unsigned int j = 0; j < k; j++)
			m = func(m, Q);

		l = count(m);
		S[d] = m >> l;

		if (N_init == S[d])
		{
			showTime();
			std::cout << "n=" << N_init << " (" << Q << "n+1) " << N_init << "(" << k << ") " << m << "(" << l << ")";
			outputfile << "n=" << N_init << " (" << Q << "n+1) " << N_init << "(" << k << ") " << m << "(" << l << ")";
			for (unsigned int j = 0; j < d + 1; j++)
			{
				std::cout << " " << S[j];
				outputfile << " " << S[j];
			}
			std::cout << std::endl;
			outputfile << endl;
			break;
		}
		else
		{
			N = S[d];
		}
	}
}


unsigned int count(mp::cpp_int x)
{
	unsigned int count = 0;
	while (x % 2 == 0) {
		x = x >> 1;
		count++;
	}
	return count;
}

mp::cpp_int func(const mp::cpp_int& x, const unsigned int& q)
{
	if (x % 2 == 0) return x >> 1;
	else			return (q * x + 1) >> 1;
}

void showTime()
{
	unsigned int elapse_time = (clock() - start_time) / 1000;
	unsigned int hour = elapse_time / 3600;
	unsigned int min = (elapse_time % 3600) / 60;
	unsigned int sec = elapse_time % 60;

	std::cout << "[" <<
		std::setfill('0') << std::setw(2) << hour << ":" <<
		std::setfill('0') << std::setw(2) << min << ":" <<
		std::setfill('0') << std::setw(2) << sec << "] ";
}


// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
