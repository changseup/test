#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define __WRITE_TEST__
#define __SLICE_CHECK__
//#define __FILE_LOG__


// build date : 2019.10.07

int Endian(const int nOrgData) {
	int temp = 0;
	temp = (nOrgData & 0x000000FF) << 24;
	temp += ((nOrgData & 0x0000FF00) >> 8) << 16;
	temp += ((nOrgData & 0x00FF0000) >> 16) << 8;
	temp += ((nOrgData & 0xFF000000) >> 24);

	return temp;
}


int getBitByPos(unsigned char *buffer, int pos) {
    return (buffer[pos/8] >> (8 - pos%8) & 0x01);
}


unsigned int decodeGolomb(unsigned char *byteStream, unsigned int *index) {
    unsigned int leadingZeroBits = -1;
    unsigned int codeNum = 0;
    unsigned int pos = *index;

	printf("Invalid input\n");
    if (byteStream == NULL || pos == 0 ) {
        printf("Invalid input\n");
        return 0;
    }

    for (int b = 0; !b; leadingZeroBits++)
        b = getBitByPos(byteStream, pos++);

    for (int b = leadingZeroBits; b > 0; b--)
        codeNum = codeNum | (getBitByPos(byteStream, pos++) << (b - 1));

    *index = pos;
    return ((1 << leadingZeroBits) - 1 + codeNum);
}

