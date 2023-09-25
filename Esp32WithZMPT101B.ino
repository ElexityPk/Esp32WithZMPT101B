#include <ZMPT101B.h>
ZMPT101B voltagesensor(34);

unsigned int dcOffsetSamples = 0;

 // Sensitivity = (Esp32 AC inputs peak volts)/(VAC input peak volts)
 // 1.4/232 = 0.0060344827586207

 float Sensitivity = 0.0060344827586207;
 float ADCScale = 1023.0;
 float Vref = 6.0;

void setup(){
  
  Serial.begin(115200);
  Serial.println("Removing DC Offset....");
  delay(100);

  unsigned int accum = 0;

  for(int i=0; i<100; i++){

    accum += analogRead(34);
    delayMicroseconds(1000);
    
    }
  dcOffsetSamples = accum/100;
  float dcOffsetVolts = dcOffsetSamples * Vref/ADCScale;

  voltagesensor.setZeroPoint(dcOffsetSamples);
  voltagesensor.setSensitivity(Sensitivity);

  Serial.println(String("DC offset =") + dcOffsetVolts + "volts.");
  
  } 
  void loop(){
    
    //GRAB ONE CYCLE OF DATA AND CACULATE RMS
    float Vrms = voltagesensor.getVoltageAC(50);

    if(Vrms<60){
      Serial.println("Wapda is Off!");
      delay(5000);
      }else{   
            Serial.println(String("Incoming AC Volts ") + Vrms );
            delay(5000);
            }
            
          //float average = 0;
         // for(int i = 0; i < 1000; i++) 
         // {
          //  average = average + (.0014 * analogRead(35) -3.78) / 1000;
          // delay(1);
         // }
         // Serial.println(String ("Current ") + average);
          //delay(5000);
    }


















    
