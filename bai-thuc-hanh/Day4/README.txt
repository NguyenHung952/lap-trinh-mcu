=========================================
NGÀY 4 - EXTERNAL INTERRUPT VÀ BUTTON DEBOUNCE
=========================================

Ngày học thứ tư tập trung tìm hiểu cơ chế ngắt ngoài (External Interrupt -
EXTI) trên STM32, cách cấu hình ngắt bằng STM32CubeMX và phân tích
toàn bộ luồng xử lý Interrupt trong thư viện HAL. Đồng thời nghiên cứu
kỹ thuật chống dội phím (Button Debounce) để nâng cao độ ổn định khi xử
lý nút nhấn trong các ứng dụng nhúng. 

Trong buổi học, thực hiện cấu hình chân GPIO ở chế độ External
Interrupt, tìm hiểu các khái niệm như Rising Edge, Falling Edge,
Pending Bit và Interrupt Priority, đồng thời đọc và phân tích mã nguồn
HAL để hiểu quá trình xử lý ngắt từ phần cứng đến ứng dụng. Bên cạnh đó,
nghiên cứu cơ chế hoạt động của HAL_GetTick(), SysTick và cách Callback
được sử dụng trong chương trình. 

Ngoài việc tìm hiểu External Interrupt, buổi học còn xây dựng thuật toán
Button Debounce bằng Timer Interrupt kết hợp Counter, State Machine và
Event Flag nhằm loại bỏ hiện tượng dội phím. Qua đó hình thành tư duy
thiết kế firmware theo mô hình Event-Driven, tách biệt rõ giữa Interrupt
Service Routine (ISR) và Application để chương trình dễ bảo trì và mở
rộng hơn. 

Đây là nền tảng quan trọng để phát triển các ứng dụng sử dụng nút nhấn,
xử lý sự kiện theo ngắt và tiếp tục học các giao tiếp ngoại vi cũng như
các dự án Embedded phức tạp hơn trong những buổi học tiếp theo.
