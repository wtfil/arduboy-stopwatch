#include <Arduboy2.h>

Arduboy2 arduboy;
unsigned long s1 = millis();
unsigned long s2 = millis();

String pad2(int n) {
    return n < 10 ? ("0" + String(n)) : String(n);
}

String formatTime(unsigned long t) {
    int ms = t % 1000;
    t /= 1000;
    int sec = t % 60;
    t /= 60;
    int min = t % 60;
    t /= 60;

    return String(t) + ":" + pad2(min) + ":" + pad2(sec);//+ "." + String(ms);
}

void setup() {
    arduboy.begin();
    arduboy.setFrameRate(30);
    arduboy.setTextSize(3);
}


void loop() {
    if (!(arduboy.nextFrame()))
        return;

    if (arduboy.pressed(B_BUTTON)) {
        s2 = millis();
    }
    if (arduboy.pressed(A_BUTTON)) {
        s1 = millis();
    }
    arduboy.clear();
    arduboy.setCursor(0, 0);
    arduboy.print(formatTime(millis() - s1));
    arduboy.setCursor(0, 30);
    arduboy.print(formatTime(millis() - s2));
    arduboy.display();
}
