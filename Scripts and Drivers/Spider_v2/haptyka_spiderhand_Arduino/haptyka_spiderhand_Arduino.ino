const int arraySize = 3; // Liczba elementów w tablicy
String myArray[arraySize];  // Tablica na przechowywanie ciągów znaków

int f1=0;
int f2=0;
int f3=0;

int on=0;
int off=0;

void setup() {
  Serial.begin(9600); // Inicjalizacja portu szeregowego
  pinMode(14,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
}

void loop() {

  if (Serial.available() > 0) { // Sprawdzenie dostępności danych w porcie szeregowym
    String input = Serial.readStringUntil('\n'); // Odczyt danych do momentu napotkania znaku nowej linii

    // Wydrukuj odczytane dane
    Serial.print("Otrzymano dane: ");
    Serial.println(input);

    // Przypisz dane do tablicy
    parseAndAssign(input);

    // Wydrukuj zawartość tablicy
    printArray();
    if(myArray[0]=="L1"){f1=0;}
    if(myArray[0]=="H1"){f1=1;}
    if(myArray[0]=="L2"){f2=0;}
    if(myArray[0]=="H2"){f2=1;}
    if(myArray[0]=="L3"){f3=0;}
    if(myArray[0]=="H3"){f3=1;}

    on=myArray[1].toInt();
    off=myArray[2].toInt();
  }

  if(f1==1) {
    analogWrite(14,on);
  }

    if(f1==0) {
    digitalWrite(14,LOW);
  }

  if(f2==1) {
    analogWrite(12,on);
  }

    if(f2==0) {
    digitalWrite(12,LOW);
  }

    if(f3==1) {
    analogWrite(13,on);
  }

    if(f3==0) {
    digitalWrite(13,LOW);
  }




}

void parseAndAssign(String data) {
  char *token = strtok((char *)data.c_str(), ","); // Rozdziel dane według przecinków

  for (int i = 0; i < arraySize; i++) {
    if (token != NULL) {
      myArray[i] = String(token); // Przypisz token do tablicy stringów
      token = strtok(NULL, ",");
    } else {
      // Jeżeli brak więcej danych, przerwij pętlę
      break;
    }
  }
}

void printArray() {
  // Wydrukuj zawartość tablicy
  Serial.print("Zawartosc tablicy: ");
  for (int i = 0; i < arraySize; i++) {
    Serial.print(myArray[i]);
    Serial.print(" ");
  }
  Serial.println();
}
