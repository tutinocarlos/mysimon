/* FFEste sketch en una versin del juego "Simon Dice"
  Existe un botn de inicio que hay que pulsar para empezar la partida
  Cuatro LEDs de colores para mostrar las secuencias
  Cuatro botones para que el jugador reproduzca la secuencia

  Al iniciar una partida se reproduce una secuencia de bienvenida al juego
  y tras un segundo se muestra la primera secuencia de 1 luz

  El jugador debe repetir la secuencia mostrada

  Si seacierta la secuencia, todos los LEDs se encienden durante 1 segundo
  y despues se muestra la nueva secuencia.
  Cada jugada la secuencia se incrementa en una luz ms y se incrementa la velocidad
  en que se muestra lasecuencia para hacer ms dificil el juego.

  Si se falla loscuatro LEDs patpadearn 3 veces y finalizar la partida.

  Hardware necesario:
  4 LEDs (1 verde, 1 amarillo,1 azul y 1 rojo)
  4 resistencias 220ohm (para los LEDs)
  5 botones/pulsadores de 4 patas
  5 resistencias 10Kohm (para los botones que se montarn como resistencias PullUp)
  1 zumbador pasivo (passive buzzer)
  1 resistencia de 100ohm (para el zumbador)
  Cables para conexin a placa arduino y para conexiones en protoboard
*/
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define DEFAULT_DELAY 1
#define LED_PIN 12 // recoiendan 1 para Trinket o Gemma
#define LED_COUNT 48

// NeoPixel brightness, 0 (min) to 255 (max)
#define BRIGHTNESS 255 // Set BRIGHTNESS to about 1/5 (max = 255)
// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB);

// definimos constantes para los diferentes pines que usamos
const byte PIN_LED_VERDE = 5;
const byte PIN_LED_AMARILLO = 4;
const byte PIN_LED_AZUL = 3;
const byte PIN_LED_ROJO = 2;

const byte PIN_BOTON_VERDE = 6;
const byte PIN_BOTON_AMARILLO = 7;
const byte PIN_BOTON_AZUL = 8;
const byte PIN_BOTON_ROJO = 9;

const byte PIN_BOTON_INICIO = 10;

const byte PIN_ZUMBADOR = 11;

const byte MAX_RONDAS = 255; // el nmero mximo de rondas ser de 255

const int VELOCIDAD_INICIAL = 500; // velocidad inicial en milisegundos a la que se mostrar la secuencia

byte ronda = 0;                    // numero de ronda en la que vamos
byte secuencia[MAX_RONDAS + 1];    // array para alojar la secuencia que se va generando. El array empieza en el elemento 0 pero no lo usamos, empezamos en el 1 para hacer coincidir con el nmero de ronda
int velocidad = VELOCIDAD_INICIAL; // tiempo en milisegundos que permanecen encendidos los LEDs cuando muestra la secuencia a repetir

#include "mylib.h"
// Definimos notas musicales, duraciones y Variable tempo
#define NOTA_B3 246.94  // Si en 3 Octava
#define NOTA_C4 261.63  // Do en 4 Octava
#define NOTA_C4S 277.18 // Do # en 4 Octava
#define NOTA_D4 293.66  // Re en 4 Octava
#define NOTA_E4 329.63  // Mi en 4 Octava
#define NOTA_F4 349.23  // Fa en 4 Octava

#define T_NEGRA 1
#define T_BLANCA 2
#define T_REDONDA 4
#define T_CORCHEA 0.5
#define T_SEMICORCHEA 0.25
#define T_FUSA 0.125
#define T_SEMIFUSA 0.0625

int tempo = 150; // duracin de un pulso en milisegundos. Se usa para la duracin de las notas

// variables para el controlde rebotes / bouncing de los pulsadores. Cada uno de los 4 pulsadores tiene las suyas
long rebote_ultima_senal_verde = 0; // momento en el que se produjo la seal anterior del boton
long rebote_ultima_senal_amarillo = 0;
long rebote_ultima_senal_azul = 0;
long rebote_ultima_senal_rojo = 0;
long rebote_retardo = 50; // tiempo en milisegundos transcurrido que si se supera entre dos seales del botn deja de considerarse un rebote


