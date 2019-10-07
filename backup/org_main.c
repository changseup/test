#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>

#include "mp4Detatil.h"
#include "mp4atom.h"
#include "utils.h"

#define __WRITE_TEST__
#define __SLICE_CHECK__
//#define __FILE_LOG__

// AVCDecoderConfigurationRecord
const unsigned char chDSI[23] = {0x00, 0x00, 0x00, 0x01, 0x67, 0x42, 0x00, 0x1E, 0x9D, 0xA8, 0x28, 0x0F, 0x64, 
								0x00, 0x00, 0x00, 0x01, 0x68, 0xCE, 0x3C, 0x80, 0x00, 0x00};
// profile : baseline
// level_idc : 3.0  (0x1E)
//const unsigned char pps[100];
//https://namu.wiki/w/H.26x
int getBitByPos(unsigned char *buffer, int pos);
unsigned int decodeGolomb(unsigned char *byteStream, unsigned int *index);

int SliceCheck(char* pFile);
int SampleSize(char* pFile);
int DSI();

enum ReturnType {
	kSuccess = 0,
	kParsingError,
	kMemoryAllocFail
};



// int moovParsing(FILE *pFileOrg, int nFileOffset, int nAtomSize)
// {
// 	int n
// 	while(nFileOffset <= nAtomSize)
// 	{

// 	}
// 	return 0;
// }


int FFReaderTest(char* pFile) 
{
	FILE *pFileOrg, *pFileOut;
	unsigned char* pbuf;
	int length = 0;
	int NAL_Val = 0;
	int i = 0, ret = 0;

	int nFileOffset = 0;
	int nbufOffset = 0;
	unsigned int bFindChk = 0;
	//unsigned int bFindChk_stsc = 0, bFindChk_stss = 0, bFindChk_stsz = 0;
	unsigned char bChkAtom = 0;

	unsigned int uAtomSize = 0, uAtomType = 0;
	int nFileSize = 0;
	

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

	// pFileOut = fopen("dump_test_20190218.dump", "wb");
	// if(NULL == pFileOut) {
	// 	printf("[%s %d] File create error.\n", __FUNCTION__, __LINE__);
	// 	return 0;
	// } else {
	// 	printf("[%s %d] File create success.\n", __FUNCTION__, __LINE__);
	// }

	pbuf = calloc(sizeof(char), nbufSize);
	if( NULL == pbuf) {
		printf("memory alloc fail.\n");
		return 0;
	}

	

	nFileSize = fseek(pFileOrg, 0, SEEK_END);
	nFileSize = ftell(pFileOrg);
	
	nFileOffset = fseek(pFileOrg, 0, SEEK_SET);
	printf("[%s %d] nFileSize : %d \r\n", __FUNCTION__, __LINE__, nFileSize);
	//return 0;


	nFileOffset = 0;
	while(1)
	{
		//unsigned char tempType[4] = {0, };

		ret = fread(&uAtomSize, sizeof(unsigned int), 1, pFileOrg);
		uAtomSize = Endian(uAtomSize);
		ret = fread(&uAtomType, sizeof(unsigned int), 1, pFileOrg);
		uAtomType = Endian(uAtomType);
		nFileOffset += 8;

		
		printf("[%s %d] AtomType(0x%08X) AtomSize(%d)\n", __FUNCTION__, __LINE__, uAtomType, uAtomSize);
		
		switch(uAtomType) 
		{
			case _FTYP_:
			{
				printf("[%s %d] find ftyp -->", __FUNCTION__, __LINE__);
				fseek(pFileOrg, (uAtomSize - 8), SEEK_CUR);
				nFileOffset += (uAtomSize - 8);
				printf(": size(%d) fileOffset(%d)\n", uAtomSize, nFileOffset);
				//return 0;
			}
			break;

			case _MDAT_:
			{
				printf("[%s %d] find mdat -->", __FUNCTION__, __LINE__);
				fseek(pFileOrg, (uAtomSize - 8), SEEK_CUR);
				nFileOffset += (uAtomSize - 8);
				printf(": size(%d) fileOffset(%d)\n", uAtomSize, nFileOffset);
			}
			break;

			case _MOOV_:
			{
				printf("[%s %d] find moov -->", __FUNCTION__, __LINE__);
				fseek(pFileOrg, (uAtomSize - 8), SEEK_CUR);
				nFileOffset += (uAtomSize - 8);
				printf(": size(%d) fileOffset(%d)\n", uAtomSize, nFileOffset);
				
			}
			break;

			case _STSC_:
			{
				printf("[%s %d] find stsc -->", __FUNCTION__, __LINE__);
				fseek(pFileOrg, (uAtomSize - 8), SEEK_CUR);
				nFileOffset += (uAtomSize - 8);
				printf(": size(%d) fileOffset(%d)\n", uAtomSize, nFileOffset);
			}
			break;

			case _STSS_:
			{
				printf("[%s %d] find stss -->", __FUNCTION__, __LINE__);
				fseek(pFileOrg, (uAtomSize - 8), SEEK_CUR);
				nFileOffset += (uAtomSize - 8);
				printf(": size(%d) fileOffset(%d)\n", uAtomSize, nFileOffset);
			}
			break;

			case _STSZ_:
			{
				printf("[%s %d] find stsz -->", __FUNCTION__, __LINE__);
				fseek(pFileOrg, (uAtomSize - 8), SEEK_CUR);
				nFileOffset += (uAtomSize - 8);
				printf(": size(%d) fileOffset(%d)\n", uAtomSize, nFileOffset);
			}
			break;

			case _FREE_:
			{
				printf("[%s %d] find free -->", __FUNCTION__, __LINE__);
				fseek(pFileOrg, (uAtomSize - 8), SEEK_CUR);
				nFileOffset += (uAtomSize - 8);
				printf(": size(%d) fileOffset(%d)\n", uAtomSize, nFileOffset);
			}
			break;

			default:
			{
				printf("[%s %d] not support atom(0x%08X) type.(skip) \n", __FUNCTION__, __LINE__, uAtomType);
				fseek(pFileOrg, (uAtomSize - 8), SEEK_CUR);
				nFileOffset += (uAtomSize - 8);
				//ftell(pFileOrg);
				printf(": size(%d) fileOffset(%d)\n", uAtomSize, nFileOffset);
			}
			break;
		}

		// nFileOffset += nbufSize;
		// } else {
		// 	nFileOffset += nbufOffset;
		// fseek(pFileOrg, nFileOffset, SEEK_SET);
		//ret = fread(pbuf, sizeof(unsigned char), nbufSize, pFileOrg);

		if( nFileOffset >= nFileSize ) {
			break;
		}
	}
	return 0;
}

