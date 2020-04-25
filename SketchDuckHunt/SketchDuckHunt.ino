#define D12 12
#define SWAP(x, y, T) do { T SWAP = x; x = y; y = SWAP; } while (0)

int max, min, pulsador;
int MIN_BLACK, MAX_BLACK;
int MIN_WHITE, MAX_WHITE; 
int input;
int i=0;
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 pinMode(LED_BUILTIN, OUTPUT);  
 pinMode(A0, INPUT);
 pinMode(D12, INPUT);
}

void loop() {   
   for (;i<2;i++) {
        esperaDato();
        input = Serial.read(); // Espero señal de calibrar blanco o negro
        input = input -48;
        if (input==1) {   
          digitalWrite (LED_BUILTIN, HIGH);       
          calibrar();
          digitalWrite (LED_BUILTIN, LOW);
          MIN_BLACK= min;
          MAX_BLACK= max;             
          serialFlush();  
          delay(1000);                           
        } else if (input==2) {        
          digitalWrite (LED_BUILTIN, HIGH);
          calibrar();
          digitalWrite (LED_BUILTIN, LOW);
          MIN_WHITE= min;
          MAX_WHITE= max;                                       
        }
        
   }   
   if (i==2) {  
        if (MAX_BLACK+5 >= MIN_WHITE) { // no se ha calibrado correctamente repetimos proceso
          Serial.println("CER"); // Avisamos a Netbeans de error de calibracion           
          i=0;        
        } else  {
          String aux;
          aux.concat(MIN_BLACK);        
          aux.concat("-");
          aux.concat(MAX_BLACK);
          aux.concat(" ");
          aux.concat(MIN_WHITE);
          aux.concat("-");
          aux.concat(MAX_WHITE);
          Serial.println(aux); // Calibración correcta  
          leerColor();        
        }        
   } 
}

void leerColor() {
  int value=0, erroneos = 0, aciertos=0, fallos=0;
  int avalues[100];
  String s1="";
  while (true) {
     pulsador = digitalRead(D12);
     if (pulsador == HIGH) {
       s1.concat(fallos);
       s1.concat("-");
       s1.concat(aciertos);
       s1.concat("-");
       s1.concat(erroneos);
       Serial.println(s1); 
       s1="";     
       delay(200); // Debemos dar tiempo a Java para cambiar de carta                  
       for (int i=0;i<100;i++) {
          avalues[i] = analogRead(A0);
          delay(2);
       }
       bubblesort (avalues, 100); 
       value = avalues[50];   // Ajustamos entre 0 y 100 al valor más cercano al rango  
       if (value >= MIN_BLACK && value <= MAX_BLACK) {
         fallos++; 
        } else if (value >= MIN_WHITE && value <= MAX_WHITE) {         
         aciertos++;
       } else {      
         erroneos++; 
       }       
       Serial.flush();              
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
  int sw=1, value;
  delay(500);
  for (int i=0;i<2500;i++) {  
    value = analogRead(A0);
    delay(2);
    if (sw==1) {
      min=999;
      max=-1;
      sw=0;
    }
    if (value<min) {
      min =value;
    }
    if (value>max) {
      max =value;
    }    
   }    
}

template<typename T> void bubblesort(T *d, size_t s) {
  bool swapped;
  do {
    swapped = false;
    for (size_t i = 0; i < s-1; i++) {
      if (d[i] > d[i+1]) {
        SWAP(d[i], d[i+1], T);
        swapped = true;
      }
    }
  } while(swapped);
}