int SampleSize(char* pFile)
{
	FILE *pFileOrg;
	FILE *pLogFileOrg;
	unsigned char* pbuf;
	int i=0, ret = 0;
	int nbufSize = 10 * 1024;//1* 1024 * 1024;
	int nFileOffset = 0;
	int nbufOffset = 0;
	unsigned int bFindChk = 0;

	int nStateCnt16k = 0, nStateCnt64k = 0, nStateCnt8k;
	unsigned int uStateSum16k = 0, uStateSum64k = 0, uStateSum8k = 0;
	unsigned int uSampleCount = 0;

	unsigned char chLogFilePath[255] = {0, };

	const unsigned char ftyp[4] = "ftyp";
	const unsigned char stsz[4] = "stsz";
	const unsigned char moov[4] = "moov";


	pFileOrg = fopen(pFile, "rb");
	if(NULL == pFileOrg) {
		printf("[%s %d] File open error.\n", __FUNCTION__, __LINE__);
		return 0;
	} else {
		printf("[%s %d] File open success.\n", __FUNCTION__, __LINE__);
	}

#ifdef __FILE_LOG__
	sprintf(chLogFilePath, "%s_log.txt", pFile);
	printf("%s \n", chLogFilePath);
	pLogFileOrg = fopen(chLogFilePath, "wb");
	if(NULL == pLogFileOrg) {
		printf("[%s %d] File open error.\n", __FUNCTION__, __LINE__);
		return 0;
	} else {
		printf("[%s %d] File open success.\n", __FUNCTION__, __LINE__);
	}
#endif

	pbuf = calloc(sizeof(unsigned char), nbufSize);
	if( NULL == pbuf) {
		printf("memory alloc fail.\n");
		return 0;
	}
	memset(pbuf, 0, nbufSize);


	// printf("ftyp : %c, %c, %c, %c \n", ftyp[0], ftyp[1], ftyp[2], ftyp[3]);
	// printf("ftyp : %X, %X, %X, %X \n", ftyp[0], ftyp[1], ftyp[2], ftyp[3]);

	
	nFileOffset = 0;
	//while(1)
	while(0 == bFindChk)
	{
		
		ret = fread(pbuf, sizeof(unsigned char), nbufSize, pFileOrg);
		//printf("pbuf: %X, %X, %X, %X \n", pbuf[0], pbuf[1], pbuf[2], pbuf[3]);

		nbufOffset = 0;	
		for(nbufOffset=0; nbufOffset<nbufSize; nbufOffset++) 
		{
#if 0
			if( (pbuf[nbufOffset] == ftyp[0]) )	// 'f'
			{
				if( (pbuf[nbufOffset+1] == ftyp[1]) && (pbuf[nbufOffset+2] == ftyp[2]) && (pbuf[nbufOffset+3] == ftyp[3]) ) 	// 'typ'
				//if( (pbuf[nbufOffset+1] == moov[1]) && (pbuf[nbufOffset+2] == moov[2]) && (pbuf[nbufOffset+3] == moov[3]) ) 	// 'typ'
				{
					
					bFindChk = 1;
					printf("find ftyp.....\n");
					break;
				}
			}

#else

			if( (pbuf[nbufOffset] == stsz[0]) )	// 'f'
			{
				if( (pbuf[nbufOffset+1] == stsz[1]) && (pbuf[nbufOffset+2] == stsz[2]) && (pbuf[nbufOffset+3] == stsz[3]) ) 	// 'typ'
				{
					if(pbuf[nbufOffset+4] == 0x00 ) {
						printf("find stsz.....\n");
						bFindChk = 1;
						break;
					}
				}
			}
#endif
		}

		if(0 == bFindChk) {
			nFileOffset += nbufSize;
		} else {
			nFileOffset += nbufOffset;
			printf("nFileOffset: %d nbufOffset: %d \n", nFileOffset, nbufOffset);
#ifdef __FILE_LOG__
			fprintf(pLogFileOrg, "nFileOffset: %d nbufOffset: %d \n", nFileOffset, nbufOffset);
#endif //__FILE_LOG__

			// To Do
			nFileOffset -= 4;
			fseek(pFileOrg, nFileOffset, SEEK_SET);
			//ret = fread(pbuf, sizeof(unsigned char), nbufSize, pFileOrg);
			//printf("pbuf: %X, %X, %X, %X \n", pbuf[0], pbuf[1], pbuf[2], pbuf[3]);

			{
				unsigned char atom[4] = {0,};
				int atomsize=0;
				unsigned int sample_size=0, sample_count=0, entry_size=0;

				// atomsize
				ret = fread(&atomsize, sizeof(int), 1, pFileOrg);
				atomsize = Endian(atomsize);
				// atom type
				ret = fread(&atom, sizeof(unsigned char), 4, pFileOrg);
				//printf("pbuf: %02X, %02X, %02X, %02X \n", atom[0], atom[1], atom[2], atom[3]);
				printf("atom type: 0x%02X%02X%02X%02X, atom size(%d) \n", atom[0], atom[1], atom[2], atom[3], atomsize);

				ret = fread(&atomsize, sizeof(int), 1, pFileOrg);

				ret = fread(&sample_size, sizeof(int), 1, pFileOrg);
				sample_size = Endian(sample_size);
				ret = fread(&sample_count, sizeof(int), 1, pFileOrg);
				sample_count = Endian(sample_count);
				uSampleCount = sample_count;

				printf("sample_size(%d) sample_count(%d) \n", sample_size, sample_count);
#ifdef __FILE_LOG__
				fprintf(pLogFileOrg, "sample_size(%d) sample_count(%d) \n", sample_size, sample_count);
#endif //__FILE_LOG__
				for(i=0; i<sample_count; i++)
				{
					ret = fread(&entry_size, sizeof(int), 1, pFileOrg);
					entry_size = Endian(entry_size);
					
					//int nStateCnt16k = 0, nStateCnt64k = 0, nStateCnt8k;
					if( entry_size > (8 * 1024)) 
					{
						nStateCnt8k++;
						uStateSum8k += entry_size;
						if( entry_size > (16 * 1024) ) 
						{
							nStateCnt16k++;
							uStateSum16k += entry_size;
							if( entry_size > (64 * 1024) )
							{
								uStateSum64k += entry_size;
								nStateCnt64k++;
							}
						}
					}
					

					printf("[%03d]	%d\n", (i+1), entry_size);
#ifdef __FILE_LOG__
					fprintf(pLogFileOrg, "[%03d]	%d\n", (i+1), entry_size);
#endif //__FILE_LOG__
					
					// if(i > 2) {
					// 	break;
					// }
				}
			}
		}
	}	/*while(0 == bFindChk)*/

//unsigned int uStateSum16k = 0, uStateSum64k = 0, uStateSum8k = 0;
	printf("Frame Size > ( 8 * 1024) : %d\t\tFrame avg. Size: %u\n", nStateCnt8k, uStateSum8k/nStateCnt8k);
	printf("Frame Size > (16 * 1024) : %d\t\tFrame avg. Size: %u\n", nStateCnt16k, uStateSum16k/nStateCnt16k);
	printf("Frame Size > (64 * 1024) : %d\t\tFrame avg. Size: %u\n", nStateCnt64k, uStateSum64k/nStateCnt64k);
	
	fclose(pFileOrg);
	fclose(pLogFileOrg);
	free(pbuf);
	pbuf = NULL;

	return 0;
}

