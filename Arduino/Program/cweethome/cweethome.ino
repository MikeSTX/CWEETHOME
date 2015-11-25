/*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *

  _____________________________________
    >> LIBRARY
  _____________________________________
 
*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  */

// Casual library
#include <SPI.h>

// Ethernet library
#include <Ethernet2.h>
#include <EthernetServer.h>
#include <EthernetClient.h>




/*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *

  _____________________________________
    >> Program
  _____________________________________
 
*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  */


// Declaration of ethernet settings
// ---------------------------------------------------
byte mac[] = { 0x90, 0xA2, 0xDA, 0x10, 0x03, 0x2A }; // MAC adress of arduino card
byte ip[] = { 192, 168, 1, 102 }; // IP adress of arduino card
byte gateway[] = { 192, 168, 1, 1 }; //Root's IP adress
byte subnet[] = { 255, 255, 255, 0 }; // Mask adress network
int port = 80; // PORT 80 (default HTTP port)
EthernetServer server(80); // Creation of server object on port 80 (default HTTP port)
EthernetClient client; // Client of the arduino card

// Declaration of globals variables
// ----------------------------------------------------

// # CONSTANT
const int MAX_NB_BYTES_CLIENT = 512; // == 2^10 Bytes
const int NB_ELEM_BY_COMMAND_OUTPUTS = 4;
const int NB_COMMAND_OUTPUTS = 24;
// # Variables about the frame
char tabBytesClient[MAX_NB_BYTES_CLIENT] = "";
int comptClientBytes = 1;
int comptTabClientBytes = 0;
int nbCharInFrame = 0;
int nbCommands = 1;
char firstCharOfTag;


// # State of arduino's output
int matrixOutputsArduino[NB_ELEM_BY_COMMAND_OUTPUTS][NB_COMMAND_OUTPUTS] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4},
                                                                            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 0, 1, 2, 3},
                                                                            {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45},
                                                                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
                                                                           };




/* ----------------------------------------------------
  
  > FUNCTION void setup()
    <> input : null
    <> output : void
    -----------------------------------------
    
    This function initializes all settings of the
    arduino card
    _____________________________________________
   
------------------------------------------------------- */
void setup()   
{

  
  // Locals variables
  // ------------------------------------------------------------------------
  int stateConnexionClient;
  
  
  // Initializes serial connection (115200 bauds) & ethernet connection
  // ------------------------------------------------------------------------
  Serial.begin(115200); 
  Serial.println(" > SETUP");
  Serial.println(" -------------------------------------------------------- ");
  Serial.println("");
  
  Ethernet.begin(mac, ip, gateway, subnet); 
  
  // Connecting the server
  // -------------------------------------------
  server.begin();
  Serial.println("Connexion to the server - SUCCES");
  
 

  // Initailizes of I/O's arduino card
  // -------------------------------------------
  Serial.println("Initializes the I/O's arduino card");
  pinMode(22, OUTPUT); //LIG is an output
  digitalWrite(22, 0);
  pinMode(23, OUTPUT); //LIG is an output
  digitalWrite(23, 0);
  pinMode(24, OUTPUT); //LIG is an output
  digitalWrite(24, 0);
  pinMode(25, OUTPUT); //LIG is an output
  digitalWrite(25, 0);
  pinMode(26, OUTPUT); //LIG is an output
  digitalWrite(26, 0);
  pinMode(27, OUTPUT); //LIG is an output
  digitalWrite(27, 0);
  pinMode(28, OUTPUT); //LIG is an output
  digitalWrite(28, 0);
  pinMode(29, OUTPUT); //LIG is an output
  digitalWrite(29, 0);
  pinMode(30, OUTPUT); //LIG is an output
  digitalWrite(30, 0);
  pinMode(31, OUTPUT); //LIG is an output
  digitalWrite(31, 0);
  pinMode(32, OUTPUT); //LIG is an output
  digitalWrite(32, 0);
  pinMode(33, OUTPUT); //LIG is an output
  digitalWrite(33, 0);
  pinMode(34, OUTPUT); //LIG is an output
  digitalWrite(34, 0);
  pinMode(35, OUTPUT); //LIG is an output
  digitalWrite(35, 0);
  pinMode(36, OUTPUT); //LIG is an output
  digitalWrite(36, 0);
  pinMode(37, OUTPUT); //LIG is an output
  digitalWrite(37, 0);
  pinMode(38, OUTPUT); //LIG is an output
  digitalWrite(38, 0);
  pinMode(39, OUTPUT); //LIG is an output
  digitalWrite(39, 0);
  pinMode(40, OUTPUT); //LIG is an output
  digitalWrite(40, 0);
  pinMode(41, OUTPUT); //LIG is an output
  digitalWrite(41, 0);
  pinMode(42, OUTPUT); //LIG is an output
  digitalWrite(42, 0);
  pinMode(43, OUTPUT); //LIG is an output
  digitalWrite(43, 0);
  pinMode(44, OUTPUT); //LIG is an output
  digitalWrite(44, 0);
  pinMode(45, OUTPUT); //LIG is an output
  digitalWrite(45, 0);
  
  Serial.println("Initialisation - SUCCES");
  Serial.println("");
  
}




