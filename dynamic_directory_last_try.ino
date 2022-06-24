#include <SdFat.h>
#include <SdFatConfig.h>
const uint8_t chipSelect = 10;
SdFat sd1;
SdFile root;
SdFile file;
SdFile dir;

void setup()
{
  Serial.begin(9600);
  delay(100);
  if (!sd1.begin(chipSelect)) {
    sd1.initErrorHalt(&Serial);
  }
  // Open root directory
  if (!dir.open("/")){
    sd1.errorHalt("dir.open failed");
  }
  char name_of_file[30]={0};
  char list_of_file[20][30]={0};
  int i=0; 
  int j=0;
  while (file.openNext(&dir, O_RDONLY)) {
    if (file.isFile())
    {
      //it is a file
      file.getName(name_of_file,26);
      strcpy(list_of_file[j], name_of_file);
      j++;
    }
    file.close();
  }
    Serial.println("printing list of files only");
    i=0;
    while(i<=19){
    if(list_of_file[i][0]=='\0')
    {
      Serial.println("no more files");
      break;
    }
    Serial.println(list_of_file[i]);
    i++;
    }
    i=0;

    Serial.println("before adding files in list, here is the first file name:");
    Serial.println(list_of_file[0]);
    while(i<=19){
    if(list_of_file[i][0]=='\0'){
      Serial.println("no more files");
      break;
    }
    i++;
    j++;
    }  
  }  
void loop(){}
