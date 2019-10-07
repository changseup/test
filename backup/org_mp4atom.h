// ATOM TYPE
#define	_FTYP_	0x66747970
#define		_3GP4_	0x33677034	// '3gp4'
#define		_3GP5_	0x33677035	// '3gp5'
#define		_3G2A_	0x33673261	// '3g2a'
#define		_K3G1_	0x6B336731	// 'k3g1'
#define		_MP41_	0x6D703431	// 'mp41'
#define		_MP42_	0x6D703432	// 'mp42'
#define		_ISOM_	0x69736F6D	// 'isom'
#define		_KDDI_	0x6B646469	// 'kddi'
#define		_MMP4_	0x6D6D7034	// 'mmp4'
#define		_SKM2_	0x736B6D32	// 'skm2'
#define _PDIN_	0x7064676E

#define _SKDV_	0x736B6476
#define		_SKTM_	0x736B746D
#define		_SKMM_	0x736B6D6D
#define			_SKMP_	0x736B6D70
#define		_SKMI_	0x736B6D69
#define		_SKBI_	0x736B6269

#define	_MOOV_	0x6D6F6F76
#define		_MVHD_	0x6D766864
#define		_IODS_	0x696F6473
#define		_TRAK_	0x7472616B
#define			_TKHD_	0x746B6864
#define			_TREF_	0x74726566				// Track reference atom
#define				_DPND_	0x64706E64
#define				_SYNC_	0x73796E63
#define			_EDTS_	0x65647473
#define				_ELST_	0x656C7374
#define			_MDIA_	0x6D646961
#define				_MDHD_	0x6D646864
#define				_HDLR_	0x68646C72
#define					_ODSM_	0x6F64736D		// ObjectDescriptorStream
#define					_CRSM_	0x6372736D		// ClockReferenceStream
#define					_SDSM_	0x7364736D		// SceneDescriptionStream
#define					_VIDE_	0x76696465		// VisualStream
#define					_SOUN_	0x736F756E		// AudioStream
#define					_M7SM_	0x7337736D		// MPEG7Stream
#define					_OCSM_	0x6F63736D		// ObjectContentInfoStream
#define					_IPSM_	0x6970736D		// IPMP Stream
#define					_MJSM_	0x6D6A736D		// MPEG-J Stream
#define					_HINT_	0x68696E74		// HINT Track
#define					_TEXT_	0x74657874		// TEXT Track.  (SKTTEXT or 3GPPTEXT)
#define					_SBTL_	0x7362746C		// SBTL Track.  (SKTTEXT or 3GPPTEXT)
#define					_SUBT_	0x73756274		// subt		20121113 CFF TT
#define				_MINF_	0x6D696E66
#define					_VMHD_	0x766D6864
#define					_SMHD_	0x736D6864
#define					_HMHD_	0x686D6864
#define					_NMHD_	0x6E6D6864
#define					_DINF_	0x64696E66
#define						_DREF_	0x64726566
#define						_URL__		0x75726C20		// 7th order
#define						_ALIS_	0x616C6973
#define						_CIOS_	0x63696F73			// cios for QT
#define					_STBL_	0x7374626C
#define						_STTS_	0x73747473
#define						_CTTS_	0x63747473
#define						_STSS_	0x73747373
#define						_STSD_	0x73747364
#define							_CHAN_	0x6368616E		// Audio Channel Layout Atom
#define							_MP4V_	0x6D703476
#define							_MP4A_	0x6D703461
#define							_ima4_	0x696D6134		// IMA ADPCM
#define								_QLCM_	0x514C434D
#define								_FMT__	0x666D7420
#define								_VORB_	0x766F7262	// Vorbis, ������ 4byte�� Check ������ ���� ��ü �� Check�ؾ� �� ���� ���� - KJSIM 110614
#define							_MP4S_	0x6D703473
#define								_ESDS_	0x65736473
#define								_ddts_	0x64647473		// DECE CFF ���� lovehis 120626
#define								_dtse_	0x64747365		// DTS-HD low bit rate formats
#define								_dtsc_	0x64747363		// DTS formats prior to DTS-HD
#define								_dtsh_	0x64747368		// DTS-HD audio foramts
#define								_dtsl_	0x6474736C		// DTS-HD Lossless formats
#define								_dac3_	0x64616333		// AC-3 (Dolby Digital)
#define								_dec3_	0x64656333		// Enhanced AC-3 (Dolby Digital Plus)
#define							_SAMR_	0x73616D72
#define							_SAWB_	0x73617762
#define								_DAMR_	0x64616D72
#define							_SAWP_  0x73617770
#define								_DAWP_	0x64617770
#define							_S263_	0x73323633
#define								_D263_	0x64323633
#define							_AVC1_	0x61766331
#define							_AVC3_	0x61766333			// MPEG DASH
#define							_VC_1_	0x76632D31
#define								_AVCC_	0x61766343
#define								_BTRT_	0x62747274
#define								_DVC1_	0x64766331
// HEVC �߰�
#define							_HVC1_	0x68766331	
#define							_HEV1_	0x68657631
#define								_HVCC_ 0x68766343
#define							_SEVC_	0x73657663
#define							_EVRC_	0x65767263
#define								_DEVC_	0x64657663
#define							_SQCP_	0x73716370
#define								_DQCP_	0x64716370
#define							_SSMV_	0x73736D76
#define								_DSMV_	0x64736D76
#define							_ULAW_	0x756C6177		// kULawCompression
#define							_ALAW_	0x616C6177		// kALawCompression
#define							_RTP__		0x72747020	
#define								_TIMS_	0x74696D73	
#define								_TSRO_	0x7473726F
#define								_SNRO_	0x736E726F	
#define								_RELY_	0x72656C79	
#define							_TX3G_	0x74783367	// 'tx3g'
#define								_FTAB_	0x66746162	// 'ftab'
#define								_STYL_	0x7374796C	// 'styl'
#define								_HLIT_	0x686C6974	// 'hlit'
#define								_HCLR_	0x68636C72	// 'hclr'
#define								_KROK_	0x6B726F6B	// 'krok'
#define								_DLAY_	0x646C6179	// 'dlay'
#define								_HREF_	0x68726566	// 'href'
#define								_TBOX_	0x74626F78	// 'tbox'
#define								_BLNK_	0x626C6E6B	// 'blnk'
#define							_S723_	0x73373233	// 's723'
#define								_D723_	0x64373233	// 'd723'

