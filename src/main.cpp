//Hector Manuel de Leon Salguero
//Universidad del Valle de Guatmala
//
//
//
//*****************************************************************************
//Librerias
//*****************************************************************************
#include <Arduino.h>

//*****************************************************************************
//Definicion de pines
//*****************************************************************************

#define Led1ContT  23
#define Led2ContT  22
#define Led3ContT  3
#define Led4ContT  21

#define Led1  19 //Leds del contador con botones
#define Led2  18
#define Led3  5
#define Led4  17

#define Boton1  32 //este boton suma
#define Boton2  33 // este boton resta

#define alarm  16 //alarma

#define prescaler 80

//*****************************************************************************
//Prototipos de funciones
//*****************************************************************************
void configurarTimer(void);
void setLedsTimer(int valor);
void contadorBinario(void);
void alarma(void);
void ledsBotones (int valor2);

//*****************************************************************************
//Variables Globales
//*****************************************************************************
//Paso1. instanciar el timer
hw_timer_t *timer = NULL;

int contBoton = 0;
int contadorTimer = 0;
//*****************************************************************************
//ISR
//*****************************************************************************
void IRAM_ATTR ISRTimer0()
{
  contadorTimer++; // es como sumarle 1
  if (contadorTimer > 15)
  {
    contadorTimer = 0;
  }
}

//*****************************************************************************
//Configuracion
//*****************************************************************************

void setup()
{
  pinMode(Led1ContT, OUTPUT);
  pinMode(Led2ContT, OUTPUT);
  pinMode(Led3ContT, OUTPUT);
  pinMode(Led4ContT, OUTPUT);

  pinMode(alarm, OUTPUT); //setup de el led indicador 
  digitalWrite(alarm, 0);
  
  configurarTimer();

  digitalWrite(Led1ContT, 0);
  digitalWrite(Led2ContT, 0);
  digitalWrite(Led3ContT, 0);
  digitalWrite(Led4ContT, 0);

  //Boton sumador
  pinMode(Boton1, INPUT_PULLUP);
  //Boton restador
  pinMode(Boton2, INPUT_PULLUP);

  //leds del boton
  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
  pinMode(Led3, OUTPUT);
  pinMode(Led4, OUTPUT);

  digitalWrite(Led1, 0);
  digitalWrite(Led2, 0);
  digitalWrite(Led3, 0);
  digitalWrite(Led4, 0);
  
}

//*****************************************************************************
//Loop principal
//*****************************************************************************
void loop()
{
  setLedsTimer(contadorTimer);
  contadorBinario();
  ledsBotones(contBoton);
  alarma();
}

//*****************************************************************************
//Funcion para timer
//*****************************************************************************
void configurarTimer(void)
{

  //Fosc(Frecuencia de oscilacion) = 80 MHz = 80,000,000 Hz
  // Fosc / prescaler = 80,000,000 / 80 = 1,000,000 Hz
  //Tosc(Tiempo de oscilacion) = 1 / Fosc = 1 uSeg

  //Paso2. Seleccionar timer
  // Timer 0, prescaler = 80, flanco de subida
  timer = timerBegin(0, prescaler, true);

  //paso3. Asignar el handler de la interrupcion

  timerAttachInterrupt(timer, &ISRTimer0, true);

  //paso4. Programar alarma
  // Tic = 1 uSeg
  // Frcuencia = se necesita 250 ms = 250,000 Tics
  timerAlarmWrite(timer, 250000, true);

  //paso5. Iniciar la alarma
  timerAlarmEnable(timer);
}

