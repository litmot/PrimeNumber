/*========================================
 Title:
 素数判定プログラム ヘッダファイル

 Destription:
 エラトステネスのふるい Eratosthenes's sieveを使用し素数を判定する
 メモリ容量削減のため、ビット列を素数リストとして使用する

 Author: litmot
 Date:   2013/11/10
========================================*/

#ifndef INC_PRIME_NUMBER_H_
#define INC_PRIME_NUMBER_H_

#include <math.h>
#include <time.h>
#include "BitSeries.h"

class Prime
{

public:
	/*-------------------------------------------
	 コンストラクタ
	--------------------------------------------*/
	Prime();
	Prime(unsigned int max_num);

	/*-------------------------------------------
	 デストラクタ
	--------------------------------------------*/
	~Prime();

	/*-------------------------------------------
	 Module:	入力値が素数か判定する
	 Argument:	U_INT num -	素数かどうか判定する数
	 Return:	bool - 		numが素数ならTRUE
	--------------------------------------------*/
	bool isPrime(unsigned int num);

	/*-------------------------------------------
	 Module:	n番目の素数を取得する
	 Argument:	U_INT n	取得したい素数のインデックス
	 Return:	U_INT	n番目の素数(取得できなかったら0)
	--------------------------------------------*/
	unsigned int getPrime(unsigned int n);

	/*-------------------------------------------
	 Module:	1からnまでの素数の数を取得する
	 Argument:	U_INT n	素数カウント上限値
	  Return:	U_INT	素数の数
	--------------------------------------------*/
	unsigned int countPrime(unsigned int n);

private:
	const unsigned int MAX_NUM;			// 最大数
	const unsigned int MAX_IDX;			// 最大数インデックス
	const unsigned int MAX_END;			// 最大素数の平方根

	BitSeries *eratosthenes_sieve;		// 3,5,7,9...と続く数列のビット列
	unsigned int s_proc;				// ふるいにかけた数

	/*-------------------------------------------
	 Module:	エラトステネスの篩で素数のビット列を作成する
	 Argument:	U_INT n		作成する素数ビット列の数
	 Return:	U_INT* -	素数ビット列のポインタ
	--------------------------------------------*/
	BitSeries* makeSieve(unsigned int num);

	/*-------------------------------------------
	 Module:	整数を奇数ビット列のインデックスに変換する
	 Argument:	U_INT num	整数
	 Return:	U_INT		奇数ビット列インデックス
	--------------------------------------------*/
	inline unsigned int convNumToIdx(unsigned int num)
	{
		return (num - 3) >> 1;
	}

	/*-------------------------------------------
	 Module:	奇数ビット列のインデックスを整数に変換する
	 Argument:	U_INT idx	奇数ビット列インデックス
	 Return:	U_INT		整数
	--------------------------------------------*/
	inline unsigned int convIdxToNum(unsigned int idx)
	{
		return (idx << 1) + 3;
	}

};

#endif /* INC_PRIME_NUMBER_H_ */

