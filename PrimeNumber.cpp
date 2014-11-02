/*========================================
PrimeNumber.cpp
Title:
素数判定プログラム ソースファイル

Destription:
エラトステネスのふるい Eratosthenes's sieveを使用し素数を判定する
メモリ容量削減のため、奇数ビット列を素数リストとして使用する

Author: litmot
Date:   2013/11/10
========================================*/

#include "PrimeNumber.h"

Prime::Prime():
	MAX_NUM		(2040000000),								// 最大数
	MAX_IDX		((MAX_NUM - 1) >> 1),						// 最大数インデックス
	MAX_END		(((unsigned int)sqrt(MAX_NUM) - 1) >> 1),	// 最大数の平方根
	s_proc		(0)											// ふるいにかけた数
{
	eratosthenes_sieve = new BitSeries(MAX_IDX, 0xff);
	sieve_size = eratosthenes_sieve->getSize();
}

Prime::Prime(unsigned int max_num):
	MAX_NUM		(max_num),									// 最大数
	MAX_IDX		((MAX_NUM - 1) >> 1),						// 最大数インデックス
	MAX_END		(((unsigned int)sqrt(MAX_NUM) - 1) >> 1),	// 最大数の平方根
	s_proc		(0)											// ふるいにかけた数
{
	eratosthenes_sieve = new BitSeries(MAX_IDX, 0xff);		// ビット列を作成
}

Prime::~Prime()
{
	delete eratosthenes_sieve;		// ビット列を削除
}


bool Prime::isPrime(unsigned int num)
{
	if (num < 2) {
		// 0, 1は素数ではない
		return false;
	}
	if (0 == num % 2) {
		// 2は素数である
		if (2 == num) {
			return true;
		}
		// 2を除く奇数は素数ではない
		return false;
	}

	// この時点で残っているのは3以上の奇数
	// ビット列を参照し素数かどうか判断する
	return makeSieve(num)->isBitOn(convNumToIdx(num));
}


unsigned int Prime::getPrime(unsigned int n)
{
	if (n < 2) {
		return n == 1 ? 2 : 0;		// 1番目の素数は2
	}

	BitSeries *sieve = makeSieve(n < 6 ? 13 : (unsigned int)(n*log(n) + n*log(log(n))));
	unsigned int cnt = 1;				// 2はビット列に含まれないのでカウントを1から開始する
	
	for (unsigned int i = 0; i < MAX_IDX; i++) {
		if (sieve->isBitOn(i)) {
			if(++cnt == n) {				// ビットが立っていたらカウントアップ
				return convIdxToNum(i);				// カウントがnに達したときの素数を返す
			}
		}
	}
	return 0;
}

unsigned int Prime::countPrime(unsigned int num)
{
	if (num < 3) {
		return num == 2 ? 1 : 0;
	}

	BitSeries *sieve = makeSieve(num);
	unsigned int num_idx = convNumToIdx(num);		//奇数列インデックス
	unsigned int cnt = 1;
	for (unsigned int i = 0; i <= num_idx; i++) {
		if (sieve->isBitOn(i)) {
			cnt++;
		}
	}
	return cnt;
}

/*-------------------------------------------
エラトステネスの篩で素数のビット列を作成する
Return: 素数ビット列のポインタ
--------------------------------------------*/
BitSeries* Prime::makeSieve(unsigned int num)
{
	unsigned int end = convNumToIdx((unsigned int)sqrt(num));	// 平方根
	unsigned int p;												// 素数

	/* numが処理できる最大数を超えている場合、endを処理できる除数の最大数とする*/
	if (end > MAX_END) {
		end = MAX_END;
	}

	/* 前回処理した数から開始する */
	for (unsigned int i = s_proc; i <= end; i++) {
		if (eratosthenes_sieve->isBitOn(i)) {
			/* 取り出したビットが立っていたら（つまり素数）その倍数のビットを落とす */
			p = convIdxToNum(i);			// 取得した素数を保持
			for (unsigned int j = i + p; j <= MAX_IDX; j += p) {
				eratosthenes_sieve->getDownBit(j);
			}
		}
	}

	/* ふるいにかけた数を更新する */
	s_proc = end + 1;

	return eratosthenes_sieve;
}

