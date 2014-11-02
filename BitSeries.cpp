/*
 * BitSeries.cpp
 *
 *  Created on: 2014/10/23
 *      Author: Takahiro Muto
 */


#include "BitSeries.h"

/*-------------------------------------------
 コンストラクタ
--------------------------------------------*/
BitSeries::BitSeries():
	bit_size	(2000000000),
	idx_size	(((bit_size - 1) >> SHIFT_IDX) + 1),
	init_bit	(0x00)
{
	this->series = new unsigned int[idx_size];
	std::memset(series, init_bit, idx_size * sizeof(unsigned int));
}

BitSeries::BitSeries(unsigned int series_size):
	bit_size	(series_size),
	idx_size	(((bit_size - 1) >> SHIFT_IDX) + 1),
	init_bit	(0x00)
{
	this->series = new unsigned int[idx_size];
	std::memset((void *)this->series, init_bit, idx_size * sizeof(unsigned int));
}

BitSeries::BitSeries(unsigned char byte):
	bit_size	(2000000000),
	idx_size	(((bit_size - 1) >> SHIFT_IDX) + 1),
	init_bit	(byte)
{
	this->series = new unsigned int[idx_size];
	std::memset((void *)this->series, init_bit, idx_size * sizeof(unsigned int));
}

BitSeries::BitSeries(unsigned int series_size, unsigned char byte):
	bit_size	(series_size),
	idx_size	(((bit_size - 1) >> SHIFT_IDX) + 1),
	init_bit	(byte)
{
	this->series = new unsigned int[idx_size];
	std::memset((void *)this->series, init_bit, idx_size * sizeof(unsigned int));
}

/*-------------------------------------------
 デストラクタ
--------------------------------------------*/
BitSeries::~BitSeries()
{
	delete[] this->series;
}

/*-------------------------------------------
 Module:	ビットを立てる
 Argument:	U_INT n -	立てるビットの位置
 Return:	-
--------------------------------------------*/
void BitSeries::getUpBit(unsigned int n)
{
	if (checkBitIdx(n)) {
		series[n >> SHIFT_IDX] |= (0x01 << (n & SHIFT_MASK));
	}
}

/*-------------------------------------------
 Module:	ビットを落とす
 Argument:	U_INT n -	落とすビットの位置
 Return:	-
--------------------------------------------*/
void BitSeries::getDownBit(unsigned int n)
{
	if (checkBitIdx(n)) {
		series[n >> SHIFT_IDX] &= ~(0x01 << (n & SHIFT_MASK));
	}
}

/*-------------------------------------------
 Module:	ビットが立っているか調べる
 Argument:	U_INT n -	調べるビットの位置
 Return:	bool - 		ビットが立っていたらTRUE
--------------------------------------------*/
bool BitSeries::isBitOn(unsigned int n)
{
	// 入力値がビット列のサイズを超えていたらfalseを返す
	if (!checkBitIdx(n)) {
		return false;
	}

	if ((series[n >> SHIFT_IDX] >> (n & SHIFT_MASK)) & 0x01) {
		return true;
	}
	return false;
}

/*-------------------------------------------
 Module:	ビット数列のサイズを取得する
 Argument:	-
 Return:	U_INT -		ビット数列のサイズ
--------------------------------------------*/
unsigned int BitSeries::getSize()
{
	return (bit_size);
}

/*-------------------------------------------
 Module:	ビット数列のサイズを変更する
 Argument:	U_INT series_size -	ビット数列の変更後サイズ
 Return:	bool -				サイズ変更成功したらtrue
--------------------------------------------*/
bool BitSeries::resizeSeries(unsigned int n_bit_size)
{
	unsigned int n_idx_size = (((n_bit_size - 1) >> SHIFT_IDX) + 1);
	// 引数のサイズが現在のサイズより小さかったらfalseを返す
	if (n_idx_size <= this->idx_size) {
		if (n_bit_size > this->bit_size) {
			this->bit_size = n_bit_size;
		}
		return false;
	}

	// 新しい領域を確保
	unsigned int *n_series = new unsigned int[n_idx_size];

	// 旧領域から新領域にデータをコピー
	std::memcpy((void *)n_series, (const void *)this->series, this->idx_size * sizeof(unsigned int));
	// 残りの領域は初期化ビットパターンで初期化
	std::memset((void *)(n_series + this->idx_size), init_bit, (n_idx_size - this->idx_size) * sizeof(unsigned int));

	// 旧領域を開放
	delete[] this->series;

	// 新領域にデータを更新
	this->bit_size = n_bit_size;
	this->idx_size = n_idx_size;
	this->series = n_series;

	return true;
}