void setup()
{

  strip.setBrightness(BRIGHTNESS);
  strip.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();  // Turn OFF all pixels ASAP
  uint32_t greenishwhite = strip.Color(0, 64, 0, 64);
  strip.fill(greenishwhite, 0, 48);
  strip.show();
  // establecemos los pines de los botones en modo entrada
  pinMode(PIN_BOTON_VERDE, INPUT);
  pinMode(PIN_BOTON_AMARILLO, INPUT);
  pinMode(PIN_BOTON_AZUL, INPUT);
  pinMode(PIN_BOTON_ROJO, INPUT);
  pinMode(PIN_BOTON_INICIO, INPUT);
  // establecemos los pines de los LEDs en modo salida
  pinMode(PIN_LED_VERDE, OUTPUT);
  pinMode(PIN_LED_AMARILLO, OUTPUT);
  pinMode(PIN_LED_AZUL, OUTPUT);
  pinMode(PIN_LED_ROJO, OUTPUT);
  // establecemos el pin del buzzer/zumbador en modo salida
  pinMode(PIN_ZUMBADOR, OUTPUT);
  // inicializamos las salidasa a LOW
  digitalWrite(PIN_LED_VERDE, LOW);
  digitalWrite(PIN_LED_AMARILLO, LOW);
  digitalWrite(PIN_LED_AZUL, LOW);
  digitalWrite(PIN_LED_ROJO, LOW);

  // inicializamos las entradas a HIGH ya que hemos diseado el circuito con botones con resistencia pullUp
  digitalWrite(PIN_BOTON_VERDE, HIGH);
  digitalWrite(PIN_BOTON_AMARILLO, HIGH);
  digitalWrite(PIN_BOTON_AZUL, HIGH);
  digitalWrite(PIN_BOTON_ROJO, HIGH);
  digitalWrite(PIN_BOTON_INICIO, HIGH);

  Serial.begin(9600);

  strip.fill(strip.Color(0, 0, 255, 40), 0, 48);
  strip.show();
  apagar();
  encenderTodo();
  delay(750);
  apagar();



  encenderTodo();
}

void loop()
{

  if (ronda == 0)
  { // si la ronda es 0 es que aun no han pulsado el botn de inicio para empezar una partida nueva
    espera_pulsacion_inicio();
  }

  if (ronda == 1)
  { // si estamos en la primera ronda hacemos las seales de bienvenida
    flash_bienvenida();
  }
  genera_secuencia(); // generamos la secuencia con tantos elementos como el nmero de ronda en el que vamos
  lee_respuesta();    // leemos la respuesta del jugador
}

void espera_pulsacion_inicio()
{
  // esperamos hasta que pulsen el boton de inico de nueva partida
  while (ronda == 0)
  {
    activarSegmento(2, 1);

    if (digitalRead(PIN_BOTON_ROJO) == LOW)
    {
      ronda = 1;
      strip.fill(strip.Color(255, 255, 255, 255), 0, 48);
      strip.show();
      apagar();

    };

  }
}

void reproduce_melodia(int notas[], int duracion[], int tempo, int nro_notas, int error = 0)
{


  /* notas = array con las notas (frecuencias o notas pre-definidas)
     duracion = array con la duracin de cada nota del array notas[] son el factor multiplicador del tempo, es decir si queremos que dure un pulso de tempo, indicaremos 1 o T_NEGRA
     tempo = duracin de un pulso (una nota negra) en milisegundos
     nro_notas = numero de notas que compone el array notas[]
  */
  //  switch (nro_notas) {
  //    case 4:
  //      strip.fill(strip.Color(255, 0, 0, 255), 0, 48);
  //      strip.show();
  //      break;
  //    case 6:
  //      strip.fill(strip.Color(0, 255, 0, 255), 0, 48);
  //      strip.show();
  //      break;
  //  }
  int x = 0;

  for (x = 0; x < nro_notas; x++)
  {

    switch (error) {
      case 1:

        strip.fill(strip.Color(255, 0, 0, 255), 0, 48);
        strip.show();
        activarSegmentoError(x + 2, 1);

        tone(PIN_ZUMBADOR, notas[x], duracion[x] * tempo);

        break;
      default:
        tone(PIN_ZUMBADOR, notas[x], duracion[x] * tempo);

    }
    tone(PIN_ZUMBADOR, notas[x], duracion[x] * tempo);
    delay(duracion[x] * tempo * 1.30);
  }

}

void reproduce_nota_led(byte led, int tiempo)
{
  int nota[] = {NOTA_C4, NOTA_D4, NOTA_E4, NOTA_F4};

  activarSegmento(led, 1);
  tone(PIN_ZUMBADOR, nota[led - 2], tiempo); // HACEMOS nota[led - 2] por que en led pasamos el pin del led que toque encender y estos empiezan en el pin 2
  delay(tiempo);
  apagar();                           // hacemos delay para que el led permanezca encendido mientras suena la nota
}

void tema_inicio()
{
  // meloda que suena al inicio de las partidas
  int notas[] = {NOTA_B3, NOTA_B3, NOTA_B3, NOTA_D4, NOTA_B3, NOTA_D4};
  int duracion[] = {T_NEGRA, T_NEGRA, T_NEGRA, T_BLANCA, T_NEGRA, T_REDONDA};
  // tempo = 150;
  //  reproducimos la meloda
  reproduce_melodia(notas, duracion, 100, 6);
}

void tema_game_over(int error)
{
  // meloda que suena al perder la partida
  int notas[] = {NOTA_D4, NOTA_C4S, NOTA_C4, NOTA_B3};
  int duracion[] = {T_NEGRA, T_NEGRA, T_NEGRA, T_REDONDA};
  reproduce_melodia(notas, duracion, 300, 4, error);

}

void flash_bienvenida()
{
  tema_inicio();
  delay(1000);
}

