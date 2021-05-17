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


I) Tên dự án: Nhà thông minh - Smart Home

II) Mô tả ngắn:
   Dự án được xây dựng nhằm mô hình hóa 1 căn nhà thông minh với tính năng chính là chống trộm, bật tắt thiết bị từ xa (đèn, quạt…) và điều chỉnh độ sáng của đèn theo ánh sáng trong phòng dựa trên sức mạnh của vi xử lý pic 16f877a.

III) Mục tiêu: 
+) Xây dựng mô hình hệ thống nhà thông minh với các tính năng như sau:
   - Đèn thông minh tự động thay đổi độ sáng dựa vào cảm biến ánh sáng
   - Hệ thống chống trộm sử dụng cảm biến chuyển động
   - Hệ thống đèn sáng nhiều chế độ
   - Hệ thống bật tắt thiết bị từ xa

+) Thông hiểu các tính năng của vi xử lý pic16f877a với các chức năng đã được học bao gồm:
   - GPIO pins
   - Timer
   - Interrupt
   - PWM mode
   - UART
   - ADC



IV) Các linh kiện sử dụng trong dự án:
   Vi xử lý PIC 16F877A

   Mạch ra chân PIC V1
 
   Mạch nạp Pickit 2

   Đèn led

   Button cảm ứng

   Buzzer điện

   Cảm biến chuyển động PIR sr 505

   Cảm biến ánh sáng quang trở

   Module wifi ESP8266



V) Mô tả chi tiết:
   Dự án vận hành với sức mạnh của vi xử lý pic 16f877a

   Đèn được điều chỉnh độ sáng theo ánh sáng trong phòng thông qua cảm biến ánh sáng quang điện trở. Khi ánh sáng trong phòng lớn, đèn sẽ sáng yếu và ngược lại. Độ sáng của đèn được điều chỉnh bằng xung PWM – điều chế bởi Timer2 của vi xử lý.

   Mô hình được trang bị 1 button cảm ứng, thực hiện hàm ngắt (Interrupt) để chuyển đổi các chế độ, chức năng phát sáng của bóng đèn.

   Chức năng chống trộm: Cảm biến chuyển động PIR sr 505 giúp phát hiện chuyển động ở gần mô hình. Khi có vật chuyển động xuất hiện, cảm biến sẽ trả về giá trị điện áp cao vào chân input của vi xử lý, từ đó còi (buzzer điện) sẽ được cấp điện và phát ra tiếng (cảnh báo có chuyển động).

   Để điều khiển bật tắt thiết bị trong phòng, vi xử lý được kết nối với module wifi ESP8266 thông qua giao thức UART, thừ đó có thể điều khiển thiết bị thông qua mạng wifi trên thiết bị di động.


