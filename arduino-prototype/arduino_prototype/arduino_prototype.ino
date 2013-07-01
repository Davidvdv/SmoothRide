// I2C device class (I2Cdev) demonstration Arduino sketch for MPU6050 class
// 10/7/2011 by Jeff Rowberg <jeff@rowberg.net>
// Updates should (hopefully) always be available at https://github.com/jrowberg/i2cdevlib
//
// Changelog:
//     2011-10-07 - initial release

/* ============================================
I2Cdev device library code is placed under the MIT license
Copyright (c) 2011 Jeff Rowberg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
===============================================
*/

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#include "Wire.h"

// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU6050.h"

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;
int16_t px, py, pz;
int16_t ax, ay, az;
int16_t gx, gy, gz;

int offset = 2000;
int detected = 0;

void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    Wire.begin();

    // initialize serial communication
    // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
    // it's really up to you depending on your project)
    Serial.begin(38400);

    // initialize device
//    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();

    // verify connection
//    Serial.println("Testing device connections...");
//    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
    
}

void loop() {
    // read raw accel/gyro measurements from device
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    // these methods (and a few others) are also available
    //accelgyro.getAcceleration(&ax, &ay, &az);
    //accelgyro.getRotation(&gx, &gy, &gz);

    // display tab-separated accel/gyro x/y/z values
//    Serial.print("a/g:\t");
//    Serial.print(ax); Serial.print("\t");
//    Serial.print(ay); Serial.print("\t");
////    Serial.print(az); Serial.print("\t");
//    Serial.println(az);

//    Serial.print(gx); Serial.print("\t");
//    Serial.print(gy); Serial.print("\t");
//    Serial.println(gz);
    
    int16_t delta_x, delta_y, delta_z = 0;
    delta_x = abs(gx - px);
    delta_y = abs(gy - py);
    delta_z = abs(gz - pz);
    
    if(delta_x > offset && delta_y > offset && delta_z > offset){
//      Serial.print(delta_x);
//      Serial.print(" - ");
//      Serial.print(delta_y);
//      Serial.print(" - ");
//      Serial.print(delta_z);
//      Serial.print("\r\n");
      
//      detected++;
//      Serial.println(detected);
      Serial.print("{\"delta_x\": "+String(delta_x)+", \"delta_y\":"+String(delta_y)+",\"delta_z\": "+String(delta_z)+"}");
      Serial.flush();
    }
    
    px = gx;
    py = gy;
    pz = gz;

    delay(100);

}

