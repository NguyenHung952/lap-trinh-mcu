# 🐍 Snake Game trên STM32

## Giới thiệu

Đây là dự án mình thực hiện trong quá trình học lập trình nhúng với STM32. Mục tiêu của dự án không chỉ là xây dựng trò chơi Snake chạy trên LCD mà còn rèn luyện tư duy thiết kế Firmware theo hướng chuyên nghiệp, với kiến trúc module hóa, dễ mở rộng và dễ bảo trì.

Thay vì viết toàn bộ chương trình trong `main.c`, dự án được chia thành nhiều module độc lập như Game, Snake, Food, Renderer, Framebuffer, LCD Driver, Timer, Button... Mỗi module chỉ đảm nhiệm một nhiệm vụ riêng và giao tiếp với nhau thông qua các API rõ ràng.

Thông qua dự án này, mình có cơ hội thực hành nhiều kiến thức quan trọng trong lập trình nhúng như quản lý bộ nhớ, State Machine, xử lý thời gian không chặn (Non-blocking), thiết kế Driver và tổ chức mã nguồn theo kiến trúc nhiều tầng.

---

# Mục tiêu dự án

- Xây dựng trò chơi Snake chạy trên vi điều khiển STM32.
- Thiết kế chương trình theo kiến trúc Firmware chuyên nghiệp.
- Hạn chế phụ thuộc giữa các module.
- Dễ dàng mở rộng thêm tính năng trong tương lai.
- Rèn luyện tư duy phân tích và thiết kế hệ thống nhúng.

---

# Chức năng

- Điều khiển rắn bằng các nút nhấn.
- Sinh thức ăn ngẫu nhiên.
- Phát hiện va chạm.
- Rắn tăng chiều dài sau khi ăn.
- Cập nhật điểm số.
- Hiển thị hình ảnh trên LCD 16x2.
- Điều khiển bằng Timer Polling (Non-blocking).
- Tách riêng phần Logic Game và phần Hiển thị.
- Có thể mở rộng AI điều khiển rắn.

---

# Phần cứng sử dụng

- ARM KIT
- STM32F207VC
- LCD 16x2 (HD44780)
- Nút nhấn
- LED
- Còi (Buzzer)

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
        ┌───────────────────┼───────────────────┐
        │                   │                   │
     Driver             Application          Adapter
        │                   │                   │
        │                   │                   │
   LCD Driver          Snake Game        Timer Adapter
   Button Driver       Snake             Button Adapter
   Timer Driver        Food
   LED Driver          Collision
   Buzzer Driver       Renderer
                        Framebuffer
                        Random
                        AI
```

Mỗi module đảm nhiệm một chức năng riêng giúp chương trình dễ đọc, dễ kiểm thử và thuận tiện khi mở rộng.

---

# Cấu trúc thư mục

```
Core
│
├── Inc
│
├── Src
│   ├── game.c
│   ├── snake.c
│   ├── food.c
│   ├── collision.c
│   ├── render.c
│   ├── framebuffer.c
│   ├── snake_renderer.c
│   ├── food_renderer.c
│   ├── lcd_renderer.c
│   ├── snake_ai.c
│   ├── random.c
│   ├── timer.c
│   ├── lcd.c
│   ├── button.c
│   ├── led.c
│   ├── buzzer.c
│   └── main.c
│
Drivers
│
STM32CubeMX
```

---

# Luồng hoạt động

```
Khởi tạo hệ thống
        │
        ▼
Khởi tạo Driver
        │
        ▼
Khởi tạo Game
        │
        ▼
Đọc nút nhấn
        │
        ▼
Cập nhật hướng di chuyển
        │
        ▼
Di chuyển rắn
        │
        ▼
Kiểm tra va chạm
        │
        ▼
Ăn thức ăn
        │
        ▼
Cập nhật Framebuffer
        │
        ▼
Render lên LCD
        │
        ▼
Lặp lại
```

---

# Kiến thức đã áp dụng

Trong quá trình thực hiện dự án mình đã thực hành:

- Embedded C
- STM32 HAL
- GPIO
- Timer
- LCD Driver
- Button Driver
- Buzzer Driver
- State Machine
- Modular Programming
- Framebuffer
- Game Loop
- Collision Detection
- Random Number Generation
- Non-blocking Programming
- Firmware Architecture

---

# Kết quả đạt được

Sau khi hoàn thành dự án, trò chơi có thể:

- Điều khiển rắn bằng nút nhấn.
- Sinh thức ăn ngẫu nhiên.
- Xử lý va chạm chính xác.
- Tăng chiều dài của rắn sau khi ăn.
- Hiển thị trò chơi trên LCD.
- Tổ chức mã nguồn theo kiến trúc module hóa.
- Dễ dàng bổ sung thêm tính năng mới mà không ảnh hưởng nhiều đến các module khác.

Quan trọng hơn, dự án giúp mình chuyển từ việc học từng ngoại vi STM32 riêng lẻ sang xây dựng một ứng dụng Embedded hoàn chỉnh với nhiều thành phần phối hợp với nhau. Đây cũng là cơ hội để mình luyện tập cách thiết kế Firmware theo hướng có thể tái sử dụng và mở rộng trong các dự án sau này.

---

# Hướng phát triển

Một số tính năng mình dự định sẽ bổ sung trong tương lai:

- Menu chính.
- Mức độ khó.
- Lưu điểm cao nhất.
- Hiệu ứng âm thanh.
- Chế độ Pause.
- AI tự chơi.
- Hiển thị điểm số.
- Hoạt ảnh Game Over.
- Tối ưu tốc độ Render.

---

# Hình ảnh

> Sẽ cập nhật sau khi hoàn thiện dự án.

---

# Tác giả

**Nguyễn Ngọc Hùng**

Dự án được thực hiện trong quá trình tự học STM32 và thực tập Firmware Embedded, với mục tiêu rèn luyện tư duy thiết kế phần mềm nhúng và xây dựng các dự án có kiến trúc rõ ràng, dễ mở rộng.
