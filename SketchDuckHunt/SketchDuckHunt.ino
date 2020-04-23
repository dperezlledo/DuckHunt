#define D12 12

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 pinMode(LED_BUILTIN, OUTPUT);  
 pinMode(A0, INPUT);
 pinMode(D12, INPUT);
}

int c=0, max, min,  value, pulsador;
int MIN_BLACK, MAX_BLACK;
int MIN_WHITE, MAX_WHITE; 
int input;
int i=0;
void loop() {   
   for (;i<2;i++) {
        esperaDato();
        input = Serial.read(); // Espero señal de calibrar blanco o negro
        input = input -48;
        if (input==1) {   
          digitalWrite (LED_BUILTIN, HIGH);       
          calibrar();
          MIN_BLACK= min;
          MAX_BLACK= max;             
          serialFlush();                             
        } else if (input==2) {        
          digitalWrite (LED_BUILTIN, LOW);
          calibrar();
          MIN_WHITE= min;
          MAX_WHITE= max;                                       
        }
        
   }   
   if (i==2) {  
        if (MAX_BLACK >= MIN_WHITE) { // no se ha calibrado correctamente repetimos proceso
          Serial.println("CER"); // Avisamos a Netbeans de error de calibracion 
          i=0;        
        } else  {
          Serial.println("OK"); // Calibración correcta  
          leerColor();        
        }        
   } 
     
  
}

void leerColor() {
  while (true) {
     pulsador = digitalRead(D12);
     if (pulsador ==HIGH) {     
       value = analogRead(A0);       
       if (value >MIN_WHITE && value <MAX_WHITE) 
         Serial.println("BLANCO");
       if (value >=MIN_BLACK && value <=MAX_BLACK)
         Serial.println("NEGRO");  
       delay(250);  
      }
  }
}

void esperaDato() {
  while (Serial.available()<=0) {
    delay(100);
  }
}

void serialFlush(){
  while(Serial.available() > 0) {
    char t = Serial.read();
  }
}   


void esperar(int t) {
  for (int i=0;i<t;i++) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
}

void calibrar() {
  int sw=1;
  for (int i=0;i<5000;i++) {  
    value = analogRead(A0);
    delay(2);
    if (sw==1) {
      min=9999;
      max=-9999;
      sw =0;
    }
    if (value<min) {
      min =value;
    }
    if (value>max) {
      max =value;
    }    
   }
    
}
