// Main include file for the Arduino SDK
#include <Arduino.h>

/*
* https://github.com/dxinteractive/ResponsiveAnalogRead
* In the Arduino IDE, go to Sketch > Include libraries > Manage libraries
* search for ResponsiveAnalogRead
* Click Install
* The library's examples will now appear under File > Examples > ResponsiveAnalogRead
*/
#include "ResponsiveAnalogRead.h"

/*
* https://github.com/MHeironimus/ArduinoJoystickLibrary
* Works with Arduino Leonardo (Pro Micro) & Micro
* Does NOT work with Arduino Uno & Mega
* Download https://github.com/MHeironimus/ArduinoJoystickLibrary/archive/master.zip
* In the Arduino IDE, select Sketch > Include Library > Add .ZIP Library...
* Browse to where the downloaded ZIP file is located and click Open
* The library's examples will now appear under File > Examples > Joystick
* Alternatively,
* extract the library from zip file, rename directory to ArduinoJoystick,
* move it to Library directory that is sibling to Arduino Sketch directory
* specified in ArduinoIDE preferences
*/
#include "Joystick.h"

/*
* Sketch development parameters
*/

// serial conn speed
constexpr long BAUD = 115200;

// false for production, true for dev/debugging
constexpr bool DEBUG = false;

// for debug print statements & production mcu load easing
constexpr int DELAY = 50;

/*
* ResponsiveANalogRead parameters
*/

// sensor activity threshold
constexpr float ACTIVITY_THRESH = 1.0;

// sensor read easing on/off
constexpr bool SLEEP_ENABLE = true;

// sensor read easing amount
constexpr float SNAP_MULTIPLIER = 0.125;

/*
* P3022-V1-CW360 parameters
*/

// sensor output pin used by Arduino board
constexpr int ANALOG_PIN = A10;

// one full rotation of sensor axle is 2^10, as Arduino's can only handle 10 bit ADC
constexpr int JOY_ADC = 1024;

// 2^12 - 1 is analog to digital converter for P3022-V1-CW360 per datasheet
constexpr int SENSOR_ADC = 4096;

/*
* Sketch parameters
*/

/*
The amount of sensor turns available.
increasing revs results in MORE rotation required to effect same amount of change.
decreasing revs results in LESS rotation required to effect same amount of change.
*/
constexpr int FULL_REVS = 8;

/*
The threshold value is used to limit the rate of rotation change.
larger divisor means smaller delta rotation allowable.
smaller divisor means larger delta rotation allowable.
*/
constexpr int FULL_ROTATION_DIFF_THRESHOLD = JOY_ADC / 4;

// the full range of trim wheel response
constexpr int MAX_RANGE = FULL_REVS * JOY_ADC;

// the min range of trim wheel response
constexpr int MIN_RANGE = 0;

// very basic instantiate joystick library
// HID report id, HID input device type
// no buttons or hats
// no x, y, z axes
// no rx axis, use ry axis, no rz axis
// no rudder, throttle
// no accelerator, brake, steering
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD,
                   0, 0,
                   false, false, false,
                   false, true, false,
                   false, false,
                   false, false, false);

// the initial joystick & sensor values
int prevJoystick;
int prevSensor;

// instantiate sensor read library with overloaded method so we don't have to 2 stage initialize
ResponsiveAnalogRead sensorReader(ANALOG_PIN, false);


/**
* @brief Gets current sensor reading.
* @return {int} currentSensor The current sensor value.
*/
int currentSensor() {
  // the value from sensor
  int currentSensor;

  // updates the value by performing an analogRead() and calculating a responsive value based off it
  sensorReader.update();
  currentSensor = sensorReader.getValue();

  return currentSensor;
}


/**
* @brief Gets the sensor delta constrained to the defined threshold of rotation.
* @details Acts as a rotation rate limiter.
* @param {int} oldSensor Previous sensor value.
* @param {int} newSensor New sensor value.
* @return {int} sensorDiff Constrained sensor value.
*/
int sensorDelta(int oldSensor, int newSensor) {
  // the constrained sensor difference
  int sensorDiff;

  // initial value presuming user stayed within delta rotation threshold
  sensorDiff = newSensor - oldSensor;

  // enough clockwise (positive) input from user, ignore new sensor input
  if(sensorDiff > FULL_ROTATION_DIFF_THRESHOLD) {
    sensorDiff = sensorDiff - newSensor;
  }

  // enough counter-clockwise (negative) input from user, restore old sensor value
  if(sensorDiff < -FULL_ROTATION_DIFF_THRESHOLD) {
    sensorDiff = oldSensor + sensorDiff;
  }

  // IFF we fall through both blocks, we return the initial value
  return sensorDiff;
}


