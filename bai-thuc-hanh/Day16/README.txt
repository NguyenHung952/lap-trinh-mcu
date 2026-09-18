# 📡 USART1 Communication trên STM32

## Giới thiệu

Đây là dự án mình thực hiện trong quá trình học giao tiếp UART/USART trên vi điều khiển STM32. Mục tiêu của dự án là tìm hiểu nguyên lý truyền dữ liệu nối tiếp, cách cấu hình USART bằng STM32CubeMX và sử dụng thư viện STM32 HAL để truyền dữ liệu từ STM32 đến máy tính.

Trong dự án, STM32 sử dụng USART1 để gửi một thông báo khởi động khi chương trình bắt đầu chạy, sau đó định kỳ gửi giá trị của một bộ đếm (Counter) lên Serial Terminal mỗi giây.

Thông qua dự án này, mình hiểu rõ hơn cách hoạt động của giao tiếp UART, cách sử dụng API của HAL và cách tổ chức một chương trình Embedded đơn giản theo hướng dễ mở rộng.

---

# Mục tiêu dự án

- Làm quen với giao tiếp USART trên STM32.
- Hiểu cách cấu hình USART bằng STM32CubeMX.
- Sử dụng STM32 HAL để truyền dữ liệu.
- Thực hành định dạng chuỗi bằng `snprintf()`.
- Hiển thị dữ liệu trên Serial Terminal.

---

# Chức năng

- Khởi tạo USART1.
- Gửi thông báo khi hệ thống khởi động.
- Gửi giá trị Counter sau mỗi 1 giây.
- Truyền dữ liệu theo chuẩn UART.
- Sử dụng HAL UART API.

Ví dụ kết quả:

```
STM32F207 USART1 READY

Counter: 0
Counter: 1
Counter: 2
Counter: 3
...
```

---

# Phần cứng sử dụng

- ARM KIT
- STM32F207VC
- ST-Link V2
- Cáp USB
- Máy tính chạy Serial Terminal

---

# Phần mềm sử dụng

- STM32CubeIDE
- STM32CubeMX
- STM32 HAL Library
- Hercules / PuTTY / Tera Term (Serial Terminal)

---

# Kiến trúc chương trình

```
             main.c
                │
      ┌─────────┴─────────┐
      │                   │
 System Init        USART1 Driver
      │                   │
      └─────────┬─────────┘
                │
          UART Transmit
                │
         Serial Terminal
```

---

# Luồng hoạt động

```
Khởi tạo hệ thống
        │
        ▼
Khởi tạo USART1
        │
        ▼
Gửi thông báo khởi động
        │
        ▼
Counter = 0
        │
        ▼
Định dạng chuỗi
        │
        ▼
HAL_UART_Transmit()
        │
        ▼
Hiển thị trên Serial Terminal
        │
        ▼
Delay 1 giây
        │
        ▼
Counter++
        │
        └────── Quay lại
```

---

# Kiến thức đã áp dụng

Trong quá trình thực hiện dự án mình đã thực hành:

- Embedded C
- STM32 HAL
- USART/UART
- STM32CubeMX
- STM32CubeIDE
- HAL_UART_Transmit()
- Chuỗi ký tự (String)
- `snprintf()`
- Buffer truyền dữ liệu
- Timer bằng `HAL_Delay()`

---

# Cấu trúc dự án

```
Core/
│
├── Inc/
│   └── main.h
│
├── Src/
│   ├── main.c
│   ├── stm32f2xx_hal_msp.c
│   ├── stm32f2xx_it.c
│   └── ...
│
Drivers/
│
STM32CubeMX Configuration
```

---

# Kết quả đạt được

Sau khi hoàn thành dự án, chương trình có thể:

- Khởi tạo USART1 thành công.
- Truyền dữ liệu từ STM32 đến máy tính.
- Hiển thị thông báo khi khởi động.
- Gửi bộ đếm liên tục theo chu kỳ 1 giây.
- Hiểu quy trình truyền dữ liệu bằng thư viện HAL.

Dự án này giúp mình nắm được những kiến thức cơ bản về giao tiếp UART/USART trên STM32 và tạo nền tảng để tiếp tục phát triển các ứng dụng sử dụng giao tiếp nối tiếp như giao tiếp với cảm biến, module GPS, Bluetooth, ESP8266 hoặc trao đổi dữ liệu với máy tính.

---

# Hướng phát triển

Trong thời gian tới mình dự định sẽ bổ sung:

- USART Receive.
- Giao tiếp hai chiều.
- Ngắt UART (Interrupt).
- DMA UART.
- Command Line Interface (CLI).
- Gửi dữ liệu cảm biến.
- Điều khiển LED từ máy tính.
- Giao tiếp giữa hai vi điều khiển STM32.

---

# Hình ảnh

> Sẽ cập nhật sau.

---

# Tác giả

**Nguyễn Ngọc Hùng**

Dự án được thực hiện trong quá trình tự học STM32 và thực tập Firmware Embedded nhằm rèn luyện kỹ năng lập trình giao tiếp USART và phát triển phần mềm nhúng.