//*****************************************************************************
//Funcion para contador de timer
//*****************************************************************************
void setLedsTimer(int valor)
{
  if (valor == 1)
  {
    digitalWrite(Led1ContT, 1);
    digitalWrite(Led2ContT, 0);
    digitalWrite(Led3ContT, 0);
    digitalWrite(Led4ContT, 0);
  }

  if (valor == 2)
  {
    digitalWrite(Led1ContT, 0);
    digitalWrite(Led2ContT, 1);
    digitalWrite(Led3ContT, 0);
    digitalWrite(Led4ContT, 0);
  }

  if (valor == 3)
  {
    digitalWrite(Led1ContT, 1);
    digitalWrite(Led2ContT, 1);
    digitalWrite(Led3ContT, 0);
    digitalWrite(Led4ContT, 0);
  }

  if (valor == 4)
  {
    digitalWrite(Led1ContT, 0);
    digitalWrite(Led2ContT, 0);
    digitalWrite(Led3ContT, 1);
    digitalWrite(Led4ContT, 0);
  }

  if (valor == 5)
  {
    digitalWrite(Led1ContT, 1);
    digitalWrite(Led2ContT, 0);
    digitalWrite(Led3ContT, 1);
    digitalWrite(Led4ContT, 0);
  }

  if (valor == 6)
  {
    digitalWrite(Led1ContT, 0);
    digitalWrite(Led2ContT, 1);
    digitalWrite(Led3ContT, 1);
    digitalWrite(Led4ContT, 0);
  }

  if (valor == 7)
  {
    digitalWrite(Led1ContT, 1);
    digitalWrite(Led2ContT, 1);
    digitalWrite(Led3ContT, 1);
    digitalWrite(Led4ContT, 0);
  }

  if (valor == 8)
  {
    digitalWrite(Led1ContT, 0);
    digitalWrite(Led2ContT, 0);
    digitalWrite(Led3ContT, 0);
    digitalWrite(Led4ContT, 1);
  }

  if (valor == 9)
  {
    digitalWrite(Led1ContT, 1);
    digitalWrite(Led2ContT, 0);
    digitalWrite(Led3ContT, 0);
    digitalWrite(Led4ContT, 1);
  }

  if (valor == 10)
  {
    digitalWrite(Led1ContT, 0);
    digitalWrite(Led2ContT, 1);
    digitalWrite(Led3ContT, 0);
    digitalWrite(Led4ContT, 1);
  }

  if (valor == 11)
  {
    digitalWrite(Led1ContT, 1);
    digitalWrite(Led2ContT, 1);
    digitalWrite(Led3ContT, 0);
    digitalWrite(Led4ContT, 1);
  }

  if (valor == 12)
  {
    digitalWrite(Led1ContT, 0);
    digitalWrite(Led2ContT, 0);
    digitalWrite(Led3ContT, 1);
    digitalWrite(Led4ContT, 1);
  }

  if (valor == 13)
  {
    digitalWrite(Led1ContT, 1);
    digitalWrite(Led2ContT, 0);
    digitalWrite(Led3ContT, 1);
    digitalWrite(Led4ContT, 1);
  }

  if (valor == 14)
  {
    digitalWrite(Led1ContT, 0);
    digitalWrite(Led2ContT, 1);
    digitalWrite(Led3ContT, 1);
    digitalWrite(Led4ContT, 1);
  }

  if (valor == 15)
  {
    digitalWrite(Led1ContT, 1);
    digitalWrite(Led2ContT, 1);
    digitalWrite(Led3ContT, 1);
    digitalWrite(Led4ContT, 1);
  }
}

//*****************************************************************************
//Funcion para contador binario
//*****************************************************************************

//Esta funcion aumenta o disminuye la variable contBoton dependiendo de 
//que boton se presione, para luego usarla para encender los leds
void contadorBinario(void)
{

  
  if (Boton1 == 0 && contBoton < 15) //si el boton se presiona y el contador
  {                                  //es menor a 15 se le suma 1 a contBoton
    contBoton = contBoton + 1;
    delay(150);    
  }
  if (Boton1 == 0 && contBoton == 15)
  {
    contBoton = 15;
    delay(150);    
  }
  if (Boton2 == 0 && contBoton > 0) //si el boton se presiona y el contador
  {                                 //es menor a 15 se le resta 1 a contBoton
    contBoton = contBoton - 1;
    delay(150);    
  }
  if (Boton2 == 0 && contBoton == 0)
  {
    contBoton = 0;
    delay(150);
  }
  
}