int FFReaderTest(char* pFile) 
{

	FILE *pFileOrg, *pFileOut;
	unsigned char* pbuf;
	int length = 0;
	int NAL_Val = 0;
	int i = 0, ret = 0;

	int offset = 0;
	int nbufSize = 1* 1024 * 1024;


	pFileOrg = fopen(pFile, "rb");
	//pFile = fopen(argv[1], "rb");
	if(NULL == pFileOrg) {
		printf("[%s %d] File open error.\n", __FUNCTION__, __LINE__);
		return 0;
	} else {
		printf("[%s %d] File open success.\n", __FUNCTION__, __LINE__);
	}

	pFileOut = fopen("dump_test_20190218.dump", "wb");
	if(NULL == pFileOut) {
		printf("[%s %d] File create error.\n", __FUNCTION__, __LINE__);
		return 0;
	} else {
		printf("[%s %d] File create success.\n", __FUNCTION__, __LINE__);
	}

	//printf("%d...\n", nbufSize);
	pbuf = calloc(sizeof(char), nbufSize);
	if( NULL == pbuf) {
		printf("memory alloc fail.\n");
		return 0;
	}

	for(i=0; i<40; i++) 
	{
		length = 0;
		ret = fread(&length, sizeof(int), 1, pFileOrg);
		if(1 != ret) {
			printf("file read error.\n");
			return 0;
		}
		offset = ftell(pFileOrg);
		//length = Endian(length);
		printf("[%s %d] sample length: %d(0x%08X) offset: %d \n", __FUNCTION__, __LINE__, length, length, offset);

#ifdef __WRITE_TEST__
		ret = fwrite(&length, sizeof(int), 1, pFileOut);
#endif //__WRITE_TEST__

		if(length > nbufSize) {
			printf("frame size is more than nbufSize. and re-alloc start.\n");

			free(pbuf);
			pbuf = NULL;
			
			nbufSize = length;
			pbuf = calloc(sizeof(unsigned char), nbufSize);
			if( NULL == pbuf) {
				printf("memory alloc fail.\n");
				return 0;
			}
		}

#ifdef __SLICE_CHECK__
		// slice check
		{
			int atomSize = 0, atomType = 0;;
			unsigned char* pTempBuf;
			int temp_offset = 0;
			int temp_Length = length;

			pTempBuf = calloc(sizeof(unsigned char), nbufSize);
			if( NULL == pTempBuf) {
				printf("memory alloc fail.\n");
				return 0;
			}
			memset(pTempBuf, 0, nbufSize);
			
			do {
				NAL_Val = 0;
				temp_offset = ftell(pFileOrg);	
				//printf("[1] fileOffset: %3d length: %d\n", temp_offset, temp_Length);

				ret = fread(&atomSize, sizeof(int), 1, pFileOrg);
				atomSize = Endian(atomSize);
				//printf("[2] atomSize: %d\n", atomSize);

				fseek(pFileOrg, temp_offset, SEEK_SET);
				memset(pTempBuf, 0, nbufSize);

				ret = fread(pTempBuf, sizeof(unsigned char), (size_t)(atomSize + 4), pFileOrg);
				temp_Length -= (atomSize + 4);
				//printf("[3] Size: %d %d\n", atomSize, temp_Length);
				
				NAL_Val = (pTempBuf[4] & 0x1F);
				//printf("[4] NAL type: %2d  remain length: %d\n", NAL_Val, temp_Length);
							
				// change bytes stream format (RAW type -> Annex B type)
				pTempBuf[0] = 0x00;
				pTempBuf[1] = 0x00;
				pTempBuf[2] = 0x00;
				pTempBuf[3] = 0x01;

				printf("sample data: ");
				for(int x=0; x< 16; x++) {
					printf("%02X ", pTempBuf[x]);
				}
				printf("\n");

#ifdef __WRITE_TEST__
				ret = fwrite(pTempBuf, sizeof(char), (size_t)(atomSize + 4), pFileOut);
#endif //__WRITE_TEST__				
				
			} while(temp_Length > 0);

			free(pTempBuf);
			pTempBuf = NULL;
		}
#endif //__SLICE_CHECK__

		//offset seek
		//fseek(pFileOrg, offset, SEEK_SET);

		//memset(pbuf, 0, nbufSize);
		//ret = fread(pbuf, sizeof(char), length, pFileOrg);

#ifdef __WRITE_TEST__
		//ret = fwrite(pbuf, sizeof(char), length, pFileOut);
#endif //__WRITE_TEST__

		switch(NAL_Val) {
			case 5:
			printf("Frame index: %3d, type: I-Frame, size: %6d\n", i+1, length);
			break;
			case 1:
			printf("Frame index: %3d, type: P/B-Frame, size: %6d\n", i+1, length);
			break;
			default:
			printf("Frame index: %3d, type: 0x%02X, size: %6d\n", NAL_Val, i+1, length);	
		}
		//printf("Frame index: %3d, size: %6d\n\n", i+1, length);
	}

	fclose(pFileOrg);
	fclose(pFileOut);
	free(pbuf);
	pbuf = NULL;
	
	return 0;
}

