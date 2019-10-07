
#ifdef __cplusplus
extern "C"
{
#endif	// __cplusplus 


// stts table ����ü
typedef struct _STTSElement {
	uint64_t	nFileOffset;	// ���� ������ offset
	//unsigned int nLength;		// Size
	unsigned int	nEntrySt;		// Entry ���� ��ȣ	// 0 ���� ���� 
	unsigned int	nEntryEnd;		// Entry �� ��ȣ
	unsigned int	nTotSampCnt;	// �ش� Page�� Sample Counter�� ����... 0 �̸� �����...
	unsigned int	nTotSampDlt;	// �ش� Page�� Sample Delta�� ����... 0 �̸� �����...
}STTSElement, *pSTTSElement;

typedef struct _S_STTSTblElement {
	unsigned int SampleCounter;		// sample_count
	unsigned int SampleDelta;		// sample_delta
}S_STTSTblElement;

typedef struct _STTSTbl {
	unsigned int			nEntryCnt;		// STTS ���̺��� Entry counter
	unsigned char				*pListBuf;		// Element list �� ����
	pSTTSElement		*pList;
	unsigned int			nListCnt;
	unsigned int			nCurTblIndex;	// ���� ����ϰ� �ִ� Table�� Index. 0 ���� ����

	pSTTSElement		pCurTbl;		// ���� Page table
	S_STTSTblElement	*pCurTblBuf;	// ���� Page table ����
	uint16_t			nSampleCnt;		// �� Sample Counter -> stsz ���� ��� �´�.
	uint64_t			nDuration;		// mdhd�� duration
}STTSTbl, *pSTTSTbl;



// ctts table ����ü
/*
typedef struct _CTTSElement {
	uint64_t nFileOffset;	// ���� ������ offset
	//unsigned int nLength;		// Size
	unsigned int nEntrySt;		// Entry ���� ��ȣ	// 0 ���� ���� 
	unsigned int nEntryEnd;		// Entry �� ��ȣ
	unsigned int nTotSampCnt;	// �ش� Page�� Sample Counter�� ����... 0 �̸� �����...
	unsigned int nTotSampDlt;	// �ش� Page�� Sample Delta�� ����... 0 �̸� �����...
}CTTSElement, *pCTTSElement;

typedef struct _S_CTTSTblElement{
	unsigned int SampleCounter;
	unsigned int SampleDelta;
}S_CTTSTblElement;


typedef struct _CTTSTbl {
	unsigned int nEntryCnt;			// CTTS ���̺��� Entry counter
	unsigned char *pListBuf;			// Element list �� ����
	pSTTSElement *pList;
	unsigned int nListCnt;
	unsigned int nCurTblIndex;		// ���� ����ϰ� �ִ� Table�� Index. 0 ���� ����
	NXFF_FILE_HANDLE fp;			// File Hanlder0
	pCTTSElement pCurTbl;			// ���� Page table
	S_CTTSTblElement *pCurTblBuf;	// ���� Page table ����
}CTTSTbl, *pCTTSTbl;
*/

// S_STSC ����ü 
typedef struct _STSCElement {
	uint64_t nFileOffset;	// ���� ������ offset
	unsigned int nEntrySt;		// Entry ���� ��ȣ	// 0 ���� ���� 
	unsigned int nEntryEnd;		// Entry �� ��ȣ
	unsigned int nTotSamples;		// �ش� Page�� chunk�� ����... 0 �̸� �����...
	unsigned int nLastFS;
}STSCElement, *pSTSCElement;

typedef struct {
	unsigned int	FirstChunkTable;
	unsigned int	SamplesPerChunkTable;
	unsigned int	SampleDescriptionIDTable;
} S_STSCTblElement;

typedef struct _STSCTbl {
	unsigned char *pListBuf;
	pSTSCElement *pList;
	unsigned int nListCnt;
	unsigned int nCurTblIndex;		// ���� ����ϰ� �ִ� Table�� Index. 0 ���� ����

	pSTSCElement pCurTbl;			// ���� Page table
	S_STSCTblElement *pCurTblBuf;		// ���� Page table ����
}STSCTbl, *pSTSCTbl;


// S_STCO ����ü 
typedef struct _STCOElement {
	uint64_t	nFileOffset;	// ���� ������ offset
	unsigned int	nEntrySt;		// Entry ���� ��ȣ	// 0 ���� ���� 
	unsigned int	nEntryEnd;		// Entry �� ��ȣ
}STCOElement, *pSTCOElement;

typedef struct _STCOTbl {
	unsigned char			bVersion;			// 0: stco, 1: co64
	unsigned char			*pListBuf;
	pSTCOElement	*pList;
	
	unsigned int		nListCnt;
	unsigned int		nCurTblIndex;		// ���� ����ϰ� �ִ� Table�� Index. 0 ���� ����
	
	pSTCOElement	pCurTbl;			// ���� Page table
	unsigned int		*pCurTbl32Buf;		// ���� STCO Page table ����
	uint64_t		*pCurTbl64Buf;		// ���� CO64 Page table ����

}STCOTbl, *pSTCOTbl;


// stsz table ����ü
typedef struct _STSZElement {
	uint64_t	nFileOffset;	// ���� ������ offset
	unsigned int	nEntrySt;		// Entry ���� ��ȣ	// 0 ���� ���� 
	unsigned int	nEntryEnd;		// Entry �� ��ȣ
	unsigned int	nTotalSize;		// �ش� Page�� �� STSZ ������... 0 �̸� �����...
}STSZElement, *pSTSZElement;

typedef struct _STSZtbl {
	unsigned char			*pListBuf;
	pSTSZElement	*pList;
	unsigned int		nListCnt;
	unsigned int		nCurTblIndex;	// ���� ����ϰ� �ִ� Table�� Index. 0 ���� ����
	pSTSZElement	pCurTbl;		// ���� Page table
	unsigned int		*pCurTblBuf;	// ���� Page table ����
}STSZTbl, *pSTSZTbl;


// stss table ����ü
typedef struct _STSSElement {
	unsigned int nFileOffset;	// ���� ������ offset
	unsigned int nEntrySt;		// Entry ���� ��ȣ	// 0 ���� ���� 
	unsigned int nEntryEnd;		// Entry �� ��ȣ
}STSSElement, *pSTSSElement;

typedef struct _STSStbl {
	unsigned char *pListBuf;
	pSTSSElement *pList;
	unsigned int nListCnt;
	unsigned int nCurTblIndex;		// ���� ����ϰ� �ִ� Table�� Index. 0 ���� ����
	pSTSSElement pCurTbl;			// ���� Page table
	unsigned int *pCurTblBuf;		// ���� Page table ����
}STSSTbl, *pSTSSTbl;





typedef struct 
{
	unsigned int	major_brand;
	unsigned int	minor_version;
	unsigned int	compatible_brands;
} S_FTYP;

typedef struct
{
	int nData;
	char	*pData;
} S_UUID;


typedef struct 
{
	unsigned char 	version;
	union {
		unsigned int	val32;
		uint64_t	    val64;
	} creation_time;
	union {
		unsigned int	val32;
		uint64_t	    val64;
	} modification_time;
	unsigned int	    timescale;
	union {
		unsigned int	val32;
		uint64_t	    val64;
	} duration;

	unsigned int	next_track_ID;
} S_MVHD;

typedef struct 
{
	unsigned char       version;
	union {
		unsigned int	val32;
		uint64_t	    val64;
	} creation_time;
	union {
		unsigned int	val32;
		uint64_t	    val64;
	} modification_time;
	union {
		unsigned int	val32;
		uint64_t	    val64;
	} duration;
	unsigned char		TrackUse;
	unsigned int	    track_ID;
	unsigned int	    pMatrix[36];
	unsigned int	    width;
	unsigned int	    height;
} S_TKHD;

typedef struct
{
	unsigned int	TrackReferenceType[5];
	unsigned char		dpndflag;
	unsigned char		syncflag;

	unsigned int	dpndtrak_num;
	unsigned int	synctrak_num;

	unsigned int	*dpndTrackID;
	unsigned int	*syncTrackID;
} S_TREF;

typedef struct 
{
	unsigned int	entry_count;
	unsigned int	StartOffset;			// �ش� �ð����� �������϶� ��� �ǹ�.
	unsigned int	*TrackDurationTable;	// segment_duration
	unsigned int	*MediaTimeTable;		// media_time
	uint16_t	*MediaRateTable;		// media_rate_integer
} S_ELST;

typedef struct 
{
	S_ELST elst;
} S_EDTS;

typedef struct 
{
	unsigned char version;
	union {
		unsigned int	val32;
		uint64_t	val64;
	} creation_time;
	union {
		unsigned int	val32;
		uint64_t	val64;
	} modification_time;
	unsigned int	timescale;
	union {
		unsigned int	val32;
		uint64_t	val64;
	} duration;
	uint16_t	language;	// ISO-639-2/T language code.
	unsigned int	mul;
	unsigned int	div;
} S_MDHD;

typedef struct 
{
	unsigned int	handler_type;
	unsigned int	unNamelength;
	unsigned char		*pName;
} S_HDLR;

typedef struct
{
	int16_t		top;
	int16_t		left;
	int16_t		bottom;
	int16_t		right;
} S_BOX_RECORD;

typedef struct
{
	uint16_t	startChar;
	uint16_t	endChar;
	uint16_t	font_ID;
	unsigned char		face_style_flags;
	unsigned char		font_size;
	unsigned char		text_color_rgba[4];
} S_STYLE_RECORD;

typedef struct
{
	uint16_t	font_ID;
	unsigned char		font_name_length;
	unsigned char		*font;
} S_FONT_RECORD;

typedef struct
{
	uint16_t		entry_count;
	S_FONT_RECORD	*font_entry;
} S_FTAB;

typedef struct 
{
	uint16_t	samplerate;
	uint16_t	width;
	uint16_t	height;
	
	unsigned int	ObjectTypeIndication;
	unsigned int	AvgBitrate;

	unsigned int	ESStreamSize;
	unsigned char		*ESStream;

	unsigned int	DecSpecificInfoSize;
	unsigned char		*DecSpecificInfo;

	// is Make AAC ASC?
	unsigned char	IsMakeAACASC;

	// 3GPP DecoderSpecificInfo Support
	// AMR
	uint16_t	mode_set;
	unsigned char		mode_change_period;
	unsigned char		frames_per_sample;				// MP4 Reader ��

	// G.711
	uint16_t	G711ChannelNum;
	uint16_t	G711SampleSize;
	uint16_t	G711SamplingRate;
	unsigned int	uSamplesperPacket;	// Samples per packet
	unsigned int	uBytesperPacket;	// Bytes per packet
	unsigned int	uBytesperFrame;		// Bytes per frame
	int		nLittleEndian;		// 1 : little endian, 0 : big endian, -1 : init. value
	unsigned int	unSampleRate;		// Sample rate of CAF at Apple.

	// H.263
	unsigned char		H263_Profile;
	unsigned char		H263_Level;
	// H.264
	unsigned char		H264_Profile;
	unsigned char		H264_Level;
	unsigned char		H264_Compatibility;
	unsigned char		H264_NALLenghtSize;

	// 3GPP Timed Text
	unsigned int	displayFlags;
	char		horizontal_justification;
	char		vertical_justification;
	unsigned char		background_color_rgba[4];
	S_BOX_RECORD	default_text_box;
	S_STYLE_RECORD	default_style;
	S_FTAB		font_table;

	// PIFF wma WaveFormatEx
	// NEX_WAVEFORMATEX		*pWF;
	// NEX_BITMAPINFOHEADER	*pBH;
} S_SAMPLE_ENTRY;

typedef struct 
{
	unsigned int			entry_count;
	S_SAMPLE_ENTRY		*mp4avs;
} S_STSD;

typedef struct 
{
	unsigned int			entry_count;
	
	// pSTTSTbl			pSTTS;
	// unsigned char				nIsTblNeed;	// ���̺��� �ʿ� �Ѱ�?
	uint64_t			nOffset;	// file �� offset

	S_STTSTblElement	*ElementTbl;
} S_STTS;

typedef struct {
	unsigned int	SampleCountTable;		// the number of consecutive samples. 
	unsigned int	SampleDurationTable;	// the offset between CT and DT, such that CT(n) = DT(n) + CTTS(n).
} S_CTTSTblElement;

typedef struct 
{
	char				nVersion;		// version of this box.
	unsigned int			entry_count;	// the number of entries in the following ElementTbl.

	union {
		unsigned int	*punSampleOffset;
		int		*pnSampleOffset;
	} SyncSampleCompositionOffset;

	S_CTTSTblElement	*ElementTbl;	
} S_CTTS;

typedef struct 
{
	unsigned int			entry_count;
	
	// pSTSCTbl			pSTSC;
	// unsigned char				nIsTblNeed;	// ���̺��� �ʿ� �Ѱ�?
	uint64_t			nOffset;	// file �� offset

	S_STSCTblElement	*ElementTbl;
} S_STSC;

typedef struct 
{
	unsigned int			DefaultSampleSize;
	unsigned int			SampleCount;

	// pSTSZTbl			pSTSZ;
	// unsigned char				nIsTblNeed;	// ���̺��� �ʿ� �Ѱ�?
	uint64_t			nOffset;	// file �� offset
	unsigned int			*SampleSizeTable;
} S_STSZ;

//20110407 co64 ����
typedef struct 
{
	unsigned char				bVersion;		// 0: 32Bit 1: 64bit
	unsigned int			entry_count;

	// pSTCOTbl			pSTCO;
	// unsigned char				nIsTblNeed;	// ���̺��� �ʿ� �Ѱ�?
	uint64_t			nOffset;	// file �� offset

	unsigned int			*Uint32Table;
	uint64_t			*Uint64Table;
	//unsigned int *ChunkOffsetTable;
} S_STCO;

typedef struct 
{
	unsigned int			existence;
	unsigned int			entry_count;

	unsigned int			nOffset;			// file �� offset
	unsigned int			nLastSyncSample;	// ������ STSS ��ȣ
	uint64_t			*nCTSTable;

	uint64_t			*pCompositionTSTable;	//	composition time offset �� �̿��� CTS.

	unsigned int			*SampleNumberTable;
} S_STSS;

typedef struct
{
	unsigned int		sample_size;
	unsigned char			subsample_priority;
	unsigned char			discardable;
} S_SUBS_SAMPLE;

typedef struct
{
	unsigned int			sample_delta;
	unsigned int			sample_count;
	S_SUBS_SAMPLE		sample[100];
} S_SUBS_ENTRY;

typedef struct
{
	unsigned int		version;
	unsigned int		entry_count;
	S_SUBS_ENTRY	entry[10];
	void			*next;
} S_SUBS;

typedef struct 
{
	S_STTS	stts;
	S_STSD	stsd;
	S_STSZ	stsz;
	S_STSC	stsc;
	S_STCO	stco;
	S_CTTS	ctts;
	S_STSS	stss;
} S_STBL;

typedef struct 
{
	S_STBL	stbl;
} S_MINF;

typedef struct 
{
	S_MDHD	mdhd;
	S_MINF	minf;
	S_HDLR	hdlr;
} S_MDIA;

typedef struct 
{
	unsigned char	Lan[3];
	unsigned int	titlelen;
	unsigned char	*title;
} S_TITL;

typedef struct 
{
	unsigned char	Lan[3];
	unsigned int	descriptionlen;
	unsigned char	*description;
} S_DSCP;

typedef struct 
{
	unsigned char	Lan[3];
	unsigned int	copyrightlen;
	unsigned char	*copyright;
} S_CPRT;

typedef struct 
{
	unsigned char	Lan[3];
	unsigned int	performerlen;
	unsigned char	*performer;
} S_PERF;

typedef struct 
{
	unsigned char	Lan[3];
	unsigned int	authorlen;
	unsigned char	*author;
} S_AUTH;

typedef struct 
{
	unsigned char	Lan[3];
	unsigned int	genrelen;
	unsigned char	*genre;
} S_GNRE;

typedef struct 
{
	unsigned int	ratingentity;
	unsigned int	ratingcriteria;
	unsigned char	Lan[3];
	unsigned int	ratinginfolen;
	unsigned char	*ratinginfo;
} S_RTNG;

typedef struct 
{
	unsigned int	classificationentity;
	uint16_t	claasificationtable;
	unsigned char	Lan[3];
	unsigned int	classificationinfolen;
	unsigned char	*classificationinfo;
} S_CLSF;

typedef struct 
{
	unsigned char	keywordsize;
	unsigned char	*keywordinfo;
} S_KEYWORD;

typedef struct 
{
	unsigned char	Lan[3];
	unsigned char	keywordCnt;
	S_KEYWORD	*keywords;
} S_KYWD;

typedef struct 
{
	unsigned char	Lan[3];
	unsigned int	namelen;
	unsigned char	*name;
	unsigned char	role;
	unsigned int	longitude;
	unsigned int	latitude;
	unsigned int	altitude;
	unsigned int	astronomical_bodylen;
	unsigned char	*astronomical_body;
	unsigned int	additional_noteslen;
	unsigned char	*additional_notes;
} S_LOCI;

typedef struct 
{
	unsigned char	Lan[3];
	unsigned int	albumtitlelen;
	unsigned char	*albumtitle;
	unsigned char	tracknum;
} S_ALBM;

typedef struct 
{
	uint16_t	recyear;
} S_YRRC;

typedef struct
{
	S_TITL	titl;
	S_DSCP	dscp;
	S_CPRT	cprt;
	S_PERF	perf;
	S_AUTH	auth;
	S_GNRE	gnre;
	S_RTNG	rtng;
	S_CLSF	clsf;
	S_KYWD	kywd;
	S_LOCI	loci;
	S_ALBM	albm;
	S_YRRC	yrrc;
} S_ASSET;

typedef struct 
{
	S_TKHD				tkhd;
	S_TREF				tref;
	S_EDTS				edts;
	S_MDIA				mdia;
	S_UUID				uuid;

	//unsigned int				SampleNumber;
	//unsigned int				prevSampleNumber;

	// stss
	//unsigned int				stssprevRAPSampleTableIndex;

	// stts
	//unsigned int				sttsCurrDTS;
	//unsigned int				sttsTableIndex;
	//unsigned int				sttsSampleCount;
	//unsigned int				sttsprevSampleCount;
	//unsigned int				sttsSampleDuration;
	//unsigned int				afterRAflag;

	// stco
	//unsigned int				prevFileOffset;
	//unsigned int				FileOffset;
	//unsigned int				prevChunkNumber;
	//unsigned int				currChunkOffset;
	//unsigned int				ChunkOffsetStartSampleNumber;

	//NXVOID				*track;
} S_TRAK;

typedef struct
{
	unsigned char	version;
	union {
		unsigned int		value32;
		uint64_t		value64;
	} fragment_duration;
} S_MEHD;

typedef struct
{
	unsigned int		track_ID;
	unsigned int		default_sample_description_index;
	unsigned int		default_sample_duration;
	unsigned int		default_sample_size;
	unsigned int		default_sample_flags;
} S_TREX;

typedef struct
{
	S_MEHD		*mehd;	// 0 or 1 entry
	unsigned int		trex_num;
	S_TREX		*trex;	// Exactly one per track in the Movie Box
} S_MVEX;

typedef struct 
{
	unsigned char		*linkptr[13];
	unsigned int	linksize[13];
	unsigned char		*midiptr;
	uint64_t	nMidiOffset;
	unsigned int	midisize;
} S_UDTA_SKT;

typedef struct
{
	unsigned int	size;
	uint16_t	flag;	// ObjectDescriptorID(10) / URL_Flag(1) / includeInlineProfileLevelFlag(1) / reserved(5)= 0b1111.1
	unsigned char		ODProfileLevelIndication;
	unsigned char		sceneProfileLevelIndication;
	unsigned char		audioProfileLevelIndication;
	unsigned char		visualProfileLevelIndication;
	unsigned char		graphicProfileLevelIndication;
	unsigned int	OD_Track_ID;
	unsigned int	SD_Track_ID;
} S_IODS;

typedef struct
{
	S_MVHD		mvhd;
	S_TRAK		*trak;
	S_UDTA_SKT	udta;
	S_MVEX		*mvex;
	S_IODS		iods;

	unsigned int	trak_num;
} S_MOOV;


#ifdef __cplusplus
}
#endif	// __cplusplus 
