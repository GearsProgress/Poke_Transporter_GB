DEF DRAWBOX_OFFSET = 0x5883
DEF DRAWBOX_SEARCH = 0xE53E

DEF SERIAL_EXCHANGEBYTES_OFFSET = 0xBF1
DEF SERIAL_EXCHANGEBYTES_SEARCH = 0xE0AB

DEF PRINTWAITINGTEXT_OFFSET = 0x49ED
DEF PRINTWAITINGTEXT_SEARCH = 0x216B

; start at 0x0bf1, search for E0 AB

; Serial_ExchangeBytes has different offsets based on language:
; RB
; EN: 0x216F
; FR: 0x216B
; DE: 0x216F
; IT: 0x216F
; SP: 0x216E
; Y
; EN: 00:1FCB
; FR: 00:1FC7
; DE: 00:1FD0
; IT: 00:1FCB
; SP: 00:1FCA
; JP
; RG&RGA: 00:0BF1
; B : 00:214F
; Y0: 00:1FF4
; Y1-3: 00:1FFD

; start at 01:5883, look for 0xE5 0x3E

; CableClub_TextBoxBorder has the following offsets:
; RB
; EN: 01:5AB3
; FR: 01:5B41
; DE: 01:5ACD
; IT: 01:5B0E & 01:5B0D
; SP: 01:5B00
; Y 
; EN: 01:5b67
; FR: 01:5be3
; DE: 01:5b6f
; IT: 01:5bb0
; SP: 01:5ba4
; JP
; G: 01:58DF
; R: 01:58DE
; GA: 01:5884
; RA: 01:5883
; B : 01:59F1 
; Y : 01:5A8D

; PrintWaitingText analysis
; 
; start 0x49ed, look for 216b
; 
; Red & Blue
; EN: 0x4c05
; FR: 0x4c82
; DE: 0x4c01
; ITR:0x4c56
; ITB:0x4c55
; SP: 0x4c3d
; JPR:0x49ed
; JPG:0x49ee
; JPB:0x4b5c
; 
; Yellow
; EN: 0x4b89
; FR: 0x4c05
; DE: 0x4b84
; IT: 0x4bd9
; SP: 0x4bc2
; JP0:0x4ad7
; JP1:0x4ad7
; JP2:0x4ad7
; JP3:0x4ad7