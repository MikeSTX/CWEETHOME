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

// Declaration of aeduino output
// ---------------------------------------------------
int LIG = 8;// declaration de la variable LED sur la broche 3


// Declaration of ethernet settings
// ---------------------------------------------------
byte mac[] = { 0x90, 0xA2, 0xDA, 0x10, 0x03, 0x2A }; // MAC adress of arduino card
byte ip[] = { 192, 168, 1, 102 }; // IP adress of arduino card
byte passerelle[] = { 192, 168, 1, 1 }; //Root's IP adress
byte masque[] = { 255, 255, 255, 0 }; // Mask adress network
EthernetServer serveurHTTP(80); // Creation of server object on port 80 (default HTTP port)
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
int nbCommands = 1;
char firstCharOfTag;
String tagOfFrame;

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
  // Initializes serial connection (115200 bauds) & ethernet connection
  // ------------------------------------------------------------------------
  Serial.begin(115200); 
  Ethernet.begin(mac, ip, passerelle, masque); 
  
  // Start server
  // ---------------------------
  serveurHTTP.begin();
 

  // Initailizes of I/O's arduino card
  // -------------------------------------------
  pinMode(22, OUTPUT); //LIG is an output
  digitalWrite(22, 1);
  pinMode(23, OUTPUT); //LIG is an output
  digitalWrite(23, 1);
  pinMode(24, OUTPUT); //LIG is an output
  digitalWrite(24, 1);
  pinMode(25, OUTPUT); //LIG is an output
  digitalWrite(25, 1);
  pinMode(26, OUTPUT); //LIG is an output
  pinMode(27, OUTPUT); //LIG is an output
  pinMode(28, OUTPUT); //LIG is an output
  pinMode(29, OUTPUT); //LIG is an output
  pinMode(30, OUTPUT); //LIG is an output
  
}




/* ----------------------------------------------------
  
  > FUNCTION void loop()
    <> input : null
    <> output : void
    -----------------------------------------
    
    This function is called each 30ms
    _____________________________________________
   
------------------------------------------------------- */
void loop(){
  
  // Locals variables
  // --------------------------------------------------
  char readBytesClient;


  
  /* ------------------------------------
      > begin of the function
  -------------------------------------- */

  
  // Check if the server work and listen the android application
  // ----------------------------------------------------------------
  if(!serveurHTTP.available())
  {
    return;
  }
  
  
  
  // Listen when android app send data on the server
  // -----------------------------------------------------------------
  if (serveurHTTP.available())
  {
    readBytesClient = client.read();
    
    // The message of the client begin at the 180th bytes of the frame
    // ---------------------------------------------------------------------
    if(comptClientBytes >= 181)
    {
      // Get all the frame of the client in a tab of char
      // -----------------------------------------------------------
      
      tabBytesClient[comptTabClientBytes] = readBytesClient;
      Serial.print(readBytesClient);
      
      // Save the fisrt char of the tag & get the tag
      // -------------------------------------------------
      if(comptTabClientBytes ==  2)
      {
        tagOfFrame = getTagOfFrame(tabBytesClient[comptTabClientBytes]);
      }
      
      
      // Count nb commands of the frame
      // -----------------------------------------------
      if(tabBytesClient[comptTabClientBytes] ==  ',')
      {
        nbCommands = nbCommands + 1;
      }
      
      // When we got all the frame record
      // ------------------------------------------------
      if(tabBytesClient[comptTabClientBytes] ==  '}')
      {
        
        // Send the frame the the devise we want tc command
        // ----------------------------------------
        if(tagOfFrame == "LIG")
        {
          updateMatriceOfCommand(0, 9);
        }
        
        if(tagOfFrame == "CUR")
        {
          updateMatriceOfCommand(10, 15);
        }
        
        if(tagOfFrame == "GAT")
        {
          updateMatriceOfCommand(16, 19);
        }
        
        if(tagOfFrame == "DOR")
        {
          updateMatriceOfCommand(20, 23);
        }
      }
      
      comptTabClientBytes = comptTabClientBytes + 1;
      

    }
    
    comptClientBytes = comptClientBytes + 1;
    
  }
  
}








/* ----------------------------------------------------
  
  > FUNCTION void getTagOfFrame()
    <> input : char - the first charactere of the tag of the frame
    <> output : String - the tag of the frame
    -----------------------------------------
    
    This function get the tag of the frame which the android app has sent
    _____________________________________________
   
------------------------------------------------------- */
String getTagOfFrame(char charTagOfFrame)
{
  if(charTagOfFrame == 'L')
  {
    return "LIG";
  }
  
  if(charTagOfFrame == 'C')
  {
    return "CUR";
  }
  
  if(charTagOfFrame == 'G')
  {
    return "GAT";
  }
  
  if(charTagOfFrame == 'D')
  {
    return "DOR";
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


