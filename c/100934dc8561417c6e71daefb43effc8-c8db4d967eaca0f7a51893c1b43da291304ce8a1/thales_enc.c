
#include <stdio.h>
#include <lnmdef.h>
#include <descrip.h>
#include <ssdef.h>
#include <stdio.h>
#include <stdlib.h>




struct itm {
             unsigned short buflen, item_code;
             void *bufaddr;
             void *retlenaddr;
};

/* Declare an item list */
struct {
         struct itm items[1];
         unsigned int terminator;
}trnlst;


void translate_logical(char* ln,char eqvbuf1[LNM$C_NAMLENGTH) {


        unsigned int status, trnattr=LNM$M_CASE_BLIND;
        unsigned int eqvdesc1, eqvdesc2;
        $DESCRIPTOR(logdesc,ln);
        $DESCRIPTOR(tabdesc,"LNM$FILE_DEV");

/* Assign values to the item list */

        trnlst.items[0].buflen = LNM$C_NAMLENGTH;
        trnlst.items[0].item_code = LNM$_STRING;
        trnlst.items[0].bufaddr = eqvbuf1;
        trnlst.items[0].retlenaddr = &eqvdesc1;

        trnlst.terminator = 0;

/* Translate the logical name */
        status = SYS$TRNLNM(&trnattr,  /* attr - attributes */
                       &tabdesc,       /* tabnam - table name */
                       &logdesc,       /* lognam - logical name */
                       0,              /* acmode - access mode */
                       &trnlst);       /* itmlst - item list */
        if((status & 1) != 1)
                LIB$SIGNAL(status);

   //     printf(eqvbuf2);
}



}

char* loadkey(char*filename){


char *source = NULL;
FILE *fp = fopen(filename, "r");
if (fp != NULL) {
    /* Go to the end of the file. */
    if (fseek(fp, 0L, SEEK_END) == 0) {
        /* Get the size of the file. */
        long bufsize = ftell(fp);
        if (bufsize == -1) { /* Error */ }

        /* Allocate our buffer to that size. */
        source = malloc(sizeof(char) * (bufsize + 1));

        /* Go back to the start of the file. */
        if (fseek(fp, 0L, SEEK_SET) != 0) { /* Error */ }

        /* Read the entire file into memory. */
        size_t newLen = fread(source, sizeof(char), bufsize, fp);
        if ( ferror( fp ) != 0 ) {
            fputs("Error reading file", stderr);
        } else {
            source[newLen++] = '\0'; /* Just to be safe. */
        }
    }
    fclose(fp);
}


return source;
//free(source);
}


int sockfd = 0;

void init(){
/*

load key from file

create connection to hsm

*/
}
void writeToHsm(char*buffer){

}

char*readFromHsm(){
}

char * encrypt_on_hsm(char*token);

char * dsc2cstr( struct dsc$descriptor_s  *desc)
{

   char*buffer= malloc(1000);

char*help;
	int jondex;
  char        space_pattern[] = "     ";
  index = 0;
  space_position = strstr( desc->dsc$a_pointer, space_pattern );
  if ( space_position == NULL )
  {
    strncpy(buffer,desc->dsc$a_pointer,desc->dsc$w_length); 
    strcat (buffer,"\0");

   for ( jondex = 0; jondex < strlen( buffer ) ; ++jondex )

   {

     buffer[jondex] = toupper( buffer[jondex] );

   }

  }

  else

  {

   help = desc->dsc$a_pointer;

   while( help != space_position )

   {

    buffer[index] = toupper( *help );

    printf( "%d ", (int)buffer[index] );

    ++index;

    ++help;

   }

   strcat (buffer,"\0");

  }

//  printf( "USER ID=%s\n", arguments[2] );

 return buffer;
 
 }



main()
{


}



 int cls_enc_dec_file_func(struct dsc$descriptor_s  *hsm_ip,

                          struct dsc$descriptor_s  *user_ID,

                          struct dsc$descriptor_s  *key_ID,

                          struct dsc$descriptor_s  *input_file,

                          struct dsc$descriptor_s  *output_file,

                          struct dsc$descriptor_s  *operation,

                         struct dsc$descriptor_s  *authentication)
{}

 

int utl_enc_by_reclen(struct dsc$descriptor_s  *hsm_ip,

                      struct dsc$descriptor_s  *user_id,

                      struct dsc$descriptor_s  *input_file,

                      struct dsc$descriptor_s  *output_file,

                      struct dsc$descriptor_s  *authentication,

                      struct dsc$descriptor_s  *key_file,

                      struct dsc$descriptor_s  *user_password,

                      struct dsc$descriptor_s  *record_len,

                      struct dsc$descriptor_s  *record_len_pad,

                      struct dsc$descriptor_s  *key_id )
{}