//*****************************************************************************
//Funcion paa alarma
//*****************************************************************************

//si el contador del timer es igual al de los botones, el del timer comienza
//desde 0 y el led de alarma se enciende

void alarma(void)
{
  if (contBoton == contadorTimer)
  {
    contadorTimer = 0;
    digitalWrite(alarm, 1);

  }
}

//*****************************************************************************
//Funcion para encender leds de botones
//*****************************************************************************

//dependiendo del valor2, que en el loop principal se establece como el 
//contador contBoton, encendera los leds de forma binaria
void ledsBotones (int valor2)
{


  if (valor2 == 1)
  {
    digitalWrite(Led1, 1);
    digitalWrite(Led2, 0);
    digitalWrite(Led3, 0);
    digitalWrite(Led4, 0);
  }

  if (valor2 == 2)
  {
    digitalWrite(Led1, 0);
    digitalWrite(Led2, 1);
    digitalWrite(Led3, 0);
    digitalWrite(Led4, 0);
  }

  if (valor2 == 3)
  {
    digitalWrite(Led1, 1);
    digitalWrite(Led2, 1);
    digitalWrite(Led3, 0);
    digitalWrite(Led4, 0);
  }

  if (valor2 == 4)
  {
    digitalWrite(Led1, 0);
    digitalWrite(Led2, 0);
    digitalWrite(Led3, 1);
    digitalWrite(Led4, 0);
  }

  if (valor2 == 5)
  {
    digitalWrite(Led1, 1);
    digitalWrite(Led2, 0);
    digitalWrite(Led3, 1);
    digitalWrite(Led4, 0);
  }

  if (valor2 == 6)
  {
    digitalWrite(Led1, 0);
    digitalWrite(Led2, 1);
    digitalWrite(Led3, 1);
    digitalWrite(Led4, 0);
  }

  if (valor2 == 7)
  {
    digitalWrite(Led1, 1);
    digitalWrite(Led2, 1);
    digitalWrite(Led3, 1);
    digitalWrite(Led4, 0);
  }

  if (valor2 == 8)
  {
    digitalWrite(Led1, 0);
    digitalWrite(Led2, 0);
    digitalWrite(Led3, 0);
    digitalWrite(Led4, 1);
  }

  if (valor2 == 9)
  {
    digitalWrite(Led1, 1);
    digitalWrite(Led2, 0);
    digitalWrite(Led3, 0);
    digitalWrite(Led4, 1);
  }

  if (valor2 == 10)
  {
    digitalWrite(Led1, 0);
    digitalWrite(Led2, 1);
    digitalWrite(Led3, 0);
    digitalWrite(Led4, 1);
  }

  if (valor2 == 11)
  {
    digitalWrite(Led1, 1);
    digitalWrite(Led2, 1);
    digitalWrite(Led3, 0);
    digitalWrite(Led4, 1);
  }

  if (valor2 == 12)
  {
    digitalWrite(Led1, 0);
    digitalWrite(Led2, 0);
    digitalWrite(Led3, 1);
    digitalWrite(Led4, 1);
  }

  if (valor2 == 13)
  {
    digitalWrite(Led1, 1);
    digitalWrite(Led2, 0);
    digitalWrite(Led3, 1);
    digitalWrite(Led4, 1);
  }

  if (valor2 == 14)
  {
    digitalWrite(Led1, 0);
    digitalWrite(Led2, 1);
    digitalWrite(Led3, 1);
    digitalWrite(Led4, 1);
  }

  if (valor2 == 15)
  {
    digitalWrite(Led1, 1);
    digitalWrite(Led2, 1);
    digitalWrite(Led3, 1);
    digitalWrite(Led4, 1);
  }
    
}