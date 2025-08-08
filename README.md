# BasicLibraryForPICO
MyAQM1602V2.h

  AQM1602液晶表示用ライブラリ改良型(5V,3.3V対応型,I2C)
 
MyDS3231.h

  DS3231 RTC用ライブラリ(I2C)

MyGPS2.h

  改良型GPSライブラリ(3.3Vシリアル通信)

MyMACROM.h

  秋月電子MACアドレス書込済 93C46(販売コード 101412)用ライブラリ(独自インターフェース)

  実質93C46の読み書き用だが最低限の機能のみ実装している。

MyMCP3425.h

  高精度ADCのMCP3425(1ch)用ライブラリ(I2C)

Mysht3xV2.h

  SHT31/SHT35 改良型温室度センサ用ライブラリ(I2C)

Mysht4x.h

  SHT4x 温室度センサ用ライブラリ(I2C)


AVR系ArduinoとRaspberry Pi PICOで動作を確認している。

I2C用は複数Wireがある場合に対応。


ライセンス

Copyright 2024 Hideto Kurosaki

Released under the MIT license

https://opensource.org/license/mit

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in the
Software without restriction, including without limitation the rights to use, copy,
modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