//#ifdef _SUPPORT_FORMAT_BCAST_APDCF_
#define							_ENCV_	0x656e6376		// 'encv'
#define							_ENCA_	0x656e6361		// 'enca'
#define							_ENCT_	0x656e6374		// 'enct'
#define							_ENCS_	0x656e6373		// 'encs'
#define								_SINF_	0x73696e66	// sinf
#define									_FRMA_	0x66726d61	// frma
#define									_SCHM_	0x7363686d	// schm
#define									_SCHI_	0x73636869	// schi
#define										_ODKM_	0x6f646b6d	// odkm
#define											_OHDR_	0x6f686472	// odhr
#define												_OBKI_	0x6f626b69	// obki
#define												_OSLT_	0x6f736c74	// oslt
#define												_GRPI_	0x67727069     // grpi
#define                                             _MDRI_  0x6D647269     // mdri
#define													_ODTT_	0x6f647474     // odtt
#define													_ODRB_  0x6f647262     // odrb
#define											_ODAF_	0x6f646166	// odaf
#define										_TENC_	0x74656E63	// tenc for // 23001-7 ����
#define							_OKSD_	0x6f6b7364	// oksd
//#endif // _SUPPORT_FORMAT_BCAST_APDCF_
#define							_AC_3_	0x61632D33		// AC-3
#define							_EC_3_	0x65632D33		// EC_3		Enhanced AC3
#define							_raw__	0x72617720		// raw,  k8BitOffsetBinary-Format
#define							_SOWT_	0x736F7774		// sowt, k16BitLittleEndian-Format
#define							_TWOS_	0x74776F73		// twos, k16BitBigEndian-Format
#define							_fl32_	0x666C3332		// fl32, kFloat32Format
#define							_fl64_	0x666C3634		// fl64, kFloat64Format
#define							_in24_	0x696E3234		// in24, k24BitFormat
#define							_in32_	0x696E3332		// in32, k32BitFormat
#define							_WAVE_	0x77617665

#define							_lpcm_	0x6C70636D		// lpcm, kLinearPCMFormat

