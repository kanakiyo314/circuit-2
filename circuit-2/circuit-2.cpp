// Circuit-2.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <iomanip>
#include <thread>
#include <time.h>
#include <vector>
#include <fstream>
#include <boost/multiprecision/cpp_int.hpp>
#include <mutex>

using namespace std;
namespace mp = boost::multiprecision;
void circuit(size_t n, size_t q, size_t depth, size_t thread_number);
unsigned int count(mp::cpp_int x);
mp::cpp_int func(const mp::cpp_int& x, const size_t& q);
void showTime();
ofstream outputfile("Circuit.txt");
clock_t start_time;

size_t thread_num;
std::mutex mtx;

int main()
{
	size_t n, q, d;

	std::cout << "n = ";
	std::cin >> n;
	std::cout << "q = ";
	std::cin >> q;
	std::cout << "depth = ";
	std::cin >> d;
	std::cout << "thread_num = ";
	std::cin >> thread_num;
	start_time = clock();
	showTime();
	std::cout << "Main start" << std::endl;

	std::vector<std::thread> threads;
	for (size_t i = 0; i < n + 1; i++)
	{
		for (size_t j = 0; j < thread_num; j++)
		{
			threads.emplace_back(std::thread(circuit, i, q, d, j + 1));
		}
	}

	for (auto& thread : threads)
	{
		thread.join();
	}

	showTime();
	std::cout << "Main end" << std::endl;
	system("pause");

	return 0;
}

void circuit(size_t n, size_t q, size_t depth, size_t number)
{
	size_t N_init = n * 2 + 1;
	size_t Q, k;
	size_t l;
	mp::cpp_int m, N;
	std::vector <mp::cpp_int> S(depth);

	for (size_t i = number; i < q + 1; i+=thread_num)
	{
		N = N_init;
		Q = i * 2 + 1;

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
				mtx.lock();
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
				mtx.unlock();
				break;
			}
			else
			{
				N = S[d];
			}
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

mp::cpp_int func(const mp::cpp_int& x, const size_t& q)
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
