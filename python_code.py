import socket
import pyautogui

HOST = "0.0.0.0"
PORT = 5000

pyautogui.FAILSAFE = False
print("🖱️ Air Mouse Server started... waiting for ESP8266 connection")

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen(1)
    conn, addr = s.accept()
    print(f"✅ Connected by {addr}")

    left_down = False
    right_down = False

    while True:
        try:
            data = conn.recv(1024).decode(errors='ignore').strip()
            if not data:
                continue

            # split lines if multiple packets arrive together
            lines = data.splitlines()

            for line in lines:
                line = line.strip()
                if not line:
                    continue
                parts = line.split(",")
                if len(parts) != 4:
                    # skip malformed data
                    continue

                dx, dy, left, right = parts
                dx, dy = int(float(dx)), int(float(dy))
                left, right = bool(int(left)), bool(int(right))

                if dx != 0 or dy != 0:
                    pyautogui.moveRel(dx, dy)

                if left and not left_down:
                    pyautogui.mouseDown(button='left')
                    left_down = True
                elif not left and left_down:
                    pyautogui.mouseUp(button='left')
                    left_down = False

                if right and not right_down:
                    pyautogui.mouseDown(button='right')
                    right_down = True
                elif not right and right_down:
                    pyautogui.mouseUp(button='right')
                    right_down = False

        except Exception as e:
            print("Parse error:", e)
