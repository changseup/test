#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>

// #include "mp4Detatil.h"
// #include "mp4atom.h"

// typedef enum ReturnType {
// 	kSuccess = 0,
//     kFrameWarning,
//     kFileError,
// 	kParsingError,
// 	kMemoryAllocFail
// } eReturnType;

// unsigned char* eRetType2Char(const eReturnType eRetType)
// {
//     unsigned char cRetChar[25] = "Not support return type.";
    
//     switch(eRetType)
//     {
//         case kSuccess:
//             return "Success";
//             break;
//         case kParsingError:
//         break;
//         case kMemoryAllocFail:
//         break;
//     }

//     return cRetChar;
// }

int Endian(const int nOrgData) {
	int temp = 0;
	temp = (nOrgData & 0x000000FF) << 24;
	temp += ((nOrgData & 0x0000FF00) >> 8) << 16;
	temp += ((nOrgData & 0x00FF0000) >> 16) << 8;
	temp += ((nOrgData & 0xFF000000) >> 24);

	return temp;
}

int64_t Endian64(const int64_t nOrgData) {
	int64_t temp = 0;
	temp =  (nOrgData & 0x00000000000000FF) << 56;
	temp += ((nOrgData & 0x000000000000FF00) >> 8) << 48;
	temp += ((nOrgData & 0x0000000000FF0000) >> 16) << 40;
	temp += ((nOrgData & 0x00000000FF000000) >> 24) << 32;
    
    temp += ((nOrgData & 0x000000FF00000000) >> 32) << 24;
    temp += ((nOrgData & 0x0000FF0000000000) >> 40) << 16;
    temp += ((nOrgData & 0x00FF000000000000) >> 48) << 8;
    temp += ((nOrgData & 0xFF00000000000000) >> 56);
	
    return temp;
}

typedef enum NaluType {
	kUnspecified = 0,
    kNonIDRPicture,
	kIDRPicture = 5,
    kSEI = 6,
	kSPS = 7,
	kPPS,
	kAU,
	kEndOfSequence,
	kEndOfStream
} eNaluType;

// nal_unit_type =>
// 1, non-IDR picture
// 5, IDR picture
// 6, SEI
// 7, SPS
// 8, PPS
// 9, AU (Access unit delimiter)
// 10, End of sequence
// 11, End of stream