  /* Blink(LED)
   
   Turns on the built-in LED(Status LED) on for 0.1 second, then off for 0.1 second,
   repeatedly. BOARD_LED_PIN is defined previously, so just use it without declaration.
   BOARD_LED_PIN was connected to pin 16 in CM-900, but connected to pin 14 in OpenCM9.04.
  
                  Compatibility
  CM900                  O
  OpenCM9.04             O
  
   created 16 Nov 2012
   by ROBOTIS CO,.LTD.
   */
   
   //test en cours non concluant
   //#include <Servo.h> 
  #include <String.h>
  #define DXL_BUS_SERIAL1 1  //Dynamixel on Serial1(USART1)  <-OpenCM9.04
  
  Dynamixel Dxl(DXL_BUS_SERIAL1);
  
  //Servo srv;
  char messageRecu[5]; //longueur a changÃ© en fonction des besoins du dev qt
  boolean lightON = false;  //pour retenir l'etat des LED
  
  
  void setup() {
    // Set up the built-in LED pin as an output:
    Dxl.begin(3);  
    Dxl.jointMode(2/*TOCHANGE*/); //jointMode() is to use position mode
    pinMode(BOARD_LED_PIN, OUTPUT);  //toggleLED_Pin_Out  
    SerialUSB.attachInterrupt(usbInterrupt);
    pinMode(BOARD_LED_PIN, OUTPUT);  //toggleLED_Pin_Out
   
    //la position d'eveil deveras Ãªtre implÃ©mentÃ© ici
  }
  
  void usbInterrupt(byte* buffer, byte nCount){
  SerialUSB.print("nCount =");
  SerialUSB.println(nCount);
  switch(buffer[0]){
    case 'z' :
      AvancerDirection('z');
      break;
    case 'q' :
      AvancerDirection('q');
      break;
    case 's' :
      AvancerDirection('s');
      break;
    case 'd' :
      AvancerDirection('d');
      break;
    case 'f' :
      AllumerLED();
      break;
    case 'a' :
      SeTourner(false);
      break;
    case 'e' :
      SeTourner(true);
      break;
    case 'b' :
      //interrupt the processus
      break;
    default :  //RAS
      break; 
  }
  for(unsigned int i=0; i < nCount;i++)  //printf_SerialUSB_Buffer[N]_receive_Data
  SerialUSB.print((char)buffer[i]);
  SerialUSB.println("");
  SerialUSB.println("commande recu\n");
  
}
  
    void SeLever(){
    //TODO
    
    int repetition = -1;
    while(repetition++ < 4){
      Dxl.goalPosition(3*repetition + 1, 512);      
      //delay(500);
    }
    
    repetition = -1;
    
    while(repetition++ < 4){
       Dxl.goalPosition(3*repetition + 2, 400);
       //delay(600);
    }
    
    repetition = -1;
    
    while(repetition++ < 4){
       Dxl.goalPosition(3*repetition + 3, 100);
       //delay(650);
    }
  }
  
  void AllumerLED(){
    int count;
    if(lightON){
      for(count = 1; count<=12;count++){
        Dxl.ledOff(count);//All Dynamixel LED off
      }
    }
    else{
      for(count = 1; count<=12;count++){
        Dxl.ledOn(count);// All dynamixel LED on
      }
    }
    lightON = !lightON;
  }
  
  void AvancerDirection(char direction){
    int idDirectoin;
    switch(direction){  //determiner id cervo avant pour savoir dans quel direction aller (n % 12) + 1
      case 'z' :
        idDirectoin = 1;
        break;
      case 'q' : 
        idDirectoin = 4;
        break;
      case 'd' :
        idDirectoin = 10;
        break;
      case 's' :
        idDirectoin = 7;
        break;
      default :
        break;}
    SeLever();    //mettre les 4 cervos interne a moitié
                  //mettre les 4 vervos medianne en haut (800-900)
                  //mettre les 4 servos externe bas (100-200)
    int repetition = -1;
    while(repetition++ < 2){
      
      Dxl.goalPosition(6*repetition + 5, 500);
      Dxl.goalPosition(6*repetition + 4, 600);// on avance les bras latéral puis on deveras prendre appuie
      //mettre appuie sur  9 et 12 si on vas vers l'avant
    }
    
    //baisser 2cervos médian avant et arrière a -50
    //avancer les 2 pates de coté grace au cervos interne et externe
    //refaire la manip avec inversion sur l'axe x (id+=3 % 12)
  }
  
  void SeTourner(boolean tournerDroite){
    //dans un premierr temps mettre le centre d'appuie sur les 2 pates sur le coté
    //puis appliqué un mouvement de rame sur les deux pates avant
    //enfin une fois le travail terminé se remettre sur un equilibre stable
  }
  
  void ChangerVitesse(char vitesse){
    for(int i = 1; i <= 12; i++){
      Dxl.goalSpeed(i, vitesse);
    }
    char *reponse = strcpy(reponse,((char*)(int)vitesse));
    SerialUSB.println(*reponse);
  }

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  
  void loop() {
    //todo//
    //ne semble actuellement pas necessaire
  }
  
  
  

