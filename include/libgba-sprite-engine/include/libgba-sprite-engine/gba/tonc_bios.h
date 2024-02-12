//
//  BIOS call functions
//  MODIFIED by Wouter Groeneveld: extern "C" - no C++ name mangling, can't find assembly methods!
//
//! \file tonc_bios.h
//! \author J Vijn
//! \date 20060508 - 20070208
//
// === NOTES ===
//
// Pretty much copied verbatim from Pern and dkARM's libgba
// (which in turn is copied from CowBite Spec (which got its info from
//  GBATek))
//
//
// === NOTES ===
// * Make SURE your data is aligned to 32bit boundaries. Defining data
//   as u32 (and I do mean define; not merely cast) ensures this. Either
//   that or use __attribute__(( aligned(4) ))
// * There is a large (70 cycle in and out) overhead for SWIs. If you
//   know what they do, consider creating replacement code
// * div by 0 locks up GBA.
// * Cpu(Fast)Set's count is in chunks, not bytes. CpuFastSet REQUIRES
//   n*32 byte data
// * SoftReset is funky with interrupts on.
// * VBlankIntrWait is your friend. If you have a VBlank isr that clears
//   REG_IFBIOS as well. Use this instead of REG_VCOUNT polling for
//   VSync.
// * I haven't tested many of these functions. The ones that are have a
//   plus (+) behind their numbers.
// * I've switched to the standard BIOS names.

#ifndef TONC_BIOS
#define TONC_BIOS

#include "tonc_types.h"

/*!
	\addtogroup grpBios
	\brief	Interfaces and constants for the GBA BIOS routines.

	For details, see
	<a href="http://www.coranac.com/tonc/text/keys.htm">tonc:keys</a>
	and especially
	<a href="http://nocash.emubase.de/gbatek.htm#biosfunctions">gbatek:bios</a>.

	\note	While the speeds of the routines are fair, there
	is a large overhead in calling the functions.
*/

/*!	\defgroup grpBiosDef	BIOS informalities
	\ingroup grpBios
*/
/*!	\{	*/


// --------------------------------------------------------------------
// CONSTANTS
// --------------------------------------------------------------------

//! \name SoftReset flags
//\{
#define ROM_RESTART		0x00	//!< Restart from ROM entry point.
#define	RAM_RESTART		0x01	//!< Restart from RAM entry point.
//\}

//! \name RegisterRamReset flags
//\{
#define RESET_EWRAM		0x0001	//!< Clear 256K on-board WRAM
#define RESET_IWRAM		0x0002	//!< Clear 32K in-chip WRAM
#define RESET_PALETTE	0x0004	//!< Clear Palette
#define RESET_VRAM		0x0008	//!< Clear VRAM
#define RESET_OAM		0x0010	//!< Clear OAM. does NOT disable OBJs!
#define RESET_REG_SIO	0x0020	//!< Switches to general purpose mode
#define RESET_REG_SOUND	0x0040	//!< Reset Sound registers
#define RESET_REG		0x0080	//!< All other registers

//#define RESET_REG_VIDEO	0x0100	//!< video regs, 00h-60h (non standard!)
//#define RESET_REG_DMA	0x0200	//!< DMA regs, B0h-100h (non standard!)
//#define	RESET_REG_TIMER	0x0400	//!< Timer regs (100h-110h) (non standard!)

#define RESET_MEM_MASK	0x001F
#define RESET_REG_MASK	0x00E0

#define RESET_GFX		0x001C	//!< Clear all gfx-related memory

//\}

//! \name Cpu(Fast)Set flags
//\{
#define CS_CPY      0			//!< Copy mode
#define CS_FILL    (1<<24)		//!< Fill mode
#define CS_CPY16    0			//!< Copy in halfwords
#define CS_CPY32   (1<<26)		//!< Copy words
#define CS_FILL32  (5<<24)		//!< Fill words

#define CFS_CPY     CS_CPY		//!< Copy words
#define CFS_FILL    CS_FILL		//!< Fill words
//\}

