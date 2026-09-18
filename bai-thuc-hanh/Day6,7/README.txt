=========================================
NGÀY 6 - LED 7 ĐOẠN VÀ THIẾT KẾ DRIVER 74HC595
=========================================

Ngày học thứ sáu tập trung tìm hiểu phương pháp điều khiển LED 7 đoạn
thông qua IC dịch 74HC595 mắc nối tiếp (Cascade) trên STM32. Nội dung
không chỉ dừng lại ở việc hiển thị dữ liệu mà còn hướng đến xây dựng
Driver theo hướng tổng quát, có khả năng mở rộng và tái sử dụng trong
các ứng dụng nhúng.

Trong buổi học, thực hiện điều khiển LED 7 đoạn bằng phương pháp
Bit-Banging thông qua các chân MOSI, SCK và RCK, đồng thời tìm hiểu
nguyên lý hoạt động của IC 74HC595, cơ chế dịch dữ liệu nối tiếp và cách
mắc nhiều IC theo phương pháp Cascade để mở rộng số lượng LED điều
khiển. Bên cạnh đó, chương trình được refactor theo mô hình Driver nhằm
tách biệt phần điều khiển phần cứng và phần ứng dụng. 

Ngoài việc mở rộng hiển thị từ một LED lên nhiều LED 7 đoạn, buổi học
còn thực hiện chương trình đếm từ 00000 đến 99999, đồng thời tìm hiểu
cách tách số thành từng chữ số để hiển thị và xây dựng các hàm điều
khiển có thể tái sử dụng cho nhiều bài toán khác nhau. Qua đó từng bước
hình thành tư duy thiết kế Driver có tính mở rộng thay vì chỉ viết chương
trình phục vụ cho một mục đích cụ thể. 

Ngày học này giúp củng cố kiến thức về giao tiếp với phần cứng, tổ chức
mã nguồn theo hướng module hóa và tạo nền tảng cho các bài học tiếp theo
về quét LED (Multiplexing), đọc nút nhấn, Timer và xây dựng các Driver
cho hệ thống Embedded. 
