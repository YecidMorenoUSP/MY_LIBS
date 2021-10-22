#----------------------------------------------------

#define DefineBLOCKS BlockSUM_INIT();       \
                     BlockPOW_INIT();       \
                     BlockABS_INIT();       \
                     BlockMULTI_INIT();     \
                     BlockNUMK_INIT();      \
					 BlockEXO3_INIT();		  \
					 BlockEXO4_INIT();		  \
					 BlockYECID_INIT();		  \
					 BlockBLOCK_TEST_INIT();		  \
					 //<ADD_BLOCK_INIT>


#define name_of_object CLIENT_TCP
#include "BLOCKS/BLOCK_CLIENT_TCP.h"

#define name_of_object DECODE_TCP
#include "BLOCKS/BLOCK_DECODE_TCP.h"

#define name_of_object ENCODE_TCP
#include "BLOCKS/BLOCK_ENCODE_TCP.h"

#define name_of_object EXO3
#include "BLOCKS/BLOCK_EXO3.h"

#define name_of_object EXO4
#include "BLOCKS/BLOCK_EXO4.h"

#define name_of_object YECID
#include "BLOCKS/BLOCK_YECID.h"

#define name_of_object BLOCK_TEST
#include "BLOCKS/BLOCK_BLOCK_TEST.h"

//<ADD_BLOCK_DEFINE_NAME_AND_INCLUDE_H>
#----------------------------------------------------