/* ----------------------------------------------------
  
  > FUNCTION void loop()
    <> input : null
    <> output : void
    -----------------------------------------
    
    This function is called each 30ms
    _____________________________________________
   
------------------------------------------------------- */
void loop()
{
  
  // Locals variables
  // --------------------------------------------------
  char readBytesClient;
  int iteratorTabOfBytesClient = 0;

  
  /* ------------------------------------
      > begin of the function
  -------------------------------------- */
  
  // Declared an incoming client connects
  // -----------------------------------------------------------------
  EthernetClient client = server.available();
  
  if(client.available())
  {
    Serial.println(" > There's a new client");
    Serial.println(" ------------------------------- ");
    
    while(readBytesClient != '}')
    {
      // Read the bytes which the app send
      // ----------------------------------------------------
      readBytesClient = client.read();
      
       
      // Show the frame of the client
      // ---------------------------------------------------
      if(comptClientBytes >= 181)
      {
        // Memorise the list of char in a tab
        // ---------------------------------------------------
        tabBytesClient[iteratorTabOfBytesClient] = readBytesClient;
        
        if(',' == tabBytesClient[iteratorTabOfBytesClient])
        {
          nbCommands = nbCommands + 1;
        }
        
        // Count the nb of command of the frame
        // ----------------------------------------------------
        Serial.print(tabBytesClient[iteratorTabOfBytesClient]);
        iteratorTabOfBytesClient = iteratorTabOfBytesClient + 1;
      }
      
      comptClientBytes = comptClientBytes + 1;
    }
    
    // Count nb command in the frame
    // ------------------------------------------------------
    Serial.println(nbCommands);
    
    // get the tag of the frame
    // ------------------------------------------------------
    if(tabBytesClient[2] == 'L')
    {
      Serial.println("Command - LIGHT");
      updateMatriceOfCommand(0, 9);
    }
    if(tabBytesClient[2] == 'C')
    {
      Serial.println("Command - CURTAINS");
      updateMatriceOfCommand(10, 15);
    }
    if(tabBytesClient[2] == 'G')
    {
      Serial.println("Command - GATE");
      updateMatriceOfCommand(16, 19);
    }
    if(tabBytesClient[2] == 'D')
    {
      Serial.println("Command - DOOR");
      updateMatriceOfCommand(20, 23);
    }
    
    
    Serial.println();
    Serial.println();
    Serial.println("Clear the tab of the frame");
    memset(tabBytesClient, 0, sizeof(tabBytesClient));
    comptClientBytes = 1;
    nbCommands = 1;
    iteratorTabOfBytesClient = 0;
    Serial.println("End of the connexion with the client");
    Serial.println(" -------------------------------------------- ");
    Serial.println();
    Serial.println();
    client.stop();
  }
}



/* ----------------------------------------------------
  
  > FUNCTION void setLightCommand()
    <> input : void
    <> output : void
    -----------------------------------------
    
    This function command the light of the house
    _____________________________________________
   
------------------------------------------------------- */
void updateMatriceOfCommand(int startTagInMatrix, int endTagInMatrix)
{
  
  /* --------------------------------------------------- 
       <> Locals variables
          ____________________________________    
  ------------------------------------------------------- */
  int iteratorCommandFrame = 0;
  
  // Var abour the frame
  // ----------------------------------
  int cursorDeviceToCommand = 7;
  int cursorStateOfDevice= 9;
  int stepNextCommand = 4;
  int intCommand;
  int intStateCommand;
  
  // Var about the matrix
  // ----------------------------------
  int cursorMatrix_Tag = 0;
  int cursorMatrix_Id = 0;
  
  
  
  
  /* --------------------------------------------------- 
     <> Program
        ____________________________________    
  ------------------------------------------------------- */
  
  
  
  // loop to apply all the command of the frame (could be several)
  for (iteratorCommandFrame = 0 ; iteratorCommandFrame < nbCommands; iteratorCommandFrame++)
  {
    /*Serial.println(tabBytesClient[cursorDeviceToCommand]);
  Serial.println(tabBytesClient[cursorStateOfDevice]);*/
    // Convert the information of the frame to type "int"
    // --------------------------------------------------------------------
    intCommand = tabBytesClient[cursorDeviceToCommand] - '0';
    intStateCommand = tabBytesClient[cursorStateOfDevice] - '0';
    
    // Look for our command in the matrix
    // ---------------------------------------------------------------------
    for(cursorMatrix_Id = startTagInMatrix ; cursorMatrix_Id < endTagInMatrix ; cursorMatrix_Id++)
    {
      if(matrixOutputsArduino[1][cursorMatrix_Id] == intCommand)
      {
        // We find it, let's update the state if the command in the matrice
        // ----------------------------------------------------------------------
        matrixOutputsArduino[3][cursorMatrix_Id] = intStateCommand;
        digitalWrite(matrixOutputsArduino[2][cursorMatrix_Id], matrixOutputsArduino[3][cursorMatrix_Id]);
        
      }
    }
    
    // go the next command of the frame tabBytesClient
    // ---------------------------------------------
    cursorDeviceToCommand = cursorDeviceToCommand + stepNextCommand;
    cursorStateOfDevice = cursorStateOfDevice + stepNextCommand;
  }
  
}


