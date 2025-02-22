/* This is a test for the NCEPLIBS-g2c project. This test is for
 * the JPEG compression functions.
 *
 * Ed Hartnett 11/1/21
 */

#include "grib2_int.h"
#include <stdio.h>
#include <stdlib.h>

#define DATA_LEN 4
#define PACKED_LEN 200
#define EPSILON .001
#define EPSILON_BIG .1

int
main()
{
    int i;

    printf("Testing JPEG functions.\n");
    /* g2c_set_log_level(10); */
#ifdef USE_JPEG2000
    printf("Testing enc_jpeg2000()/dec_jpeg2000() call...");
    {
        unsigned char data[DATA_LEN] = {1, 2, 3, 4};
        g2int width = 2, height = 2, nbits = 4;
        g2int ltype = 0, ratio = 0, retry = 0, jpclen = PACKED_LEN;
        char outjpc[PACKED_LEN];
        g2int outfld[DATA_LEN];
        int ret;

        /* Encode some data. */
        if ((ret = enc_jpeg2000(data, width, height, nbits, ltype,
                                ratio, retry, outjpc, jpclen)) < 0)
            return G2C_ERROR;

        /* Now decode it. */
        if ((ret = dec_jpeg2000(outjpc, jpclen, outfld)))
            return G2C_ERROR;

        for (i = 0; i < DATA_LEN; i++)
        {
            if (outfld[i] != data[i])
                return G2C_ERROR;
        }
    }
    printf("ok!\n");
    printf("Testing g2c_enc_jpeg2000()/g2c_dec_jpeg2000() call...");
    {
        unsigned char data[DATA_LEN] = {1, 2, 3, 4};
        int width = 2, height = 2, nbits = 4;
        int ltype = 0, ratio = 0, retry = 0;
        size_t jpclen = PACKED_LEN;
        char outjpc[PACKED_LEN];
        int outfld[DATA_LEN];
        int ret;

        /* Encode some data. */
        if ((ret = g2c_enc_jpeg2000(data, width, height, nbits, ltype,
                                    ratio, retry, outjpc, jpclen)) < 0)
            return G2C_ERROR;

        /* Now decode it. */
        if ((ret = g2c_dec_jpeg2000(outjpc, jpclen, outfld)))
            return G2C_ERROR;

        for (i = 0; i < DATA_LEN; i++)
        {
            if (outfld[i] != data[i])
                return G2C_ERROR;
        }
    }
    printf("ok!\n");
#endif
    {
        g2int height = 2, width = 2;
        g2int len = PACKED_LEN, ndpts = DATA_LEN;
        unsigned char cpack[PACKED_LEN];

        printf("Testing jpcpack()/jpcunpack() call...");
        {
            float fld[DATA_LEN] = {100.0, 200.0, 300.0, 0.0};
            float fld_in[DATA_LEN];
            g2int lcpack = PACKED_LEN;
            g2int idrstmpl[7] = {0, 1, 1, 16, 0, 0, 0};
            int i;

            /* Pack the data. */
            jpcpack(fld, width, height, idrstmpl, cpack, &lcpack);

            /* Unpack the data. */
            if (jpcunpack(cpack, len, idrstmpl, ndpts, fld_in))
                return G2C_ERROR;

            for (i = 0; i < DATA_LEN; i++)
            {
                /* printf("%g %g\n", fld[i], fld_in[i]); */
                if (fld[i] != fld_in[i])
                    return G2C_ERROR;
            }
        }
        printf("ok!\n");
        printf("Testing g2c_jpcpackd()/g2c_jpcunpackd() call...");
        {
            double fld[DATA_LEN] = {10000.0, 20000.0, 30000.0, 0.0};
            double fld_in[DATA_LEN];
            size_t lcpack_st = PACKED_LEN;
            int idrstmpl[7] = {0, 1, 1, 16, 0, 0, 0};

            /* Pack the data. */
            g2c_jpcpackd(fld, width, height, idrstmpl, cpack, &lcpack_st);

            /* Unpack the data. */
            if (g2c_jpcunpackd(cpack, len, idrstmpl, ndpts, fld_in))
                return G2C_ERROR;

            for (i = 0; i < DATA_LEN; i++)
            {
                /* printf("%g %g\n", fld[i], fld_in[i]); */
                if (fld[i] != fld_in[i])
                    return G2C_ERROR;
            }
        }
        printf("ok!\n");
        printf("Testing g2c_jpcpackf()/g2c_jpcunpackf() call...");
        {
            float fld[DATA_LEN] = {1000.0, 2000.0, 3000.0, 0.0};
            float fld_in[DATA_LEN];
            size_t lcpack_st = PACKED_LEN;
            int idrstmpl[7] = {0, 1, 1, 16, 0, 0, 0};

            /* Pack the data. */
            g2c_jpcpackf(fld, width, height, idrstmpl, cpack, &lcpack_st);

            /* Unpack the data. */
            if (g2c_jpcunpackf(cpack, len, idrstmpl, ndpts, fld_in))
                return G2C_ERROR;

            for (i = 0; i < DATA_LEN; i++)
            {
                /* printf("%g %g\n", fld[i], fld_in[i]); */
                if (fld[i] != fld_in[i])
                    return G2C_ERROR;
            }
        }
        printf("ok!\n");
        printf("Testing jpcpack()/jpcunpack() call with different drstmpl values...");
        {
            float fld[DATA_LEN] = {1.0, 2.0, 3.0, 0.0};
            float fld_in[DATA_LEN];
            g2int lcpack = PACKED_LEN;
            /* See
             * https://www.nco.ncep.noaa.gov/pmb/docs/grib2/grib2_doc/grib2_temp5-40.shtml */
            g2int idrstmpl[7] = {
                0,  /* Reference value (R) (IEEE 32-bit floating-point value) */
                0,  /* Binary scale factor (E) */
                1,  /* Decimal scale factor (D) */
                32, /* Number of bits required to hold the resulting scaled and referenced data values. (i.e. The depth of the grayscale image.) (see Note 2) */
                0,  /* Type of original field values (see Code Table 5.1) */
                0,  /* Type of Compression used. (see Code Table 5.40) */
                1   /* Target compression ratio, M:1 (with respect to the bit-depth specified in octet 20), when octet 22 indicates Lossy Compression. Otherwise, set to missing (see Note 3) */
            };

            /* Pack the data. */
            jpcpack(fld, width, height, idrstmpl, cpack, &lcpack);

            /* Unpack the data. */
            if (jpcunpack(cpack, len, idrstmpl, ndpts, fld_in))
                return G2C_ERROR;

            for (i = 0; i < DATA_LEN; i++)
                if (fld[i] != fld_in[i])
                    return G2C_ERROR;
        }
        printf("ok!\n");
        printf("Testing g2c_jpcpackd()/g2c_jpcunpackd() call with different drstmpl values...");
        {
            double fld[DATA_LEN] = {1.0, 2.0, 3.0, 0.0};
            double fld_in[DATA_LEN];
            size_t lcpack = PACKED_LEN;
            int idrstmpl[7] = {0, 0, 1, 32, 0, 0, 1};

            /* Pack the data. */
            g2c_jpcpackd(fld, width, height, idrstmpl, cpack, &lcpack);

            /* Unpack the data. */
            if (g2c_jpcunpackd(cpack, len, idrstmpl, ndpts, fld_in))
                return G2C_ERROR;

            for (i = 0; i < DATA_LEN; i++)
                if (fld[i] != fld_in[i])
                    return G2C_ERROR;
        }
        printf("ok!\n");
        printf("Testing g2c_jpcpackd()/g2c_jpcunpackd() call with drstmpl values as in NCEPLIBS-g2 test_jpcpack...");
        {
            double fld[DATA_LEN] = {1.1, 2.2, 3.3, 4.4};
            double fld_in[DATA_LEN];
            size_t lcpack = PACKED_LEN;
            int idrstmpl[7] = {0, 1, 1, 32, 0, 0, 1};

            /* Pack the data. */
            g2c_jpcpackd(fld, width, height, idrstmpl, cpack, &lcpack);

            /* Unpack the data. */
            if (g2c_jpcunpackd(cpack, len, idrstmpl, ndpts, fld_in))
                return G2C_ERROR;

            for (i = 0; i < DATA_LEN; i++)
                if (abs(fld[i] - fld_in[i]) > EPSILON)
                    return G2C_ERROR;
        }
        printf("ok!\n");
        printf("Testing jpcpack()/jpcunpack() call with drstmpl values as in NCEPLIBS-g2 test_jpcpack...");
        {
            float fld[DATA_LEN] = {1.1, 2.2, 3.3, 4.4};
            float fld_in[DATA_LEN];
            g2int lcpack = PACKED_LEN;
            g2int idrstmpl[7] = {0, 1, 1, 32, 0, 0, 1};

            /* Pack the data. */
            jpcpack(fld, width, height, idrstmpl, cpack, &lcpack);

            /* Unpack the data. */
            if (jpcunpack(cpack, len, idrstmpl, ndpts, fld_in))
                return G2C_ERROR;

            for (i = 0; i < DATA_LEN; i++)
            {
                /* printf("%d %g %g\n", i, fld[i], fld_in[i]); */
                if (abs(fld[i] - fld_in[i]) > EPSILON_BIG)
                    return G2C_ERROR;
            }
        }
        printf("ok!\n");
        printf("Testing jpcpack()/jpcunpack() call with constant data field...");
        {
            float fld[DATA_LEN] = {1.0, 1.0, 1.0, 1.0};
            float fld_in[DATA_LEN];
            g2int lcpack = PACKED_LEN;
            g2int idrstmpl[7] = {0, 0, 1, 32, 0, 0, 1};

            /* Pack the data. */
            jpcpack(fld, width, height, idrstmpl, cpack, &lcpack);

            /* Unpack the data. */
            if (jpcunpack(cpack, len, idrstmpl, ndpts, fld_in))
                return G2C_ERROR;

            for (i = 0; i < DATA_LEN; i++)
                if (fld[i] != fld_in[i])
                    return G2C_ERROR;
        }
        printf("ok!\n");
        printf("Testing g2c_jpcpackd()/g2c_jpcunpackd() call with constant data field...");
        {
            double fld[DATA_LEN] = {1.0, 1.0, 1.0, 1.0};
            double fld_in[DATA_LEN];
            size_t lcpack = PACKED_LEN;
            int idrstmpl[7] = {0, 0, 1, 32, 0, 0, 1};

            /* Pack the data. */
            g2c_jpcpackd(fld, width, height, idrstmpl, cpack, &lcpack);

            /* Unpack the data. */
            if (g2c_jpcunpackd(cpack, len, idrstmpl, ndpts, fld_in))
                return G2C_ERROR;

            for (i = 0; i < DATA_LEN; i++)
                if (fld[i] != fld_in[i])
                    return G2C_ERROR;
        }
        printf("ok!\n");
    }
    printf("SUCCESS!\n");
    return 0;
}
