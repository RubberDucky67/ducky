curl -O https://raw.githubusercontent.com/RubberDucky67/ducky/refs/heads/main/main.cpp
cat main.cpp

Invoke-WebRequest -Uri "https://raw.githubusercontent.com/RubberDucky67/ducky/refs/heads/main/main.cpp" -OutFile "main.cpp"
type main.cpp
g++ main.cpp -o main.exe
.\main.exe
