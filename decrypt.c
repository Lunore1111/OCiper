#include<stdio.h>
#include<inttypes.h>
#include<stdlib.h>

#define SUCCESS_TOKEN 1

int main(int argc,char* argv[])
{
  if(argc < 3)
  {
    printf("pls pass encryted file and the key");
    return -1;
  }
   

     FILE* read_encrypted_file = fopen(argv[1],"rb");
      if(read_encrypted_file == nullptr)
      {
        printf("encrypted file cant be open");
        return -1;
      }
      fseek(read_encrypted_file,0,SEEK_END);
      u_int64_t size = ftell(read_encrypted_file);
      rewind(read_encrypted_file);

      u_int8_t*  encrypted_file_buffer = malloc(size);
      
       fread(encrypted_file_buffer,1,size,read_encrypted_file);

       fclose(read_encrypted_file);

       FILE* read_key = fopen(argv[2],"rb");
       if(read_key == nullptr)
       {
        printf("cant read key");
        free(encrypted_file_buffer);
        return -1;
       }
       uint8_t* key_buffer = malloc(size);
       fread(key_buffer,1,size,read_key);
       fclose(read_key);
        
       uint8_t* decrypted_buffer = malloc(size);

       for(uint64_t i = 0;i < size;i++)
       {
    decrypted_buffer[i] = (encrypted_file_buffer[i] - key_buffer[i] + 256) % 256;
       }        
      
       if(decrypted_buffer[size+1] = SUCCESS_TOKEN) 
       {
        printf("bingo");
        
        FILE* generate_file = fopen("decrypted.png","wb");
        if(generate_file == nullptr)
        {
         printf("cant open decrypted file.png");
           
       free(encrypted_file_buffer);
       free(key_buffer);
       free(decrypted_buffer); 
        return -1;
        } 
        fwrite(decrypted_buffer,1,size,generate_file);
        fclose(generate_file);
      
       }
       
       else
       {
        printf("you messed up in success token");
       }

       free(encrypted_file_buffer);
       free(key_buffer);
       free(decrypted_buffer);
       
}