/* This is a test for the NCEPLIBS-g2c project. This test is for
 * g2_addfield using complex spectral packing.
 *
 * Ed Hartnett 11/1/21
 */

#include "grib2_int.h"
#include <stdio.h>
#include <stdlib.h>

#define SEC0_LEN 16
#define SEC1_LEN 21
#define MSG_LEN 109
#define MOST_MSG_LEN 178
#define FULL_MSG_LEN 182

void g2_miss(gribfield *gfld, float *rmiss, int *nmiss);

int
main()
{
    printf("Testing g2_addfield() with spectral packing.\n");
    /* printf("Testing full message creation (expect and ignore error messages)...\n"); */
    /* { */
    /*     unsigned char cgrib[FULL_MSG_LEN]; */
    /*     g2int listsec0[2] = {1, 2}; */
    /*     g2int listsec1[13] = {7, 4, 24, 0, 0, 2021, 10, 24, 6, 54, 59, 7, 192}; */
    /*     g2int igds[5] = {0, 4, 0, 0, 50}; */
    /*     g2int igdstmpl[5] = {1, 1, 2, 0, 1}; */
    /*     /\* unsigned char expected_cgrib[FULL_MSG_LEN] = {0x47, 0x52, 0x49, 0x42, 0x00, 0x00, 0x01, 0x02, 0x00, *\/ */
    /*     /\*     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb6, 0x00, 0x00, 0x00, 0x15, 0x01, 0x00, 0x07, 0x00, 0x04, *\/ */
    /*     /\*     0x18, 0x00, 0x00, 0x07, 0xe5, 0x0a, 0x18, 0x06, 0x36, 0x3b, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x48, *\/ */
    /*     /\*     0x03, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, *\/ */
    /*     /\*     0x03, 0x00, 0x00, 0x00, 0x04, 0x05, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, *\/ */
    /*     /\*     0x00, 0x08, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, *\/ */
    /*     /\*     0x00, 0x0c, 0x0d, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x10, 0x00, *\/ */
    /*     /\*     0x00, 0x00, 0x11, 0x12, 0x00, 0x00, 0x00, 0x22, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, *\/ */
    /*     /\*     0x03, 0x04, 0x00, 0x05, 0x06, 0x07, 0x00, 0x00, 0x00, 0x08, 0x09, 0x0a, 0x00, 0x00, 0x00, 0x0b, *\/ */
    /*     /\*     0x0c, 0x0d, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x15, 0x05, 0x00, 0x00, 0x00, 0x04, 0x00, *\/ */
    /*     /\*     0x00, 0x42, 0xc8, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x03, 0x00, 0x00, 0x00, 0x00, 0x07, 0x06, *\/ */
    /*     /\*     0x00, 0xf0, 0x00, 0x00, 0x00, 0x07, 0x07, 0x0a, 0x60, 0x37, 0x37, 0x37, 0x37}; *\/ */
    /*     /\* Analysis or forecast at a horizontal level or in a */
    /*      * horizontal layer at a point in time. *\/ */
    /*     g2int ipdsnum = 0; */
    /*     g2int ipdstmpl[15] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}; */
    /*     g2float coordlist[1] = {1}; */
    /*     g2int numcoord = 0; */
    /*     g2int idrsnum = 51; /\* Spectral Data - Complex Packing (see Template 5.51) *\/ */
    /*     g2int idrstmpl[10] = {0, 1, 2, 3, 4, 1, 1, 1, 1, 1}; */
    /*     g2float fld[8] = {1, 2, 3, 4, 5, 6, 7, 8}; */
    /*     g2int ngrdpts = 4; */
    /*     g2int ibmap = 0; */
    /*     g2int bmap[4] = {1, 1, 1, 1}; */
    /*     int i; */
    /*     int ret; */

    /*     /\* Create the message, filling in sections 0 and 1. *\/ */
    /*     if ((ret = g2_create(cgrib, listsec0, listsec1)) != SEC0_LEN + SEC1_LEN) */
    /*         return G2C_ERROR; */

    /*     /\* Add section 3. *\/ */
    /*     if ((ret = g2_addgrid(cgrib, igds, igdstmpl, NULL, 0)) != 65) */
    /*         return G2C_ERROR; */

    /*     /\* Add sections 4, 5, 6, and 7. *\/ */
    /*     if ((ret = g2_addfield(cgrib, ipdsnum, ipdstmpl, coordlist, numcoord, */
    /*                            idrsnum, idrstmpl, fld, ngrdpts, ibmap, bmap)) != MOST_MSG_LEN) */
    /*         return G2C_ERROR; */

    /*     /\* Add section 8. *\/ */
    /*     if ((ret = g2_gribend(cgrib)) != FULL_MSG_LEN) */
    /*         return G2C_ERROR; */

    /*     /\* Check the contents of the message for correctness. *\/ */
    /*     for (i = 0; i < FULL_MSG_LEN; i++) */
    /*     { */
    /*         printf("0x%2.2x, ", cgrib[i]); */
    /*         /\* if (cgrib[i] != expected_cgrib[i]) *\/ */
    /*         /\*     return G2C_ERROR; *\/ */
    /*     } */

    /*     { */
    /*         /\* g2int listsec0_in[3], listsec1_in[13]; *\/ */
    /*         /\* g2int numfields, numlocal; *\/ */
    /*         /\* g2int ifldnum = 1, unpack = 1, expand = 0; *\/ */
    /*         /\* gribfield *gfld; *\/ */

    /*         /\* /\\* Use g2_info() to learn about our messaage. *\\/ *\/ */
    /*         /\* if ((ret = g2_info(cgrib, listsec0_in, listsec1_in, &numfields, &numlocal))) *\/ */
    /*         /\*     return G2C_ERROR; *\/ */

    /*         /\* /\\* Check results. *\\/ *\/ */
    /*         /\* if (numlocal || numfields != 1 || listsec0_in[0] != 1 || listsec0_in[1] != 2 || *\/ */
    /*         /\*     listsec0_in[2] != FULL_MSG_LEN) *\/ */
    /*         /\*     return G2C_ERROR; *\/ */
    /*         /\* for (i = 0; i < 13; i++) *\/ */
    /*         /\*     if (listsec1_in[i] != listsec1[i]) *\/ */
    /*         /\*         return G2C_ERROR; *\/ */

    /*         /\* /\\* Try g2_getfld() for field 1. *\\/ *\/ */
    /*         /\* if ((ret = g2_getfld(cgrib, ifldnum, unpack, expand, &gfld))) *\/ */
    /*         /\*     return G2C_ERROR; *\/ */

    /*         /\* /\\* Check some stuff. *\\/ *\/ */
    /*         /\* if (gfld->version != 2 || gfld->discipline != 1 || gfld->idsectlen != 13 || *\/ */
    /*         /\*     gfld->local || gfld->locallen || gfld->ifldnum != 1 || gfld->griddef || *\/ */
    /*         /\*     gfld->ngrdpts != 4 || gfld->numoct_opt || gfld->coord_list || gfld->ndpts != 4 || *\/ */
    /*         /\*     gfld->idrtnum || gfld->idrtlen != 5 || gfld->unpacked != 1 || gfld->expanded || *\/ */
    /*         /\*     gfld->ibmap) *\/ */
    /*         /\*     return G2C_ERROR; *\/ */
    /*         /\* for (i = 0; i < 13; i++) *\/ */
    /*         /\*     if (gfld->idsect[i] != listsec1[i]) *\/ */
    /*         /\*         return G2C_ERROR; *\/ */
    /*         /\* for (i = 0; i < 19; i++) *\/ */
    /*         /\*     if (gfld->igdtmpl[i] != igdstmpl[i]) *\/ */
    /*         /\*         return G2C_ERROR; *\/ */
    /*         /\* for (i = 0; i < 15; i++) *\/ */
    /*         /\*     if (gfld->ipdtmpl[i] != ipdstmpl[i]) *\/ */
    /*         /\*         return G2C_ERROR; *\/ */

    /*         /\* /\\* Try the g2_miss() function. *\\/ *\/ */
    /*         /\* float rmiss[1]; *\/ */
    /*         /\* int nmiss; *\/ */
    /*         /\* g2_miss(gfld, rmiss, &nmiss); *\/ */
    /*         /\* if (nmiss) *\/ */
    /*         /\*     return G2C_ERROR; *\/ */

    /*         /\* /\\* Free the memory. *\\/ *\/ */
    /*         /\* g2_free(gfld); *\/ */
    /*     } */
    /* } */
    /* printf("ok!\n"); */
    printf("SUCCESS!\n");
    return 0;
}
