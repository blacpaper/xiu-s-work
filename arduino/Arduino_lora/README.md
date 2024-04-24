**项目内容**

​	通过外接 Lora 模块，可以实现多个Arduino的远距离通信。

**硬件**

|            硬件            | 数量 |          备注           |
| :------------------------: | :--: | :---------------------: |
| Arduino UNO / Arduino Nano |  1   | 若要做通信，至少需要 *2 |
|            Lora            |  1   |          同上           |
|           杜邦线           | 若干 |                         |

**接线**

| Arduino | Lora |
| :-----: | :--: |
|   5V    | VCC  |
|   GND   | GND  |
|   RX    |  TX  |
|   TX    |  RX  |

**编译IDE**

​	Arduino IDE