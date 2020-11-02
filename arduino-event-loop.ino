// This just gives a name to the type so we can call it 'TaskFn' in the future
//  instead of repeating the full type
typedef void (*TaskFn)();

// All data we need to evaluate a task
struct Task {
  bool enabled = false;               // Whether the task is enabled or not
  unsigned long lastExecution;        // Last moment of execution (timestamp in ms since Arduino boot)
  unsigned long interval;             // Interval between tasks in ms
  TaskFn taskFunction;                // Function to execute
};

// Prepare a list of tasks to execute in parallel
Task tasks[] = {
  { true, 0, 500, toggleRed },
  { true, 0, 1000, toggleGreen },
  { true, 0, 2000, toggleBlue }
};

// State of the LEDs, in this case we're blinking 3 LEDs on separate intervals
bool redPin = false;
bool greenPin = false;
bool bluePin = false;

// Regular setup, 
//  make sure the LED pins are set to OUTPUT mode
void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
}

// This loops through the tasks, and evaluates whether they should be executed or not
void loop() {
  for (int i = 0; i < (sizeof(tasks) / sizeof(Task)); i++) {
    if (tasks[i].enabled && tasks[i].lastExecution + tasks[i].interval < millis()) {
      // Execute the task
      tasks[i].taskFunction();

      // Reset the last executed timestamp
      tasks[i].lastExecution = millis();
    }
  }

  // This delay is optional on physical devices, but is nice in simulators so they don't go crazy
  // Without this line the Arduino will spin at 100% CPU usage so to speak, which is fine for a
  //  real physical device, but in a simulator this might hang your pc.
  delay(1);
}

// The tree functions below just flip the current state of the LED (on to off, off to on)
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