//! \name ObjAffineSet P-element offsets
//\{
#define BG_AFF_OFS		2		//!< BgAffineDest offsets
#define OBJ_AFF_OFS		8		//!< ObjAffineDest offsets
//\}

//! \name Decompression routines
#define BUP_ALL_OFS		(1<<31)

#define LZ_TYPE			0x00000010
#define LZ_SIZE_MASK	0xFFFFFF00
#define LZ_SIZE_SHIFT	  8

#define HUF_BPP_MASK	0x0000000F
#define HUF_TYPE		0x00000020
#define HUF_SIZE_MASK	0xFFFFFF00
#define HUF_SIZE_SHIFT	  8

#define RL_TYPE			0x00000030
#define RL_SIZE_MASK	0xFFFFFF00
#define RL_SIZE_SHIFT	  8

#define DIF_8			0x00000001
#define DIF_16			0x00000002
#define DIF_TYPE		0x00000080
#define DIF_SIZE_MASK	0xFFFFFF00
#define DIF_SIZE_SHIFT	  8
//\}

//! \name Multiboot modes
//\{
#define MBOOT_NORMAL	0x00
#define MBOOT_MULTI		0x01
#define MBOOT_FAST		0x02
//\}

// --------------------------------------------------------------------
// MACROS
// --------------------------------------------------------------------


//! BIOS calls from C
/*!	You can use this macro in a C BIOS-call wrapper. The wrapper
*	  should declare the flags, then this call will do the rest.
*	\param x	Number of swi call (THUMB number)
*	\note	It checks the __thumb__ \#define to see whether we're
*	  in ARM or THUMB mode and fixes the swi number accordingly.
*	  Huzzah for the C proprocessor!
*	\deprecated	This macro will not work properly for functions that have IO.
*/
#if	defined	( __thumb__ )
#define	swi_call(x)	 __asm("swi\t"#x ::: "r0", "r1", "r2", "r3")
#else
#define	swi_call(x)	 __asm("swi\t"#x"<<16" ::: "r0", "r1", "r2", "r3")
#endif

// --------------------------------------------------------------------
// CLASSES
// --------------------------------------------------------------------


// --- affine function 0x0E and 0x0F ---

/*
*  Notational convention: postfix underscore is 2d vector
*
*	p_ = (px, py)		= texture coordinates
*	q_ = (qx, qy)		= screen coordinates
*	P  = | pa pb |		= affine matrix
*	     | pc pd |
*	d_ = (dx, dy)		= background displacement
*
*  Then:
*
* (1)	p_ = P*q_ + d_
*
*  For transformation around a different point
*  (texture point p0_ and screen point q0_), do
*
* (2)	p_ - p0_ = P*(q_-q0_)
*
*  Subtracting eq 2 from eq1 we immediately find:
*
* (3)	_d = p0_ - P*q0_
*
*  For the special case of a texture->screen scale-then-rotate
*  transformation with
*	s_ = (sx, sy)	= inverse scales (s>1 shrinks)
*	a = alpha		= Counter ClockWise (CCW) angle
*
* (4)	P  = | sx*cos(a) -sx*sin(a) |
*            | sy*sin(a)  sy*cos(a) |
*
*
*  ObjAffineSet takes a and s_ as input and gives P
*  BgAffineSet does that and fills in d_ as well
*
*/

// affine types in tonc_types.h

//! BitUpPack ( for swi 10h)
typedef struct BUP
{
	u16 src_len;	//!< source length (bytes)
	u8 src_bpp;		//!< source bitdepth (1,2,4,8)
	u8 dst_bpp;		//!< destination bitdepth (1,2,4,8,16,32)
	u32 dst_ofs;	//!< {0-30}: added offset {31}: zero-data offset flag
} BUP;

//! Multiboot struct
typedef	struct
{
	u32	reserved1[5];
	u8	handshake_data;
	u8	padding;
	u16	handshake_timeout;
	u8	probe_count;
	u8	client_data[3];
	u8	palette_data;
	u8	response_bit;
	u8	client_bit;
	u8	reserved2;
	u8	*boot_srcp;
	u8	*boot_endp;
	u8	*masterp;
	u8	*reserved3[3];
	u32	system_work2[4];
	u8	sendflag;
	u8	probe_target_bit;
	u8	check_wait;
	u8	server_type;
} MultiBootParam;


