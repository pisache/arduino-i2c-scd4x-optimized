#include <Wire.h>
#include <SensirionI2cScd4x.h>

SensirionI2cScd4x scd4x;

char errorMessage[42];
bool gasConn = false;

void setup()
{
  Wire.begin();
  Serial.begin(115200);
  delay(1000);
  
  scd4x.begin(Wire, SCD40_I2C_ADDR_62);
  uint16_t error = scd4x.stopPeriodicMeasurement();
  if (error)
  {
    Serial.print("Stop measure error: ");
    errorToString(error, errorMessage, sizeof(errorMessage));
    Serial.println(errorMessage);
  }

  error = scd4x.startPeriodicMeasurement();
  if (error)
  {
    Serial.print("Start maesure error: ");
    errorToString(error, errorMessage, sizeof(errorMessage));
    Serial.println(errorMessage);
  }
  
  delay(5000);
}

void loop()
{
  delay(3000);
  bool dataReady = false;
  uint16_t error = scd4x.getDataReadyStatus(dataReady);
  if (error) 
  {
    errorToString(error, errorMessage, sizeof(errorMessage));
    Serial.print("Data ready check failed: ");
    Serial.println(errorMessage);
    delay(1000);
    return;
  }

  if (dataReady) 
  {
    uint16_t co2;
    float temp, humidity;
    error = scd4x.readMeasurement(co2, temp, humidity);
    Serial.println("Reading MEASUREMENTS");
    if (error) 
    {
      errorToString(error, errorMessage, sizeof(errorMessage));
      Serial.print("Read error: ");
      Serial.println(errorMessage);
    }
    else
    {
      Serial.print("Ch 0 ");
      Serial.print(": CO2="); Serial.print(co2); Serial.print(" ");
      Serial.print("Temp="); Serial.print(temp); Serial.print(" ");
      Serial.print("Humidity="); Serial.print(humidity); Serial.println("%");
    }
  }

  delay(3000);
}