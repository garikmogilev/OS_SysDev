#include <iostream>
#include <synchapi.h>
#include <Windows.h>

int main() {
   for(int i = 0; i < 1000; i++ ){
       std::cout << "PID: " << GetCurrentProcessId() << std::endl;
       Sleep(1000);
   }
    return 0;
}
