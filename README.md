# 🚀 Lập trình MCU với STM32

Kho lưu trữ các dự án, bài thực hành và tài liệu học tập về lập trình vi điều khiển STM32.

Repository tập trung vào quá trình học và xây dựng Firmware Embedded từ GPIO, Interrupt, Timer, SPI, Shift Register, LED 7 đoạn, LCD đến Communication và Mini Project.

## 🎯 Mục tiêu
- Học Embedded C trên STM32.
- Cấu hình ngoại vi bằng STM32CubeMX.
- Xây dựng Driver và Application theo module.
- Thực hành State Machine và Non-blocking Programming.
- Lưu source code theo project để dễ học, tra cứu và tái sử dụng.

## 📂 Cấu trúc
~~~text
lap-trinh-mcu/
├── projects/      # Source code các project STM32
├── notes/         # Ghi chú kiến thức
├── docs/          # Tài liệu tham khảo
├── README.md
└── .gitignore
~~~

## 🧩 Projects
| Nhóm | Project |
|---|---|
| Interrupt | exti-basic |
| Interrupt | button-debounce |
| Seven Segment | 74hc595-counter |
| Seven Segment | multiplexing |
| Seven Segment | button-input-74hc165 |
| LCD | lcd-driver |
| LCD | lcd-timer-driver |
| Application | stopwatch |
| Application | digital-clock |
| Application | alarm-clock-ds3231 |
| Application | snake-game |
| Communication | usart-basic |

## 🛠️ Công nghệ
- MCU: STM32
- Ngôn ngữ: Embedded C
- IDE: STM32CubeIDE
- Configuration: STM32CubeMX
- Library: STM32 HAL
- Debug / Flash: ST-Link

## 🧱 Kiến trúc
~~~text
Application
    ↓
Services
    ↓
Drivers
    ↓
STM32 HAL / Peripheral
    ↓
Hardware
~~~

## ▶️ Sử dụng
Clone repository, chọn một thư mục trong projects/ và mở project bằng STM32CubeIDE.

Trước khi build hoặc nạp chương trình, kiểm tra MCU, GPIO mapping, clock, peripheral configuration và phần cứng thực tế.

## 📖 Tài liệu
- notes/: kiến thức và bài học.
- docs/hardware/: tài liệu kit/phần cứng.
- docs/learning/: tài liệu học tập.
- docs/references/: tài liệu kỹ thuật.

## 🚧 Định hướng
- UART Interrupt / DMA
- I2C
- ADC
- PWM
- DMA
- FreeRTOS
- Communication Protocol
- Embedded Debugging
- Firmware Architecture

## 👨‍💻 Tác giả
**Nguyễn Ngọc Hùng**

Sinh viên Điện tử - Viễn thông
Định hướng Embedded Systems / Firmware

> Learning by building. 🔧