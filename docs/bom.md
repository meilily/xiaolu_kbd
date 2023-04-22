パーツリスト
============

## PCB

Xiaolu Keyboard PCBはKicad 6で設計され、51mm x 76mmの寸法を持つ2層設計になっています。PCBには、16個のダイオード（1N4148）と2個の4.7kΩ抵抗（4.7kΩ 0402 Resister）のSMT部品が含まれています。

.kicad_pcb、.kicad_schなどのPCB設計ファイルは、「pcb」フォルダーにあります。

このPCBは、一般的なPCBメーカーである[JLCPCB](https://jlcpcb.com/)で製造することを前提に設計されています。PCBをJLCPCB PCB+SMT製造サービスに発注するには、KiCadのプラグインで製造用のガーバーファイルなどのファブリケーションファイルを生成できる[JLCPCB fabrication toolkit](https://github.com/bennymeg/JLC-Plugin-for-KiCad)を利用することができます。このツールキットを使うと、JLCPCBに発注するのに必要なファブリケーションファイルであるgerber.zip、bom.csv、position.csvを生成できます。


SMT 部品表

|部品名             |数量|LCSC Part #                                                                                                                     |
|-------------------|----|--------------------------------------------------------------------------------------------------------------------------------|
|1N4148 Diode       |16  |[C2128](https://www.lcsc.com/product-detail/Switching-Diode_Jiangsu-Changjing-Electronics-Technology-Co-Ltd-1N4148WS_C2128.html)|
|4.7kΩ 0402 Resistor|2   |[C25900](https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_UNI-ROYAL-Uniroyal-Elec-0402WGF4701TCE_C25900.html)    |

## 電子部品

|部品名                                |数量|秋月通販コード                                          |備考                     |
|--------------------------------------|----|--------------------------------------------------------|-------------------------|
|Seeed XIAO RP2040                     |1   |[M-17044](https://akizukidenshi.com/catalog/g/gM-17044/)|必須                     |
|Switronic TS-AGGNH-G プッシュボタン   |16  |[P-03654](https://akizukidenshi.com/catalog/g/gP-03654/)|必須                     |
|USB Type C ケーブル                   |1   |-                                                       |必須。適当なもので良い   |
|GroveコネクタL型スルーホール          |1   |[C-12634](https://akizukidenshi.com/catalog/g/gC-12634/)|Grove拡張用オプション部品|
|TRRS ジャック PJ-320A(または MJ-4PP-9)|1   |[C-06070](https://akizukidenshi.com/catalog/g/gC-06070/)|TRRS拡張用オプション部品 |

## ケース

ケースセットアップの例をいくつか記載します。

### 最も安価なケースセットアップ〜市販品の利用〜

Xiaolu Keyboard PCBは、ケースの組み立てを容易にするために、四隅にM3ホールが配置されています。このM3ホールは、秋月電子のC基板との互換となる配置と直径になっています。これにより、秋月電子C基板用のケースやアクリルパネルに、Xiaolu Keyboard を簡単に組み込むことができます。

以下は、最も安価なケースセットアップの一例です。

|部品名                                     |数量|秋月通販コード                                          |備考                                    |
|-------------------------------------------|----|--------------------------------------------------------|----------------------------------------|
|C基板用アクリルパネル                      |1   |[P-09853](https://akizukidenshi.com/catalog/g/gP-09853/)|                                        |
|3mmプラネジ(7mm)+六角スペーサー(14mm)セット|1   |[P-01861](https://akizukidenshi.com/catalog/g/gP-01861/)|8 x M3プラネジと4 x M3スペーサーのセット|

### サンドイッチマウントケース

未設計

## 工具

Xiaolu Keyboard PCBはハンダ付けが必要なため、ハンダ付けやその他の電子工作のための一般的な工具が必要です。

* ハンダごて - 温度調節機能付きのものでも、ベーシックなものでもよいのですが、温度調節機能付きのものを強くお勧めします。
* ハンダ - この組み立てには、はんだが必要です。
* ドライバーセット - ケースの組み立てには、ドライバーセットが必要です。

工具を扱うときは、常に適切な安全対策に従ってください。
