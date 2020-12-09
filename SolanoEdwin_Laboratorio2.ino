/*
 * UTN_FICA_CITEl
 * sitemas embebidos 
 * laboratorio 2
 * Nombre: Solano Edwin
 * 
 * objetivo: realoj 
 *           configurar hora de analogo a digital
 *           juego de luces 
 *           activacion de sensores
 *      
 *funciones : libreria MsTimer2
 *            conversor map
 *            sensores 
 *            interrupciones attachInterupth
 * 
 */
 #include <MsTimer2.h>//llamar a libreria MsTimer dos
 #include<LiquidCrystal.h>//llamar a libreria de lcd
 LiquidCrystal lcd (13,12,11,10,9,8);//configuracion de pines lcd
   const int led1=4;//asignacion variable led 1 pin 4
   const int led2=5;//asignacion variable led 2 pin 5
   const int led3=6;//asignacion variable led 3 pin 6
   const int led4=7;//asignacion variable led 4 pin 7
   const int sensor1=A2;//asignacion variable a pin analogo sensor 1
   const int sensor2=A3;//asignacion variable a pin analogo sensor 2
   const int sensor3=A4;//asignacion variable a pin analogo sensor 3
   const int sensor4=A5;//asignacion variable a pin analogo sensor 4
         int btn1;//variable para boton 1 potenciometro analogo a digital horas
         int btn2;//variable para boton 2 potenciometro analogo a digital minutos
         int horas=0;//inicio variable contador horas
         int minutos=0;//inicio variable contador minutos
         int segundos=0;//inicio variable contador segundos 
         int cont;//contador para interrupciones
         int power=0;//inicio del sistema 
         int tiempo=0;//variable de tiempo espera
  void setup(){
    lcd.begin(16,4);//tamaño del lcd
    lcd.setCursor(0,0);//posicion del cursor en la lcd
    lcd.print("SolanoEdwinlab2");//mensaje de bienbenida en lcd
       
    pinMode(led1,OUTPUT);//pin 4 como salida
     pinMode(led2,OUTPUT);//pin 5 como salida
      pinMode(led3,OUTPUT);//pin 6 como salida
       pinMode(led4,OUTPUT);//pin 7 como salida
       Serial.begin(9600);//comunicacion CX
        attachInterrupt(0,activacion,LOW);//interrupciones inico
        attachInterrupt(1,contador,LOW);//interrucion contador   
  }
  void loop(){
    if(power==1){//encendido del sistema
      reloj();//llama al metodo reloj enciende 
    }
    if(cont==1){//interrupcion
      andigHoras();//llama al metodo configurar hora
    }
    if(cont==2){//interrupcion
      juegoLuces();//llama al metodo con juego de luces
    }
    if(cont==3){//interrupcion
      actSensor();//llama al metodo de sensores
    }
  }

  void activacion(){//interrucpcion activacion del sistema
    switch(power){//encendido
      case 0://primer caso mensaje de bienvenida en CX y LCD
      Serial.println("UTN-FICA-CITEL");//mensaje en CX
      Serial.println("Laboratorio 2");//mensaje en CX
      Serial.println("Solano Edwin");//mensaje en CX
      Serial.println("SELECCIONE EL MODO");//mensaje en CX
      lcd.clear();
      lcd.setCursor(0,1);//posicion del cursor en LCD
      lcd.print("INICIO SISTEMA");//mensaje en lcd
      power++;//contador de interrucpicones
      reloj();//inicio metodo relog
      break;
      case 1://interrucpcion de fin de prgama
      Serial.println("POWER OFF");//mensaje en CX
      cont=0;//reincio de variables
      power=0;//reinicio de variables
      minutos=0;//reinicio de variables
      horas=0;//reinicio de variables
      segundos=0;//reinicio de variables
      lcd.clear();//limpiar LCD
      lcd.setCursor(0,2);//posicion del cursor
      lcd.print("SISTEMA:apagado");//mensaje en LCD
      break;
    }
  }
  void contador(){//interrucpcion de conteo uso del progrma
    if(power==1){//incio sistema
      switch(cont){//contador para modo
        case 0://modo fijar hora
        Serial.println("FIJAR HORA");//mensaje en CX
        cont++;//aumento 
        break;
        case 1://modo juego de luces
        Serial.println("JUEGO DE LUCES");//mensaje en CX
        cont++;//aumento
        break;
        case 2://modo sistema de seguridad
        Serial.println("SISTEMA DE SEGURIDAD");//mensaje en CX
        actSensor();//llamar al metodo activar sensor
        cont++;//aumento
        break;
      }
    }
  }
  void reloj(){//metodo inicio de reloj
     MsTimer2::set(10,reloj);//inciiar reloj
      MsTimer2::start();//inicio reloj
    if(segundos<100)//conteo de reloj segundos minutos y horas
  segundos++;//contador segundos
  else{
    segundos=0;//reinicio
     if(minutos<60)
     
         minutos++;//contador minutos
       else{
       minutos=0;//reinicio
        if(horas<24)
        
           horas++;//contador horas
        else
        horas=0;//reinicio
       }
    }
    lcd.setCursor(0,3);//posicion en LCD
      lcd.print(String("HORA: ")+String(horas)+String(":")+String(minutos));//impresion en LCD anidados
    
  }
  void andigHoras(){//conversor de analogo digital para configurar hora
   
       btn1=analogRead(0);//leer el dato minutos
       btn1=map(btn1,0,1023,0,60);//conversion
       minutos=btn1;//asignacion de dato
       btn2=analogRead(1);//ler segundo dato horas
       btn2=map(btn2,0,1023,0,24);//conversion
       horas=btn2;//asignacion de dato 
    
  }
  void juegoLuces() {//metodo juego de luces
    tiempo++;//tiempo de encendido
    if(tiempo<200){//numero de veces igual a tiempo
      digitalWrite(led1,HIGH);//led encendido
      digitalWrite(led4,HIGH);//led encendido
      delay(100);//temporizador
      digitalWrite(led2,HIGH);//led encendido
      digitalWrite(led3,HIGH);//led encendido
      delay(100);//temporizador
      digitalWrite(led1,LOW);//led apagado
      digitalWrite(led4,LOW);//led apagado
      delay(100);//temporizador
      digitalWrite(led2,LOW);//led apagado
      digitalWrite(led3,LOW);//led apagado
      delay(100);//temporizador
      digitalWrite(led2,HIGH);//led encendido
      digitalWrite(led4,HIGH);//led encendido
      delay(100);//temporizador
      digitalWrite(led1,HIGH);//led encendido
      digitalWrite(led3,HIGH);//led encendido
      delay(100);//temporizador
      delay(100);//temporizador
      digitalWrite(led1,LOW);//led apagado
      digitalWrite(led2,LOW);//led apagado
      digitalWrite(led3,LOW);//led apagado
      digitalWrite(led4,LOW);//led apagado
      delay(100);  //temporizador    
    }
  }

  void actSensor(){//metodo para activar sensor
    if(digitalRead(sensor1)==HIGH){//leer sensor uno en alto imprimr en CX
      delay(200);//temporizador
      Serial.println("ALARMA sensor uno acivado");//mensaje en CX
    }
    else{
      Serial.println("sensor uno no activo");//mensaje en CX
    }
       if(digitalRead(sensor2)==HIGH){//leer sensor dos en alto imprimr en CX
         delay(200);//temporizador
      Serial.println("ALARMA sensor dos acivado");//mensaje en CX
    }
    else{
      Serial.println("sensor uno no activo");//mensaje en CX
    }
       if(digitalRead(sensor3)==HIGH){//leer sensor tres en alto imprimr en CX
         delay(200);//temporizador
      Serial.println("ALARMA sensor tres acivado");//mensaje en CX
    }
    else{
      Serial.println("sensor uno no activo");//mensaje en CX
    }
       if(digitalRead(sensor4)==HIGH){//leer sensor cuatro en alto imprimr en CX
         delay(200);//temporizador
      Serial.println("ALARMA sensor cuatro acivado");//mensaje en CX
    }
    else{
      Serial.println("sensor uno no activo");//mensaje en CX
    }
    delay(10000); //temporizador
  }
   