/*----------------------*/

int STSZParsing(FILE* pFile, S_ROOT* root, const int nSize)
{
	S_STSZ *stsz;
	unsigned int TempInt;
	int i=0;

	stsz = &root->moov.trak[root->moov.trak_num].mdia.minf.stbl.stsz;
	
	fread(&TempInt, sizeof(unsigned char), 4, pFile);
	TempInt = Endian(TempInt);
	
	fread(&TempInt, sizeof(unsigned char), 4, pFile);
	stsz->DefaultSampleSize = Endian(TempInt);
	fread(&TempInt, sizeof(unsigned char), 4, pFile);
	stsz->SampleCount = Endian(TempInt);
	
	if(0 == stsz->DefaultSampleSize) {
		if(nSize > 12) {
			uint64_t nTemp64 = (uint64_t)stsz->SampleCount;
			if( (nSize - 12) < (nTemp64 * 4) ) {
				stsz->SampleCount = (unsigned int)((nSize - 12) >> 2);
			}
		}

		if(stsz->SampleCount) 
		{
			stsz->SampleSizeTable = (unsigned int *)calloc(sizeof(unsigned int), stsz->SampleCount);
			for(i=0; i<stsz->SampleCount; i++)
			{
				fread(&TempInt, sizeof(unsigned char), 4, pFile);
				stsz->SampleSizeTable[i] = Endian(TempInt);
			}
		}
	} else {

	}

	// debug
	printf("\t SampleCount : %d \r\n", stsz->SampleCount);
	for(i=0; i<10; i++)
	{
		printf("\t Sample[%d] : size(%u) \r\n", i+1, stsz->SampleSizeTable[i]);
	}

	return 1;
}

int STTSParsing(FILE* pFile, S_ROOT* root, const int nSize)
{
	S_STTS *stts;
	S_STTSTblElement *stts_tbl = NULL;
	unsigned int TempInt;
	int i=0;

	stts = &root->moov.trak[root->moov.trak_num].mdia.minf.stbl.stts;
	
	fread(&TempInt, sizeof(unsigned char), 4, pFile);
	TempInt = Endian(TempInt);
	fread(&TempInt, sizeof(unsigned char), 4, pFile);
	stts->entry_count = Endian(TempInt);

	if( nSize > 8 ) {
		unsigned int uTemp32 = stts->entry_count;
		if( (nSize - 8) < (uTemp32 * 8)) {
			stts->entry_count = (unsigned int)((nSize - 8) >> 3);
		}
	}

	if( stts->entry_count ) 
	{
		stts_tbl = (S_STTSTblElement *)calloc(stts->entry_count, sizeof(S_STTSTblElement));
		stts->ElementTbl = stts_tbl;

		for(i=0; i<stts->entry_count; i++)
		{
			
			fread(&TempInt, sizeof(unsigned char), 4, pFile);
			stts_tbl[i].SampleCounter = Endian(TempInt);
			fread(&TempInt, sizeof(unsigned char), 4, pFile);
			stts_tbl[i].SampleDelta = Endian(TempInt);
		}
	}

	// debug
	for(i=0; i<10; i++)
	{
		printf("\tSample_count : %d, Sample_delta : %d \r\n", stts_tbl[i].SampleCounter, stts_tbl[i].SampleDelta);
	}
	return 1;
}

int STCOParsing(FILE* pFile, S_ROOT* root, const int nSize)
{
	S_STCO *stco;
	unsigned int TempInt;
	int i=0;

	stco = &root->moov.trak[root->moov.trak_num].mdia.minf.stbl.stco;
	fread(&TempInt, sizeof(unsigned char), 4, pFile);
	TempInt = Endian(TempInt);
	stco->bVersion = 0;		// 32bit

	fread(&TempInt, sizeof(unsigned char), 4, pFile);
	stco->entry_count = Endian(TempInt);

	if( nSize > 8 ) {
		unsigned int uTemp32 = stco->entry_count;
		if( (nSize - 8) < (uTemp32 * 4)) {
			stco->entry_count = (unsigned int)((nSize - 8) >> 2);
		}
	}

	if(stco->entry_count) {
		stco->Uint32Table = (unsigned int *)calloc(1, (stco->entry_count * 4));
		for(i=0; i<stco->entry_count; i++) 
		{
			fread(&TempInt, sizeof(unsigned char), 4, pFile);
			stco->Uint32Table[i] = Endian(TempInt);
		}
	}

	// debug
	printf("\tChunk Count : %d \r\n", stco->entry_count);
	for(i=0; i<10; i++) {
		printf("\tchunk_offset[%d] : %d \r\n", i+1, stco->Uint32Table[i]);
	}

	return 1;
}

int STSSParsing(FILE* pFile, S_ROOT* root, const int nSize)
{
	S_STSS	*stss;
	unsigned int TempInt;
	int i=0;

	stss = &root->moov.trak[root->moov.trak_num].mdia.minf.stbl.stss;
	fread(&TempInt, sizeof(unsigned char), 4, pFile);
	TempInt = Endian(TempInt);
	fread(&TempInt, sizeof(unsigned char), 4, pFile);
	stss->entry_count = Endian(TempInt);

	if( nSize > 8 ) {
		unsigned int uTemp32 = stss->entry_count;
		if( (nSize - 8) < (uTemp32 * 4)) {
			stss->entry_count = (unsigned int)((nSize - 8) >> 2);
		}
	}

	if(stss->entry_count)
	{
		stss->existence = 1;
		stss->SampleNumberTable = (unsigned int *)calloc(1, (stss->entry_count * 4));
		for(i=0; i<stss->entry_count; i++)
		{
			fread(&TempInt, sizeof(unsigned char), 4, pFile);
			stss->SampleNumberTable[i] = Endian(TempInt);
		}
	}	

	// debug
	printf("\tSyncSample Count : %d \r\n", stss->entry_count);
	for(i=0; i<10; i++) {
		printf("\tSample[%d] : %d \r\n", i+1, stss->SampleNumberTable[i]);
	}

	return 1;
}

