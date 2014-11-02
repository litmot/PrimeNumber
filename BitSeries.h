/*
 * BitSeries.h
 *
 *  Created on: 2014/10/23
 *      Author: Takahiro Muto
 */

#ifndef INC_BIT_SERIES_H_
#define INC_BIT_SERIES_H_

#include <cstring>

#define VAR_SIZE	(32)				/* 1バイトあたりのビット数 */
#define SHIFT_IDX	(5)					/* 配列添字のシフト数 */
#define SHIFT_MASK	(0x0000001F)		/* ビット取得シフト数の剰余数マスク */

class BitSeries
{

public:
	/*-------------------------------------------
	 コンストラクタ
	--------------------------------------------*/
	BitSeries();
	BitSeries(unsigned int series_size);						// size: ビット列のサイズ
	BitSeries(unsigned char byte);								// byte: 初期化ビットパターン
	BitSeries(unsigned int series_size, unsigned char byte);

	/*-------------------------------------------
	 デストラクタ
	--------------------------------------------*/
	~BitSeries();

	/*-------------------------------------------
	 Module:	ビットを立てる
	 Argument:	U_INT n -	立てるビットの位置
	 Return:	処理成功したらtrue
	--------------------------------------------*/
	void getUpBit(unsigned int n);

	/*-------------------------------------------
	 Module:	ビットを落とす
	 Argument:	U_INT n -	落とすビットの位置
	 Return:	処理成功したらtrue
	--------------------------------------------*/
	void getDownBit(unsigned int n);

	/*-------------------------------------------
	 Module:	ビットが立っているか調べる
	 Argument:	U_INT n -	調べるビットの位置
	 Return:	bool - 		ビットが立っていたらTRUE
	--------------------------------------------*/
	bool isBitOn(unsigned int n);

	/*-------------------------------------------
	 Module:	ビット数列のサイズを取得する
	 Argument:
	 Return:	U_INT		ビット列のサイズ
	--------------------------------------------*/
	unsigned int getSize();

	/*-------------------------------------------
	 Module:	ビット数列のサイズ変更する
	 Argument:	U_INT n -	ビット数列のサイズ
	 Return:	-
	--------------------------------------------*/
	bool resizeSeries(unsigned int series_size);

private:
	/*-------------------------------------------
	 Module:	インデックスが範囲内かチェックする
	 Argument:	U_INT n -	インデックス
	 Return:	bool		範囲内ならtrue
	--------------------------------------------*/
	inline bool checkBitIdx(unsigned int n)
	{
		if (n > bit_size) {
			return false;
		}
		return true;
	}

	unsigned int *series;		// ビット数列のポインタ
	unsigned int bit_size;		// ビット数列のサイズ
	unsigned int idx_size;		// ビット数列のサイズ
	unsigned char init_bit;		// 初期化ビットパターン

};


#endif /* INC_BITSERIES_H_ */
