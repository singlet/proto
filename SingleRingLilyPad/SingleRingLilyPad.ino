// SingleRing controller.

typedef struct color
  {
  int red;
  int green;
  int blue;
  } color;
  
// Four buttons.
int colorButton = 5;
//int ageButton = 13;

// Four target positions.
int redPin = A4;
int greenPin = A2;
int bluePin = A3;

// Rotating LEDs.
int led1 = 6;
int led2 = 9;
int led3 = 10;
int led4 = 11;
int led5 = A5;

color dark;
color pink;
color blue;
color purple;
color green;

color * colors[] = { & dark, & pink, & blue, & purple, & green };
int currentColorIndex = 0;

int runner[] = { led1, led2, led3, led4, led5 };
int currentRunnerIndex = 0;
int currentRunner = 0;
int currentRunnerDelay = 10;

int colorButtonWasPushed = 0;
int ageButtonWasPushed = 0;
void setColor(color c);

// Setup the program.
void setup()
  {
  dark.red = 0;
  dark.green = 0;
  dark.blue = 0;
  
  pink.red = 255;
  pink.green = 0;
  pink.blue = 0;
  
  blue.red = 0;
  blue.green = 0;
  blue.blue = 255;
  
  purple.red = 255;
  purple.green = 0;
  purple.blue = 255;
  
  green.red = 0;
  green.green = 255;
  green.blue = 0;

  pinMode(colorButton, INPUT_PULLUP);
  //pinMode(ageButton, INPUT);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);

  for(int i = 0; i < 5; ++i)
    digitalWrite(runner[i], LOW);
    
  // Setup serial output.
  Serial.begin(9600);

  Serial.println("Running...");
  }
  
// Run forever.
void loop()
  {
  int colorButtonPushed = digitalRead(colorButton);
  
  if(!colorButtonPushed && colorButtonWasPushed)
    {
    ++currentColorIndex;
    
    if(currentColorIndex > 4)
      currentColorIndex = 0;
      
    colorButtonWasPushed = 0;
    }
  else if(colorButtonPushed)
    colorButtonWasPushed = colorButtonPushed;
    
  setColor(*colors[currentColorIndex]);
  
  int ageButtonPushed = 0; // digitalRead(ageButton);
  
  if(!ageButtonPushed && ageButtonWasPushed)
    {
    ++currentRunnerDelay;
    
    if(currentRunnerDelay > 10)
      currentRunnerDelay = 0;
      
    ageButtonWasPushed = 0;
    }
  else if(ageButtonPushed)
    ageButtonWasPushed = ageButtonPushed;

  for(int i = 0; i < 5; ++i)
    digitalWrite(
      runner[i], 
      (!currentRunnerDelay || (i == currentRunnerIndex)) ? HIGH : LOW);
  
  delay(100);
  
  ++currentRunner;
  
  if(!(currentRunner % currentRunnerDelay))
    ++currentRunnerIndex;
   
  Serial.print("Current runner ");
  Serial.println(currentRunnerIndex);
  
  if(currentRunnerIndex > 4)
    currentRunnerIndex = 0;
  }
 
void setColor(color c)
  {
  Serial.print("Current color ");
  Serial.print(c.red);
  Serial.print(" ");
  Serial.print(c.green);
  Serial.print(" ");
  Serial.print(c.blue);
  Serial.println();
  analogWrite(redPin, 255 - c.red);
  analogWrite(greenPin, 255 - c.green);
  analogWrite(bluePin, 255 - c.blue);
  }
