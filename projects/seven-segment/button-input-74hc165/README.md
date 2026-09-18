# Seven-Segment + 74HC165 Button Input

Kết hợp 74HC595 để điều khiển LED 7 đoạn và 74HC165 để đọc nhiều nút nhấn.

## Nội dung

- Parallel-in / Serial-out với 74HC165.
- Shift Register.
- Đọc nhiều nút nhấn.
- Multiplexing LED 7 đoạn.
- Timer.
- State Machine.
- Button Driver tách khỏi Application.

~~~text
74HC165 → Button Driver → State Machine
74HC595 → LED Driver    → Display
~~~