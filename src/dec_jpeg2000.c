/** @file
 * @brief Decodes JPEG2000 code stream.
 * @author Stephen Gilbert @date 2002-12-02
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grib2_int.h"
#include "jasper/jasper.h"

/**
 * This Function decodes a JPEG2000 code stream specified in the
 * JPEG2000 Part-1 standard (i.e., ISO/IEC 15444-1) using [JasPer
 * Software](https://github.com/jasper-software/jasper).
 *
 * ### Program History Log
 * Date | Programmer | Comments
 * -----|------------|---------
 * 2002-12-02 | Gilbert | Initial
 * 2022-04-15 | Hartnett | Converted to use jas_ instead of jpc_ functions.
 *
 * @param injpc Input JPEG2000 code stream.
 * @param bufsize Length (in bytes) of the input JPEG2000 code stream.
 * @param outfld Output matrix of grayscale image values.
 *
 * @return
 * - 0 Successful decode
 * - ::G2_JASPER_DECODE Error decode jpeg2000 code stream.
 * - ::G2_JASPER_DECODE_COLOR decoded image had multiple color
 *     components. Only grayscale is expected.
 * - ::G2_JASPER_INIT Error inializing Jasper library.
 *
 * @author Stephen Gilbert @date 2002-12-02
 * @author Ed Hartnett
 */
int
dec_jpeg2000(char *injpc, g2int bufsize, g2int *outfld)
{
    g2int i, j, k;
    jas_image_t *image = NULL;
    jas_stream_t *jpcstream;
    jas_image_cmpt_t *pcmpt;
    char *opts = NULL;
    jas_matrix_t *data;
    int fmt;

    /* Initialize Jasper. */
#ifdef JASPER3
    jas_conf_clear();
    /* static jas_std_allocator_t allocator; */
    /* jas_std_allocator_init(&allocator); */
    /* jas_conf_set_allocator(JAS_CAST(jas_std_allocator_t *, &allocator)); */
    jas_conf_set_max_mem_usage(10000000);
    jas_conf_set_multithread(true);
    if (jas_init_library())
        return G2_JASPER_INIT;
    if (jas_init_thread())
        return G2_JASPER_INIT;
#else
    if (jas_init())
        return G2_JASPER_INIT;
#endif /* JASPER3 */

    /* Create jas_stream_t containing input JPEG200 codestream in
     * memory. */
    jpcstream = jas_stream_memopen(injpc, bufsize);

    /* Get jasper ID of JPEG encoder. */
    fmt = jas_image_strtofmt(G2C_JASPER_JPEG_FORMAT_NAME);

    /* Decode JPEG200 codestream into jas_image_t structure. */
    if (!(image = jas_image_decode(jpcstream, fmt, opts)))
        return G2_JASPER_DECODE;

    pcmpt = image->cmpts_[0];
    /*
      printf(" SAGOUT DECODE:\n");
      printf(" tlx %d \n", image->tlx_);
      printf(" tly %d \n", image->tly_);
      printf(" brx %d \n", image->brx_);
      printf(" bry %d \n", image->bry_);
      printf(" numcmpts %d \n", image->numcmpts_);
      printf(" maxcmpts %d \n", image->maxcmpts_);
      printf(" colorspace %d \n", image->clrspc_);
      printf(" inmem %d \n", image->inmem_);
      printf(" COMPONENT:\n");
      printf(" tlx %d \n", pcmpt->tlx_);
      printf(" tly %d \n", pcmpt->tly_);
      printf(" hstep %d \n", pcmpt->hstep_);
      printf(" vstep %d \n", pcmpt->vstep_);
      printf(" width %d \n", pcmpt->width_);
      printf(" height %d \n", pcmpt->height_);
      printf(" prec %d \n", pcmpt->prec_);
      printf(" sgnd %d \n", pcmpt->sgnd_);
      printf(" cps %d \n", pcmpt->cps_);
      printf(" type %d \n", pcmpt->type_);
    */

    /* Expecting jpeg2000 image to be grayscale only. No color components. */
    if (image->numcmpts_ != 1)
        return G2_JASPER_DECODE_COLOR;

    /* Create a data matrix of grayscale image values decoded from the
     * jpeg2000 codestream. */
    data = jas_matrix_create(jas_image_height(image), jas_image_width(image));
    jas_image_readcmpt(image, 0, 0, 0, jas_image_width(image),
                       jas_image_height(image), data);

    /* Copy data matrix to output integer array. */
    k = 0;
    for (i = 0; i < pcmpt->height_; i++)
        for (j = 0; j < pcmpt->width_; j++)
            outfld[k++] = data->rows_[i][j];

    /* Clean up JasPer work structures. */
    jas_matrix_destroy(data);
    jas_stream_close(jpcstream);
    jas_image_destroy(image);

    /* Finalize jasper. */
#ifdef JASPER3
    jas_cleanup_thread();
    jas_cleanup_library();
#else
    jas_cleanup();
#endif /* JASPER3 */

    return 0;
}
