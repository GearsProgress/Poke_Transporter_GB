DEF NULL = 0x0
DEF FarCall = 0x8
DEF Bankswitch_GSC = 0x10
DEF SerialInterrupt = 0x58
DEF Start = 0x100
DEF GLOBAL_CHECKSUM = 0x014E
DEF ClearScreen_KOR = 0x0F00
DEF Bankswitch = 0x3E84
DEF PlaceWaitingTextBank = 0x01
DEF PlaceWaitingText = 0x4000

DEF wMuteAudioAndPauseMusic = 0xC002
DEF wMusicFadeID = 0xC1A9
DEF wTileMap = 0xC3A0
DEF wSerialPartyMonsPatchList = 0xC508
DEF wSerialEnemyMonsPatchList = 0xC5D0
DEF wSerialEnemyMonsPatchList_GS = 0xC5D0
DEF wSerialEnemyMonsPatchList_C = 0xC6D0
DEF wSerialOtherGameboyRandomNumberListBlock = 0xCD91
DEF wPrinterConnectionOpen = 0xD499
DEF wSerialEnemyDataBlock = 0xD893

DEF hCGB_C = 0xFFE6
DEF hCGB_GS = 0xFFE8

DEF SerialPatchAlignedAddress = 0xC800
DEF SpecificPayloadAddress = 0xC900
DEF SerialOffset_GS = 0x66
DEF SerialOffset_C = 0x70

DEF PACKET_SEND = 0xC6D0
DEF PACKET_RECEIVE = 0xC6DC

DEF CHECKSUMPACKET_SIZE = 7

DEF RNGSIZE_GEN2 = 0x11
DEF LINKDATASIZE_GEN2 = 0x1C2
DEF PATCHLIST_GEN2 = 0xC8
DEF LINKMAILSIZE_GEN1 = 0x186