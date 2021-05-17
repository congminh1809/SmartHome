# SmartHome

<p align="center">
   <img width="500" height="500" src="https://github.com/congminh1809/SmartHome/blob/main/Screenshot%202021-05-17%20144841.jpg">
</p>

*) Cần: servo, led, pickit, pic16f877a, mạch ra chân, cảm biến khoảng cách, cảm biến nhiệt độ(nếu cảm biến khoảng cách có vấn đè), màn LCD, module esp32, còi

*) Ý tưởng:
Timer: hiển thị nhiệt độ, thời gian
Interrupt: có trộm thì báo còi, đo bằng cảm biến khoảng cách
ADC: cảm biến khoảng cách, cảm biến nhiệt độ
PWM: servo, bật tắt led
UART: bật tắt đèn từ xa

Dùng cảm biến ánh sáng để giữ độ sáng trong phòng

*) Note:
+ Servo TS90M 3 dây: 1 dây cấp nguồn, 1 dây GND, 1 dây cấp PWM. Thường chu kì xung là T = 20ms. Độ rộng xung thường là từ 1ms đến 2ms.
Cần tìm độ rộng xung min và max của servo để điều chỉnh vị trí quay. (500ms – 1500ms theo thông số nhà sản xuất)
Timer2 dùng riêng cho PWM