void flash_respuesta_correcta()
{
  // esperamos 1 segundo para continuar con la siguiente secuencia
  delay(1000);
}

void flash_respuesta_incorrecta()
{
  // Suena la meloda game over con los 4 leds encendidos

  tema_game_over(1);//paso 1 para marcar error

  delay(1000);
}

void genera_secuencia()
{
  // Generamos el sigeuinte elemento de la secuncia y la reproducimos
  randomSeed(analogRead(A0) * 0.785478545); // generamos una semilla para generar el nmero aleatorio
  secuencia[ronda] = random(2, 6); // generamos un numero aleatorio entre 2 y 5 que son lospines dondea estn los leds
  for (int x = 1; x <= ronda; x++) // reproducimos la secuencia
  {
    reproduce_nota_led(secuencia[x], velocidad);
    //    apagar();
    //     delay(velocidad);
    delay(100 * velocidad / VELOCIDAD_INICIAL);
  }
}

void lee_respuesta()
{
  // leemos las pulsaciones del jugador y vamos comprobando que la secuencia sea correcta
  boolean correcto = true;
  byte x = 1;
  byte pulsacion = 0;
  while (correcto and x <= ronda)
  { // vamos leyendo pulsacion a pulsacin y comprobando que la secuencia vaya siendo correcta
    if (digitalRead(PIN_BOTON_ROJO) == LOW)
    {
      digitalWrite(PIN_LED_ROJO, HIGH);
      reproduce_nota_led(PIN_LED_ROJO, 250);
      digitalWrite(PIN_LED_ROJO, LOW);
      pulsacion = PIN_LED_ROJO;
      rebote_ultima_senal_rojo = millis();
    }
    else if (digitalRead(PIN_BOTON_AZUL) == LOW)
    {
      digitalWrite(PIN_LED_AZUL, HIGH);
      reproduce_nota_led(PIN_LED_AZUL, 250);
      digitalWrite(PIN_LED_AZUL, LOW);
      pulsacion = PIN_LED_AZUL;
      rebote_ultima_senal_azul = millis();
    }
    else if (digitalRead(PIN_BOTON_AMARILLO) == LOW)
    {
      digitalWrite(PIN_LED_AMARILLO, HIGH);
      reproduce_nota_led(PIN_LED_AMARILLO, 250);
      digitalWrite(PIN_LED_AMARILLO, LOW);
      pulsacion = PIN_LED_AMARILLO;
      rebote_ultima_senal_amarillo = millis();
    }
    else if (digitalRead(PIN_BOTON_VERDE) == LOW)
    {
      digitalWrite(PIN_LED_VERDE, HIGH);
      reproduce_nota_led(PIN_LED_VERDE, 250);
      digitalWrite(PIN_LED_VERDE, LOW);
      pulsacion = PIN_LED_VERDE;
      rebote_ultima_senal_verde = millis();
    }

    if ((pulsacion == PIN_LED_ROJO && (millis() - rebote_ultima_senal_rojo) > rebote_retardo) ||
        (pulsacion == PIN_LED_AZUL && (millis() - rebote_ultima_senal_azul) > rebote_retardo) ||
        (pulsacion == PIN_LED_AMARILLO && (millis() - rebote_ultima_senal_amarillo) > rebote_retardo) ||
        (pulsacion == PIN_LED_VERDE && (millis() - rebote_ultima_senal_verde) > rebote_retardo))
    {
      // Solo entramos en caso de que se haya pulsado un boton y ya se haya soltado,
      // para saber si se solt de verdad utilizamos las comparaciones de rebote para evitar falsas sueltas del botn
      if (pulsacion != secuencia[x])
      { // si se ha fallado correcto = false y se sale del bucle
        correcto = false;
      }
      else
      { // si no se ha fallado se pasa al siguiente elemento de la secuencia
        x++;
        pulsacion = 0;
      }
    }
  } // fin while

  if (correcto == true)
  { // si correcto es que se ha acertado toda la secuencia
    ronda++; // incrementamos una ronda
    if (ronda == MAX_RONDAS) {
      Serial.println("gano");
      segmento(strip.Color(  0,   255,   0, 255), 0, 48, 2); // True white (not RGB white)

      delay(500);
      apagar();
      delay(500);
      segmento(strip.Color(  0,   255,   0, 255), 0, 48, 2); // True white (not RGB white)

      tema_inicio();

      ronda = 0;
      velocidad = VELOCIDAD_INICIAL;
      espera_pulsacion_inicio();

    }
    delay(100);
    flash_respuesta_correcta();


    if (velocidad >= 50)
    {
      velocidad = velocidad - 50; // incrementamos la velocidad de muestra de la secuencia (10 milisegundos ms rpida)
    }


  }
  else
  { // si correcto == false es que se ha fallado

    flash_respuesta_incorrecta();
    ronda = 0; // ponemos ronda a 0 para volver a esperar que inicien una nueva partida
    velocidad = VELOCIDAD_INICIAL;
    espera_pulsacion_inicio();
  }
}
