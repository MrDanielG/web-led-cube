#include <PubSubClient.h>
#include <WiFi.h>

const int nColumns = 16;
const int nLevels = 4;
int columns [5][5] = {
  {0,0,0,0,0},
  {0,15,22,21,23},
  {0,32,4,19,5},
  {0,33,2,18,1},
  {0,25,26,17,3},
};
int timeBetweenEffects = 500;
int levels[] = {0,27, 14, 12, 13};
int currentPattern = 0;

// change the state of a single led
void turnLed(int x, int y, int z, bool state)
{
  // x: row, y: column, z: height
  if (state)
  {
    digitalWrite(columns[x][y], LOW);
    digitalWrite(levels[z], HIGH);
  }
  else
  {
    digitalWrite(columns[x][y], HIGH);
    digitalWrite(levels[z], LOW);
  }
}
// change the state of a single level
void turnLevel(int level, bool state)
{
  if (state)
    digitalWrite(levels[level], HIGH);
  else
    digitalWrite(levels[level], LOW);
}
// change the state of a single column
void turnColumn(int x, int y, bool state)
{
  if (state)
  {
    digitalWrite(columns[x][y], HIGH);
  }
  else
  {
    digitalWrite(columns[x][y], LOW);
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
      delay(timeBetweenEffects / 6);
    }
  }
}

// Flicker level by level a number of times
void flickerLevelByLevel()
{
  turnAllLedsOn();
  for (int i = 4; i > 0; i--)
  {
    turnLevel(i, false);
    delay(timeBetweenEffects / 6);
    turnLevel(i, true);
  }
  for (int i = 1; i <= 4; i++)
  {
    turnLevel(i, false);
    delay(timeBetweenEffects / 6);
    turnLevel(i, true);
  }
}
// random leds (christmas tree)
void xmasTree()
{ 
  int i = random(1, 5);
  int j = random(1, 5);
  int k = random(1, 5);
  turnLed(i, j, k, true);
  delay(timeBetweenEffects / 4);
  turnLed(i, j, k, false);
}
// Simulate rain drops
void drops()
{
  int i = random(1, 5);
  int j = random(1, 5);
  for (int n = 4; n > 0; n--)
  {
    turnLed(i, j, n, true);
    delay(timeBetweenEffects / 6);
    turnLed(i, j, n, false);
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
// the previous one depending on the direction of the cycle
void cubeResizing() {
  for (int i=1; i<4; i++)
  {
    customSizeCube(i, true);
    delay(timeBetweenEffects/6);
    customSizeCube(i, false);
  }
  turnAllLedsOn();
  delay(timeBetweenEffects/8);
  turnAllLedsOff();
  for (int j=3; j>0; j--)
  {
    customSizeCube(j, true);
    delay(timeBetweenEffects/6);
    customSizeCube(j, false);
  }
}
void turnOffLed(int x, int y, int z)
{
  turnLed(x, y, z, false);
  delay(timeBetweenEffects / 6);
}
// The cube is traversed level by level
// and each level simulates a spiral
void spiralLevelByLevel()
{
  turnAllLedsOn();
  delay(timeBetweenEffects / 4);
  for (int level=1; level<=1; level++)
  {
    for (int i=1; i<=4; i++)
    {
      turnOffLed(1, i, level);
    }
    turnLed(2, 4, level, false);
    turnLed(3, 4, level, false);
    //turnOffLed(2, 4, level);
    //turnOffLed(3, 4, level);
    for (int j=4; j>0; j--)
    {
      turnOffLed(4, j, level);
    }
    turnOffLed(3, 1, level);
    for (int k=1; k<4; k++)
    {
      turnOffLed(2, k, level);
    }
    turnLed(3, 3, level, false);
    turnLed(3, 2, level, false);
    //turnOffLed(3, 3, level);
    //turnOffLed(3, 2, level);
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
// the previous one depending on the direction of the cycle
void cubeResizing() {
  for (int i=1; i<4; i++)
  {
    customSizeCube(i, true);
    delay(timeBetweenEffects);
    customSizeCube(i, false);
  }
  turnAllLedsOn();
  delay(timeBetweenEffects);
  turnAllLedsOff();
  for (int j=3; j>0; j--)
  {
    customSizeCube(j, true);
    delay(timeBetweenEffects);
    customSizeCube(j, false);
  }
}
void turnOffLed(int x, int y, int z)
{
  turnLed(x, y, z, false);
  delay(timeBetweenEffects / 4);
}
// The cube is traversed level by level
// and each level simulates a spiral
void spiralLevelByLevel()
{
  turnAllLedsOn();
  delay(timeBetweenEffects / 2);
  for (int level=1; level<=4; level++)
  {
    for (int i=1; i<=4; i++)
    {
      turnOffLed(1, i, level);
    }
    turnOffLed(2, 4, level);
    turnOffLed(3, 4, level);
    for (int j=4; j>0; j--)
    {
      turnOffLed(4, j, level);
    }
    turnOffLed(3, 1, level);
    for (int k=1; k<4; k++)
    {
      turnOffLed(2, k, level);
    }
    turnOffLed(3, 3, level);
    turnOffLed(3, 2, level);
  }
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
    currentPattern = 0;
  }
  else if((char)payload[0] == '1'){
    currentPattern = 1;
  }
  else if((char)payload[0] == '2'){
    currentPattern = 2;
  }
  else if((char)payload[0] == '3'){
    currentPattern = 3;
  }
  else if((char)payload[0] == '4'){
    currentPattern = 4;
  }
  else if((char)payload[0] == '5'){
    currentPattern = 5;
  }
  else if((char)payload[0] == '6'){
    currentPattern = 6;
  }
  else if((char)payload[0] == '7'){
    currentPattern = 7;
  }
  else if((char)payload[0] == '6'){
    turnAllLedsOff();
    cubeResizing();
  }
  else if((char)payload[0] == '7'){
    turnAllLedsOff();
    spiralLevelByLevel();
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
  for (int i = 1; i <= 4; i++)
  {
    for(int j = 1; j <= 4; j++){
      pinMode(columns[i][j], OUTPUT);
    }
  }
  for (int i = 1; i <= nLevels; i++)
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
flickerLevelByLevel() -> 2
turnOnColumnByColumn(false) -> 3
xmasTree() -> 4
drops() -> 5
cuberesize -> 6
spiral -> 7
*/
void loop()
{
  // put your main code here, to run repeatedly:
  if(client.connected() == false){
    reconnect();
  }
  client.loop();
  turnAllLedsOff();
  if(currentPattern == 2){
    flickerLevelByLevel();
  }
  else if(currentPattern == 3){
    turnOnColumnByColumn(false);
  }
  else if(currentPattern == 4){
    xmasTree();
  }
  else if(currentPattern == 5){
    drops();
  }
  else if(currentPattern == 6){
    cubeResizing();
  }
  else if(currentPattern == 7){
    spiralLevelByLevel();
  }
  
}