int DSI() 
{
	FILE *pDSI, *pSPS, *pPPS;
	unsigned char pbuf[25] = {0x01, 0x64, 0x00, 0x1F, 0xFF, /* AVC DecodConfiguration */
								0xE1, 0x00, 0x0A, 0x67, 0x64, 0x00, 0x1F, 0xAC, 0xB4, 0x02, 0x80, 0x2D, 0xC8, /* SPS */
								0x01, 0x00, 0x04, 0x68, 0xEE, 0x0D, 0x8B}; /* PPS */
	
	int ret = 0;

#if 0
	pDSI = fopen("DSI.dump", "wb");
	for(int i=0; i<25; i++)
	{
		printf("0x%02X ", pbuf[i]);
		if(i > 4) {
			if( (0x08 == (pbuf[i] & 0x1F)) || (0x07 == (pbuf[i] & 0x1F)) ) 
			{
				printf("\n");
			}
		}
	}
	ret = fwrite(&pbuf, sizeof(unsigned char), (size_t)(25), pDSI);
	fclose(pDSI);
#endif

	if( (0x01 == pbuf[0]) && (0xE0 == (pbuf[5] & 0xE0)))
	{
		int nNALSize = 0;
		nNALSize = (pbuf[4] & 0x03) + 1;
		printf("NAL Size: %d \n", nNALSize);
	}
	return 0;
}

int main(int argc, char* argv[])
{
	int ret = 0;

#if 0
	DSI();
	return 0;
#endif

	if(1 == argc) {
		printf("Do not arguments. please help.");
		return 0;
	}

	if(!strncmp("--help", argv[1], 6)) {
		printf("HELP DESCRIPTION...\n");
		printf("./main (file directory...) )\n");
		return 0;
	}

	//FFReaderTest(argv[1]);
	SampleSize(argv[1]);

	return 0;
}


#if 0
	step 1. ftyp box 
	step 2. moov box
		(2-1) mvhd box
		(2-2) trak box
			(2-2-1) tkhd box
			(2-2-2) edts box
			(2-2-3) mdia box
				(2-2-3-1) mdhd box
				(2-2-3-2) hdlr box
				(2-2-3-3) minf box
					(2-2-3-3-1) vmhd box
					(2-2-3-3-2) dinf box
					(2-2-3-3-3) stbl box
						stsd box
						stts box
						stsc box
						stsz box
						stco box

#endif