#include <iostream>
#include <unistd.h>

int main() {
    
    while (true) {
        system("touch .nvim-cfg");
        system("git add . && git commit -m \"Update\" -S && git push -u origin main");

        sleep(2);

        system("rm .nvim-cfg");
        system("git add . && git commit -m \"New main\" -S && git push -u origin main");
    
        sleep(2);
    }

    return 0;
}
