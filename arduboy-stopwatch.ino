#include <Arduboy2.h>
#define TOTAL 2

String pad2(int n) {
    return n < 10 ? ("0" + String(n)) : String(n);
}

class Timer {
    private:
        unsigned long startTime = 0;
        unsigned long pausedTime = 0;
    public:
        bool isPaused = true;
        void start() {
            startTime = millis();
        }
        void reset() {
            pausedTime = 0;
            start();
        }
        void toggle() {
            if (isPaused) {
                start();
                isPaused = false;
            } else {
                pausedTime = getTime();
                isPaused = true;
            }
        }
        unsigned long getTime() {
            return isPaused ?
                pausedTime :
                (millis() - startTime + pausedTime);
        }
        String format() {
            unsigned long t = getTime();
            int ms = t % 1000;
            t /= 1000;
            int sec = t % 60;
            t /= 60;
            int min = t % 60;
            t /= 60;
            return String(t) + ":" + pad2(min) + ":" + pad2(sec);
        }
};

Arduboy2 arduboy;
int index = 0;
Timer timers[TOTAL];
Timer timer;

void setup() {
    arduboy.begin();
    arduboy.setFrameRate(30);

    for (int i = 0; i < TOTAL; i ++) {
        timers[i] = Timer();
    }
    timer = timers[index];
}

void loop() {
    if (!(arduboy.nextFrame()))
        return;

    arduboy.pollButtons();
    if (arduboy.justPressed(DOWN_BUTTON) && index < TOTAL - 1) {
        timer = timers[++ index];
    } else if (arduboy.justPressed(UP_BUTTON) && index > 0) {
        timer = timers[-- index];
    } else if (arduboy.justPressed(A_BUTTON)) {
        timer.toggle();
    } else if (arduboy.justPressed(B_BUTTON)) {
        timer.reset();
    }
    arduboy.clear();

    arduboy.setTextSize(1);
    arduboy.setCursor(0, 0);
    String status = String(index + 1) + "/" + String(TOTAL);
    status += timer.isPaused ?
        " A to start" :
        " A to pause";
    arduboy.print(status);

    arduboy.setCursor(0, 10);
    arduboy.print("    B to reset");

    arduboy.setTextSize(3);
    arduboy.setCursor(0, 30);
    arduboy.print(timer.format());

    arduboy.display();
}
