// Dakota Rowehl - Watering System for Liz - 1/19/2021

// General Declarations -----------------------------------------------------------------
int numReadings = 25;


// First Plant Declarations -------------------------------------------------------------
int SkipButtonPin1 = 2;
int SensorRelayPin1 = 6;
int PumpRelayPin1 = 8;
int analogInputPin1 = A0;

int WaitCycles1 = 0;
int WaterToken1 = 0;
int Moisture1 = 0;

// Second Plant Declarations -------------------------------------------------------------
int SkipButtonPin2 = 3;
int SensorRelayPin2 = 11;
int PumpRelayPin2 = 12;
int analogInputPin2 = A1;

int WaitCycles2 = 0;
int WaterToken2 = 0;
int Moisture2 = 0;



// Third Plant Declarations --------------------------------------------------------------
int SkipButtonPin3 = 4;



void setup() {
  
  // Pin Declarations
  pinMode(SkipButtonPin1, INPUT);
  pinMode(SkipButtonPin2, INPUT);
  pinMode(SkipButtonPin3, INPUT);
  
  pinMode(PumpRelayPin1, OUTPUT);
  pinMode(SensorRelayPin1, OUTPUT);
  pinMode(PumpRelayPin2, OUTPUT);
  pinMode(SensorRelayPin2, OUTPUT);
  
  
  
  // Begin Monitoring
  Serial.begin(9600);
  
}





void loop() {  
  
   // Plant 1: ---------------------------------------------------------------------------
   
      // Updating
      if (WaitCycles1 > 0){
        WaitCycles1 = WaitCycles1 - 1;
      }
      
      // Sampling
      Serial.println("Sampling Moisture 1: ");
      Moisture1 = PlantSensor(analogInputPin1, SensorRelayPin1);
      delay(500);
      Serial.print("Moisture 1 Average is: ");
      Serial.println( Moisture1);

      
      // Updating, check at ... below water moisture
      if ((Moisture1 >= 550) && (WaterToken1 == 0)) {
        WaitCycles1 = 6;
        WaterToken1 = 1;
      }
      
      // Watering
      if ((WaitCycles1 == 0) && (WaterToken1 == 1)){
        PlantWaterPump(PumpRelayPin1,2);
          /*digitalWrite(PumpRelayPin1, HIGH);
          delay(5000);
          digitalWrite(PumpRelayPin1, LOW);
          delay(1000);*/
        
        WaterToken1 = 0;
      }

  // Plant 2: ---------------------------------------------------------------------------
    
      // Updating
      if (WaitCycles2 > 0){
        WaitCycles2 = WaitCycles2 - 1;
      }
      
      // Sampling
      Serial.println("Sampling Moisture 2: ");
      Moisture2 = PlantSensor(analogInputPin2, SensorRelayPin2);
      delay(500);
      Serial.print("Moisture 2 Average is: ");
      Serial.println( Moisture2);

      
      // Updating, check at ... below water moisture
      if ((Moisture2 >= 270) && (WaterToken2 == 0)) {
        WaitCycles2 = 6;
        WaterToken2 = 1;
      }
      
      // Watering
      if ((WaitCycles2 == 0) && (WaterToken2 == 1)){
        PlantWaterPump(PumpRelayPin2,2);
          /*digitalWrite(PumpRelayPin2, HIGH);
          delay(5000);
          digitalWrite(PumpRelayPin2, LOW);
          delay(1000);*/
        
        WaterToken2 = 0;
      }


  // Plant 3: --------------------------------------------------------------------------- 




  
  // Four Hour Timer --------------------------------------------------------------------

   Serial.print(WaitCycles1);
   Serial.println(WaitCycles2);

   Serial.print(WaterToken1);
   Serial.println(WaterToken2);

      /*for (int Hours = 0; Hours < 1; Hours++) {                 
         for (int Minutes = 0; Minutes < 1; Minutes++) {        
             for (int Seconds = 0; Seconds < 10; Seconds++) {   
                delay(1000);
                Serial.print(digitalRead(SkipButtonPin1));                                
                Serial.print(digitalRead(SkipButtonPin2));
                Serial.println(digitalRead(SkipButtonPin3));

                  //Plant 1 Water
                  if (digitalRead(SkipButtonPin1) == HIGH){
                   PlantWaterPump(PumpRelayPin1, 1);
                   
                   WaterToken1 = 0;
                   WaitCycles1 = 0;
                   
                  }
                  //Plant 2 Water
                  if (digitalRead(SkipButtonPin2) == HIGH){
                   PlantWaterPump(PumpRelayPin2, 2);
                   
                   WaterToken2 = 0;
                   WaitCycles2 = 0;
                  }
                  //Plant 3 Water
                  if (digitalRead(SkipButtonPin3) == HIGH){
                   //PlantWaterPump(PumpRelayPin3, 3);
                   //WaterToken3 = 0;
                  }

      }}}*/

      
      for (int Hours = 0; Hours < 4; Hours++) {                 //Skips 4 hours
         for (int Minutes = 0; Minutes < 60; Minutes++) {       //Skips 1 hour
             for (int Seconds = 0; Seconds < 60; Seconds++) {   //Skips 1 minute              
                delay(1000);                                    //Skips 1 second
                Serial.print(digitalRead(SkipButtonPin1));                                
                Serial.print(digitalRead(SkipButtonPin2));
                Serial.println(digitalRead(SkipButtonPin3));
                
                 //Plant 1 Water
                  if (digitalRead(SkipButtonPin1) == HIGH){
                   PlantWaterPump(PumpRelayPin1,1);
                   WaterToken1 = 0;
                   WaitCycles1 = 0;
                  }
                  //Plant 2 Water
                  if (digitalRead(SkipButtonPin2) == HIGH){
                   PlantWaterPump(PumpRelayPin2,2);
                   WaterToken2 = 0;
                   WaitCycles2 = 0;
                  }
                  //Plant 3 Water
                  if (digitalRead(SkipButtonPin3) == HIGH){
                   //PlantWaterPump(PumpRelayPin3);
                   //WaterToken3 = 0;
                  }
                            
      }}}
    
}





// Plant Moisture Sensor Function ---------------------------------------------------------
int PlantSensor(int X, int Y){      

      int InputPin = X;
      int SensorPWR = Y;
      int Moisture = 0;
      int AVGMoisture = 0; 

      digitalWrite(SensorPWR, HIGH);
      delay(500);
      for (int i = 0; i < numReadings; i++){
        Moisture = Moisture + analogRead(InputPin);
        Serial.println(analogRead(InputPin));
        delay(100);
      }
      digitalWrite(SensorPWR, LOW);
      delay(100);
      
      AVGMoisture = Moisture / numReadings;
      Moisture = 0;  
      
  return AVGMoisture;
}

// Plant Water Pump Function --------------------------------------------------------------
void PlantWaterPump(int Z, int A){

      int PumpPWR = Z;
  
      digitalWrite(PumpPWR, HIGH);
      if (A == 1){
        delay(2000);
      }
      if (A == 2){
        delay(2000);
      }
      digitalWrite(PumpPWR, LOW);
      delay(1000);
}
