# Snake Game STM32

Snake Game dùng để thực hành tổ chức Firmware thành nhiều module.

## Chức năng

- Điều khiển rắn bằng nút nhấn.
- Sinh thức ăn.
- Phát hiện va chạm.
- Tăng chiều dài.
- Cập nhật điểm số.
- Hiển thị trên LCD.
- Tách Game Logic và Rendering.

## Kiến trúc

~~~text
main
 ├── Driver
 └── Application
     ├── Game
     ├── Snake
     ├── Food
     ├── Collision
     └── Renderer
~~~