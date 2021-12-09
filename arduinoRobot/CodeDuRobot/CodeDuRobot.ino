/* Minimum_Source*/
#include <String.h>  
#include <stdlib.h>
#define DXL_BUS_SERIAL1 1  //Dynamixel on Serial1(USART1)  <-OpenCM9.04
  
  Dynamixel Dxl(DXL_BUS_SERIAL1);
  
  //Servo srv;
  char messageRecu[5]; //longueur a changÃ© en fonction des besoins du dev qt
  boolean lightON = false;  //pour retenir l'etat des LED

void setup() {
    Dxl.begin(3);  
    Dxl.jointMode(2/*TOCHANGE*/); //jointMode() is to use position mode
    pinMode(BOARD_LED_PIN, OUTPUT);  //toggleLED_Pin_Out  
    SerialUSB.attachInterrupt(usbInterrupt);

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
    case 'v':
      SeLever();
      break;
    case 'w' :  //a revoir, methodedangereuse qui rends l e obot non receptif
      SeCoucher();
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
  word SyncPage1[36]=
    { 
    1,512,100,
    4,512,100,  // 3 Dynamixels are move to position 0
    7,512,100,  // with velocity 100
    10,512,100,
    2,400,100,
    5,400,100,  // 3 Dynamixels are move to position 0
    8,400,100,  // with velocity 100
    11,400,100,
    3,100,100,
    6,100,100,  // 3 Dynamixels are move to position 0
    9,100,100,  // with velocity 100
    12,100,100};
    Dxl.syncWrite(30,2,SyncPage1,36);
    delay(500);
  }
  
  void SeCoucher(){
  word SyncPage1[36]=
    { 
    1,512,100,
    4,512,100,  // 3 Dynamixels are move to position 0
    7,512,100,  // with velocity 100
    10,512,100,
    2,200,100,
    5,200,100,  // 3 Dynamixels are move to position 0
    8,200,100,  // with velocity 100
    11,200,100,
    3,200,100,
    6,200,100,  // 3 Dynamixels are move to position 0
    9,200,100,  // with velocity 100
    12,200,100};
    Dxl.syncWrite(30,2,SyncPage1,36);
    delay(500);
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
        Dxl.ledOn(count);// All dynamixel LED onz
      }
    }
    lightON = !lightON;
  }
  
  void AvancerDirection(char direction){
    //ecrire une methode pour chaque axe serait lourd mais tres facile, je recherche une methode pour factoriser cela
    /*int idDirectoin;
    switch(direction){  //determiner id cervo avant pour savoir dans quel direction aller (n % 12) + mais pb si n = 12 on auras l'id 1 (ce n'est pas ce qui est voulu)
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
        break;}*/
    SeLever();    
    //pas opti en mémoire mais très utile pour tout faire d'un coup
    word SyncPageDebut[16]=
    { 
    2,450,100,
    8,450,100,  // 4 Dynamixels are move to needed postion
    7,400,100,
    1,600,100};
    Dxl.syncWrite(30,2,SyncPageDebut,16);
    delay(1000);
    
    word SyncPage1[16]=
    { 
    5,500,100,
    11,500,100,  // 4 Dynamixels are move to needed postion
    4,600,100,
    10,600,100};
    Dxl.syncWrite(30,2,SyncPage1,16);
    delay(500);
    
    word SyncPage2[16]=
    { 
    12,100,100,
    9,100,100,  // 4 Dynamixels are move to needed postion
    7,800,100,
    1,400,100};
    Dxl.syncWrite(30,2,SyncPage2,16);
    delay(500);
  }
  
  void SeTourner(boolean tournerDroite){
    //dans un premierr temps mettre le centre d'appuie sur les 2 pates sur le coté
    //puis appliqué un mouvement de rame sur les deux pates avant
    //enfin une fois le travail terminé se remettre sur un equilibre stable
  }
  
  void ChangerVitesse(unsigned char vitesse){  //methode dangereuse, blocante en l'état
    for(int i = 1; i <= 12; i++){
      Dxl.goalSpeed(i, vitesse);
    }
    char *reponse = strcpy(reponse,((char*)(int)vitesse));
    SerialUSB.println(*reponse);
  }

void loop() {
  // put your main code here, to run repeatedly: 
}

