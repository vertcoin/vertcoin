#include <crypto/verthash.h>
#include "clientversion.h"
#include <random.h>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <validation.h>
#include <boost/filesystem.hpp>
#include "verthash_constants.h"

uint32_t Verthash::Fnv1a(uint32_t a, uint32_t b)
{
    return (a ^ b) * 0x1000193;
}

void Verthash::Hash(const char* input, char* output, const int height)
{
    unsigned char header[80];
    memcpy(header, input, 80);

    int i;
    for(i=1;i<23;i++) if(height < 1U<<i) break;
    uint32_t bitmask = (0xffffffff >> (23-i)) & 0xfffffff0;

    fs::path dataFile = GetDataDir() / "verthash.dat";
    if(!boost::filesystem::exists(dataFile)) {
        throw std::runtime_error("Verthash datafile not found");
    }
    uint32_t nonce, ntime, h_n, h_na, i_base[HASH_CHUNK_SIZE/4], i_shrink[8], i_final[8], address[129];
    memcpy(&nonce, header+76, 4);
    memcpy(&ntime, header+68, 4);

    for(int i = 0;i < 8;i++)				//8X SHA3-512
    {
        sha3(header, (size_t)80, &address[i*16], 64);
        ntime++;
        memcpy(header+68, &ntime, 4);
    }

    FILE* VerthashDatFile = fsbridge::fopen(dataFile.c_str(),"rb");
    h_n = Fnv1a(nonce, 2166136261);
    for(int i = 0;i < 128;i++)
    {
        fseek(VerthashDatFile, (address[i]&bitmask), SEEK_SET);
        fread((void *)i_base, sizeof(uint32_t), HASH_CHUNK_SIZE/4, VerthashDatFile);

	    h_na = Fnv1a(h_n, Fnv1a(address[i], 2166136261));

        for(int j = 0;j < 8;j++)
        {
            i_shrink[j] = Fnv1a(Fnv1a(Fnv1a(Fnv1a(Fnv1a(Fnv1a(Fnv1a(Fnv1a(h_na, i_base[8*j]), i_base[8*j+1]), i_base[8*j+2]), i_base[8*j+3]), i_base[8*j+4]), i_base[8*j+5]), i_base[8*j+6]), i_base[8*j+7]);

            if(i==0) i_final[j] = i_shrink[j];
            else i_final[j] = Fnv1a(i_final[j], i_shrink[j]);
        }
        address[i+1] = Fnv1a(Fnv1a(Fnv1a(Fnv1a(Fnv1a(Fnv1a(Fnv1a(Fnv1a(address[i+1], i_shrink[0]), i_shrink[1]), i_shrink[2]), i_shrink[3]), i_shrink[4]), i_shrink[5]), i_shrink[6]), i_shrink[7]);
    }

    memcpy(output, (unsigned char *)i_final, 32);

    fclose(VerthashDatFile);

}
