typedef void (*TaskFn)();

struct Task {
  bool enabled = false;
  unsigned long lastExecution;
  unsigned long interval;
  TaskFn taskFunction;
};

Task tasks[] = {
  { true, 0, 500, toggleRed },
  { true, 0, 1000, toggleGreen },
  { true, 0, 2000, toggleBlue }
};

bool redPin = false;
bool greenPin = false;
bool bluePin = false;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {
  for (int i = 0; i < (sizeof(tasks) / sizeof(Task)); i++) {
    if (tasks[i].lastExecution + tasks[i].interval < millis()) {
      tasks[i].taskFunction();
      tasks[i].lastExecution = millis();
    }
  }
  delay(1);
}

void toggleRed() {
  redPin = !redPin;
  digitalWrite(13, redPin);
}

void toggleGreen() {
  greenPin = !greenPin;
  digitalWrite(12, greenPin);
}

void toggleBlue() {
  bluePin = !bluePin;
  digitalWrite(11, bluePin);
}