int STSCParsing(FILE* pFile, S_ROOT* root, const int nSize)
{
	S_STSC *stsc;
	S_STSCTblElement *stsc_tbl = NULL;
	unsigned int TempInt;
	int i=0;

	stsc = &root->moov.trak[root->moov.trak_num].mdia.minf.stbl.stsc;
	fread(&TempInt, sizeof(unsigned char), 4, pFile);	// version & flags
	TempInt = Endian(TempInt);
	fread(&TempInt, sizeof(unsigned char), 4, pFile);	// entry_count
	stsc->entry_count = Endian(TempInt);
	// printf("\tEntry_count : %d \r\n", stsc->entry_count);

	if( nSize > 8 ) {
		unsigned int uTemp32 = stsc->entry_count;
		if( (nSize - 8) < (uTemp32 * 12)) {
			stsc->entry_count = (unsigned int)((nSize - 8) / 12);
		}
	}

	stsc_tbl = (S_STSCTblElement *)calloc(stsc->entry_count, sizeof(S_STSCTblElement));
	stsc->ElementTbl = stsc_tbl;

	for(i=0; i<stsc->entry_count; i++)
	{
		fread(&TempInt, sizeof(unsigned char), 4, pFile);
		stsc_tbl[i].FirstChunkTable = Endian(TempInt);
		fread(&TempInt, sizeof(unsigned char), 4, pFile);
		stsc_tbl[i].SamplesPerChunkTable = Endian(TempInt);
		fread(&TempInt, sizeof(unsigned char), 4, pFile);
		stsc_tbl[i].SampleDescriptionIDTable = Endian(TempInt);
	}

	// debug
	printf("\tSTSC Count : %d\r\n", stsc->entry_count);
	for(i=0; i<10; i++)
	{
		printf("\tEntry[%d], first-chunk : %d, sample-per-chunk : %d, sample-desc-index : %d \r\n", 
				i+1, stsc_tbl[i].FirstChunkTable, stsc_tbl[i].SamplesPerChunkTable, stsc_tbl[i].SampleDescriptionIDTable);
	}

	return 1;
}

int STBLParsing(FILE* pFile, S_ROOT* root, const int nSize)
{
	int i = 0, ret = 0;
	unsigned int uAtomSize = 0, uAtomType = 0;
	int nBoxOffset = 0, nOrgOffset = 0;

	do
	{
		ret = fread(&uAtomSize, sizeof(unsigned int), 1, pFile);
		uAtomSize = Endian(uAtomSize);
		ret = fread(&uAtomType, sizeof(unsigned int), 1, pFile);
		uAtomType = Endian(uAtomType);
		nBoxOffset += 8;

		switch(uAtomType)
		{
			case _STSD_:
			{
				printf("[%s %d] find \t\t\t\t_STSD_ --> size(%d) Box Offset(%d) \r\n", __FUNCTION__, __LINE__, uAtomSize, nBoxOffset);
				nOrgOffset = ftell(pFile);
				// if(MVHDParsing(pFile, root, (uAtomSize - 8)) < 0) {
				// 	// ERROR
				// } 

				fseek(pFile, (nOrgOffset + uAtomSize - 8), SEEK_SET);
				nBoxOffset += (uAtomSize - 8);
			}
			break;
			case _STTS_:
			{
				printf("[%s %d] find \t\t\t\t_STTS_ --> size(%d) Box Offset(%d) \r\n", __FUNCTION__, __LINE__, uAtomSize, nBoxOffset);
				nOrgOffset = ftell(pFile);
				if(STTSParsing(pFile, root, (uAtomSize - 8)) < 0) {
					// ERROR
				} 
				fseek(pFile, (nOrgOffset + uAtomSize - 8), SEEK_SET);
				nBoxOffset += (uAtomSize - 8);
			}
			break;
			case _STSC_:
			{
				printf("[%s %d] find \t\t\t\t_STSC_ --> size(%d) Box Offset(%d) \r\n", __FUNCTION__, __LINE__, uAtomSize, nBoxOffset);
				nOrgOffset = ftell(pFile);
				if(STSCParsing(pFile, root, (uAtomSize - 8)) < 0) {
					// ERROR
				} 
				fseek(pFile, (nOrgOffset + uAtomSize - 8), SEEK_SET);
				nBoxOffset += (uAtomSize - 8);
			}
			break;
			case _STCO_:
			{
				printf("[%s %d] find \t\t\t\t_STCO_ --> size(%d) Box Offset(%d) \r\n", __FUNCTION__, __LINE__, uAtomSize, nBoxOffset);
				nOrgOffset = ftell(pFile);
				if(STCOParsing(pFile, root, (uAtomSize - 8)) < 0) {
					// ERROR
				} 
				fseek(pFile, (nOrgOffset + uAtomSize - 8), SEEK_SET);
				nBoxOffset += (uAtomSize - 8);
			}
			break;
			case _STSZ_:
			{
				printf("[%s %d] find \t\t\t\t_STSZ_ --> size(%d) Box Offset(%d) \r\n", __FUNCTION__, __LINE__, uAtomSize, nBoxOffset);
				nOrgOffset = ftell(pFile);
				if(STSZParsing(pFile, root, (uAtomSize - 8)) < 0) {
					// ERROR
				} 
				fseek(pFile, (nOrgOffset + uAtomSize - 8), SEEK_SET);
				nBoxOffset += (uAtomSize - 8);
			}
			break;
			case _STSS_:
			{
				printf("[%s %d] find \t\t\t\t_STSS_ --> size(%d) Box Offset(%d) \r\n", __FUNCTION__, __LINE__, uAtomSize, nBoxOffset);
				nOrgOffset = ftell(pFile);
				if(STSSParsing(pFile, root, (uAtomSize - 8)) < 0) {
					// ERROR
				} 
				fseek(pFile, (nOrgOffset + uAtomSize - 8), SEEK_SET);
				nBoxOffset += (uAtomSize - 8);
			}
			break;
			case _CTTS_:
			{
				printf("[%s %d] find \t\t\t\t_CTTS_ --> size(%d) Box Offset(%d) \r\n", __FUNCTION__, __LINE__, uAtomSize, nBoxOffset);
				fseek(pFile, (uAtomSize - 8), SEEK_CUR);
				nBoxOffset += (uAtomSize - 8);
			}
			break;

			default:
			{
				printf("[%s %d] not support atom(0x%08X) type.(skip) \n", __FUNCTION__, __LINE__, uAtomType);
				fseek(pFile, (uAtomSize - 8), SEEK_CUR);
				nBoxOffset += (uAtomSize - 8);
				printf(": size(%d) fileOffset(%d)\n", uAtomSize, nBoxOffset);
			}
			break;
		}
		

	} while(nBoxOffset < nSize);
	return 1;
}

