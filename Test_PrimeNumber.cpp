//============================================================================
// Name        : Test_PrimeNumber.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : 素数判定プログラム PrimeNumber のテストプログラム
//============================================================================

#include <iostream>
using namespace std;

#include "PrimeNumber.h"


void test_PrimeNumber_isPrime();
void test_PrimeNumber_getPrime();
void test_PrimeNumber_countPrime();


void test_PrimeNumber()
{

	cout << "---------- Test: Prime::isPrime() ----------" << endl;
	test_PrimeNumber_isPrime();
	cout << endl;
	cout << "---------- Test: Prime::getPrime() ----------" << endl;
	test_PrimeNumber_getPrime();
	cout << endl;
	cout << "---------- Test: Prime::countPrime() ----------" << endl;
	test_PrimeNumber_countPrime();
}


void test_PrimeNumber_isPrime()
{
	const int MAX = 10000;

	clock_t t1, t2;
	Prime *c = new Prime(MAX);
	int num = 1;

	t1 = clock();
	while (num <= MAX) {
		if (c->isPrime(num)) {
			cout << num << endl;
		}
		t2 = clock();
		num += 1;
	}
	cout << "Runtime: " << ((double)(t2 - t1) / CLOCKS_PER_SEC) << endl;	// 処理時間を出力
	cout << endl;
	delete c;
	cout << "End." << endl;
}


void test_PrimeNumber_getPrime()
{
	const int MAX = 1000000;

	clock_t t1, t2;
	Prime *c = new Prime(MAX);
	int num = 1;

	t1 = clock();
	while (num <= MAX) {
		cout << "Prime count to " << num << " is" << endl;
		cout << c->countPrime(num) << endl;
		t2 = clock();
		cout << "Runtime: " << ((double)(t2 - t1) / CLOCKS_PER_SEC) << endl;	// 処理時間を出力
		cout << endl;
		num *= 10;
	}
	num /= 10;
	while (num >= 1) {
		cout << "Prime count to " << num << " is" << endl;
		cout << c->countPrime(num) << endl;
		t2 = clock();
		cout << "Runtime: " << ((double)(t2 - t1) / CLOCKS_PER_SEC) << endl;	// 処理時間を出力
		cout << endl;
		num /= 10;
	}
	delete c;
	cout << "End." << endl;
}


void test_PrimeNumber_countPrime()
{
	const int MAX = 1000000;
	clock_t t1, t2;
	Prime *c = new Prime(16000000);		// 100万番目の素数=15485863
	int num = 1;

	t1 = clock();
	while (num <= MAX) {
		cout << num << "th prime number is" << endl;
		cout << c->getPrime(num) << endl;
		t2 = clock();
		cout << "Runtime: " << ((double)(t2 - t1) / CLOCKS_PER_SEC) << endl;	// 処理時間を出力
		cout << endl;
		num *= 10;
	}
	num /= 10;
	while (num >= 1) {
		cout << num << "th prime number is" << endl;
		cout << c->getPrime(num) << endl;
		t2 = clock();
		cout << "Runtime: " << ((double)(t2 - t1) / CLOCKS_PER_SEC) << endl;	// 処理時間を出力
		cout << endl;
		num /= 10;
	}
	delete c;
	cout << "End." << endl;
}


