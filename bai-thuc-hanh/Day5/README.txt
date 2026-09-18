=========================================
NGÀY 5 - GIAO TIẾP SPI VÀ IC DỊCH 74HC595
=========================================

Ngày học thứ năm tập trung tìm hiểu giao tiếp SPI trên STM32 và ứng dụng
để điều khiển IC dịch 74HC595, từ đó điều khiển LED 7 đoạn. Bên cạnh
việc thực hành lập trình, buổi học còn giúp hiểu nguyên lý hoạt động của
SPI Hardware, cơ chế Alternate Function và quá trình truyền dữ liệu giữa
STM32 với thiết bị ngoại vi. 

Trong buổi học, thực hiện xây dựng bảng mã hiển thị (Lookup Table) cho
LED 7 đoạn, điều khiển 74HC595 bằng phương pháp Bit-Banging để hiểu rõ
quá trình dịch dữ liệu nối tiếp. Sau đó tiếp tục cấu hình và sử dụng SPI
Hardware nhằm nâng cao hiệu quả truyền dữ liệu, đồng thời tìm hiểu chức
năng của các tín hiệu MOSI, SCK và ST_CP trong quá trình điều khiển IC
74HC595.

Ngoài phần lập trình ứng dụng, buổi học còn tìm hiểu cơ chế Alternate
Function của STM32, cách tra cứu Datasheet để xác định các chân SPI và
đọc mã nguồn thư viện HAL nhằm hiểu quá trình HAL_SPI_Transmit() thao
tác với các thanh ghi phần cứng như SPI_DR, SPI_SR cùng các cờ trạng
thái TXE và BSY. 

Ngày học này giúp hiểu rõ hơn về giao tiếp SPI, quá trình truyền dữ liệu
giữa vi điều khiển và ngoại vi, đồng thời tạo nền tảng cho việc xây dựng
các driver điều khiển thiết bị ngoại vi và tiếp tục nghiên cứu các giao
tiếp khác như UART, I2C, DMA cũng như lập trình ở mức thanh ghi trong
các bài học tiếp theo. 