int MINFParsing(FILE* pFile, S_ROOT* root, const int nSize)
{
	int i = 0, ret = 0;
	unsigned int uAtomSize = 0, uAtomType = 0;
	int nBoxOffset = 0, nOrgOffset = 0;

	do
	{
		ret = fread(&uAtomSize, sizeof(unsigned int), 1, pFile);
		uAtomSize = Endian(uAtomSize);
		ret = fread(&uAtomType, sizeof(unsigned int), 1, pFile);
		uAtomType = Endian(uAtomType);
		nBoxOffset += 8;

		switch(uAtomType)
		{
			case _DINF_:
			{
				printf("[%s %d] find \t\t\t_DINF_ --> size(%d) Box Offset(%d) \r\n", __FUNCTION__, __LINE__, uAtomSize, nBoxOffset);
				nOrgOffset = ftell(pFile);
				// if(MVHDParsing(pFile, root, (uAtomSize - 8)) < 0) {
				// 	// ERROR
				// } 

				fseek(pFile, (nOrgOffset + uAtomSize - 8), SEEK_SET);
				nBoxOffset += (uAtomSize - 8);
			}
			break;
			case _STBL_:
			{
				printf("[%s %d] find \t\t\t_STBL_ --> size(%d) Box Offset(%d) \r\n", __FUNCTION__, __LINE__, uAtomSize, nBoxOffset);
				nOrgOffset = ftell(pFile);
				if(STBLParsing(pFile, root, (uAtomSize - 8)) < 0) {
					// ERROR
				} 
				fseek(pFile, (nOrgOffset + uAtomSize - 8), SEEK_SET);
				nBoxOffset += (uAtomSize - 8);
			}
			break;
			case _VMHD_:
			{
				printf("[%s %d] find \t\t\t_VMHD_ --> size(%d) Box Offset(%d) \r\n", __FUNCTION__, __LINE__, uAtomSize, nBoxOffset);
				fseek(pFile, (uAtomSize - 8), SEEK_CUR);
				nBoxOffset += (uAtomSize - 8);
			}
			break;
			case _SMHD_:
			{
				printf("[%s %d] find \t\t\t_SMHD_ --> size(%d) Box Offset(%d) \r\n", __FUNCTION__, __LINE__, uAtomSize, nBoxOffset);
				fseek(pFile, (uAtomSize - 8), SEEK_CUR);
				nBoxOffset += (uAtomSize - 8);
			}
			break;

			default:
			{
				printf("[%s %d] not support atom(0x%08X) type.(skip) - ", __FUNCTION__, __LINE__, uAtomType);
				fseek(pFile, (uAtomSize - 8), SEEK_CUR);
				nBoxOffset += (uAtomSize - 8);
				printf(" size(%d) fileOffset(%d)\n", uAtomSize, nBoxOffset);
			}
			break;
		}
		

	} while(nBoxOffset < nSize);
	return 1;
} 

int HDLRParsing(FILE* pFile, S_ROOT* root, const int nSize)
{
	S_HDLR *hdlr;
	unsigned int TempInt;
	int nNameLength = nSize;
	
	hdlr = &root->moov.trak[root->moov.trak_num].mdia.hdlr;
	fread(&TempInt, sizeof(unsigned char), 4, pFile);
	TempInt = Endian(TempInt);
	nNameLength -= 4;
	
	fseek(pFile, (4), SEEK_CUR);		// pre_defined = 0
	nNameLength -= (4);
	fread(&TempInt, sizeof(unsigned char), 4, pFile);
	hdlr->handler_type = Endian(TempInt);
	nNameLength -= 4;
	fseek(pFile, (4+4+4), SEEK_CUR);		// reserved
	nNameLength -= (4+4+4);

	hdlr->pName = (unsigned char *)calloc(sizeof(unsigned char), nNameLength);
	fread(hdlr->pName, sizeof(unsigned char), nNameLength, pFile);

	printf("HDLR -> Name(%d) : %s \r\n", nNameLength, hdlr->pName);

	return 1;
}

int MDHDParsing(FILE* pFile, S_ROOT* root, const int nSize)
{
	S_MDHD *mdhd;
	unsigned int TempInt;
	unsigned char flags = 0;
	
	mdhd = &root->moov.trak[root->moov.trak_num].mdia.mdhd;
	fread(&TempInt, sizeof(unsigned char), 4, pFile);
	TempInt = Endian(TempInt);
	mdhd->version = (unsigned char)((TempInt & 0xFF000000) >> 24);

	if( mdhd->version ) {
		// version is 1.
	} else {
		// version is 0.
		fread(&TempInt, sizeof(unsigned char), 4, pFile);
		mdhd->creation_time.val32 = Endian(TempInt);
		fread(&TempInt, sizeof(unsigned char), 4, pFile);
		mdhd->modification_time.val32 = Endian(TempInt);
		fread(&TempInt, sizeof(unsigned char), 4, pFile);
		mdhd->timescale = Endian(TempInt);
		fread(&TempInt, sizeof(unsigned char), 4, pFile);
		mdhd->duration.val32 = Endian(TempInt);
	}
	fseek(pFile, (4+4+4+4), SEEK_CUR);
	// debug
	{
		float fPlayDuration = 0;
		fPlayDuration = (float)(mdhd->duration.val32 / mdhd->timescale);
		printf("MDHD -> fPlayDuration : %f [sec] \r\n", fPlayDuration);
	}

	return 1;
}

