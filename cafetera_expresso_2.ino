const int pump = 3;  //Bomba de agua
const int heater = 2; //Calentador
int tempSensor = A4; //Sensor de temperatura
int IdealTemp = 400; //Temperatura ideal
bool hacerCafe = false;

const int selectorFrio = 12;
int valorFrio = 0;
const int selectorAbrir = 11;
int valorAbrir = 0;
const int selectorCaliente = 10;
int valorCaliente = 0;

int powerSwitchBtn = 9; //need a counter to see which step? or we have a held/press time (if long press turn off ex)
int powerSwitchRed = 8; //PWM
int powerSwitchGreen = 7; //PWM

const int motor1 = 5;
const int motor2 = 6;

void setup()
{
  pinMode(pump,  OUTPUT);
  pinMode(heater, OUTPUT);
  digitalWrite(pump, HIGH);
  digitalWrite(heater, HIGH);
  pinMode(12, INPUT);
  pinMode(11, INPUT);
  pinMode(10, INPUT);
  pinMode(powerSwitchBtn, INPUT);
  pinMode(powerSwitchGreen, OUTPUT);
  pinMode(powerSwitchRed, OUTPUT);

  Serial.begin(9600);
}
void loop()
{
  int temp = analogRead(tempSensor);
  char opcion;
  bool eligio = false;

  Serial.println("––– Dolce Gusto  –––");

  if (!hacerCafe) {

    digitalWrite(powerSwitchRed, HIGH);

    valorFrio = digitalRead(selectorFrio);  //lectura digital de pin
    valorAbrir = digitalRead(selectorAbrir);  //lectura digital de pin
    valorCaliente = digitalRead(selectorCaliente);  //lectura digital de pin

    if (valorFrio == HIGH) {
      Serial.println("--Bebida Fria Seleccionada--");
    }

    if (valorAbrir == HIGH) {
      Serial.println("--Inserte o retire capsula--");
    }

    if (valorCaliente == HIGH) {
      Serial.println("--Bebida Caliente Seleccionada--");
    }

    Serial.println("Ingrese el número de la opción deseada: ");
    Serial.println("1- Hacer café.");
    Serial.println("2- Insertar o retirar capsula.");
    Serial.println("3- Bebida Caliente.");
    Serial.println("4- Bebida Fría.");

    while (!eligio) { //Mientras no elija una opción
      while (Serial.available() > 0) //Comprobamos si en el buffer hay datos
      {
        opcion = (char)Serial.read(); //Lee cada carácter uno por uno y se almacena en una variable
        Serial.print("Usted eligió la opción: ");
        Serial.println(opcion);  //Imprimimos en la consola la opcion deseada
        eligio = true;
      }
    }

    if (opcion == '1') {
      Serial.println("Preparando para hacer cafe....");
      if (valorCaliente == HIGH || valorFrio == HIGH) {
        hacerCafe = true;
      }
      else {
        Serial.println("Antes de HACER CAFE seleccione que tipo de bebida quiere preparar (FRIA o CALIENTE)");
      }
      eligio = false;
    }

    if (opcion == '2') {
      // Mover el selector hasta abrir contenedor
      if (valorCaliente == HIGH) {
        while (valorAbrir != HIGH) {
          valorAbrir = digitalRead(selectorAbrir);  //lectura digital de pin
          digitalWrite(motor1, LOW);
          digitalWrite(motor2, HIGH);
        }
        digitalWrite(motor1, LOW);
        digitalWrite(motor2, LOW);
      }
      else {
        while (valorAbrir != HIGH) {
          valorAbrir = digitalRead(selectorAbrir);  //lectura digital de pin
          digitalWrite(motor1, HIGH);
          digitalWrite(motor2, LOW);
        }
        digitalWrite(motor1, LOW);
        digitalWrite(motor2, LOW);
      }
      Serial.println("Puede abrir el contenedor de capsulas....");
      Serial.println("Retire la capsula usada y coloque una nueva.");
      eligio = false;
    }

    if (opcion == '3') {
      // Mover el selector hasta bebida caliente
      while (valorCaliente != HIGH) {
        valorCaliente = digitalRead(selectorCaliente);  //lectura digital de pin
        digitalWrite(motor1, HIGH);
        digitalWrite(motor2, LOW);
      }
      Serial.println("Preparado para hacer bebida caliente....");
      eligio = false;
    }

    if (opcion == '4') {
      // Mover el selector hasta bebida fria
      while (valorFrio != HIGH) {
        valorFrio = digitalRead(selectorFrio);  //lectura digital de pin
        digitalWrite(motor1, LOW);
        digitalWrite(motor2, HIGH);
      }
      Serial.println("Preparado para hacer bebida fria....");
      eligio = false;
    }


  }

  if (hacerCafe) {
    if (temp < IdealTemp) {
      Serial.print("Temperatura baja: ");
      Serial.println(temp);
      digitalWrite(heater, LOW);
      temp = analogRead(tempSensor);
      digitalWrite(powerSwitchRed, !digitalRead(powerSwitchRed));
      delay(500);
    }
    else {
      Serial.println("Temperatura correcta! :)");
      Serial.println("Haciendo Cafe...");
      digitalWrite(powerSwitchRed, LOW);
      digitalWrite(powerSwitchGreen, HIGH);
      digitalWrite(heater, HIGH);
      digitalWrite(pump, LOW);
      delay(25000);
      digitalWrite(pump, HIGH);
      digitalWrite(powerSwitchGreen, LOW);
      hacerCafe = false;
      // Poner el selector en retirar capsula
    }
  }
}
