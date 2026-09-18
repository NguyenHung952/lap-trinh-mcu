# 🚀 Lập trình MCU với STM32

Repository lưu trữ quá trình học tập và thực hành **lập trình vi điều khiển STM32**, theo từng buổi học (`Day1` → `Day16`). Nội dung gồm bài thực hành, mã nguồn/project đóng gói và tài liệu phục vụ học tập.

## 🎯 Mục tiêu

- Làm quen với lập trình Embedded C trên STM32
- Thực hành GPIO, Timer, Interrupt và các ngoại vi cơ bản
- Làm việc với LED 7 đoạn, LCD, UART và các ứng dụng thời gian thực
- Rèn luyện quy trình cấu hình và phát triển project STM32
- Lưu trữ bài thực hành theo tiến trình để dễ học và tra cứu

## 📂 Cấu trúc repository

```text
lap_trinh_mcu/
├── bai-thuc-hanh/
│   ├── Day1/
│   ├── Day2/
│   ├── Day3/
│   ├── Day4/
│   ├── Day5/
│   ├── Day6,7/
│   ├── Day8/
│   ├── Day9/
│   ├── Day10/
│   ├── Day11/
│   ├── Day12/
│   ├── Day13/
│   ├── Day14/
│   ├── Day15/
│   └── Day16/
├── tai-lieu/
│   ├── Arm Kit 01.docx
│   ├── Học Lập trình STM32.docx
│   ├── PCSCADA & Factory Automation Solutions.pdf
│   ├── STM32F205 Reference.pdf
│   ├── Tài Khoản CTy Điện Tự Động Phú Cường.doc
│   ├── Tài liệu TT Kỹ thuật số và Vi điều khiển v1.0.pdf
│   ├── stm32f405zg.pdf
│   └── stm32f407ve.pdf
└── README.md
```

## 🧩 Nội dung thực hành

| Buổi | Nội dung chính thể hiện qua project hiện có |
|---|---|
| Day1 | LED chớp tắt |
| Day2 | Điều khiển LED |
| Day3 | Timer và ngắt |
| Day4 | Ngắt ngoài EXTI, xử lý nút nhấn |
| Day5 | LED 7 đoạn và 74HC595 |
| Day6,7 | LED 7 đoạn mở rộng |
| Day8–9 | LED 7 đoạn trên STM32, nút nhấn |
| Day10–11 | LCD với STM32 |
| Day12 | Stopwatch |
| Day13 | Digital Clock |
| Day14 | Alarm Clock, DS3231 |
| Day15 | Snake Game trên STM32 |
| Day16 | USART |

> Bảng trên được tổng hợp từ tên project hiện có; nội dung chi tiết của từng buổi vẫn được giữ trong `README.txt` tương ứng.

## 🛠️ Công nghệ & công cụ

- **MCU:** STM32
- **Ngôn ngữ:** Embedded C
- **IDE:** STM32CubeIDE
- **Cấu hình:** STM32CubeMX
- **Thư viện:** STM32 HAL
- **Debug/Program:** ST-Link
- **Version control:** Git & GitHub

## 📚 Cách sử dụng

1. Chọn buổi học trong thư mục `bai-thuc-hanh/`.
2. Đọc `README.txt` của buổi đó trước khi mở project.
3. Mở file project bằng môi trường STM32 phù hợp.
4. Kiểm tra cấu hình phần cứng và board/MCU trước khi build hoặc nạp chương trình.
5. Sử dụng thư mục `tai-lieu/` để tra cứu tài liệu và thông tin liên quan.

## ⚠️ Lưu ý

- Repository phục vụ mục đích học tập và lưu trữ cá nhân.
- Tên file và nội dung các tài liệu/project gốc được giữ nguyên; chỉ sắp xếp lại vị trí để repository dễ quản lý hơn.
- Một số file trong repository hiện có kích thước rất nhỏ/không chứa dữ liệu đầy đủ; không tự ý thay thế hoặc xóa chúng nếu chưa kiểm tra bản gốc.
- Kiểm tra thông tin tài khoản, tài liệu nội bộ hoặc dữ liệu của bên thứ ba trước khi chia sẻ công khai.

## 👨‍💻 Tác giả

**Nguyễn Ngọc Hùng**

- Electronics & Telecommunications Student
- Embedded Systems Learner
- Learning STM32 Embedded Development

---

> **Learning by doing.** 🔧