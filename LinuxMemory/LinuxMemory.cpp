//
//  main.cpp
//  ASG4
//
//  Created by Lucas Igel-Dunn on 2/22/19.
//  Copyright © 2019 Lucas Igel-Dunn. All rights reserved.
//

#include <iostream>
#include <cstdio>

// Function for VMZ calculation
void vmz(FILE *f,unsigned long offset){
    
    // Totalvmz variable
    unsigned long totalvmz = 0;
    
    // Address of 1st virtual memory descriptor
    fseek(f,offset + 132, SEEK_SET);
    unsigned long num = 0;
    fread(&num,1,4,f);
    // If 0 just print 0 for VMZ
    if(num == 0){
        std::cout << "VMZ: " << "0";
        std::cout << "\n";
    }
    // If not 0.....
    if(num != 0){
    num = num - 3221225472;
    
    // 1st virtual memory descriptor
    fseek(f, num, SEEK_SET);
    unsigned long num1 = 0;
    fread(&num1,1,4,f);
    // Check for non zero VMZ's
    if(num1 != 0){
    
    num1 = num1 - 3221225472;
    
    // Loop through virtual memory areas of process to find VMZ
    while(num1 != 0){
    
    // First Address
    fseek(f, num1 + 4, SEEK_SET);
    unsigned long faddress = 0;
    fread(&faddress, 1,4,f);
    
 
    // Second Address
    fseek(f,num1 + 8, SEEK_SET);
    unsigned long saddress = 0;
    fread(&saddress,1,4,f);
    

   // Memory Address of the next virtual memory area
    fseek(f, num1 + 12, SEEK_SET);
    unsigned long nextloc = 0;
    fread(&nextloc, 1, 4, f);
        if(nextloc == 0){
            
        }else{
            nextloc = nextloc - 3221225472;
        }
    
    // Update offset(num1)
    num1 = 0;
    num1 = nextloc;
    
    // Add up VMZ's
    totalvmz += saddress - faddress;
    
    }
    // Convert to KB
    totalvmz = totalvmz/1000;
   
    std::cout << "VMZ: " << std::dec <<  totalvmz;
    std::cout << "\n";
    }
    }
    
}

// Function to Print tasks
void task(long number){
    
    unsigned long task = 0;
    task = number + 3221225472;
    std::cout << "Task: " << std::hex << task;
    
    std::cout << "\n";
}
// Function to Print PID, PPID, UID, TASK and COMM
void process(FILE *f, long offset){

    // For loop that goes through all the proccesses
    for(long i = 0; i < 89; i++){
   
        // Get PID
        fseek(f,offset + 168,SEEK_SET);
        unsigned long num = 0;
        fread(&num,1, 4, f);
    
        std::cout <<  "PID: " << std::dec << num;
        std::cout << "\n";
        
    
        // Get PPID
        fseek(f,offset + 176, SEEK_SET);
        unsigned long num1 = 0;
        fread(&num1,1,4,f);
        num1 = num1 - 3221225472;
        fseek(f, num1 + 168, SEEK_SET);
        unsigned long num2 = 0;
        fread(&num2,1,4,f);
        
        std::cout << "PPID: " << std::dec << num2;
        std::cout << "\n";

        // Get UID
        fseek(f,offset + 332,SEEK_SET);
        unsigned long num3 = 0;
        fread(&num3, 1, 4, f);
        
        std::cout << "UID: "  << std::dec << num3;
        std::cout << "\n";
        
        // Call to VMZ function
        vmz(f,offset);
        // Call to TASK function
        task(offset);
        
        // Get COMM
        fseek(f,offset + 404,SEEK_SET);
        char num4 = 0;
        fread(&num4, 1, 16, f);
        
        std::cout << "Comm: " << &num4;
        std::cout << "\n";
        
        // Get next process
        fseek(f,offset + 124, SEEK_SET);
        unsigned long placer = 0;
        fread(&placer , 1, 4, f);
        placer = placer - 3221225472;
        placer = placer - 124;
        
        // Go to next offset
        offset = placer;
        std::cout << "\n";
    }
    
}
int main(int argc, const char * argv[]) {
    
    // Prepare File
    FILE *fin;
    fin = fopen("challenge.mem", "rb");
    if(fin == 0){
        perror("fopen");
        exit(1);
    }
    
    // Offset for first process descriptor
    process(fin,6687680);
    
    // Close file
    fclose(fin);
    
    return 0;
}
