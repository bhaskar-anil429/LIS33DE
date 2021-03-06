// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// LIS33DE
// This code is designed to work with the LIS33DE_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Accelorometer?sku=LIS33DE_I2CS#tabs-0-product_tabset-2

#include<Wire.h>

// LIS33DE I2C address is 0x1C(28)
#define Addr 0x1C

void setup()
{
	// Initialise I2C communication as MASTER
	Wire.begin();
	// Initialise Serial Communication, set baud rate = 9600
	Serial.begin(9600);
	
	// Start I2C Transmission
	Wire.beginTransmission(Addr);
	// Select control register 1
	Wire.write(0x20);
	// Enable X, Y, Z-Axis, active mode 
	Wire.write(0x47);
	// Stop I2C Transmission
	Wire.endTransmission();
	delay(300);
}

void loop()
{
	unsigned int data[3];
  for(int i = 0; i < 3; i++)
  { 
    // Start I2C Transmission
    Wire.beginTransmission(Addr);
    // Select data register
    Wire.write(40 + ((2 * i) + 1));
    // Stop I2C Transmission
    Wire.endTransmission();
    
    // Request 1 byte of data
    Wire.requestFrom(Addr,1);
    // Read 3 bytes of data
    // xAccl, yAccl, zAccl
    if(Wire.available()==1)
    {
      data[i] = Wire.read();
    }
    delay(300);
  }

  // Convert the data
  int xAccl = data[0];
  if(xAccl > 127)
  {
    xAccl -= 256;
  }
  int yAccl = data[1];
  if(yAccl > 127)
  {
    yAccl -= 256;
  }
  int zAccl = data[2];
  if(zAccl > 127)
  {
    zAccl -= 256;
  }
  
  // Output data to serial monitor 
  Serial.print("Acceleration in X-Axis :	");
  Serial.print(xAccl); 
  Serial.println(" g");   
  Serial.print("Acceleration in Y-Axis :	");
  Serial.print(yAccl);
  Serial.println(" g"); 
  Serial.print("Acceleration in Z-Axis :	");
  Serial.print(zAccl);
  Serial.println(" g");
  delay(300);
}
