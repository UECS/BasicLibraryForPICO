/*
 * MySHT4x.h - SHT40/SHT41 温度湿度センサーライブラリ
 * Ver.1.0 - SHT3xライブラリ完全互換版（遅延初期化）
 * 
 * 対応マイコン:
 * - Arduino UNO
 * - ESP32 (複数I2Cバス対応)
 * - Raspberry Pi Pico (複数I2Cバス対応)
 */

#ifndef _MYSHT4X_H_
#define _MYSHT4X_H_

#include "Arduino.h"
#include "Wire.h"

#define SHT4X_ADDR    0x44

class SHT4x {
public:
  // コンストラクタ（SHT3xと同じインターフェース）
  SHT4x();
  SHT4x(TwoWire &w);
  
  // メイン関数（SHT3xと完全互換）
  bool autoRead1Sec();  // 毎秒1回呼ぶ関数
  bool begin(unsigned char i2caddr = SHT4X_ADDR);
  bool startMeasure(void);
  bool getTempHumid(void);
  
  // パブリック変数（SHT3xと同じ）
  double humidity, temp, humiddiff;
  int retryCount;
  
  // 追加機能
  bool reset(void);
  bool readSerialNumber(uint32_t* serialNumber);
  void setPrecision(unsigned char precision);  // 0:高精度, 1:中精度, 2:低精度
  unsigned char getPrecision();
  bool isConnected();
  
  // 静的ユーティリティ
  static float celsiusToFahrenheit(float celsius);
  static float fahrenheitToCelsius(float fahrenheit);
  static float calculateDewPoint(float temperature, float humidity);
  static float calculateHeatIndex(float temperature, float humidity);

private:
  TwoWire *wire;
  unsigned char _i2caddr;
  unsigned char _precision;  // 0:高精度, 1:中精度, 2:低精度
  bool _initialized;
  
  // プライベートメソッド
  unsigned char crc8Dallas(const unsigned char *data, int len);
  unsigned char getPrecisionCommand();
  unsigned char getPrecisionDelay();
};

#endif
