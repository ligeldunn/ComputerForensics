//
//  StegoBreak.cpp
//  ASG6CompForensics
//
//  Created by Lucas Igel-Dunn on 3/15/19.
//  Copyright © 2019 Lucas Igel-Dunn. All rights reserved.
//

#include <iostream>

// Binary to dec function
unsigned int binaryToDecimal(std::string n)
{
    std::string num = n;
    unsigned int dec_value = 0;
    
    // Initializing base value to 1, i.e 2^0
    int base = 1;
    
    int len = num.length();
    for (int i=len-1;i>=0;i--)
    {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }
    
    return dec_value;
}
// Dec to binary function
unsigned int decToBinary(unsigned int n){
    
    unsigned int binaryNum[1000];
    int i = 0;
    
    while(n > 0){
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
    //for (int j = i - 1; j >= 0; j--){
    //  std::cout << binaryNum[j];
    // }
    
    unsigned int temp = binaryNum[0];
    return temp;
    
    
}
// Two channel function
void twoChannels(unsigned int image[][3],int x, int x1,char *tmp,int num){
    FILE *ftemp;
    
    
    // Array to capture LSB
    unsigned int LSB[524288];
    int y = 511;
    int z = 0;
    unsigned int temp1 = 0;
    int count = 0;
    while(y < 262144){
        
        
        // For loop to obtain LSB's
        for(int i = y; i >= z; i--){
           
            temp1 = image[i][x];
            temp1 = decToBinary(temp1);
            LSB[count] = temp1;
            count++;
            
           
            temp1 = image[i][x1];
            temp1 = decToBinary(temp1);
            LSB[count] = temp1;
            count++;
            
            
        }
        z = y + 1;
        y = y += 512;
        
    }
   

    
    std::string test1 = std::to_string(LSB[0]) +  std::to_string(LSB[1])+  std::to_string(LSB[2]) + std::to_string(LSB[3])+ std::to_string(LSB[4])+  std::to_string(LSB[5])+ std::to_string(LSB[6])+ std::to_string(LSB[7]);
    unsigned int tester1 = 0;
    // 1st char
    tester1 = binaryToDecimal(test1);
    
    std::string test2 = std::to_string(LSB[8]) +  std::to_string(LSB[9])+  std::to_string(LSB[10]) + std::to_string(LSB[11])+ std::to_string(LSB[12])+  std::to_string(LSB[13])+ std::to_string(LSB[14])+ std::to_string(LSB[15]);
    unsigned int tester2 = 0;
    // 2nd char
    tester2 = binaryToDecimal(test2);
    
    std::string test3 = std::to_string(LSB[16]) +  std::to_string(LSB[17])+  std::to_string(LSB[18]) + std::to_string(LSB[19])+ std::to_string(LSB[20])+  std::to_string(LSB[21])+ std::to_string(LSB[22])+ std::to_string(LSB[23]);
    unsigned int tester3 = 0;
    // 3rd char
    tester3 = binaryToDecimal(test3);
    
    std::string test4 = std::to_string(LSB[24]) +  std::to_string(LSB[25])+  std::to_string(LSB[26]) + std::to_string(LSB[27])+ std::to_string(LSB[28])+  std::to_string(LSB[29])+ std::to_string(LSB[30])+ std::to_string(LSB[31]);
    unsigned int tester4 = 0;
    // 4th char
    tester4 = binaryToDecimal(test4);
    
    std::string test5 = std::to_string(LSB[32]) +  std::to_string(LSB[33])+  std::to_string(LSB[34]) + std::to_string(LSB[35])+ std::to_string(LSB[36])+  std::to_string(LSB[37])+ std::to_string(LSB[38])+ std::to_string(LSB[39]);
    unsigned int tester5 = 0;
    // 5th char
    tester5 = binaryToDecimal(test5);
    
    std::string test6 = std::to_string(LSB[40]) +  std::to_string(LSB[41])+  std::to_string(LSB[42]) + std::to_string(LSB[43])+ std::to_string(LSB[44])+  std::to_string(LSB[45])+ std::to_string(LSB[46])+ std::to_string(LSB[47]);
    unsigned int tester6 = 0;
    // 6th char
    tester6 = binaryToDecimal(test6);
    
    std::string test7 = std::to_string(LSB[48]) +  std::to_string(LSB[49])+  std::to_string(LSB[50]) + std::to_string(LSB[51])+ std::to_string(LSB[52])+  std::to_string(LSB[53])+ std::to_string(LSB[54])+ std::to_string(LSB[55]);
    unsigned int tester7 = 0;
    // 7th char
    tester7 = binaryToDecimal(test7);
    
    
    std::string test8 = std::to_string(LSB[56]) +  std::to_string(LSB[57])+  std::to_string(LSB[58]) + std::to_string(LSB[59])+ std::to_string(LSB[60])+  std::to_string(LSB[61])+ std::to_string(LSB[62])+ std::to_string(LSB[63]);
    unsigned int tester8 = 0;
    // 8th char
    tester8 = binaryToDecimal(test8);
    
    // Check for file signatures
    if(tester1 == 255 && tester2 == 216 && tester3 == 255){
        char buffer[16];
        snprintf(buffer, sizeof(buffer), "lena%d-%s.jpg", num,tmp);
        ftemp = fopen(buffer, "wb");
        
        
    }else if(tester1 == 66 && tester2 == 77){
        
        char buffer[16];
        snprintf(buffer, sizeof(buffer), "lena%d-%s.bmp", num,tmp);
        ftemp = fopen(buffer, "wb");
        
    }else if(tester1 == 80 && tester2 == 75 && tester3 == 3 && tester4 == 4 && tester5 == 20 && tester6 == 0 && tester7 == 6 && tester8 == 0){
        
        char buffer[16];
        snprintf(buffer, sizeof(buffer), "lena%d-%s.docx",num,tmp);
        ftemp = fopen(buffer, "wb");
        
    }else if(tester1 == 37 && tester2 == 80 && tester3 == 68 && tester4 == 70){
        
        char buffer[16];
        snprintf(buffer, sizeof(buffer), "lena%d-%s.pdf", num,tmp);
        ftemp = fopen(buffer, "wb");
        
    }else if(tester1 == 73 && tester2 == 68 && tester3 == 51){
        
        char buffer[16];
        snprintf(buffer, sizeof(buffer), "lena%d-%s.mp3", num,tmp);
        ftemp = fopen(buffer, "wb");
        
    }else{
        
        return;
    }
    
    
    unsigned int counter = 0;
    
    for(int i = 0; i < 524288; i+=8){
        
        // Every 8 bits turn into character
        std::string test = std::to_string(LSB[counter]) +  std::to_string(LSB[counter+1])+  std::to_string(LSB[counter+2]) + std::to_string(LSB[counter+3])+ std::to_string(LSB[counter+4])+  std::to_string(LSB[counter+5])+ std::to_string(LSB[counter+6])+ std::to_string(LSB[counter+7]);
        
        
        counter = counter + 8;
        unsigned int tester = 0;
        tester = binaryToDecimal(test);
        unsigned char conversion = tester;
        // Write char to file
        fwrite(&conversion,1, 1,ftemp);
   
        
        
    }
    fclose(ftemp);
    
}

// One channel function
void oneChannel(unsigned int image[][3],int x,char *tmp,int num){
    FILE *ftemp;
  
    // Array to capture LSB
    unsigned int LSB[262144];
    int y = 511;
    int z = 0;
    unsigned int temp1 = 0;
    int count = 0;
    while(y < 262144){
        
        
        // For loop to obtain LSB's
        for(int i = y; i >= z; i--){
            
            
            temp1 = image[i][x];
            temp1 = decToBinary(temp1);
            LSB[count] = temp1;
            count++;
            
           
            
            
        }
        z = y + 1;
        y = y += 512;
        
    }
    
    std::string test1 = std::to_string(LSB[0]) +  std::to_string(LSB[1])+  std::to_string(LSB[2]) + std::to_string(LSB[3])+ std::to_string(LSB[4])+  std::to_string(LSB[5])+ std::to_string(LSB[6])+ std::to_string(LSB[7]);
    unsigned int tester1 = 0;
    // 1st char
    tester1 = binaryToDecimal(test1);
    
    std::string test2 = std::to_string(LSB[8]) +  std::to_string(LSB[9])+  std::to_string(LSB[10]) + std::to_string(LSB[11])+ std::to_string(LSB[12])+  std::to_string(LSB[13])+ std::to_string(LSB[14])+ std::to_string(LSB[15]);
    unsigned int tester2 = 0;
    // 2nd char
    tester2 = binaryToDecimal(test2);
    
    std::string test3 = std::to_string(LSB[16]) +  std::to_string(LSB[17])+  std::to_string(LSB[18]) + std::to_string(LSB[19])+ std::to_string(LSB[20])+  std::to_string(LSB[21])+ std::to_string(LSB[22])+ std::to_string(LSB[23]);
    unsigned int tester3 = 0;
    // 3rd char
    tester3 = binaryToDecimal(test3);
    
    std::string test4 = std::to_string(LSB[24]) +  std::to_string(LSB[25])+  std::to_string(LSB[26]) + std::to_string(LSB[27])+ std::to_string(LSB[28])+  std::to_string(LSB[29])+ std::to_string(LSB[30])+ std::to_string(LSB[31]);
    unsigned int tester4 = 0;
    // 4th char
    tester4 = binaryToDecimal(test4);
    
    std::string test5 = std::to_string(LSB[32]) +  std::to_string(LSB[33])+  std::to_string(LSB[34]) + std::to_string(LSB[35])+ std::to_string(LSB[36])+  std::to_string(LSB[37])+ std::to_string(LSB[38])+ std::to_string(LSB[39]);
    unsigned int tester5 = 0;
    // 5th char
    tester5 = binaryToDecimal(test5);
    
    std::string test6 = std::to_string(LSB[40]) +  std::to_string(LSB[41])+  std::to_string(LSB[42]) + std::to_string(LSB[43])+ std::to_string(LSB[44])+  std::to_string(LSB[45])+ std::to_string(LSB[46])+ std::to_string(LSB[47]);
    unsigned int tester6 = 0;
    // 6th char
    tester6 = binaryToDecimal(test6);
    
    std::string test7 = std::to_string(LSB[48]) +  std::to_string(LSB[49])+  std::to_string(LSB[50]) + std::to_string(LSB[51])+ std::to_string(LSB[52])+  std::to_string(LSB[53])+ std::to_string(LSB[54])+ std::to_string(LSB[55]);
    unsigned int tester7 = 0;
    // 7th char
    tester7 = binaryToDecimal(test7);
    
    
    std::string test8 = std::to_string(LSB[56]) +  std::to_string(LSB[57])+  std::to_string(LSB[58]) + std::to_string(LSB[59])+ std::to_string(LSB[60])+  std::to_string(LSB[61])+ std::to_string(LSB[62])+ std::to_string(LSB[63]);
    unsigned int tester8 = 0;
    // 8th char
    tester8 = binaryToDecimal(test8);
    
    // Check for file signatures
    if(tester1 == 255 && tester2 == 216 && tester3 == 255){
        char buffer[16];
        snprintf(buffer, sizeof(buffer), "lena%d-%s.jpg", num,tmp);
        ftemp = fopen(buffer, "wb");
        
        
    }else if(tester1 == 66 && tester2 == 77){
        
        char buffer[16];
        snprintf(buffer, sizeof(buffer), "lena%d-%s.bmp", num,tmp);
        ftemp = fopen(buffer, "wb");
        
    }else if(tester1 == 80 && tester2 == 75 && tester3 == 3 && tester4 == 4 && tester5 == 20 && tester6 == 0 && tester7 == 6 && tester8 == 0){
        
        char buffer[16];
        snprintf(buffer, sizeof(buffer), "lena%d-%s.docx", num,tmp);
        ftemp = fopen(buffer, "wb");
        
    }else if(tester1 == 37 && tester2 == 80 && tester3 == 68 && tester4 == 70){
        
        char buffer[16];
        snprintf(buffer, sizeof(buffer), "lena%d-%s.pdf", num,tmp);
        ftemp = fopen(buffer, "wb");
        
    }else if(tester1 == 73 && tester2 == 68 && tester3 == 51){
        
        char buffer[16];
        snprintf(buffer, sizeof(buffer), "lena%d-%s.mp3", num,tmp);
        ftemp = fopen(buffer, "wb");
        
    }else{
        
        return;
    }
    
    
    
    
    
    unsigned int counter = 0;
    
    for(int i = 0; i < 262144; i+=8){

        // every 8 bits turn into character
        std::string test = std::to_string(LSB[counter]) +  std::to_string(LSB[counter+1])+  std::to_string(LSB[counter+2]) + std::to_string(LSB[counter+3])+ std::to_string(LSB[counter+4])+  std::to_string(LSB[counter+5])+ std::to_string(LSB[counter+6])+ std::to_string(LSB[counter+7]);
        
        
        counter = counter + 8;
        unsigned int tester = 0;
        tester = binaryToDecimal(test);
        unsigned char conversion = tester;
        // Write char to file
        fwrite(&conversion,1, 1,ftemp);
        
        
        
    }
    fclose(ftemp);
 
    
}
// Three channel function
void threeChannels(unsigned int image[][3],int x, int x1, int x2,char *tmp,int num){
    FILE *ftemp;
    
    // Array to capture LSB
    unsigned int LSB[786432];
    int y = 511;
    int z = 0;
    unsigned int temp1 = 0;
    int count = 0;
    while(y < 262144){
        
       
        
        // For loop to obtain LSB's
        for(int i = y; i >= z; i--){
            
            temp1 = image[i][x];
            temp1 = decToBinary(temp1);
            LSB[count] = temp1;
            count++;
            
            temp1 = image[i][x1];
            temp1 = decToBinary(temp1);
            LSB[count] = temp1;
            count++;
            
            
            temp1 = image[i][x2];
            temp1 = decToBinary(temp1);
            LSB[count] = temp1;
            count++;
            
            
        }
        z = y + 1;
        y = y += 512;
        
    }
    
    std::string test1 = std::to_string(LSB[0]) +  std::to_string(LSB[1])+  std::to_string(LSB[2]) + std::to_string(LSB[3])+ std::to_string(LSB[4])+  std::to_string(LSB[5])+ std::to_string(LSB[6])+ std::to_string(LSB[7]);
    unsigned int tester1 = 0;
    // 1st char
    tester1 = binaryToDecimal(test1);
    
    std::string test2 = std::to_string(LSB[8]) +  std::to_string(LSB[9])+  std::to_string(LSB[10]) + std::to_string(LSB[11])+ std::to_string(LSB[12])+  std::to_string(LSB[13])+ std::to_string(LSB[14])+ std::to_string(LSB[15]);
    unsigned int tester2 = 0;
    // 2nd char
    tester2 = binaryToDecimal(test2);
    
    std::string test3 = std::to_string(LSB[16]) +  std::to_string(LSB[17])+  std::to_string(LSB[18]) + std::to_string(LSB[19])+ std::to_string(LSB[20])+  std::to_string(LSB[21])+ std::to_string(LSB[22])+ std::to_string(LSB[23]);
    unsigned int tester3 = 0;
    // 3rd char
    tester3 = binaryToDecimal(test3);
    
    std::string test4 = std::to_string(LSB[24]) +  std::to_string(LSB[25])+  std::to_string(LSB[26]) + std::to_string(LSB[27])+ std::to_string(LSB[28])+  std::to_string(LSB[29])+ std::to_string(LSB[30])+ std::to_string(LSB[31]);
    unsigned int tester4 = 0;
    // 4th char
    tester4 = binaryToDecimal(test4);
    
    std::string test5 = std::to_string(LSB[32]) +  std::to_string(LSB[33])+  std::to_string(LSB[34]) + std::to_string(LSB[35])+ std::to_string(LSB[36])+  std::to_string(LSB[37])+ std::to_string(LSB[38])+ std::to_string(LSB[39]);
    unsigned int tester5 = 0;
    // 5th char
    tester5 = binaryToDecimal(test5);
    
    std::string test6 = std::to_string(LSB[40]) +  std::to_string(LSB[41])+  std::to_string(LSB[42]) + std::to_string(LSB[43])+ std::to_string(LSB[44])+  std::to_string(LSB[45])+ std::to_string(LSB[46])+ std::to_string(LSB[47]);
    unsigned int tester6 = 0;
    // 6th char
    tester6 = binaryToDecimal(test6);
    
    std::string test7 = std::to_string(LSB[48]) +  std::to_string(LSB[49])+  std::to_string(LSB[50]) + std::to_string(LSB[51])+ std::to_string(LSB[52])+  std::to_string(LSB[53])+ std::to_string(LSB[54])+ std::to_string(LSB[55]);
    unsigned int tester7 = 0;
    // 7th char
    tester7 = binaryToDecimal(test7);
    
    
    std::string test8 = std::to_string(LSB[56]) +  std::to_string(LSB[57])+  std::to_string(LSB[58]) + std::to_string(LSB[59])+ std::to_string(LSB[60])+  std::to_string(LSB[61])+ std::to_string(LSB[62])+ std::to_string(LSB[63]);
    unsigned int tester8 = 0;
    // 8th char
    tester8 = binaryToDecimal(test8);
    
    // Check for file signatures
    
    if(tester1 == 255 && tester2 == 216 && tester3 == 255){
        char buffer[16];
        snprintf(buffer, sizeof(buffer), "lena%d-%s.jpg", num,tmp);
        ftemp = fopen(buffer, "wb");
        
        
    }else if(tester1 == 66 && tester2 == 77){
        
        char buffer[16];
        snprintf(buffer, sizeof(buffer), "lena%d-%s.bmp", num,tmp);
        ftemp = fopen(buffer, "wb");
        
    }else if(tester1 == 80 && tester2 == 75 && tester3 == 3 && tester4 == 4 && tester5 == 20 && tester6 == 0 && tester7 == 6 && tester8 == 0){
        
        char buffer[16];
        snprintf(buffer, sizeof(buffer), "lena%d-%s.docx", num,tmp);
        ftemp = fopen(buffer, "wb");
        
    }else if(tester1 == 37 && tester2 == 80 && tester3 == 68 && tester4 == 70){
        
        char buffer[16];
        snprintf(buffer, sizeof(buffer), "lena%d-%s.pdf", num,tmp);
        ftemp = fopen(buffer, "wb");
        
    }else if(tester1 == 73 && tester2 == 68 && tester3 == 51){
        
        char buffer[16];
        snprintf(buffer, sizeof(buffer), "lena%d-%s.mp3", num,tmp);
        ftemp = fopen(buffer, "wb");
        
    }else{
        return;
    }
    unsigned int counter = 0;
    
    for(int i = 0; i < 786432; i+=8){
        // every 8 bits turn into character
        std::string test = std::to_string(LSB[counter]) +  std::to_string(LSB[counter+1])+  std::to_string(LSB[counter+2]) + std::to_string(LSB[counter+3])+ std::to_string(LSB[counter+4])+  std::to_string(LSB[counter+5])+ std::to_string(LSB[counter+6])+ std::to_string(LSB[counter+7]);
        
        
        counter = counter + 8;
        unsigned int tester = 0;
        tester = binaryToDecimal(test);
        unsigned char conversion = tester;
         // Write char to file
        fwrite(&conversion,1, 1,ftemp);
       
        
        
    }
    fclose(ftemp);
 
}


int main(int argc, const char * argv[]) {
    
    // Loop through arguments
    int counterr = 0;
    for(int i = 1; i < 8; i++){
    FILE *f = fopen(argv[i], "rb");
    
    
    if(f == NULL){
        
        printf("file %s cant be opened\n", "unalloc.img");
        exit(0);
        }else{
        printf("file %s opened\n", "unalloc.img" );
        }
   
    printf("\n");

    
    // Width x height
    unsigned int image[262144][3];
    
    // Seek through header
    fseek(f,54,SEEK_SET);
    unsigned int temp = 0;

    // Get pixel bit map from bmp
    for(int i = 262143; i >= 0; i--){
        
        //b
        image[i][2] = getc(f);
        temp = image[i][2];
        temp = decToBinary(temp);
      
        //g
        image[i][1] = getc(f);
        temp = image[i][1];
        temp = decToBinary(temp);
        
        //r
        image[i][0] = getc(f);
       
        // r g b print
        //printf("pixel %d : [%d,%d,%d]\n",i+1,image[i][0],image[i][1],image[i][2]);
        
        
        
    }
  
    // red channel = 0, green = 1, blue = 2
  
    char *red = "r";
    char *green = "g";
    char *blue = "b";
    
    char *rb = "rb";
    char *rg= "rg";
    char *br = "br";
    char *bg = "bg";
    char *gr = "gr";
    char *gb = "gb";
        
    char* rgb = "rgb";
    char* rbg = "rbg";
    char* gbr = "gbr";
    char* grb = "grb";
    char* bgr = "bgr";
    char* brg = "brg";
    
   
    // Call to channel functions
    
    twoChannels(image,0,1,rg,counterr);

    twoChannels(image,1,0,gr,counterr);

    twoChannels(image,2,1,bg,counterr);

    twoChannels(image,1,2,gb,counterr);

    twoChannels(image,2,0,br,counterr);
  
    twoChannels(image,0,2,rb,counterr);
  
   
    oneChannel(image,0,red,counterr);

    oneChannel(image,1,green,counterr);
   
    oneChannel(image,2,blue,counterr);
        
    
    threeChannels(image, 0,1,2, rgb,counterr);

    threeChannels(image, 0,2,1, rbg,counterr);

    threeChannels(image, 1,2,0,gbr,counterr);

    threeChannels(image, 1,0,2, grb,counterr);
    
    threeChannels(image, 2,1,0, bgr,counterr);
   
    threeChannels(image, 2,0,1,brg,counterr);
    
 
    counterr++;
    fclose(f);

    
    }
   
    return 0;
}
