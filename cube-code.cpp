#include <PubSubClient.h>
#include <WiFi.h>

const int nColumns = 16;
const int nLevels = 4;
int columns[nColumns] = {15, 22, 21, 23, 32, 4, 19, 5, 33, 2, 18, 1, 25, 26, 17, 3};
int timeBetweenEffects = 500;
int levels[nLevels] = {27, 14, 12, 13};

// change the state of a single led
void turnLed(int x, int y, int z, bool state)
{
  // x: row, y: column, z: height
  int level = z - 1;
  int pos = 4 * (x - 1);
  pos += (y - 1);
  if (state)
  {
    digitalWrite(columns[pos], LOW);
    digitalWrite(levels[level], HIGH);
  }
  else
  {
    digitalWrite(columns[pos], HIGH);
    digitalWrite(levels[level], LOW);
  }
}
// change the state of a single level
void turnLevel(int level, bool state)
{
  if (state)
    digitalWrite(levels[level - 1], HIGH);
  else
    digitalWrite(levels[level - 1], LOW);
}
// change the state of a single column
void turnColumn(int x, int y, bool state)
{
  int pos = 4 * (x - 1);
  pos += (y - 1);
  if (state)
  {
    digitalWrite(columns[pos], HIGH);
  }
  else
  {
    digitalWrite(columns[pos], LOW);
  }
}
// Turn all the leds off
void turnAllLedsOff()
{
  for (int i = 1; i <= 4; i++)
  {
    for (int j = 1; j <= 4; j++)
    {
      for (int k = 1; k <= 4; k++)
      {
        turnLed(j, k, i, false);
      }
    }
  }
}
// Turn all the leds on
void turnAllLedsOn()
{
  for (int i = 1; i <= 4; i++)
  {
    for (int j = 1; j <= 4; j++)
    {
      for (int k = 1; k <= 4; k++)
      {
        turnLed(j, k, i, true);
      }
    }
  }
}
// Turn on column by column from right to left or viceversa
void turnOnColumnByColumn(bool sense)
{
  int start, finish, increment;
  if (sense)
  {
    start = 1;
    finish = 5;
    increment = 1;
  }
  else
  {
    start = 4;
    finish = 0;
    increment = -1;
  }
  for (int i = start; i != finish; i += increment)
  {
    turnLevel(i, true);
  }

  for (int j = start; j != finish; j += increment)
  {
    for (int k = 1; k <= 4; k++)
    {
      turnColumn(j, k, false);
      delay(timeBetweenEffects / 4);
    }
  }
}

// Flicker level by level a number of times
void flickerLevelByLevel(int times)
{
  turnAllLedsOn();
  for (int c = 0; c < times * 2; c++)
  {
    for (int i = 4; i > 0; i--)
    {
      turnLevel(i, false);
      delay(timeBetweenEffects / 4);
      turnLevel(i, true);
    }
    for (int i = 1; i <= 4; i++)
    {
      turnLevel(i, false);
      delay(timeBetweenEffects / 4);
      turnLevel(i, true);
    }
  }
}
// random leds (christmas tree)
void xmasTree()
{
  for (int c = 0; c < 50; c++)
  {
    int i = random(1, 5);
    int j = random(1, 5);
    int k = random(1, 5);
    turnLed(i, j, k, true);
    delay(timeBetweenEffects / 4);
    turnLed(i, j, k, false);
  }
}
// Simulate rain drops
void drops()
{
  for (int c = 0; c < 20; c++)
  {
    int i = random(1, 5);
    int j = random(1, 5);
    for (int n = 4; n > 0; n--)
    {
      turnLed(i, j, n, true);
      delay(timeBetweenEffects / 2);
      turnLed(i, j, n, false);
    }
  }
}
// Displays a cube with a custom size
void customSizeCube(int size, int state) {
  if (size == 1)
  {
    turnLed(1, 1, 1, state);
  }
  if (size > 1 && size <= 4)
  {
    for (int i=1; i<=size; i++)
    {
      for (int j=1; j<=size; j++)
      {
        for (int k=1; k<=size; k++)
        {
          turnLed(k, j, i, state);
        }
      }
    }
  }
}
// Displays a cube of custom size larger or smaller than
// the previous one depending on the direction of the cycle.
void cubeResizing() {
  for (int i=1; i<=4; i++)
  {
    customSizeCube(i, true);
    delay(timeBetweenEffects / 2);
    customSizeCube(i, false);
  }
  delay(timeBetweenEffects / 2);
  for (int j=4; j>0; j--)
  {
    customSizeCube(j, true);
    delay(timeBetweenEffects / 2);
    customSizeCube(j, false);
  }
}

