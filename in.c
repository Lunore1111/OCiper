#include<stdio.h>
#include<inttypes.h>
#include<stdlib.h>
#include<time.h>
int main()
{
 
    int correct = 0;

    srand(time(nullptr));
    FILE* in = fopen("custom lady.png","rb");
    if(in == nullptr) 
    {   
        printf("file cant be opne");
        return -1;
    }
    fseek(in,0,SEEK_END);
    long long size = ftell(in);
    rewind(in);
    printf("%ld\n",size);
    
    int8_t* buffer = malloc(size);
    int8_t* ran_buffer = malloc(size); 
    int8_t* res_buffer = malloc(size);
    int8_t* correct_buffer = malloc(size);
    fread(buffer,1,size,in);
   
    for(int64_t i = 0;i<size;i++)
    {
        int ran_num = (rand() % (100 - 1 + 1) + 1);
        ran_buffer[i] = ran_num;
    }

   for(int64_t i = 0;i<size;i++)
   {
     u_int8_t res = (buffer[i] + ran_buffer[i]) % 256;
     res_buffer[i] = res; 
   }

 FILE* store_key = fopen("key.bin","wb");
 if(store_key == nullptr)
 {
    printf("cant open key file ");
    free(buffer);
    free(ran_buffer);
    free(res_buffer);
    free(correct_buffer);
    return -1;
 }   
 
fwrite(ran_buffer,1,size,store_key);

fclose(store_key);
 
 FILE* out = fopen("decoded.png","wb");
 if(out == nullptr)
{
    printf("out file cant be opne");
   free(buffer);
   free(ran_buffer);
   free(res_buffer);
   free(correct_buffer);
    return -1;
}

// fwrite(res_buffer,1,size,out);

for(int64_t i =0;i<size;i++)
{
    uint8_t res = (res_buffer[i] - ran_buffer[i] + 256) % 256;
    correct_buffer[i] = res;
}

fwrite(correct_buffer,1,size,out);

for(uint64_t i = 0;i<size;i++) 
{
    if(correct_buffer[i] == buffer[i]) correct = 1;
    else if(correct_buffer[i] != buffer[i]) printf("%"PRIu64"\n",i);
}
if(correct)  printf(" BINGO !!! ");
else printf("you messed up");

fclose(out);
fclose(in);


free(buffer);
free(ran_buffer);
free(res_buffer);
free(correct_buffer);
}