int MDIAParsing(FILE* pFile, S_ROOT* root, const int nSize)
{
	int i = 0, ret = 0;
	unsigned int uAtomSize = 0, uAtomType = 0;
	int nBoxOffset = 0, nOrgOffset = 0;

	do
	{
		ret = fread(&uAtomSize, sizeof(unsigned int), 1, pFile);
		uAtomSize = Endian(uAtomSize);
		ret = fread(&uAtomType, sizeof(unsigned int), 1, pFile);
		uAtomType = Endian(uAtomType);
		nBoxOffset += 8;

		switch(uAtomType)
		{
			case _MDHD_:
			{
				printf("[%s %d] find \t\t_MDHD_ --> size(%d) Box Offset(%d) \r\n", __FUNCTION__, __LINE__, uAtomSize, nBoxOffset);
				nOrgOffset = ftell(pFile);
				if(MDHDParsing(pFile, root, (uAtomSize - 8)) < 0) {
					// ERROR
				} 

				fseek(pFile, (nOrgOffset + uAtomSize - 8), SEEK_SET);
				nBoxOffset += (uAtomSize - 8);
			}
			break;
			case _HDLR_:
			{
				printf("[%s %d] find \t\t_HDLR_ --> size(%d) Box Offset(%d) \r\n", __FUNCTION__, __LINE__, uAtomSize, nBoxOffset);
				
				nOrgOffset = ftell(pFile);
				if(HDLRParsing(pFile, root, (uAtomSize - 8)) < 0) {
					// ERROR
				} 

				fseek(pFile, (nOrgOffset + uAtomSize - 8), SEEK_SET);
				nBoxOffset += (uAtomSize - 8);
			}
			break;
			case _MINF_:
			{
				printf("[%s %d] find \t\t_MINF_ --> size(%d) Box Offset(%d) \r\n", __FUNCTION__, __LINE__, uAtomSize, nBoxOffset);
				nOrgOffset = ftell(pFile);
				if(MINFParsing(pFile, root, (uAtomSize - 8)) < 0) {
					// ERROR
				} 

				fseek(pFile, (nOrgOffset + uAtomSize - 8), SEEK_SET);
				nBoxOffset += (uAtomSize - 8);
			}
			break;

			default:
			{
				printf("[%s %d] not support atom(0x%08X) type.(skip) \n", __FUNCTION__, __LINE__, uAtomType);
				fseek(pFile, (uAtomSize - 8), SEEK_CUR);
				nBoxOffset += (uAtomSize - 8);
				printf(": size(%d) fileOffset(%d)\n", uAtomSize, nBoxOffset);
			}
			break;
		}
		

	} while(nBoxOffset < nSize);
	return 1;
}


int TKHDParsing(FILE* pFile, S_ROOT* root, const int nSize)
{
	S_TKHD *tkhd;
	unsigned int TempInt;
	unsigned char flags = 0;

	tkhd = &root->moov.trak[root->moov.trak_num].tkhd;
	fread(&TempInt, sizeof(unsigned char), 4, pFile);
	TempInt = Endian(TempInt);
	printf("THKD -> TempInt : %d \r\n", TempInt);
	tkhd->version = (unsigned char)((TempInt & 0xFF000000) >> 24);
	flags = (((TempInt & 0x00FFFFFF) >> 16) & 0x01) ? 1 : 0;

	printf("THKD -> version : %d \r\n", tkhd->version);

	if(tkhd->version) {
		// version is 1.
	} else {
		// version is 0.
		fread(&TempInt, sizeof(unsigned char), 4, pFile);
		tkhd->creation_time.val32 = Endian(TempInt);
		fread(&TempInt, sizeof(unsigned char), 4, pFile);
		tkhd->modification_time.val32 = Endian(TempInt);
		fread(&TempInt, sizeof(unsigned char), 4, pFile);
		tkhd->track_ID = Endian(TempInt);
		fread(&TempInt, sizeof(unsigned char), 4, pFile);	// skip 4 bytes
		fread(&TempInt, sizeof(unsigned char), 4, pFile);
		tkhd->duration.val32 = Endian(TempInt);
	}
	fseek(pFile, (4+4+4+4), SEEK_CUR);
	fseek(pFile, 36, SEEK_CUR);	// 4 bytes * 9 ==> matrix

	fread(&TempInt, sizeof(unsigned char), 4, pFile);
	
	tkhd->width = (unsigned int)(Endian(TempInt) >> 16);
	fread(&TempInt, sizeof(unsigned char), 4, pFile);
	tkhd->height = (unsigned int)(Endian(TempInt) >> 16);
	printf("THKD -> width : %d, height : %d \r\n", tkhd->width, tkhd->height);

	return 1;
}

int TRAKParsing(FILE* pFile, S_ROOT* root, const int nSize)
{
	int i = 0, ret = 0;
	unsigned int uAtomSize = 0, uAtomType = 0;
	int nBoxOffset = 0, nOrgOffset = 0;

	do
	{
		ret = fread(&uAtomSize, sizeof(unsigned int), 1, pFile);
		uAtomSize = Endian(uAtomSize);
		ret = fread(&uAtomType, sizeof(unsigned int), 1, pFile);
		uAtomType = Endian(uAtomType);
		nBoxOffset += 8;

		switch(uAtomType)
		{
			case _TKHD_:
			{
				printf("[%s %d] find \t_TKHD_ --> size(%d) Box Offset(%d) \r\n", __FUNCTION__, __LINE__, uAtomSize, nBoxOffset);
				nOrgOffset = ftell(pFile);
				if(TKHDParsing(pFile, root, (uAtomSize - 8)) < 0) {
					// ERROR
				} 

				fseek(pFile, (nOrgOffset + uAtomSize - 8), SEEK_SET);
				nBoxOffset += (uAtomSize - 8);
			}
			break;
			case _EDTS_:
			{
				printf("[%s %d] find \t_EDTS_ --> size(%d) Box Offset(%d) \r\n", __FUNCTION__, __LINE__, uAtomSize, nBoxOffset);
				fseek(pFile, (uAtomSize - 8), SEEK_CUR);
				nBoxOffset += (uAtomSize - 8);
			}
			break;
			case _MDIA_:
			{
				printf("[%s %d] find \t_MDIA_ --> size(%d) Box Offset(%d) \r\n", __FUNCTION__, __LINE__, uAtomSize, nBoxOffset);
				nOrgOffset = ftell(pFile);
				if( MDIAParsing(pFile, root, (uAtomSize - 8)) < 0 ) {
					// ERROR
				}
				fseek(pFile, (nOrgOffset + uAtomSize - 8), SEEK_SET);
				nBoxOffset += (uAtomSize - 8);
			}
			break;

			default:
			{
				printf("[%s %d] not support atom(0x%08X) type.(skip) \n", __FUNCTION__, __LINE__, uAtomType);
				fseek(pFile, (uAtomSize - 8), SEEK_CUR);
				nBoxOffset += (uAtomSize - 8);
				printf(": size(%d) fileOffset(%d)\n", uAtomSize, nBoxOffset);
			}
			break;
		}
		

	} while(nBoxOffset < nSize);
	return 1;
}

