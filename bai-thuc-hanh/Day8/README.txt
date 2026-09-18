=========================================
NGÀY 8 - LED 7 ĐOẠN, 74HC595 VÀ MULTIPLEXING
=========================================

Ngày học thứ tám tập trung tìm hiểu phần cứng LED 7 đoạn trên ARM KIT,
xây dựng Driver điều khiển bằng phương pháp GPIO Bit-Banging kết hợp IC
dịch 74HC595 và nghiên cứu nguyên lý quét LED (Multiplexing). Mục tiêu
không chỉ là hiển thị dữ liệu mà còn hiểu được mối liên hệ giữa phần cứng
và chương trình điều khiển để xây dựng thư viện có khả năng tái sử dụng
trong các ứng dụng nhúng. 

Trong buổi học, tiến hành khảo sát từng bit điều khiển trên board ARM KIT
để xác định bảng chọn LED, mapping các đoạn hiển thị và xây dựng bảng mã
hiển thị số. Đồng thời phát triển Driver theo hướng module hóa với các hàm
độc lập như SendBitLED(), SendByte() và DisplayDigit(), giúp chương trình
dễ đọc, dễ bảo trì và thuận tiện mở rộng khi số lượng LED tăng lên. 

Bên cạnh đó, tìm hiểu nguyên lý quét LED (Multiplexing), sử dụng Timer
Polling để tạo chu kỳ quét ổn định và áp dụng các phép dịch bit cùng phép
AND để xử lý dữ liệu trước khi truyền vào IC 74HC595. Qua quá trình thực
hành, từng bước hiểu được sự khác nhau giữa điều khiển một LED và nhiều
LED 7 đoạn hoạt động đồng thời.

Ngày học này giúp củng cố tư duy thiết kế Driver cho thiết bị ngoại vi,
hiểu rõ hơn quá trình truyền dữ liệu nối tiếp đến Shift Register và tạo
nền tảng cho các bài học tiếp theo về đọc nút nhấn bằng 74HC165, xây
dựng thư viện điều khiển LED 7 đoạn hoàn chỉnh và phát triển các ứng dụng
Embedded theo hướng chuyên nghiệp. 
