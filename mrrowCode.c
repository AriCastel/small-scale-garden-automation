#include <Adafruit_Sensor.h>

#include <DHT.h>
#include <DHT_U.h>

//Pins
    int pinPump = 13;
    int sensorWater = A0;
    int pinLED = 12;
    int sensorPanel = A1;
    int pinFan = 11;
    int sensorHeat = 10; 


//DH 11 sensor 
#define DHTPIN sensorHeat
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//Times that each function will be executed for
    int timePump = 10000;
    int timeFan = 10000;
    int timeLed = 10000;

//Limits, thresholds that will trigger each action
    int minWater = 700;
    float minLight = 2.0;
    float maxHeat = 20.0;
    float maxWet = 30.0;

//Functions 
    void waterControl(){ //Code for the Water Pump
        Serial.print("reading Water Levels");
        int wetness = analogRead(sensorWater);
        Serial.print(wetness);
  
        if(wetness < minWater){
            Serial.println("Water Pump engaged");
            digitalWrite(pinPump, HIGH); 
            delay(timePump);
            digitalWrite(pinPump, LOW);
        }
    }

    void temperatureControl(){ //Code for the Fan 
        Serial.print("reading Atmospheric Conditions");
        float humidity = dht.readHumidity(); //Reading Humidity
        float temperature = dht.readTemperature(); //Reading temperature
        Serial.print("Humidity ");
        Serial.print(humidity);
        Serial.print("pct");
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.print(" *C ");

        if (temperature > maxHeat || humidity > 60.0){
            Serial.println("Fan Engaged");
            digitalWrite(pinFan, HIGH);
            delay(timeFan);
            digitalWrite(pinFan, LOW);
        }


     }

    void lightControl(){ //Code for the LED array
        Serial.print("Reading Radiation Levels");
        int light = analogRead(sensorPanel);
        Serial.println(light);

        if (light < minLight ){
            Serial.println("LEDs engaged");
            digitalWrite(pinLED, HIGH); 
            delay(timeLed);
            digitalWrite(pinLED, LOW);         
        }


     }

    void testPump(){ //Tests the Pump once on start
        
        digitalWrite(pinPump, HIGH);
        Serial.println("Testing Pump");
        int i=0;        
        for(i=1;i<=3;i++){      
            digitalWrite(LED_BUILTIN, HIGH); 
            delay(1000);                      
            digitalWrite(LED_BUILTIN, LOW);
            delay(1000);

        }     
        
        digitalWrite(pinPump, LOW);
        Serial.println("Pump Test done");
    }

    void testLED(){ //Test the LED array on start
        Serial.println("Testing LEDs");
        digitalWrite(pinLED, HIGH);

        int i=0;        
        for(i=1;i<=2;i++){      
            digitalWrite(LED_BUILTIN, HIGH); 
            delay(5000);                      
            digitalWrite(LED_BUILTIN, LOW);
            delay(1000);

        } 

        digitalWrite(pinLED, LOW);
        Serial.println("LED Test Done");
    }

    void testFan(){ //Tests the Fan on Start
        Serial.println("Testing Fan");
        digitalWrite(pinFan, HIGH);

        int i=0;        
        for(i=1;i<=30;i++){      
            digitalWrite(LED_BUILTIN, HIGH); 
            delay(100);                      
            digitalWrite(LED_BUILTIN, LOW);
            delay(100);

        } 
        digitalWrite(pinFan, LOW);
        Serial.println("Fan Test Done");
    }


// Set up  
void setup() {

    Serial.begin(9600);
    Serial.println("Initializing...");
    
    dht.begin();

    // Pin Modes 
        pinMode(pinPump, OUTPUT);
        pinMode(pinLED, OUTPUT);
        pinMode(pinFan, OUTPUT);
        pinMode(sensorHeat, INPUT);
        pinMode(LED_BUILTIN, OUTPUT);

    testFan();
    testLED();
    testPump();
    Serial.println("Set Up done");       
} 
//Loop
long TSLR=0;; //Time Since Last Reading
void loop() {
    if(millis()- TSLR>2000){ //Performs the actions
        temperatureControl();
        waterControl();
        lightControl();
        Serial.println("Readings done");
}

    TSLR =millis(); //Time Since Last reading Updated 

}