const int pump = 3;  //Bomba de agua
const int heater = 2; //Calentador
int tempSensor = A4; //Sensor de temperatura
int IdealTemp = 400; //Temperatura ideal
bool hacerCafe = false;

void setup()
{
  pinMode(pump,  OUTPUT);
  pinMode(heater, OUTPUT);
  digitalWrite(pump, HIGH);
  digitalWrite(heater, HIGH);

  Serial.begin(9600);
}
void loop()
{
  int temp = analogRead(tempSensor);
  char opcion;
  bool eligio = false;
  Serial.println(temp);

  if (!hacerCafe) {
    Serial.println("Ingrese el número de la opción deseada: ");
    Serial.println("1- Hacer café");
    Serial.println("2- Abrir contenedor de capsulas");
    Serial.println("3- Bebida Caliente");
    Serial.println("4- Bebida Fría");

    while (!eligio) { //Mientras no elija una opción
      while (Serial.available() > 0) //Comprobamos si en el buffer hay datos
      {
        opcion = (char)Serial.read(); //Lee cada carácter uno por uno y se almacena en una variable
        Serial.println("Usted eligió la opción: ");
        Serial.println(opcion);  //Imprimimos en la consola la opcion deseada
        eligio = true;
      }
    }

    if (opcion == '1') { 
      Serial.println("Preparando para hacer cafe....");
      hacerCafe = true;
      eligio = false;
    }


  }

  if (hacerCafe) {
    if (temp < IdealTemp) {
      Serial.println("Temperatura baja");
      digitalWrite(heater, LOW);
      temp = analogRead(tempSensor);
    }
    else {
      Serial.println("Temperatura correcta");
      digitalWrite(heater, HIGH);
      digitalWrite(pump, LOW);
      delay(25000);
      digitalWrite(pump, HIGH);
      hacerCafe = false;
    }
  }
}