#define								_ENDA_	0x656E6461	// endian atom
#define							_MS_U_	0x6D730055		// MP3, _MP4A_�� ���� ������ �Ľ�
#define							_MP3__	0x2E6D7033		// MP3�� ��ǥ�������� �ٴ� ���ڴ����� ������� ������ �־� ���� 100203STSDParsing
#define							_DIVX_	0x44495658		// DIVX�� ��ǥ�������� �ٴ� ���ڴ����� ������� ������ �־� ���� 100203STSDParsing
#define							_H263_	0x48323633		// H263
#define							_h263_	0x68323633		// h263
#define							_DX50_	0x44583530		// QT MOV
#define								_GLBL_	0x676C626C
#define							_WMA__	0x776D6120		// PIFF
#define								_WFEX_	0x77666578		// WAVEFORMATEX
#define							_ALAC_	0x616C6163		// ALAC
#define							_JPEG_	0x6A706567		// JPEG (MOV, Motion JPEG Video)
#define							_STPP_	0x73747070		// stpp 20121113 CFF
#define							_TTML_	0x74746D6C		// ttml 20121205 PIFF TTML
#define							_DFXP_	0x64667870		// dfxp, TTML
#define						_STSZ_	0x7374737A
#define						_STSC_	0x73747363
#define						_STCO_	0x7374636F
#define						_CO64_	0x636F3634
#define						_STSH_	0x73747368
#define						_STDP_	0x73746470
#define			_UDTA_	0x75647461
#define				_TITL_	0x7469746C
#define				_DSCP_	0x64736370
#define				_CPRT_	0x63707274
#define				_PERF_	0x70657266
#define				_AUTH_	0x61757468
#define				_GNRE_	0x676E7265
#define				_RTNG_	0x72746E67
#define				_CLSF_	0x636C7366
#define				_KYWD_	0x6B797764
#define				_LOCI_	0x6C6F6369
#define				_ALBM_	0x616C626D
#define				_YRRC_	0x79727263
#define		_MVEX_	0x6D766578	// 'mvex'
#define			_MEHD_	0x6D656864	// 'mehd'
#define			_TREX_	0x74726578	// 'trex'
#define		_PSSH_	0x70737368	// 'pssh'
#define _MOOF_	0x6D6F6F66	// 'moof'
#define _STYP_	0x73747970	// 'styp'	Segment Type Box
#define _SIDX_	0x73696478	// 'sidx'	Segment Index Box
#define _PRFT_	0x70726674	// 'prft'
#define		_MFHD_	0x6D666864	// 'mfhd'
#define		_TRAF_	0x74726166	// 'traf'
#define			_TFHD_	0x74666864	// 'tfhd'
#define			_TFDT_	0x74666474	// 'tfht'	20120730 DASH ���� �߰�
#define			_SAIZ_	0x7361697A	// 'saiz'
#define			_SAIO_	0x7361696F	// 'saio'
#define			_TRUN_	0x7472756E	// 'trun'
#define			_SENC_	0x73656E63	// senc		DECE CFF UV DRM
//#define			_STDP_  0x73746370	// 'stdp'
#define			_SDTP_	0x73647470	// 'sdtp'
#define			_SBGP_	0x73626770	// 'sbgp'
#define			_SGPD_	0x73677064	// 'sgpd'
#define			_SEIG_	0x73656967	// 'seig'
#define			_SUBS_	0x73756273	// 'subs'

#define _MFRA_	0x6D667261	// 'mfra'
#define		_TFRA_	0x74667261	// 'tfra'
#define		_MFRO_	0x6D66726F	// 'mfro'
#define	_MDAT_	0x6d646174
#define	_SKIP_	0x736B6970
#define	_FREE_	0x66726565
#define _META_	0x6d657461
#define _MECO_	0x6d65636F

#define _UUID_	0x75756964

// TLVdata for WMF RTFD v1.1
#define _DELY_	0x64656C79
#define _DROP_	0x64726F70

#define _WMFS_	0x776D6673
#define	_CPRT_	0x63707274 

// SKT Project
#define _LINK_	0x6C696E6B
#define	_MIDI_	0x6D696469 


const unsigned char ftyp[4] = "ftyp";
const unsigned char moov[4] = "moov";

