=========================================
NGÀY 13 - DIGITAL CLOCK VÀ KIẾN TRÚC PHẦN MỀM NHÚNG
=========================================

Ngày học thứ mười ba tập trung thiết kế và hoàn thiện ứng dụng Digital
Clock trên STM32 theo kiến trúc phân tầng giữa Driver và Application.
Buổi học hướng đến việc kết hợp các Driver đã xây dựng trước đó như LCD,
Button, Timer và LED để phát triển một ứng dụng hoàn chỉnh với cấu trúc
rõ ràng, dễ mở rộng và thuận tiện cho việc bảo trì.

Trong buổi học, tiến hành xây dựng kiến trúc phần mềm với các module độc
lập cho Driver và Application, thiết kế luồng xử lý chính của chương
trình theo mô hình Input → Process → Output và áp dụng State Machine để
quản lý các chế độ hoạt động của đồng hồ. Đồng thời xây dựng giao diện
hiển thị trên LCD, xử lý sự kiện từ nút nhấn và cập nhật thời gian bằng
Timer Polling theo phương pháp Non-blocking.

Bên cạnh việc hoàn thiện chức năng của ứng dụng, buổi học còn chú trọng
đến việc tổ chức mã nguồn theo hướng module hóa, phân chia rõ trách
nhiệm giữa các thành phần trong hệ thống và xây dựng các API có khả năng
tái sử dụng. Điều này giúp chương trình dễ kiểm thử, dễ mở rộng và phù
hợp với quy trình phát triển phần mềm nhúng trong các dự án thực tế. 

Ngày học này đánh dấu bước tiến từ việc xây dựng các Driver và Mini
Project sang thiết kế một ứng dụng Embedded hoàn chỉnh với kiến trúc
phần mềm chuyên nghiệp. Đây cũng là nền tảng quan trọng để tiếp tục phát
triển các hệ thống nhúng có nhiều chức năng, nhiều module và quy mô lớn
hơn trong tương lai.