int MVHDParsing(FILE* pFile, S_ROOT* root, const int nSize)
{
	S_MVHD *mvhd;
	unsigned int TempInt;

	mvhd = &root->moov.mvhd;
	
	fread(&TempInt, sizeof(unsigned char), 4, pFile);
	TempInt = Endian(TempInt);

	mvhd->version = (unsigned char)((TempInt & 0xFF000000) >> 24);
	if(mvhd->version) {
		// version is 1.
	} else {
		// version is 0.
		fread(&TempInt, sizeof(unsigned char), 4, pFile);
		mvhd->creation_time.val32 = Endian(TempInt);
		fread(&TempInt, sizeof(unsigned char), 4, pFile);
		mvhd->modification_time.val32 = Endian(TempInt);
		fread(&TempInt, sizeof(unsigned char), 4, pFile);
		mvhd->timescale = Endian(TempInt);
		fread(&TempInt, sizeof(unsigned char), 4, pFile);
		mvhd->duration.val32 = Endian(TempInt);
		printf("\t%d\r\n", mvhd->duration.val32);
	}
	fseek(pFile, 76, 1);
	fread(&TempInt, sizeof(unsigned char), 4, pFile);
	mvhd->next_track_ID = Endian(TempInt);
	
	return 0;	
}

int MOOVParsing(FILE* pFile, S_ROOT* root, const int nSize)
{
	int i = 0, ret = 0;
	unsigned int uAtomSize = 0, uAtomType = 0;
	int nBoxOffset = 0, nOrgOffset = 0;

	do
	{
		ret = fread(&uAtomSize, sizeof(unsigned int), 1, pFile);
		uAtomSize = Endian(uAtomSize);
		ret = fread(&uAtomType, sizeof(unsigned int), 1, pFile);
		uAtomType = Endian(uAtomType);
		nBoxOffset += 8;

		switch(uAtomType)
		{
			case _MVHD_:
			{
				printf("[%s %d] find _MVHD_ --> size(%d) Box Offset(%d) \r\n", __FUNCTION__, __LINE__, uAtomSize, nBoxOffset);
				nOrgOffset = ftell(pFile);
				if(MVHDParsing(pFile, root, (uAtomSize - 8)) < 0) {
					// ERROR
				} 

				fseek(pFile, (nOrgOffset + uAtomSize - 8), SEEK_SET);
				nBoxOffset += (uAtomSize - 8);
			}
			break;
			case _TRAK_:
			{
				printf("[%s %d] find _TRAK_ --> size(%d) Box Offset(%d) \r\n", __FUNCTION__, __LINE__, uAtomSize, nBoxOffset);
				nOrgOffset = ftell(pFile);
				
				if(0 == root->moov.trak_num) {
					root->track_reader = (S_TRACK_READER *)calloc(2/*root->moov.trak_num*/, sizeof(S_TRACK_READER));
					root->moov.trak = (S_TRAK *)calloc(2, sizeof(S_TRAK));
				}

				if(TRAKParsing(pFile, root, (uAtomSize - 8)) < 0) {
					// ERROR
				}
				fseek(pFile, (nOrgOffset + uAtomSize - 8), SEEK_SET);
				nBoxOffset += (uAtomSize - 8);

				root->moov.trak_num++;
			}
			break;
			case _META_:
			{
				printf("[%s %d] find _META_ --> size(%d) Box Offset(%d) \r\n", __FUNCTION__, __LINE__, uAtomSize, nBoxOffset);
				fseek(pFile, (uAtomSize - 8), SEEK_CUR);
				nBoxOffset += (uAtomSize - 8);
			}
			break;
			case _MVEX_:
			{
				printf("[%s %d] find _MVEX_ --> size(%d) Box Offset(%d) \r\n", __FUNCTION__, __LINE__, uAtomSize, nBoxOffset);
				fseek(pFile, (uAtomSize - 8), SEEK_CUR);
				nBoxOffset += (uAtomSize - 8);
			}
			break;
			case _UDTA_:
			{
				printf("[%s %d] find _UDTA_ --> size(%d) Box Offset(%d) \r\n", __FUNCTION__, __LINE__, uAtomSize, nBoxOffset);
				fseek(pFile, (uAtomSize - 8), SEEK_CUR);
				nBoxOffset += (uAtomSize - 8);
			}
			break;
			default:
			{
				printf("[%s %d] not support atom(0x%08X) type.(skip) - ", __FUNCTION__, __LINE__, uAtomType);
				fseek(pFile, (uAtomSize - 8), SEEK_CUR);
				nBoxOffset += (uAtomSize - 8);
				printf(" size(%d) fileOffset(%d)\n", uAtomSize, nBoxOffset);
			}
			break;
		}
	} while(nBoxOffset < nSize);

	return 1;
}