const unsigned char stsz[4] = "stsz";
const unsigned char stsc[4] = "stsc";
const unsigned char stss[4] = "stss";
const unsigned char stco[4] = "stco";




//////////////////////////////////////////////////
//	Structure Type Definition
//////////////////////////////////////////////////
typedef struct {
	unsigned int	stsc_index;
	unsigned int	stco_index;
	unsigned int	chunk_sample_index;
	unsigned int	stsz_index;
	
	unsigned int	stts_index;
	unsigned int	stts_sample_index;
	
	unsigned int	ctts_index;
	unsigned int	ctts_sample_index;
} S_TRACK_READER_INI_FRAG;


typedef struct {
	// S_MOOF		*moof;
	// S_TRAF		*traf;
	// S_TRUN		*trun;
	unsigned int	trun_sample_index;

	unsigned int	sample_description_index;
	unsigned int	default_sample_duration;
	unsigned int	default_sample_size;
	unsigned int	default_sample_flags;
} S_TRACK_READER_SUB_FRAG;


typedef struct {
	unsigned int	frag_index;
	S_TRAK		*trak;
	S_MVEX		*mvex;
	S_TREX		*trex;
	// S_MOOF		*moof_head;
	// S_TFRA		*tfra;

	union {
		S_TRACK_READER_INI_FRAG ini;
		S_TRACK_READER_SUB_FRAG sub;
	} frag;

	uint64_t		offset;
	uint64_t		dts;
	uint64_t		cts;

	uint64_t		total_duration;
	unsigned int		total_sn;
} S_TRACK_READER;

typedef struct
{
	// NXFF_FILE_HANDLE	fp;
	// NXFF_FILE_HANDLE	audfp;
	// NXFF_FILE_HANDLE	textfp;
	// NXFF_FILE_HANDLE	bifsfp;
	// NXFF_FILE_HANDLE	odfp;

	uint64_t			filesize;
	uint16_t			rel4version;
	int				error;
	unsigned char				frames_per_sample;				// MP4 Writer ��

	S_FTYP				ftyp;
	S_MOOV				moov;
	// S_MOOF				*moof;
	// S_MFRA				*mfra;
	// S_SIDX				*sidx;
	S_ASSET				asset;

	unsigned char			nACurTrack;
	unsigned char			nVCurTrack;
	unsigned char			nTCurTrack;

	unsigned int			moof_num;

	unsigned int			G711ChannelNumber;
	unsigned int			G711SampleUnit;

	unsigned int			total_duration_in_msec;

	unsigned char				flagADTSHeader;

	S_TRACK_READER		*track_reader;

	unsigned char			bHasMoovAfterFree;

	// Composition Time Stamp
	unsigned char				bCompositionTSFlag;
	unsigned char				bUseCompositionTS;		// CTS ��� ����(default : TRUE)
} S_ROOT;



/*************************************************************
	Functions
*************************************************************/
// mp4reader.c

