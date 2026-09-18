# ⏰ Đồng Hồ Báo Thức STM32 Kết Hợp Đo Nhiệt Độ

## Giới thiệu

Đây là dự án được mình thực hiện trong quá trình học lập trình nhúng với STM32. Mục tiêu của dự án không chỉ là xây dựng một chiếc đồng hồ báo thức hoạt động được mà còn rèn luyện cách thiết kế phần mềm nhúng theo hướng module hóa, dễ mở rộng và dễ bảo trì.

Trong dự án, mình kết hợp các Driver đã tự xây dựng ở những buổi học trước như LCD, Button, Timer, LED và DS3231 để tạo thành một ứng dụng hoàn chỉnh chạy trên vi điều khiển STM32.

Thông qua dự án này, mình làm quen với cách tổ chức mã nguồn theo mô hình Driver/Application, xây dựng State Machine, thiết kế API giữa các module và phát triển chương trình theo tư duy của một Firmware Engineer thay vì chỉ viết code để chương trình chạy được.

---

# Chức năng

- Hiển thị thời gian thực (HH:MM:SS)
- Cài đặt thời gian báo thức
- Bật/Tắt báo thức
- Đọc thời gian từ DS3231
- Hiển thị nhiệt độ từ cảm biến tích hợp trong DS3231
- Hiển thị thông tin trên LCD 16x2
- Báo thức bằng LED và Còi
- Điều khiển bằng các nút nhấn trên KIT
- Thiết kế theo kiến trúc module

---

# Phần cứng sử dụng

- ARM KIT
- STM32
- LCD 16x2 (HD44780)
- Module RTC DS3231
- LED
- Còi (Buzzer)
- Nút nhấn

---

# Phần mềm sử dụng

- STM32CubeIDE
- STM32CubeMX
- STM32 HAL Library
- ST-Link V2

---

# Kiến trúc chương trình

```
                 main.c
                    │
        ┌───────────┴───────────┐
        │                       │
     Driver                  Application
        │                       │
 ┌──────┼──────┐        ┌────────┼────────┐
 │      │      │        │        │        │
LCD   Button Timer    Clock    Alarm     Menu
 │      │      │        │        │        │
 └──────┴──────┴────────┴────────┴────────┘
                    │
                  DS3231
                    │
              LCD + LED + Buzzer
```

Mỗi module chỉ đảm nhiệm một chức năng riêng, giúp chương trình dễ đọc, dễ kiểm thử và thuận tiện khi bổ sung thêm tính năng mới.

---

# Luồng hoạt động

```
Khởi tạo hệ thống
        │
        ▼
Khởi tạo LCD
        │
        ▼
Khởi tạo DS3231
        │
        ▼
Đọc thời gian
        │
        ▼
Đọc nhiệt độ
        │
        ▼
Đọc nút nhấn
        │
        ▼
Xử lý Menu
        │
        ▼
Cập nhật LCD
        │
        ▼
Kiểm tra báo thức
        │
        ▼
Điều khiển LED và Còi
```

---

# Kiến thức đã áp dụng

Thông qua dự án này mình đã thực hành:

- GPIO
- Timer
- I2C
- LCD 16x2
- RTC DS3231
- Đọc nhiệt độ
- State Machine
- Non-blocking Programming
- Driver Development
- Modular Programming
- Firmware Architecture
- STM32 HAL Library

---

# Kết quả đạt được

Sau khi hoàn thành dự án, chương trình có thể:

- Hiển thị thời gian chính xác theo DS3231.
- Hiển thị nhiệt độ môi trường.
- Cài đặt và kích hoạt báo thức.
- Báo bằng LED và còi khi đến thời gian đã cài.
- Dễ dàng mở rộng thêm các tính năng mới nhờ kiến trúc module.

Đây là dự án đánh dấu quá trình mình chuyển từ việc học từng ngoại vi riêng lẻ sang xây dựng một ứng dụng Embedded hoàn chỉnh. Qua đó mình hiểu rõ hơn cách tổ chức mã nguồn, thiết kế API giữa các module và xây dựng phần mềm theo hướng có thể tái sử dụng trong các dự án sau này.

---

# Hướng phát triển

Trong thời gian tới mình dự định sẽ bổ sung thêm:

- Stopwatch
- Countdown Timer
- Hiển thị ngày/tháng/năm
- Lưu cài đặt bằng EEPROM
- UART Debug
- Giao tiếp PC
- Chế độ tiết kiệm năng lượng

---

# Hình ảnh

> Sẽ cập nhật sau.

---

# Tác giả

**Nguyễn Ngọc Hùng**

Dự án được thực hiện trong quá trình học STM32 và thực tập Firmware Embedded.