int ReadOneSample(FILE* pFile, S_ROOT* root)
{
	int retVal =0;
	int nStcoIndex=0, nStscIndex=1;
	int nSamplePerChunk = 0, nSampleIndex=0, nSampleCount = 0;
	unsigned char* pbuf = NULL;
	size_t bufLength = 32;

	int nChunkOffset = 0, nReadSize = 0;
	int NaluSize = 4;
	int nFrameSize = 0;

	// debug
	int i=0;

	// only video track....
	int nTrackNum = -1;
	if(_VIDE_ == root->moov.trak[0].mdia.hdlr.handler_type ) {
		nTrackNum = 0;
	} else if(_VIDE_ == root->moov.trak[1].mdia.hdlr.handler_type ) {
		nTrackNum = 1;
	} else {
		printf("[ERROR] Not support track.\r\n");
		return 0;
	}

	S_STSC *stsc = &root->moov.trak[nTrackNum].mdia.minf.stbl.stsc;
	S_STCO *stco = &root->moov.trak[nTrackNum].mdia.minf.stbl.stco;
	S_STSZ *stsz = &root->moov.trak[nTrackNum].mdia.minf.stbl.stsz;
	S_STTS *stts = &root->moov.trak[nTrackNum].mdia.minf.stbl.stts;

	S_STSCTblElement *stsc_tbl = NULL;

	if( pbuf ) {
		free(pbuf);
		pbuf = NULL;
	}
	pbuf = (unsigned char *)calloc(1, bufLength);
	memset(pbuf, 0, bufLength);

	stsc_tbl = stsc->ElementTbl;

	for(nStcoIndex=0; nStcoIndex<stco->entry_count; nStcoIndex++)
	{
		// stco offset seek
		nChunkOffset = fseek(pFile, stco->Uint32Table[nStcoIndex], SEEK_SET);

		for(nSampleIndex=0; nSampleIndex<stsc_tbl[nStscIndex - 1].SamplesPerChunkTable; nSampleIndex++)
		{
			memset(pbuf, 0, bufLength);
			nFrameSize = 0;
			nSampleCount++;

			// stsz size 만큼 read....
		#if 0
			nReadSize = fread(pbuf, sizeof(unsigned char), stsz->SampleSizeTable[nSamplePerChunk + nSampleIndex], pFile);
		#else
			nReadSize = fread(pbuf, sizeof(unsigned char), bufLength, pFile);
			fseek(pFile, (stsz->SampleSizeTable[nSamplePerChunk + nSampleIndex] - bufLength), SEEK_CUR);
		#endif
			// if( nReadSize != stsz->SampleSizeTable[nSamplePerChunk + nSampleIndex]) {
			// 	printf("ERROR. request size : %d, result size : %d \r\n", stsz->SampleSizeTable[nSamplePerChunk + nSampleIndex], nReadSize);
			// 	printf("nSamplePerChunk: %d nSampleIndex: %d \r\n", nSamplePerChunk, nSampleIndex);
			// }

			// frame size check
			{
				nFrameSize = ((int)pbuf[0] << 24) | ((int)pbuf[1] << 16) | ((int)pbuf[2] << 8) | (int)pbuf[3];
				// printf("Sample(%d) Size(%d) Size(0x%08X)\r\n", nSampleCount, nFrameSize, nFrameSize);

				if( stsz->SampleSizeTable[nSamplePerChunk + nSampleIndex] != (unsigned int)(nFrameSize + NaluSize)) {
					printf("[ERROR] Sample size(%u) and frame size(%u) are different. \r\n", stsz->SampleSizeTable[nSamplePerChunk + nSampleIndex], (unsigned int)(nFrameSize + NaluSize));
					retVal = -1;
					return retVal;
				}

				if( (pbuf[NaluSize] & 0x1F) == 0 || (pbuf[NaluSize] & 0x1F) > 19 ) {
					printf("[ERROR] NAL unit type false. \r\n");
					retVal = -1;
					return retVal;
				}
			}

#if 0
			// debug
			printf("Chunk #%d: %d \t", nStcoIndex+1, stco->Uint32Table[nStcoIndex]);
			// printf("ChunkIndex : %d, nStscIndex : %d, nSampleIndex : %d, Sample Size : %d\r\n", 
			// 					nStcoIndex+1, nStscIndex, nSampleIndex+1, stsz->SampleSizeTable[nSamplePerChunk + nSampleIndex]);	
			// printf("stsc_tbl[%d].FirstChunkTable : %d \t\t %d \r\n", nStscIndex, stsc_tbl[nStscIndex].FirstChunkTable, stsc->ElementTbl[nStscIndex].FirstChunkTable);

			printf("Sample[%3d] size(%d):  \t\t", nSampleCount, stsz->SampleSizeTable[nSamplePerChunk + nSampleIndex]);
			for(i=0; i<10; i++) {
				printf("%02X ", pbuf[i]);
			}
			printf("\r\n");
#endif
		}
		nSamplePerChunk = nSampleCount;
		
		// file seek to next chunk offset.
		if((nStcoIndex + 1) == (stsc_tbl[nStscIndex].FirstChunkTable - 1)) {
			nStscIndex++;
			// printf("\t\t\tSTSC Index : %d \t\tSTCO Index: %d\r\n", nStscIndex, nStcoIndex);
		}
	}
	
	if( pbuf ) {
		free(pbuf);
		pbuf = NULL;
	}

	return 1;
}


void MP4Close(S_ROOT* root)
{
	S_TRAK *trak;
	int i=0;

	if(root->moov.trak) 
	{
		// track 2 fix..
		for(i=0; i<2; i++)
		{
			trak = &(root->moov.trak[i]);
			if( (trak->mdia.hdlr.unNamelength > 0) || (NULL != trak->mdia.hdlr.pName) ) {
				free(trak->mdia.hdlr.pName);
				trak->mdia.hdlr.pName = NULL;
				trak->mdia.hdlr.unNamelength = 0;
			}

			if (trak->mdia.minf.stbl.stts.ElementTbl) {
				free(trak->mdia.minf.stbl.stts.ElementTbl);
				trak->mdia.minf.stbl.stts.ElementTbl = NULL;
			}

			if (trak->mdia.minf.stbl.stsc.ElementTbl) {
				free(trak->mdia.minf.stbl.stsc.ElementTbl);
				trak->mdia.minf.stbl.stsc.ElementTbl = NULL;
			}

			if (trak->mdia.minf.stbl.stco.Uint32Table) {
				free(trak->mdia.minf.stbl.stco.Uint32Table);
				trak->mdia.minf.stbl.stco.Uint32Table = NULL;
			}

			if (trak->mdia.minf.stbl.stsz.SampleSizeTable) {
				free(trak->mdia.minf.stbl.stsz.SampleSizeTable);
				trak->mdia.minf.stbl.stsz.SampleSizeTable = NULL;
			}
		}

		free(root->moov.trak);
		root->moov.trak = NULL;
	}
}

