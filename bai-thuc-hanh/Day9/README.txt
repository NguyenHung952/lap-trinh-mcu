=========================================
NGÀY 9 - 74HC165, 74HC595 VÀ QUẢN LÝ NGOẠI VI
=========================================

Ngày học thứ chín tập trung xây dựng hệ thống điều khiển và đọc dữ liệu
thông qua hai IC dịch 74HC595 và 74HC165 trên ARM KIT. Nội dung buổi
học hướng đến việc tổ chức chương trình theo từng module, kết hợp giữa
điều khiển LED 7 đoạn, đọc nhiều nút nhấn và xây dựng thuật toán xử lý
theo State Machine để tạo nền tảng cho các ứng dụng nhúng hoàn chỉnh. 

Trong buổi học, thực hiện tìm hiểu nguyên lý hoạt động của IC 74HC165,
quá trình nạp dữ liệu song song và dịch dữ liệu nối tiếp để đọc trạng
thái nhiều nút nhấn thông qua giao tiếp Shift Register. Đồng thời xây
dựng thư viện điều khiển Button nhằm quản lý việc đọc dữ liệu từ phần
cứng một cách độc lập với chương trình ứng dụng. 

Bên cạnh đó, tiếp tục hoàn thiện Driver điều khiển LED 7 đoạn bằng
74HC595, kết hợp kỹ thuật quét LED (Multiplexing) và Timer để hiển thị
dữ liệu ổn định. Các nút nhấn được sử dụng để thay đổi chế độ hoạt động
của chương trình thông qua mô hình State Machine, giúp nâng cao khả năng
tổ chức và mở rộng phần mềm. 

Ngày học này giúp hiểu rõ hơn về cách giao tiếp với nhiều thiết bị ngoại
vi thông qua Shift Register, xây dựng Driver theo hướng module hóa và
tách biệt giữa phần cứng với phần mềm ứng dụng. Đây là nền tảng quan
trọng để tiếp tục nghiên cứu Button Debounce, LCD, các Mini Project và
kiến trúc phần mềm Embedded trong những bài học tiếp theo. 