/**
* @brief Enforce the user's input to specified min/max joystick range constants.
* @param {long} joystickInput Movement input by user.
* @return {long} enforcedJoystick Enforced joystick value.
*/
int enforceJoystickRange(int joystickInput) {
  /*
  constrain accepts int, long, float and double, and returns a value of the same type as its input argument
  however, you could get implicit type conversions, so best practice to pass all variables as same type
  */

  int enforcedJoystick;

  enforcedJoystick = constrain(joystickInput, MIN_RANGE, MAX_RANGE);

  return enforcedJoystick;
}


void setup() {
  // enables print output for dev/debugging purposes
  if (DEBUG) {
    Serial.begin(BAUD);
  }

  // P3022-V1-CW360 is 12 bit (4096) ADC, not 10 bit like arduino pro micro (leonardo) & micro
  sensorReader.setAnalogResolution(SENSOR_ADC);

  if(SLEEP_ENABLE) {
    // enabling sleep will cause values to take less time to stop changing and potentially stop changing more abruptly
    sensorReader.enableSleep();

    // edge snap ensures that values at the edges of the spectrum (0 and 1023) can be easily reached when sleep is enabled
    sensorReader.enableEdgeSnap();

    // snapMultiplier - a value from 0 to 1 that controls the amount of easing
    // increase this to lessen the amount of easing (such as 0.1) and make the responsive values more responsive
    // but doing so may cause more noise to seep through if sleep is not enabled
    sensorReader.setSnapMultiplier(SNAP_MULTIPLIER);

    // the amount of movement that must take place to register as activity and start moving the output value
    sensorReader.setActivityThreshold(ACTIVITY_THRESH);
  } else {
    // reset everything to defaults
    sensorReader.disableEdgeSnap();
    sensorReader.disableSleep();
    sensorReader.setSnapMultiplier(0.01);
    sensorReader.setActivityThreshold(4.0);
  }

  // set initial sensor and joystick values
  prevSensor = currentSensor();
  prevJoystick = map(prevSensor, MIN_RANGE, JOY_ADC, MIN_RANGE, MAX_RANGE);

  Joystick.begin();
  Joystick.setRyAxisRange(MIN_RANGE, MAX_RANGE);

  // ArduinoJoystickLibrary is expecting int32_t (long) type
  Joystick.setRyAxis(static_cast<long>(prevJoystick));
}


void loop() {
  // movement after rotation threshold constraining
  int joystickMove;

  // joystick value after abs min/max constraining
  int newJoystick;

  // new value after user has moved sensor
  int newSensor;

  // axis value sent to computer
  long axisValue;

  // sensor value constrained for threshold delta value
  int sensorThresh;

  // sensor constrained rotation delta value give us our sensitivity to change
  newSensor = currentSensor();
  sensorThresh = sensorDelta(prevSensor, newSensor);

  // accumulate our joystick value and keep it within operating range
  joystickMove = prevJoystick + sensorThresh;
  newJoystick = enforceJoystickRange(joystickMove);

  // ArduinoJoystickLibrary is expecting int32_t (long) type
  axisValue = static_cast<long>(newJoystick);
  Joystick.setRyAxis(axisValue);

  if (DEBUG) {
    long rotationValue;
    long maxJoystick = 65536;

    // map the rx axis value, 0 to (max turns * full turn), 0 to 2^16
    rotationValue = map(axisValue, MIN_RANGE, MAX_RANGE, MIN_RANGE, maxJoystick);

    if (rotationValue < MIN_RANGE) {
      rotationValue = MIN_RANGE;
    } else if (rotationValue > maxJoystick) {
      rotationValue = maxJoystick;
    }

    // Serial.print has limitations that sprintf doesn't, but sprintf needs different setup
    char printBuffer[150];
    sprintf(
      printBuffer,
      "Prev sensor: %d | New sensor: %d | Sensor diff: %d | Prev joy: %d | Joy move: %d | New joystick %d | RX axis value: %ld | RX value: %ld",
      prevSensor, newSensor, sensorThresh, prevJoystick, joystickMove, newJoystick, axisValue, rotationValue
    );
    Serial.println(printBuffer);
    delay(DELAY);
  }

  prevJoystick = newJoystick;
  prevSensor = newSensor;

  // always need a little delay so mcu doesn't get overwhelmed (the good old Apollo 11 1204 error!)
  if(!DEBUG) {
    delay(DELAY);
  }
}