int MP4FileOpen(char* pFile)
{
	FILE *pFileOrg, *pFileOut;
	int retVal = 0;
	int nFileSize = 0, nFileOffset = 0;
	int i = 0;
	int ret = 0;
	unsigned int bFindChk = 0;
	unsigned char bChkAtom = 0;

	unsigned int uAtomSize = 0, uAtomType = 0;

	// File open
	pFileOrg = fopen(pFile, "rb");
	if(NULL == pFileOrg) {
		printf("[%s %d] File open error.\n", __FUNCTION__, __LINE__);
		return 0;
	} else {
		printf("[%s %d] File open success.\n", __FUNCTION__, __LINE__);
	}
	// file size check
	nFileSize = fseek(pFileOrg, 0, SEEK_END);
	nFileSize = ftell(pFileOrg);
	
	nFileOffset = fseek(pFileOrg, 0, SEEK_SET);
	if( nFileSize < 9 ) {
		retVal = -1;
		printf("[%s %d] ERROR. File size less than 8 byte. (%d) \r\n", __FUNCTION__, __LINE__, retVal);
		return retVal;
	}


	S_ROOT	*root;
	root = (S_ROOT *)calloc(1, sizeof(root));
	if(!root) {
		retVal = -1;
		printf("[%s %d] ERROR. Memory alloc fail. (%d) \r\n", __FUNCTION__, __LINE__, retVal);
		return retVal;
	}

	root->filesize = (uint64_t)nFileSize;
	printf("[%s %d] File size : %lu \r\n", __FUNCTION__, __LINE__, root->filesize);
	

	nFileOffset = 0;
	while(1)
	{
		//unsigned char tempType[4] = {0, };

		ret = fread(&uAtomSize, sizeof(unsigned int), 1, pFileOrg);
		uAtomSize = Endian(uAtomSize);
		ret = fread(&uAtomType, sizeof(unsigned int), 1, pFileOrg);
		uAtomType = Endian(uAtomType);
		nFileOffset += 8;

		
		// printf("[%s %d] AtomType(0x%08X) AtomSize(%d)\n", __FUNCTION__, __LINE__, uAtomType, uAtomSize);
		
		switch(uAtomType) 
		{
			case _FTYP_:
			{
				printf("[%s %d] find _FTYP_ -->", __FUNCTION__, __LINE__);
				fseek(pFileOrg, (uAtomSize - 8), SEEK_CUR);
				nFileOffset += (uAtomSize - 8);
				printf(": size(%d) fileOffset(%d)\n", uAtomSize, nFileOffset);
				//return 0;
			}
			break;

			case _MDAT_:
			{
				printf("[%s %d] find _MDAT_ -->", __FUNCTION__, __LINE__);
				fseek(pFileOrg, (uAtomSize - 8), SEEK_CUR);
				nFileOffset += (uAtomSize - 8);
				printf(": size(%d) fileOffset(%d)\n", uAtomSize, nFileOffset);
			}
			break;

			case _MOOV_:
			{
				int j = 0;
				printf("[%s %d] find _MOOV_ --> size(%d)  fileOffset(%d) \r\n", __FUNCTION__, __LINE__, uAtomSize, nFileOffset);
								
				if( MOOVParsing(pFileOrg, root, (uAtomSize - 8)) < 0) {
					// ERROR.
					printf("[%s %d] MOOVParsing ERROR. \r\n", __FUNCTION__, __LINE__);
				}
				
				fseek(pFileOrg, (nFileOffset + uAtomSize - 8), SEEK_SET);
				nFileOffset += (uAtomSize - 8);
			}
			break;
#if 0
			case _STSC_:
			{
				printf("[%s %d] find stsc -->", __FUNCTION__, __LINE__);
				fseek(pFileOrg, (uAtomSize - 8), SEEK_CUR);
				nFileOffset += (uAtomSize - 8);
				printf(": size(%d) fileOffset(%d)\n", uAtomSize, nFileOffset);
			}
			break;

			case _STSS_:
			{
				printf("[%s %d] find stss -->", __FUNCTION__, __LINE__);
				fseek(pFileOrg, (uAtomSize - 8), SEEK_CUR);
				nFileOffset += (uAtomSize - 8);
				printf(": size(%d) fileOffset(%d)\n", uAtomSize, nFileOffset);
			}
			break;

			case _STSZ_:
			{
				printf("[%s %d] find stsz -->", __FUNCTION__, __LINE__);
				fseek(pFileOrg, (uAtomSize - 8), SEEK_CUR);
				nFileOffset += (uAtomSize - 8);
				printf(": size(%d) fileOffset(%d)\n", uAtomSize, nFileOffset);
			}
			break;
#endif
			case _FREE_:
			{
				printf("[%s %d] find _FREE_ -->", __FUNCTION__, __LINE__);
				fseek(pFileOrg, (uAtomSize - 8), SEEK_CUR);
				nFileOffset += (uAtomSize - 8);
				printf(": size(%d) fileOffset(%d)\n", uAtomSize, nFileOffset);
			}
			break;
			case _UDTA_:
			{
				printf("[%s %d] find _UDTA_ -->", __FUNCTION__, __LINE__);
				fseek(pFileOrg, (uAtomSize - 8), SEEK_CUR);
				nFileOffset += (uAtomSize - 8);
				printf(": size(%d) fileOffset(%d)\n", uAtomSize, nFileOffset);
			}
			break;

			default:
			{
				printf("[%s %d] not support atom(0x%08X) type.(skip) \n", __FUNCTION__, __LINE__, uAtomType);
				fseek(pFileOrg, (uAtomSize - 8), SEEK_CUR);
				nFileOffset += (uAtomSize - 8);
				//ftell(pFileOrg);
				printf(": size(%d) fileOffset(%d)\n", uAtomSize, nFileOffset);
			}
			break;
		}
		if( nFileOffset >= nFileSize ) {
			break;
		}
	}



	/*--------------*/
	// read frame
	// int ReadOneSample(FILE* pFile, S_ROOT* root);
	retVal = ReadOneSample(pFileOrg, root);
	if(retVal < 0) {
		printf("\t[ERROR] Read one sample.\r\n");
	}

	/*--------------*/
	// void MP4Close(S_ROOT* root)
	MP4Close(root);

	if(root) {
		free(root);
		root = NULL;
	}
	return retVal;
}


int main(int argc, char* argv[])
{
	int ret = 0;

	if(1 == argc) {
		printf("Do not arguments. please help.");
		return 0;
	}

	if(!strncmp("--help", argv[1], 6)) {
		printf("HELP DESCRIPTION...\n");
		printf("./main (file directory...) )\n");
		return 0;
	}

	ret = MP4FileOpen(argv[1]);
	return ret;

	// FFReaderTest(argv[1]);
	//SampleSize(argv[1]);
	
	// frame dump 파일에 대한 slice 체크.
	// SliceCheck(argv[1]);

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
	if(pbuf) {
		free(pbuf);
		pbuf = NULL;
	}

	return 0;
}

int SliceCheck(char* pFile)
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

	pFileOut = fopen("recon_BigBunny_1080p_baseline41_bitrate_1024_fps10_g10.mp4.dump", "wb");
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

	for(i=0; i<6000; i++) 
	{
		length = 0;
		//ret = fread(&length, sizeof(int), 1, pFileOrg);

		ret = fread(&length, sizeof(int), 1, pFileOrg);
		if(1 != ret) {
			printf("file read error.\n");
			//return 0;
			break;
		}
		offset = ftell(pFileOrg);
		//length = Endian(length);
		printf("[%s %d] sample length: %d(0x%08X) offset: %d \n", __FUNCTION__, __LINE__, length, length, offset);

#ifdef __WRITE_TEST__
		//ret = fwrite(&length, sizeof(int), 1, pFileOut);
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