#ifdef __cplusplus
extern "C" {
#endif

int MP4CommonOpen(S_ROOT *root, int memaccessflag);
int MovieAtomAllocation(S_ROOT *root);

int MVHDParsing(FILE* pFile, S_ROOT* root, const int nSize);
int TRAKParsing(FILE* pFile, S_ROOT* root, const int nSize);
int STSZParsing(FILE* pFile, S_ROOT* root, const int nSize);
int TKHDParsing(FILE* pFile, S_ROOT* root, const int nSize);
int MDHDParsing(FILE* pFile, S_ROOT* root, const int nSize);
int HDLRParsing(FILE* pFile, S_ROOT* root, const int nSize);
int STTSParsing(FILE* pFile, S_ROOT* root, const int nSize);
int STCOParsing(FILE* pFile, S_ROOT* root, const int nSize);
int STSSParsing(FILE* pFile, S_ROOT* root, const int nSize);
int STSCParsing(FILE* pFile, S_ROOT* root, const int nSize);



// int ReadAtomHeader(unsigned int *atsize, unsigned int *attype, unsigned int level, NXFF_FILE_HANDLE fp, pNxFFReaderFileAPI pFileAPI);
int IODSParsing(unsigned int size, S_ROOT *root);
// int MVHDParsing(unsigned int size, S_ROOT *root);
// int TKHDParsing(unsigned int size, S_ROOT *root);
int TREFParsing(unsigned int size, S_ROOT *root);
int ELSTParsing(unsigned int size, S_ROOT *root);
// int MDHDParsing(unsigned int size, S_ROOT *root);
// int HDLRParsing(unsigned int size, S_ROOT *root);
int HMHDParsing(unsigned int size, S_ROOT *root);
// int STTSParsing(unsigned int size, S_ROOT *root);
int CTTSParsing(unsigned int size, S_ROOT *root);
// int STSZParsing(unsigned int size, S_ROOT *root);
// int STSCParsing(unsigned int size, S_ROOT *root);
// int STCOParsing(unsigned int size, S_ROOT *root);
int CO64Parsing(unsigned int size, S_ROOT *root);
// int STSSParsing(unsigned int size, S_ROOT *root);
int STSDParsing(unsigned int size, S_ROOT *root);
int TITLParsing(unsigned int size, S_ROOT *root);
int DSCPParsing(unsigned int size, S_ROOT *root);
int CPRTParsing(unsigned int size, S_ROOT *root);
int PERFParsing(unsigned int size, S_ROOT *root);
int AUTHParsing(unsigned int size, S_ROOT *root);
int GNREParsing(unsigned int size, S_ROOT *root);
int RTNGParsing(unsigned int size, S_ROOT *root);
int CLSFParsing(unsigned int size, S_ROOT *root);
int KYWDParsing(unsigned int size, S_ROOT *root);
int LOCIParsing(unsigned int size, S_ROOT *root);
int ALBMParsing(unsigned int size, S_ROOT *root);
int YRRCParsing(unsigned int size, S_ROOT *root);




#if 0       // just holding....


// For SKT PMP
int SKTMParsing(unsigned int size, S_ROOT *root);
int SKMPParsing(unsigned int size, S_ROOT *root, unsigned char i);
int SKMIParsing(unsigned int size, S_ROOT *root);
int SKBIParsing(unsigned int size, S_ROOT *root);

// mp4datause.c
unsigned int GetObjectTypeIndication(S_ROOT *root, unsigned int track_ID);
void GetIODstream(NxFFReaderWBuffer *buf, S_ROOT *root);
void GetIODstreamForISO(NxFFReaderWBuffer *buf, S_ROOT *root);
void GetIODstreamForNonISO(NxFFReaderWBuffer *buf, S_ROOT *root);
//int GetDTS(S_TRAK *trak, NXFF_FILE_HANDLE fp, int *ret);
//int GetSLpacketheader(NxFFReaderWBuffer *buf, S_TRAK *trak, NXFF_FILE_HANDLE fp);
void RemakeSLpacketpayload(NxFFReaderWBuffer *buf, S_TRAK *trak, S_ROOT *root, unsigned int payloadoffset);
void ObjectDescrUpdate(NxFFReaderRBuffer *rbuf, NxFFReaderWBuffer *buf, S_TRAK *trak, S_ROOT *root);

unsigned int GetAMRFramesPerSample(S_ROOT *root, unsigned int track_ID);
unsigned int GetAMRPayloadSize(unsigned char *buf);

unsigned int GetQCELPPayloadSize(unsigned char *buf);
unsigned int GetEVRCFramesPerSample(S_ROOT *root, unsigned int track_ID);   
unsigned int GetEVRCPayloadSize(unsigned char *buf);
 
unsigned int NxFFReaderGCD(unsigned int a, unsigned int b);

unsigned int GetSpeechFramesPerSample(S_ROOT *root, unsigned int track_ID);
unsigned int GetTrackNumberFromTrackID(S_ROOT *root, unsigned int track_ID);
unsigned int GetTrackDuration(S_ROOT *root, unsigned int track_ID);
unsigned int GetMediaDuration(S_ROOT *root, unsigned int track_ID);
unsigned int GetSeekRAPtime(S_ROOT *root, unsigned int track_ID, unsigned int UserTime);
unsigned int GetPrevRAPtime(S_ROOT *root, unsigned int track_ID, unsigned int UserTime);
unsigned int GetNextRAPtime(S_ROOT *root, unsigned int track_ID, unsigned int UserTime);
void SetSampleNumberToUserTime(S_ROOT *root, unsigned int track_ID, unsigned int UserTime);
unsigned int GetUserTimeToSampleNumber(S_ROOT *root, unsigned int track_ID, unsigned int SampleNumber);
unsigned int GetSampleNumberToTrackUserTime(S_ROOT *root, unsigned int track_ID, unsigned int UserTime, NXFF_FILE_HANDLE fp, int *ret);
unsigned int GetTrackUserTimeToSampleNumber(S_ROOT *root, unsigned int track_ID, unsigned int SampleNumber, NXFF_FILE_HANDLE fp, int *ret); 
unsigned int GetSeekRAPTimeToSampleNumber(S_ROOT *root, unsigned int track_ID, unsigned int SampleNumber, unsigned int trackUserTime);
unsigned int GetPrevRAPTimeToSampleNumber(S_ROOT *root, unsigned int track_ID, unsigned int SampleNumber);
unsigned int GetNextRAPTimeToSampleNumber(S_ROOT *root, unsigned int track_ID, unsigned int SampleNumber);
void SkipRAPtime(S_ROOT *root, unsigned int track_ID, unsigned int RAPtime); 

//unsigned int GetSeekRAPTimeSetRAPSNToSampleNumber(S_ROOT *root, unsigned int track_ID, unsigned int SampleNumber, unsigned int trackUserTime, NXFF_FILE_HANDLE fp, int *ret);
//unsigned int GetPrevRAPTimeSetRAPSNToSampleNumber(S_ROOT *root, unsigned int track_ID, unsigned int SampleNumber, NXFF_FILE_HANDLE fp, int *ret);
//unsigned int GetNextRAPTimeSetRAPSNToSampleNumber(S_ROOT *root, unsigned int track_ID, unsigned int SampleNumber, NXFF_FILE_HANDLE fp, int *ret);

unsigned int CheckShortVideoHeader(unsigned char *DecSpecificInfo, unsigned int DecSpecificInfoSize);

// tableManager.c
int createSTBLTbl(S_ROOT *pRoot);

// STTS
pSTTSTbl createSingleSTTSTbl(S_ROOT *pRoot, NXFF_FILE_HANDLE fp, unsigned int nCnt, unsigned int nDlt);
pSTTSTbl createSTTSTbl(S_ROOT *pRoot, S_TRAK *trak, NXFF_FILE_HANDLE fp, uint64_t nOffset, unsigned int nMaxHeapSize, unsigned int nEntryCnt, unsigned int nSampleCnt);
void destroySTTSTbl(S_ROOT *pRoot, pSTTSTbl pSTTS);
int getSTTSSampleCnt(S_ROOT *pRoot, pSTTSTbl pSTTS, unsigned int nIdx, unsigned int *pSampleCount);
int getSTTSSampleDelta(S_ROOT *pRoot, pSTTSTbl pSTTS, unsigned int nIdx, unsigned int *pSampleDelta);
int setSTTSSampleCnt(S_ROOT *pRoot, pSTTSTbl pSTTS, unsigned int nIdx, unsigned int nSampleCount);
int setSTTSSampleDelta(S_ROOT *pRoot, pSTTSTbl pSTTS, unsigned int nIdx, unsigned int nSampleDelta);
unsigned int getSTTSDTSToIdx(S_ROOT *pRoot, pSTTSTbl pSTTS, uint64_t nDTS, uint64_t *pDTS, unsigned int *pSTTSIdx, unsigned int *pSTTSSampleIdx);
int getCTStoFrameIndex(S_ROOT *pRoot, S_STTS *stts, uint64_t nCTS, unsigned int *nFrameIndex);
int getFrameIndextoCTS(S_ROOT *pRoot, S_STTS *stts, unsigned int nFrameIndex, uint64_t *nCTS);

// CTTS
int getCTTSSampleOffset(IN S_ROOT *pRoot, IN S_CTTS *ctts, IN unsigned int unIdx, INOUT int *pSampleOffset);


// STSC
pSTSCTbl createSingleSTSCTbl(S_ROOT *pRoot, NXFF_FILE_HANDLE fp, unsigned int nFChunk, unsigned int nSPChunk, unsigned int nSDIdx);
pSTSCTbl createSTSCTbl(S_ROOT *pRoot, NXFF_FILE_HANDLE fp, uint64_t nOffset, unsigned int nMaxHeapSize, unsigned int nEntryCnt);
void destroySTSCTbl(S_ROOT *pRoot, pSTSCTbl pSTTS);
unsigned int getSTSCFChunk(S_ROOT *pRoot, pSTSCTbl pSTSC, unsigned int nIdx, int *nErrorRet);
unsigned int getSTSCSPChunk(S_ROOT *pRoot, pSTSCTbl pSTSC, unsigned int nIdx, int *nErrorRet);
unsigned int getSTSCSDIndex(S_ROOT *pRoot, pSTSCTbl pSTSC, unsigned int nIdx);


int getSTSCDTSToSID(S_ROOT *pRoot, S_TRAK *pTrak, uint64_t nDTS, uint64_t *pDTS, unsigned int nSD, S_TRACK_READER_INI_FRAG *ini);


// 20110909 lovehis chunk mode ����
unsigned int getSTSCIdxToSTCOIdx(S_ROOT *pRoot, pSTSCTbl pSTSC, unsigned int nIdx, unsigned int *pChunkSampleInx, unsigned int *pSTSCIdx);


// STCO
pSTCOTbl createSingleSTCOTbl(S_ROOT *pRoot, NXFF_FILE_HANDLE fp, unsigned char bVersion, uint64_t nChunkOffset);
pSTCOTbl createSTCOTbl(S_ROOT *pRoot, NXFF_FILE_HANDLE fp, uint64_t nOffset, unsigned int nMaxHeapSize, unsigned char bVersion, unsigned int nEntryCnt);
void destroySTCOTbl(S_ROOT *pRoot, pSTCOTbl pSTTS);
uint64_t getSTCOChunkOffset(S_ROOT *pRoot, S_STCO *pSTCO, unsigned int nIdx, int *nErrorRet);

// STSZ
pSTSZTbl createSTSZTbl(S_ROOT *pRoot, NXFF_FILE_HANDLE fp, uint64_t nOffset, unsigned int nMaxHeapSize, unsigned int nEntryCnt);
void destroySTSZTbl(S_ROOT *pRoot, pSTSZTbl pSTSZ);
int getSTSZSampleSize(S_ROOT *pRoot, pSTSZTbl pSTSZ, unsigned int nIdx, unsigned int *pSampleSize);
unsigned int getSTSZRangeLength(S_ROOT *pRoot, S_STSZ *STSZ, unsigned int nIdx1, unsigned int nIdx2);
unsigned int getSTTZTotLength(S_ROOT *pRoot, pSTSZTbl pSTSZ);

// STSS
int createSTSSTbl(S_ROOT *pRoot, S_TRAK *pTrak);

/******************************************************************************
 * Comment :	- target time stamp �� stss �� time stamp ���̺����� �˻�.
 *				- �˻��� time stamp �� �̿��Ͽ� ���� sample index �� ã��. ( getSTTSDTSToIdx() )
******************************************************************************/
int findSeekPointer(IN S_ROOT *pRoot, IN S_TRAK *pTrak, IN unsigned int mode, IN uint64_t nT_DTS, INOUT uint64_t *pR_DTS, INOUT unsigned int *pSampleIdx, INOUT unsigned int *pSTTSIdx, INOUT unsigned int *pSTTSSampleIdx);
int getSTSSEntry(S_ROOT *pRoot, S_STSS *pSTSS, unsigned int nIdx);

/*
pSTSSTbl createSTSSTbl(S_ROOT *pRoot, NXFF_FILE_HANDLE fp, unsigned int nOffset, unsigned int nMaxHeapSize, unsigned int nEntryCnt);
void destroySTSSTbl(S_ROOT *pRoot, pSTSSTbl pSTSZ);
unsigned int getSTSSSampleNumber(S_ROOT *pRoot, pSTSSTbl pSTSS, unsigned int nIdx);
*/

/******************************************************************************
 * Comment : Composition Time Stamp �� �Է��ϸ� DTS �� ��ȯ�ϴ� �Լ�.
******************************************************************************/
int _getCompositionTS2DTS(IN S_ROOT *pRoot, IN S_TRAK *pTrak, IN uint64_t unCompositionTS, OUT uint64_t *punDTS );


int parse_sidx(unsigned int size, S_ROOT *root, S_SIDX *sidx);

#endif


#ifdef __cplusplus
}
#endif