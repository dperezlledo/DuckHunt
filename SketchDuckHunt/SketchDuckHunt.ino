#define D12 12

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 pinMode(LED_BUILTIN, OUTPUT);  
 pinMode(A0, INPUT);
 pinMode(D12, INPUT);
}

int c=0, max, min, sw=1, value, calibracion=1, pulsador;
int MIN_BLACK, MAX_BLACK;
int MIN_WHITE, MAX_WHITE; 

void loop() {
  while (calibracion==1) {
    Serial.println("CALIBRANDO COLORES NEGRO Y BLANCO");
    Serial.print("Posicionese en color NEGRO (10 seg de espera) ");
    esperar(10);
    calibrar();
    MIN_BLACK= min;
    MAX_BLACK=max;
    sw=1;
    Serial.print("Posicionese en color BLANCO (10 seg de espera)");
    esperar(10);
    calibrar();
    MIN_WHITE= min;
    MAX_WHITE=max;
    
    if (MAX_BLACK >= MIN_WHITE) { // no se ha calibrado correctamente repetimos proceso
      Serial.println("No se ha calibrado correctamente, se repetirá el proceso");
      calibracion=1;
    } else  {
      Serial.print("Negro => (");
      Serial.print (MIN_BLACK);
      Serial.print (",");
      Serial.print (MAX_BLACK );
      Serial.print (")\n");
      Serial.print("Blanco => (");
      Serial.print (MIN_WHITE);
      Serial.print (",");
      Serial.print (MAX_WHITE);
      Serial.print (")\n"); 
      delay(5000);
      calibracion=0;
    }        
   }   
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

void esperar(int t) {
  for (int i=0;i<t;i++) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
}

void calibrar() {
  Serial.println("Realice circulos sobre el color adecuado y espere mientras tomamos datos");
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