void turnColumnWithDelay(int x, int y, bool state)
{
  turnColumn(x, y, state);
  delay(timeBetweenEffects / 4);
}
// Spiral by columns
void positiveSpiral()
{
  bool state = true;
  turnColumnWithDelay(3, 2, state);
  turnColumnWithDelay(3, 3, state);
  for (int i = 3; i > 0; i--)
  {
    turnColumnWithDelay(2, i, state);
  }
  turnColumnWithDelay(3, 1, state);
  for (int j=1; j<=4; j++)
  {
    turnColumnWithDelay(4, j, state);
  }
  turnColumnWithDelay(3, 4, state);
  turnColumnWithDelay(2, 4, state);
  for (int i=4; i>0; i--)
  {
    turnColumnWithDelay(1, i, state);
  }
}
// Spiral by columns
void negativeSpiral()
{
  bool state = false;
  for (int i=1; i<=4; i++)
  {
    turnColumnWithDelay(1, i, state);
  }
  turnColumnWithDelay(2, 4, state);
  turnColumnWithDelay(3, 4, state);
  for (int j=4; j>0; j--)
  {
    turnColumnWithDelay(4, j, state);
  }
  turnColumnWithDelay(3, 1, state);
  for (int i=1; i<4; i++)
  {
    turnColumnWithDelay(2, i, state);
  }
  turnColumnWithDelay(3, 3, state);
  turnColumnWithDelay(3, 2, state);
}

const char* ssid = "IZZI-6FDA";
const char* password =  "D4AB826E6FDA";

const char* mqtt_server = "driver.cloudmqtt.com";
const int  mqtt_port =  18625;
const char* mqtt_user = "bmtqnhmu";
const char* mqtt_pass = "KHw4Itds6hTj";
WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
char msg[50];
int value = 0;

void callback(char* topic, byte* payload, unsigned int length)
{

  if ((char)payload[0] == '0')
  {
    turnAllLedsOff();
  }
  else if((char)payload[0] == '1'){
    turnAllLedsOff();
    turnAllLedsOn();
  }
  else if((char)payload[0] == '2'){
    turnAllLedsOff();
    flickerLevelByLevel(4);
  }
  else if((char)payload[0] == '3'){
    turnAllLedsOff();
    turnOnColumnByColumn(false);
  }
  else if((char)payload[0] == '4'){
    turnAllLedsOff();
    xmasTree();
  }
  else if((char)payload[0] == '5'){
    turnAllLedsOff();
    drops();
  }
  else if((char)payload[0] == '6'){
    turnAllLedsOff();
    cubeResizing();
  }
  else if((char)payload[0] == '7'){
    turnAllLedsOff();
    positiveSpiral();
    negativeSpiral();
  }
}
void reconnect(){
  while (!client.connected())
  {

    String clientId = "iot_1_";
    clientId = String (random(0xffff), HEX);

    if(client.connect(clientId.c_str(),mqtt_user,mqtt_pass))
    {
      // client.publish("salida_Omar", "primer mensaje");
      client.subscribe ("entrada_Omar");
    }
    else
    {
      delay(5000);
    }
  }
}
void setup_wifi(){
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
  }
}

void setup()
{
  // put your setup code here, to run once:
  // Initialize columns and levels of the cube
  for (int i = 0; i < nColumns; i++)
  {
    pinMode(columns[i], OUTPUT);
  }
  for (int i = 0; i < nLevels; i++)
  {
    pinMode(levels[i], OUTPUT);
  }
  randomSeed(analogRead(34));
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  turnAllLedsOff();
}
/*
turnAllLedsOff() -> 0
turnAllLedsOn() -> 1
flickerLevelByLevel(4) -> 2
turnOnColumnByColumn(false) -> 3
xmasTree() -> 4
drops() -> 5
*/
void loop()
{
  // put your main code here, to run repeatedly:
  if(client.connected() == false){
    reconnect();
  }
  client.loop();
  
}