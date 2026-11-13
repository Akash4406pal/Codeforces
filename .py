python -c"
import socket

s = socket.socket()
s.connect(('localhost', 9999))
print('Connected to MiniRedis! Type commands (e.g. PING, SET foo bar, GET foo) or quit')

while True:
    try:
        cmd = input('redis> ')
        if not cmd.strip():
            continue
        if cmd.strip().lower() == 'quit':
            break
        s.sendall((cmd + '\n').encode())
        res = s.recv(1024).decode()
        print(res, end='')
    except (KeyboardInterrupt, EOFError):
        break

s.close()
"
