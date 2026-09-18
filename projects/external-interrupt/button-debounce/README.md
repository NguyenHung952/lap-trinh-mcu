# Button Debounce

Thực hành chống dội nút nhấn và tổ chức firmware theo hướng Event-Driven.

## Nội dung

- Timer Interrupt.
- Counter.
- State Machine.
- Event Flag.
- Tách ISR và Application.
- Giảm ảnh hưởng của hiện tượng dội phím.

## Kiến trúc

~~~text
Interrupt
   ↓
Debounce State
   ↓
Event Flag
   ↓
Application
~~~