/*!	\}	*/



// --------------------------------------------------------------------
// BASIC BIOS ROUTINES
// --------------------------------------------------------------------



/*!	\defgroup grpBiosMain	BIOS functions
*	\ingroup grpBios
*/
/*! \{	*/

//! \name Reset functions
//\{
extern "C" void SoftReset(void);
extern "C" void RegisterRamReset(u32 flags);
//\}

//! \name Halt functions
//\{
extern "C" void Halt(void);
extern "C" void Stop(void);
extern "C" void IntrWait(u32 flagClear, u32 irq);
extern "C" void VBlankIntrWait(void);
//\}


//! \name Math functions
//\{
extern "C" s32 Div(s32 num, s32 den);
extern "C" s32 DivArm(s32 den, s32 num);
extern "C" u32 Sqrt(u32 num);
extern "C" s16 ArcTan(s16 dydx);
extern "C" s16 ArcTan2(s16 x, s16 y);
//\}

//! \name Memory copiers/fillers
//\{
// Technically, these are misnomers. The convention is that
// xxxset is used for fills (comp memset, strset). Or perhaps
// the C library functions are misnomers, since set can be applied
// to both copies and fills.
extern "C" void CpuSet(const void *src, void *dst, u32 mode);
extern "C" void CpuFastSet(const void *src, void *dst, u32 mode);
//\}

extern "C" u32 BiosCheckSum(void);


//! \name Rot/scale functions
//\{
// These functions are misnomers, because ObjAffineSet is merely
// a special case of/precursor to BgAffineSet. Results from either
// can be used for both objs and bgs. Oh well.
extern "C" void ObjAffineSet(const ObjAffineSource *src, void *dst, s32 num, s32 offset);
extern "C" void BgAffineSet(const BgAffineSource *src, BgAffineDest *dst, s32 num);
//\}

//! \name Decompression (see GBATek for format details)
//\{
extern "C" void BitUnPack(const void *src, void *dst, const BUP *bup);
extern "C" void LZ77UnCompWram(const void *src, void *dst);
extern "C" void LZ77UnCompVram(const void *src, void *dst);
extern "C" void HuffUnComp(const void *src, void *dst);
extern "C" void RLUnCompWram(const void *src, void *dst);
extern "C" void RLUnCompVram(const void *src, void *dst);
extern "C" void Diff8bitUnFilterWram(const void *src, void *dst);
extern "C" void Diff8bitUnFilterVram(const void *src, void *dst);
extern "C" void Diff16bitUnFilter(const void *src, void *dst);
//\}

//! \name Sound Functions
//\{
// (I have even less of a clue what these do than for the others ---
extern "C" void SoundBias(u32 bias);
extern "C" void SoundDriverInit(void *src);
extern "C" void SoundDriverMode(u32 mode);
extern "C" void SoundDriverMain(void);
extern "C" void SoundDriverVSync(void);
extern "C" void SoundChannelClear(void);
extern "C" u32 MidiKey2Freq(void *wa, u8 mk, u8 fp);
extern "C" void SoundDriverVSyncOff(void);
extern "C" void SoundDriverVSyncOn(void);
//\}

//! \name Multiboot handshake
//\{
extern "C" int MultiBoot(MultiBootParam* mb, u32 mode);
//\}


/*!	\}	*/


/*!	\defgroup grpBiosEx	More BIOS functions
*	\ingroup grpBios
*/
/*! \{	*/

//\{

// You can find these in swi_ex.s
extern "C" void VBlankIntrDelay(u32 count);
extern "C" int DivSafe(int num, int den);
extern "C" int Mod(int num, int den);
extern "C" u32 DivAbs(int num, int den);
extern "C" int DivArmMod(int den, int num);
extern "C" u32 DivArmAbs(int den, int num);
extern "C" void CpuFastFill(u32 wd, void *dst, u32 count);

#define DivMod	Mod
//\}

/*!	\}	*/


#endif // TONC_BIOS