////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// VEDriver.h//______________________________________________________________________________________________________________________//                                                Copyright (c) 1993//                                   INTELLIGENT RESOURCES INTEGRATED SYSTEMS INC.//                                                All Rights Reserved.////                           This is unpublished work and is the proprietary source code of//                                   INTELLIGENT RESOURCES INTEGRATED SYSTEMS INC.//                                       and should be treated as confidential//______________________________________________________________________________________________________________________//// Author		Date			Description// ------		----			-----------// JDZ			XX/XX/XX		Xxxxx.// ESH			09/12/91		Changed to driver .980// FEA			10/22/91		Changed to driver .993// MJG			12/17/91		Changed to driver .994// MJG			01/06/92		Changed to driver .996// MJG			01/14/92		Changed to driver .997// MJG			02/10/92		Changed to driver .997A// MJG			04/09/92		Changed to driver .997L		Added startNow value in CAPTURE MULTIPLEXER.//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////#ifndef	_VEDriver_h_#define	_VEDriver_h_/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////************************************************************************//*	Constants															*//************************************************************************/#define vendorCSCBase		1000#define cscSetMemoryAddressing	(vendorCSCBase+0)#define cscSetPhysicalMemoryOffset	(vendorCSCBase+1)#define cscSetMemoryProtectMask	(vendorCSCBase+2)#define cscSetBankState		(vendorCSCBase+3)#define cscSetPairDecoder	(vendorCSCBase+4)#define cscSetDYUV8Decoder	(vendorCSCBase+5)#define cscSetBusMuxChannel	(vendorCSCBase+6)#define cscSetPriority		(vendorCSCBase+7)#define cscSetChannel		(vendorCSCBase+8)#define cscSetColorFormat	(vendorCSCBase+9)#define cscSetAlphaDisplayChannel	(vendorCSCBase+10)#define cscSetChannelColor	(vendorCSCBase+11)#define cscSetCaptureState	(vendorCSCBase+12)#define cscSetCaptureWindow	(vendorCSCBase+13)#define cscSetCaptureChannel	(vendorCSCBase+14)#define cscSetCaptureFormat	(vendorCSCBase+15)#define cscSetCaptureColor	(vendorCSCBase+16)#define cscSetClockState	(vendorCSCBase+17)#define cscSetMasterClockSource	(vendorCSCBase+18)#define cscSetClockDividerInterval	(vendorCSCBase+19)#define cscSetMasterControl	(vendorCSCBase+20)#define cscSetRefreshRate	(vendorCSCBase+21)#define cscSetInterruptEnables	(vendorCSCBase+22)#define cscSetInterruptClears	(vendorCSCBase+23)#define cscSetAbsoluteInterruptMode	(vendorCSCBase+24)#define cscSetHVStatus		(vendorCSCBase+25)#define cscSetHVControl		(vendorCSCBase+26)#define cscSetTimeSequencerParameters	(vendorCSCBase+27)#define cscSetHorizontalSequenceCommands	(vendorCSCBase+28)#define cscSetVerticalSequenceCommands	(vendorCSCBase+29)#define cscSetSyncControls	(vendorCSCBase+30)#define cscSetGenlockControls	(vendorCSCBase+31)#define cscSetExtendedVideoMode	(vendorCSCBase+32)#define cscSetMemoryBankConfiguration	(vendorCSCBase+33)#define cscSetBankDisplayAttributes	(vendorCSCBase+34)#define cscSetLiveMosaics	(vendorCSCBase+35)#define cscSetVDESyncLoadControl	(vendorCSCBase+36)#define cscSetVSCSyncLoadControl	(vendorCSCBase+37)#define cscSetSerialBusControl	(vendorCSCBase+38)#define cscSetDigitalVideoPort	(vendorCSCBase+39)#define cscSetDVPWriteValue	(vendorCSCBase+40)#define cscSetMultiplierConstants	(vendorCSCBase+41)#define cscSetMultiplierConstantsChannel	(vendorCSCBase+42)#define cscSetMultiplierICFControls	(vendorCSCBase+43)#define cscSetMultiplierMode	(vendorCSCBase+44)#define cscSetMultiplierSigns	(vendorCSCBase+45)#define cscSetNoiseChannel	(vendorCSCBase+46)#define cscSetMultiplierFilterChannel	(vendorCSCBase+47)#define cscSetMultiplierPartialSumInChannel	(vendorCSCBase+48)#define cscSetCLUTMode		(vendorCSCBase+49)#define cscSetCLUTMixRatio	(vendorCSCBase+50)#define cscSetCLUTSource	(vendorCSCBase+51)#define cscSetCLUTMatrixConfiguration	(vendorCSCBase+52)#define cscExtendedSetEntries	(vendorCSCBase+53)#define cscSetThresholderRange	(vendorCSCBase+54)#define cscSetThresholderSigns	(vendorCSCBase+55)#define cscSetThresholderColorFormat	(vendorCSCBase+56)#define cscSetThresholderTransitionMode	(vendorCSCBase+57)#define cscSetRectangleBounds	(vendorCSCBase+58)#define cscSetRectangleControl	(vendorCSCBase+59)#define cscSetBlendRatioRateOfChange	(vendorCSCBase+60)#define cscSetLineControlMode	(vendorCSCBase+61)#define cscSetLineCommands	(vendorCSCBase+62)#define cscSetRawLineCommands	(vendorCSCBase+63)#define cscSetPixelControlMode	(vendorCSCBase+64)#define cscUnusedControl0	(vendorCSCBase+65)#define cscSetPixelICF		(vendorCSCBase+66)#define cscSetPixelMultiplierChannel	(vendorCSCBase+67)#define cscSetPixelThresholderChannel	(vendorCSCBase+68)#define cscSetPixelDisplayChannelColorFormat	(vendorCSCBase+69)#define cscSetPixelNoiseMode	(vendorCSCBase+70)#define cscWriteToSlotSpace	(vendorCSCBase+71)//Status calls#define cscGetMemoryAddressing	(vendorCSCBase+0)	#define cscGetPhysicalMemoryOffset	(vendorCSCBase+1)#define cscGetMemoryProtectMask	(vendorCSCBase+2)#define cscGetHWStatus		(vendorCSCBase+3)#define cscGetBankState		(vendorCSCBase+4)#define cscGetPairDecoder	(vendorCSCBase+5)#define cscGetDYUV8Decoder	(vendorCSCBase+6)#define cscGetBusMuxChannel	(vendorCSCBase+7)#define cscGetPriority		(vendorCSCBase+8)#define cscGetChannel		(vendorCSCBase+9)#define cscGetAlphaDisplayChannel	(vendorCSCBase+10)#define cscGetColorFormat	(vendorCSCBase+11)#define cscGetChannelColor	(vendorCSCBase+12)#define cscGetBankCaptureEnables	(vendorCSCBase+13)#define cscGetCaptureWindow	(vendorCSCBase+14)#define cscGetCaptureChannel	(vendorCSCBase+15)#define cscGetCaptureFormat	(vendorCSCBase+16)#define cscGetCaptureColor	(vendorCSCBase+17)#define cscGetClockState	(vendorCSCBase+18)#define cscGetMasterClockSource	(vendorCSCBase+19)#define cscGetClockDividerInterval	(vendorCSCBase+20)#define cscGetMasterControl	(vendorCSCBase+21)#define cscGetRefreshRate	(vendorCSCBase+22)#define cscGetInterruptEnables	(vendorCSCBase+23)#define cscGetInterruptStatus	(vendorCSCBase+24)#define cscGetAbsoluteInterruptMode	(vendorCSCBase+25)#define cscGetHVStatus		(vendorCSCBase+26)#define cscGetHVControl		(vendorCSCBase+27)#define cscGetTimeSequencerParameters	(vendorCSCBase+28)#define cscGetHorizontalSequenceCommands	(vendorCSCBase+29)#define cscGetVerticalSequenceCommands	(vendorCSCBase+30)#define cscGetSyncControls	(vendorCSCBase+31)#define cscGetGenlockControls	(vendorCSCBase+32)#define cscGetMemoryBankConfiguration	(vendorCSCBase+33)#define cscGetBankDisplayAttributes	(vendorCSCBase+34)#define cscGetLiveMosaics	(vendorCSCBase+35)#define cscGetLiveADConfigurationStatus	(vendorCSCBase+36)#define cscGetVDESyncLoadControl	(vendorCSCBase+37)#define cscGetVSCSyncLoadControl	(vendorCSCBase+38)#define cscGetSerialBusControl	(vendorCSCBase+39)#define cscGetDigitalVideoPort	(vendorCSCBase+40)#define cscGetDVPWriteValue	(vendorCSCBase+41)#define cscReadDVPData		(vendorCSCBase+42)#define cscGetDACInfo		(vendorCSCBase+43)#define cscGetMultiplierConstants	(vendorCSCBase+44)#define cscGetMultiplierConstantsChannel	(vendorCSCBase+45)#define cscGetMultiplierICFControls	(vendorCSCBase+46)#define cscGetMultiplierMode	(vendorCSCBase+47)#define cscGetMultiplierSigns	(vendorCSCBase+48)#define cscGetNoiseChannel	(vendorCSCBase+49)#define cscGetMultiplierFilterChannel	(vendorCSCBase+50)#define cscGetMultiplierPartialSumInChannel	(vendorCSCBase+51)#define cscGetCLUTMode		(vendorCSCBase+52)#define cscGetCLUTMixRatio	(vendorCSCBase+53)#define cscGetCLUTSource	(vendorCSCBase+54)#define cscGetCLUTMatrixConfiguration	(vendorCSCBase+55)#define cscGetThresholderRange	(vendorCSCBase+56)#define cscGetThresholderSigns	(vendorCSCBase+57)#define cscGetThresholderColorFormat	(vendorCSCBase+58)#define cscGetThresholderTransitionMode	(vendorCSCBase+59)#define cscGetRectangleBounds	(vendorCSCBase+60)#define cscGetRectangleControl	(vendorCSCBase+61)#define cscGetBlendRatioRateOfChange	(vendorCSCBase+62)#define cscGetLineControlMode	(vendorCSCBase+63)#define cscGetRawLineCommands	(vendorCSCBase+64)#define cscGetPixelControlMode	(vendorCSCBase+65)#define cscUnusedStatus0	(vendorCSCBase+66)#define cscGetPixelICF		(vendorCSCBase+67)#define cscGetPixelMultiplierChannel	(vendorCSCBase+68)#define cscGetPixelThresholderChannel	(vendorCSCBase+69)#define cscGetPixelDisplayChannelColorFormat	(vendorCSCBase+70)#define cscGetPixelNoiseMode	(vendorCSCBase+71)#define cscReadFromSlotSpace	(vendorCSCBase+72)//Define constants for maximum Control, Status, extended Control,//and extended Status control status codes#define maxControl		(cscSetDefaultMode)#define maxStatus		(cscGetDefaultMode)#define maxXControl		(cscWriteToSlotSpace-vendorCSCBase)#define maxXStatus		(cscReadFromSlotSpace-vendorCSCBase)//-------------------------------------------------------------------------//		TEMPLATES#define VDAddressing_depth	0	//INTEGER: pixel depth { 1, 2, 4, 8, 16, 32 }#define VDAddressing_rowBytes	2	//INTEGER: hardware row bytes { 1K, 2K, 4K }#define VDAddressing_rows	4	//INTEGER: rows { 512, 1K, 2K, 4K, 8K }#define VDAddressing_interleaving	6	//BitState: (byte & pad) for double plane interleaving#define VDMemoryProtectMask_mask	0	//long:#define VDPhysicalMemoryOffset_offset	0	//point:#define VDHWStatus_VSCVersion	0	//word:#define VDHWStatus_VDEVersion	2	//word:#define VDHWStatus_WICVersion	4	//word:#define VDHWStatus_EEPROMStatus	6	//BitState: if true, EEPROM is present and functional#define VDHWStatus_videoSets	8	//BitState: if true, 2 sets of video RAM are present else only 1#define VDHWStatus_vmemType	10	//BitState: if true, 1 or 2MByte devices are used else 4MByte#define VDHWStatus_InputModuleStatus	12	//long:#define VDHWStatus_lightPenStatus	16	//long: currently unused and zero#define VDHWStatus_outputModuleStatus	20	//long: Returns the output module ID in LSByte#define VDHWStatus_displayCardStatus	24	//long: Returns the default start ID in 31:24, Serial Number in 23:0#define VDHWStatus_displayCardSignature	28	//long: Returns the main card Signature ( board type )#define VDBankState_bankID	0	//BankID: { NoBank, BankA, BankB, BankC, BankD }#define VDBankState_CCCEnable	2	//BitState: BitState for CCCEnable#define VDBankState_bankDepth	4	//INTEGER: { 1, 2, 4, 8 }#define VDBankState_CLUTIndexMSBs	6	//byte: most significant bits for depth<8#define VDBankState_pad1	7#define VDBankPairState_pairID	0	//PairID: { PairAB, PairCD }#define VDBankPairState_pairMode	2	//PairMode: { PairModeRGB555, PairModeYCc, PairModeCCC4 }#define VDBankPairState_RGB555LSBs	4	//INTEGER: Least significant bits for RGB555 mode#define VDBankPairState_alphaMode	6	//AlphaMode: { alphaBitNotUsed, alphaBitIsGreen, alphaBitIsSavedThresholder, alphaBitIsSourceEnable }#define VDDYUV8State_bankID	0	//BankID: { NoBank, BankA, BankB, BankC, BankD }#define VDDYUV8State_yLUT	2	//PTR: NIL, or pointer to 16 byte y LUT#define VDDYUV8State_uvLUT	6	//PTR: NIL, or pointer to 16 byte uv LUT#define VDDYUV8State_interpolate	10	//BitState:  enable chrominance interpolation#define VDBusMuxState_busMux	0	//BusMux: { BusMuxVB1, BusMuxVB2 }#define VDBusMuxState_busCompMask	2	//INTEGER: { BusCompMaskA + BusCompMaskB + BusCompMaskC + BusCompMaskD }#define VDBusMuxState_channel	4	//ChannelID: { memBankChannel, DYUVdecoderChannel, ABdecoderChannel, CDdecoderChannel }#define VDControlState_control	0	//ControlID:#define VDControlState_priority	2	//INTEGER: priority#define VDControlState_channel	4	//ChannelID:#define VDAlphaDisplaySource_channel	0	//ChannelID:#define VDAlphaDisplaySource_default	2	//AlphaDisplayMode:#define VDChannelColorState_channel	0	//ChannelID: display source#define VDChannelColorState_colorFormat	2	//INTEGER: { Color24, Color24fromAlpha, Color24fromRed, Color24fromGreen, Color24fromBlue }#define VDChannelColorState_color	4	//LONGINT: ARGB8888 color#define VDCaptureState_box	0	//CaptureBoxID: { CaptureBox1 }#define VDCaptureState_captureEnables	2	//BusCompMask: { A + B + C + D }#define VDCaptureState_captureRectID	4	//INTEGER: [currently unused, set to zero]#define VDCaptureState_captureRect	6	//Rect: (8 bytes) QuickDraw rect#define VDCaptureState_captureChannel	14	//ChannelID: capture source#define VDCaptureState_captureFormat	16	//CaptureFormat: { Capture32Bits, CaptureRGB555, CaptureYCcEvenPixelCc,//CaptureYCcAveragePixelCc, CaptureAlphaToComponents,//CaptureRedToComponents, CaptureGreenToComponents, CaptureBlueToComponents }#define VDCaptureState_captureStart	18	//CaptureStart: { startOdd, startEven, startNext }#define VDCaptureState_captureLength	20	//CaptureLength: { captureField, captureFrame, captureContinuous }#define VDCaptureState_waitTillDone	24	//Boolean: If true, wait till done capturing#define VDCaptureColor_color	0	//LONGINT: ARGB8888 color#define VDClockState_chroma	0	//BitState: enable the chroma clock output#define VDClockState_square	2	//BitState: convert the VCO Clock and the Reference Clock from pulses to square waves#define VDClockState_line	4	//BitState: enable the shift clock to the line command processor#define VDClockState_vRAM	6	//BitState: enable the shift clock to the video memory#define VDClockState_DCLK	8	//BitState: drive the clock pins on the digital video ports as outputs#define VDClockState_PCLK	10	//BitState: sync the phase clock to input instead of free running#define VDClockSource_masterClockSource	0	//MasterClockSource: { MasterClockFromVCO, MasterClockFromInputModule, MasterClockFromReference, MasterClockFromDigitalVideoPort }#define VDClockDivider_divider	0	//ClockDivider: { PixelClkDivider, ChromaClkDivider, VCOClkDivider, ReferenceClkDivider }#define VDClockDivider_interval	2	//LONGINT: divider value (period of clock)#define VDClockDivider_squareClock	6	//BitState: convert from pulses to square waves (divide by 2)#define VDMasterControl_refresh	0	//BitState: enables RAM refresh#define VDMasterControl_transfer	2	//BitState: enables Transfer Cycles to video RAM#define VDMasterControl_interrupt	4	//BitState: master interrupt enable for the entire board#define VDInterruptStates_time	0	//BitState: Absolute time interrupt#define VDInterruptStates_pen	2	//BitState: Light Pen interrupt#define VDInterruptStates_penTrigger	4	//BitState: Light Pen trigger interrupt#define VDInterruptStates_directPen	6	//BitState: Actual state of pen#define VDInterruptStates_directTrigger	8	//BitState: Actual state of trigger#define VDInterruptMode_mode	0	//AbsoluteInterruptMode: { InterruptEveryFrame, InterruptEveryField, InterruptEveryLine }#define VDInterruptMode_where	2	//Point: the point on the screen this interrupt is set for#define VDHVStatus_mode		0	//HVStatusMode: { FreezeHVStatus, ContinuousHVStatus, LightPenHVStatus }#define VDHVStatus_where	2	//Point: horizontal and vertical coordinates (based on mode)#define VDHVControl_onOff	0	//BitState:#define VDHVControl_interleave	2	//BitState: if enabled, generate adjusted clocks#define VDTimeSequencerState_HRAM	0	//INTEGER: Address within horizontal display sequencer#define VDTimeSequencerState_VRAM	2	//INTEGER: Address within vertical display sequencer#define VDTimeSequencerState_HCnt	4	//INTEGER: Address within horizontal display sequencer#define VDTimeSequencerState_VCnt	6	//INTEGER: Address within vertical display sequencer#define VDTimeSequencerState_HLV	8	//INTEGER: Horizontal load value#define VDTimeSequencerState_VLV	10	//INTEGER: Vertical load value#define VDTimeSequencerState_command1	12	//INTEGER: H/V command pair#define VDTimeSequencerState_command2	14	//INTEGER#define VDTimeSequencerState_commandCount	16	//INTEGER: Command pair counter activation value#define VDSyncControl_inputSyncSource	0	//SyncSource: { SyncFromSame, syncSource0, syncSource1 }#define VDSyncControl_IREclamp	2	//BitState: if true, IRE clamping in effect#define VDSyncControl_interlace	4	//BitState: if true, sync is interlaced#define VDSyncControl_EQAndSer	6	//BitState: if true, equalization and serration is in effect#define VDSyncControl_syncOnVideo	8	//BitState: if true, sync is output on video signals#define VDSyncControl_VBDigital	10	//BitState: if true, VideoBahn Digital Master#define VDSyncControl_VBComposite	12	//BitState: if true, VideoBahn Composite Master#define VDSyncControl_TTLsync	14	//TTLsyncMode: { TTLsyncSame, TTLsyncOff, TTLsyncHsync, TTLsyncHESsync, TTLsyncComposite12PixelDelay,//TTLsyncComposite11PixelDelay, TTLsyncComposite10PixelDelay, TTLsyncComposite1PixelDelay,//TTLsyncCompositeNoPixelDelay }#define VDGenlockControl_genlockControl	0	//word: genlock control word#define VDGenlockControl_genlockReserved	2	//word: RESERVED#define VDGenlockControl_HorzNoLockThreshold	4	//INTEGER: this is the number of times genlock must miss//a horizontal frame before search mode begins#define VDGenlockControl_VertNoLockThreshold	6	//INTEGER: this is the number of times genlock must miss//a vertical frame before search mode begins#define VDGenlockControl_hLockAquisitionTime	8	//INTEGER: this is the number of frame locks//required before HLockStatus is set#define VDGenlockControl_hLockStatus	10	//BitState: if true, horizontal lock achieved#define VDGenlockControl_vLockStatus	12	//BitState: if true, vertical lock achieved#define VDGenlockControl_singleHSSmode	14	//BitState: if true, only one horizontal start sync command can be issued//by the sequencer after a horizontal HSS enable command#define VDModeInfo_newMode	0	//sResource ID#define VDModeInfo_oldMode	2	//sResource ID#define VDBankConfiguration_ConcatenateMode	0	//MemoryConcatenation: Bank concatenation mode#define VDBankConfiguration_ABInterleaving	2	//BitState: 8  bit interleave, only valid for some configs#define VDBankConfiguration_CDInterleaving	4	//BitState: 8  bit interleave, only valid for some configs#define VDBankConfiguration_ABCDInterleaving	6	//BitState: 16 bit interleave, only valid for some configs#define BankAttributeRecord_bankID	0	//BankID:#define BankAttributeRecord_attributeID	2	//attributeID: { BankDisplayOffset | BankDisplayZoom | BankDisplayMosaic }#define BankAttributeRecord_point	4	//Point: { BankDisplayOffset | BankDisplayZoom | BankDisplayMosaic }#define BankAttributeRecord_size	8#define VDBankDisplayAttributes_numRecs	0	//long: the number of display attribute records that follow#define VDBankDisplayAttributes_attributeRecs	4	//BankAttributeRecord	//BankAttributeRecord[1..numRecs]: bank/attribute/value records#define VDVDESyncLoadState_multiplier		0	//BitState: if true, multiplier control registers are loaded synchronously#define VDVDESyncLoadState_evenMultConstants		2	//BitState:#define VDVDESyncLoadState_oddMultConstants		4	//BitState:#define VDVDESyncLoadState_CLUTMatrixOffset		6	//BitState:#define VDVDESyncLoadState_defaultDisplayChannel	8	//BitState:#define VDVDESyncLoadState_captureDataSourceFormat	10	//BitState:#define VDVDESyncLoadState_evenFieldSync		12	//BitState: if true above register writes are delayed till the end of an even field#define VDVDESyncLoadState_oddFieldSync		14	//BitState: if true above register writes are delayed till the end of an odd field#define VDVSCSyncLoadState_bankOffsets	0	//BitState:#define VDVSCSyncLoadState_bankZooms_Mosaics	2	//BitState:#define VDVSCSyncLoadState_captureBankEnables	4	//BitState:#define VDVSCSyncLoadState_bankConfig_CCCEnables	6	//BitState:#define VDVSCSyncLoadState_captureWindow	8	//BitState:#define VDVSCSyncLoadState_rectangles	10	//BitState:#define VDVSCSyncLoadState_busMux_bankDepth	12	//BitState:#define VDVSCSyncLoadState_CLUTOffsets	14	//BitState:#define VDVSCSyncLoadState_lineControl_priority	16	//BitState:#define VDVSCSyncLoadState_syncLoadMode	18	//SyncLoadMode:#define VDSerialState_IMDOutputEnable	0	//BitState: if True, enables IMD as output#define VDSerialState_IMCOutput	2	//BitState: output bit#define VDSerialState_IMIOutput	4	//BitState: output bit#define VDSerialState_IMDOutput	6	//BitState: output bit#define VDSerialState_IMDInput	8	//BitState: input bit#define VDDVPState_port	0	//DigitalVideoPort: { digitalVideoPort1, digitalVideoPort1 }#define VDDVPState_inputEnable	2	//BitState: if True, port is enabled for input#define VDDVPState_outputEnable	4	//BitState: if True, port is enabled for output#define VDDVPState_channel	6	//INTEGER: { memBankChannel, DYUVdecoderChannel, ABdecoderChannel, CDdecoderChannel }#define VDDVPState_DVPWriteValue	8	//LONGINT: DVP write register value#define VDDVPState_DVPReadValue	12	//LONGINT: value read from DVP#define VDDACInfo_RAMDACBase	0	//Ptr:#define VDMultiplierConstants_multiplierID	0	//MultiplierID: { multiplier1 }#define VDMultiplierConstants_arraySelect	2	//OddEven: access to the odd and/or even array#define VDMultiplierConstants_arrayPtr	4	//Ptr: Pointer to array of Fixed multiplier constants#define VDMultiplierConstants_arrayBounds	8	//Rect: (8 bytes) QuickDraw rect (sizes array)#define VDMultiplierState_multiplierID	0	//MultiplierID: { multiplier1 }#define VDMultiplierState_channel	2	//ChannelID:#define VDMultiplierState_busComp	4	//BusComp: { busCompA, busCompB, busCompC, busCompD }#define VDMultiplierState_multiplierMode	6	//multiplierMode:#define VDMultiplierState_filterTaps	8	//word: 9 or 18#define VDMultiplierState_clampedBits	10	//word: 8 or 16#define VDMultiplierState_CLUT2Override	12	//BitState: if True, even multiplier output overrides CLUT2#define VDMultiplierState_multiplexMode	14	//MultiplierMultiplexMode: { dependent, independent }#define VDMultiplierSigns_multiplierID	0	//MultiplierID: { multiplier1 }#define VDMultiplierSigns_signType	2	//MultSignType: { BlendInputSigns, TransformInputSigns, MultiplierOutputSigns, PartialSumOutputSign }#define VDMultiplierSigns_arraySelect	4	//OddEven: access to the odd or even array#define VDMultiplierSigns_arrayPtr	6	//Ptr: Pointer to word array of multiplier signs#define VDMultiplierSigns_arrayBounds	10	//Rect: (8 bytes) QuickDraw rect (sizes array)#define VDICFState_ICFScaleFactor	0	//Fixed: 16.16 value. 2.7 useable bits#define VDICFState_blendRatioTotal	4	//Fixed: 16.16 value. 3.7 useable bits#define VDICFState_blendRatioRate	8	//Fixed: 16.16 value. 3.9 useable bits#define VDLineControl_mode	0	//PixelControlMode: { lineControlOff, activeLineControl, preScanLineControl, activeAndPreScanLineControl }#define VDLineControl_rect	2	//Rect: defines the region, in lines and commands#define VDLineControl_commands	10	//Ptr: pointer to raw or pseudo line control commands#define VDPixelControl_mode	0	//PixelControlMode: { pixelIs8BitICF, pixelIs4BitDisplayChannel4BitPriority,//pixelIs7BitICF1BitChoiceControl,pixelIs8BitChoiceControl,//pixelIsCaptureAndShiftControl}#define VDPixelControl_source	2	//ICFSource: { ICFSourceFromPixelControl, ICFSourceFromNoise }#define VDPixelControl_signState	4	//BitState: if true ICF is 8 bit signed value -0.9999 to 0.9999//if false ICF is 8 bit value 0 to 1.9999#define VDPixelControl_ICFScaleSource	6	//ICFScaleFactorSource: { ICFscaleFactorFromRegister, ICFscaleFactorFromPixelControl, ICFscaleFactorFromNoise }#define VDPixelState_pixelSelect	0	//pixelSelectChoice: { PixelSelect0, PixelSelect1 }#define VDPixelState_multiplierID	2	//MultiplierID: { multiplier1 }#define VDPixelState_multiplierColumn	4	//INTEGER: Column affected (1..3)#define VDPixelState_multiplierChannel	6	//Channel: { inputModuleChannel, liveDigitalInChannel, videoBus1Channel, videoBus2Channel, CLUT1Channel,//CLUT2Channel, multiplierOutChannel, liveDigitalInAlpha_partialSum16Channel }#define VDPixelState_thresholderID	8	//ThresholderID: { thresholder1 }#define VDPixelState_thresholderChannel	10	//Channel: { inputModuleChannel, liveDigitalInChannel, videoBus1Channel, videoBus2Channel, CLUT1Channel,//CLUT2Channel, multiplierOutChannel, liveDigitalInAlpha_partialSum16Channel }#define VDPixelState_colorFormat	12	//ColorFormat: { Color24, Color24fromAlpha, Color24fromRed, Color24fromGreen, Color24fromBlue }#define VDPixelState_pixelICF	14	//Fixed: 16.16 value. 1.7 useable bits#define VDNoiseState_channel	0	//ChannelID: { videoBus2Channel, liveDigitalInChannel, monochrome8BitNoise, color24BitNoise }#define VDNoiseState_busComp	2	//BusComp: { busCompA, busCompB, busCompC, busCompD }#define VDNoiseState_syncMode	4	//NoiseSync: { nonSyncNoise, frameSyncNoise }#define VDNoiseState_taps	6	//word: { 13, 19 } (repeat every 8,191 values, or every 524,287 values)#define VDNoiseState_bits	8	//word: { 7, 8 } (7-bit noise, or 8-bit noise)#define VDCLUTState_CLUTID	0	//CLUTID: { CLUT1, CLUT2 }#define VDCLUTState_CLUTMode	2	//CLUTMode:#define VDCLUTState_mixRatio	4	//unsigned word: $FFFF is 100%#define VDCLUTState_channel	6	//ChannelID: { videoBus2Channel, multiplierOutChannel }#define VDCLUTState_busComp	8	//BusComp: { busCompA, busCompB, busCompC, busCompD }#define VDCLUTMatrixState_CLUTID	0	//CLUTID: { CLUT1, CLUT2 }#define VDCLUTMatrixState_size	2	//CLUTmatrixSize: { MatrixSize16, MatrixSize32 }#define VDCLUTMatrixState_start	4	//Point: (QuickDraw point)#define VDXEntryRecord_csTable	0	//^ColorSpec: Pointer to an array of color specs#define VDXEntryRecord_csStart	4	//word: - Which spec in array to start with, or -1#define VDXEntryRecord_csCount	6	//word: - Number of color spec entries to set#define VDXEntryRecord_csCLUTID	8	//CLUTID: { CLUT1, CLUT2 }#define VDXEntryRecord_csCLUTMode	10	//CLUTMode:#define VDThresholderState_thresholderID	0	//ThresholderID: { thresholder1 }#define VDThresholderState_loColor	2	//long:	RGB888#define VDThresholderState_hiColor	6	//long:	RGB888#define VDThresholderState_dim	10	//number of elements of the sign bit array#define VDThresholderState_compMasks	12	//*BusComp: pointer to the array to be read from#define VDThresholderState_colorFormat	16	//ColorFormat: { color24, color24fromAlpha, color24fromRed, color24fromGreen, color24fromBlue }#define VDThresholderState_transitionMode	18	//TransitionMode: { transitionInactive, transitionInside, transitionOutside, transitionInsideAndOutside }#define VDRectangleState_rectangleID	0	//RectangleID:	{ rectangle1, rectangle2, rectangle3, rectangle4 }#define VDRectangleState_bounds	2	//Rect: (8 bytes) QuickDraw rect#define VDRectangleState_control	10	//RectangleControl:#define VDPixelNoiseControl_noiseBits	0	//word: { 8, 9 } (8-bit noise, or 9-bit noise)#define VDPixelNoiseControl_signedNoise	2	//BitState: if true noise is signed#define VDPixelNoiseControl_synchronous	4	//BitState: if true noise is synchronous to a frame#define VDDataBlock_offset	0	//LONGINT: offset into minor slot space (24 bit range)#define VDDataBlock_size	4	//LONGINT: size of data to write#define VDDataBlock_data	8	//byte[size]: data to write to card//-------------------------------------------------------------------------//		Constants used in VX Control and Status calls//@@ These will change from �Rate to �Mode since they also//@@ will indicate size of screen.  Waiting for list of from IRIS.//@@ There can still be both a logical and physical screen size//@@ if virtual screens are supported.//@@//@@ DON'T USE THESE. DRVR calls use the sResource IDs which are offset//@@ by 128, and are divided between the 24-bit mode Color QuickDraw and//@@ 32-bit mode 32-Bit QuickDraw versions since the OS also uses these//@@ modes for distinguishing the momory model for the base address.//@@ Currently the real equates are in VXROM.a. Those Equates should be moved.//NTSCRate	EQU	1	;Scan rate constants//PALRate	EQU	2//MacRate	EQU	3//VGARate	EQU	4//some constants#define yLUTSize	16		//Number of bytes in DYUV LUTs#define uvLUTSize	16//some, somewhat useful data types#define falseState	0		//Type BitState#define trueState	1#define doNotKnowState	2#define oppositeState	3#define disableIt	(falseState)	//Type ControlIt#define enableIt	(trueState)#define doNotChangeIt	(doNotKnowState)#define changeIt	(oppositeState)//VIDEO MEMORY#define noBank	0		//Type BankID#define bankA	1#define bankB	2#define bankC	3#define bankD	4#define BankDisplayOffset	0		//Type AttributeID#define BankDisplayZoom		1#define BankDisplayMosaic	2#define pairAB	0		//Type PairID#define pairCD	1#define pairModeRGB555	0		//Type PairMode#define pairModeYCc	1#define pairModeCCC4	2#define alphaBitNotUsed		0		//Type AlphaMode#define alphaBitIsGreen		1#define alphaBitIsSavedThresholder	2#define alphaBitIsSourceEnable	3#define busMuxVB1	0		//Type BusMux#define busMuxVB2	1#define busCompABit	3#define busCompBBit	2#define busCompCBit	1#define busCompDBit	0#define busCompMaskA	0x0008#define busCompMaskB	0x0004#define busCompMaskC	0x0002#define busCompMaskD	0x0001#define busCompMaskNone	0#define busCompMaskAll	0xFFFF#define busCompNone	0		//Type BusComp#define busCompAll	1#define busCompA	2		//BusComp A, B, C, and D must be sequential#define busCompB	3#define busCompC	4#define busCompD	5#define busCompAlpha	(busCompA)#define busCompRed	(busCompB)#define busCompGreen	(busCompC)#define busCompBlue	(busCompD)//Below is a list of channels for various Video Explorer multiplexers#define sameChannel		0		//Type ChannelID#define inputModuleChannel	1#define liveDigitalInChannel	2#define videoBus1Channel	3#define videoBus2Channel	4#define CLUT1Channel		5#define CLUT2Channel		6#define multiplierOutChannel	7#define defaultColor1Channel	8#define defaultColor2Channel	9#define liveDigitalInAlphaChannel	10#define videoBus2AlphaChannel	11#define zero_partialSum16Channel	12#define multiplierY_inputModuleChannel	13	//Pseudo channels for capture multiplexer//;liveDigitalInChannel#define partialSumHigh8_multiplierOutChannel	14//;videoBus2Channel#define displayMuxChannel	15#define defaultCaptureColorChannel	16#define partialSum16AR16GBChannel	17//;reserved#define memBankChannel		18	//Pseudo channels for video bus 1 and 2#define DYUVdecoderChannel	19#define ABdecoderChannel	20#define CDdecoderChannel	21#define CCC2decoderChannel	22//;videoBus2Channel					;Pseudo channels for digital video ports//;displayMuxChannel//;inputModuleChannel#define DVPWriteDataChannel	23#define liveDigitalInAlpha_multiplierOutChannel	24#define videoBus2Alpha_multiplierOutChannel	25#define videoBus2AR_partialSum16Channel	26//;CLUT1Channel/CLUT1Channel//;inputModuleChannel					;Pseudo channels for MultiplierInputSource1/2/3//;liveDigitalInChannel//;videoBus1Channel//;videoBus2Channel//;CLUT1Channel//;CLUT2Channel#define multiplierDefaultColorChannel	27#define noiseGeneratorChannel	28//;inputModuleChannel					;Pseudo channel for Pixel0/1RangeThresholderInputSource//;liveDigitalInChannel//;videoBus1Channel//;videoBus2Channel//;CLUT1Channel//;CLUT2Channel//;multiplierOutChannel#define liveDigitalInAlpha_partialSum16Channel	29//Below psuedo channels are for sources which take single COMPONENTS only.//;videoBus2Channel (alpha)				;Pseudo channels for CLUT1/2 source//;videoBus2Channel (red)//;videoBus2Channel (green)//;videoBus2Channel (blue)//;multiplierOutChannel (red)//;reserved#define MatrixAddressGeneratorChannel	30//;reserved#define lineOrPixelConstantsChannel	31	//Pseudo channels for MultiplierConstantsSource//;NoiseGeneratorChannel//;videoBus2Channel (red)//;liveDigitalInChannel (alpha)//;reserved//;reserved//;reserved#define multiplierConstantsChannel	32//;videoBus2Channel (alpha)				;Pseudo channels for FilterSource#define multipliersFirstInputChannel	33//;videoBus2Channel (alpha)				;Pseudo channels for MultiplierBWNoiseGenerator//;videoBus2Channel (red)//;videoBus2Channel (green)//;videoBus2Channel (blue)//;liveDigitalInChannel (alpha)//;reserved#define monochrome8BitNoise	34#define color24BitNoise		35//;memBankChannel (alpha)				;Pseudo channels for PartialSumIn//;memBankChannel (red)//;memBankChannel (green)//;memBankChannel (blue)#define zeroComponentInputChannel	36//@@@	Below are from Ron. They are unknown. Removal is pending check with Ron.#define MultiplierPartialSumAlphaChannel	37//Constants for control of synchronous loading#define evenFieldEndOfBlanking	0		//Type SyncLoadMode#define evenFieldEndOfSync	1#define oddFieldEndOfBlanking	2#define oddFieldEndOfSync	3#define noSyncLoad		4#define evenOddEndOfBlanking	5#define evenOddEndOfSync	6//EXTERNAL DIGITAL VIDEO PORTS#define digitalVideoPort1	0		//Type DigitalVideoPort#define digitalVideoPort2	1//PRIORITY RESOLVER#define defaultControl		0		//Type ControlID#define ABRGB555Control		1#define CDRGB555Control		2#define CLUT1Control		3#define CLUT1BlackDetectControl	4#define CLUT2Control		5#define CLUT2BlackDetectControl	6#define rectangle1Control	7#define rectangle2Control	8#define rectangle3Control	9#define rectangle4Control	10#define thresholder1State0Control	11#define thresholder1State1Control	12#define thresholder1State2Control	13#define thresholder1State3Control	14#define thresholder1State4Control	15#define thresholder1State5Control	16#define thresholder1State6Control	17#define thresholder1State7Control	18#define thresholderTransitionControl	19#define lineControlControl	20#define pixelControlSelect0Control	21#define pixelControlSelect1Control	22#define color24		0		//Type ColorFormat#define color24fromAlpha	1#define color24fromRed		2#define color24fromGreen	3#define color24fromBlue		4//CLOCK CONTROL#define masterClockFromVCO	0		//Type MasterClockSource#define masterClockFromInputModule	1#define masterClockFromReference	2#define masterClockFromDigitalVideoPort	3#define pixelClockDivider	0		//Type ClockDivider#define chromaClockDivider	1#define VCOClockDivider		2#define referenceClockDivider	3//ABSOLUTE TIMING#define interruptEveryFrame	0		//Type AbsoluteInterruptMode#define interruptEveryField	1#define interruptEveryLine	2#define freezeHVStatus		0		//Type HVStatusMode#define continuousHVStatus	1#define lightPenHVStatus	2#define syncFromSame	0		//Type SyncSource#define syncSource0		3#define syncSource1		4#define TTLSyncSame		0		//Type TTLSyncMode#define TTLSyncOff		1#define TTLSyncHsync		2#define TTLSyncHESsync		3#define TTLSyncComposite12PixelDelay	4#define TTLSyncComposite11PixelDelay	5#define TTLSyncComposite10PixelDelay	6#define TTLSyncComposite1PixelDelay	7#define TTLSyncCompositeNoPixelDelay	8//RELATIVE TIMING#define concatTheSame	0		//Type MemoryConcatenation#define concatA_B_C_D	1#define concatABX_C_D	2#define concatABY_C_D	3#define concatA_B_CDX	4#define concatABX_CDX	5#define concatABY_CDX	6#define concatA_B_CDY	7#define concatABX_CDY	8#define concatABY_CDY	9#define concatACX_BDX	10#define concatACY_BDY	11#define concatABX_CDXX	12#define concatABY_CDYY	13#define concatABX_CDXY	14#define selectedAlphaChannelMode	0		//Type AlphaDisplayMode#define associatedAlphaChannelMode	1//CAPTURE MULTIPLEXER#define captureBox1	0		//Type CaptureBoxID#define capture32Bits		0		//Type CaptureFormat ;Capture 32 bits to banks ABCD#define captureRGB555		1		//Capture 16 bits as RGB555 to banks AB, and banks CD#define captureYCcEvenPixelCc	2		//Capture as 16-bit YCc to banks AB, and banks CD#define captureYCcAveragePixelCc	3		//Capture as 16-bit YCc to banks AB, and banks CD#define captureAlphaToComponents	4		//Capture single component to banks ABCD#define captureRedToComponents	5#define captureGreenToComponents	6#define captureBlueToComponents	7#define startEven	0		//Type captureStart#define startOdd	1#define startNext	2#define startNow	3#define captureField		1		//Type CaptureLength#define captureFrame		2#define captureContinuous	(-1)//MULTIPLIERS#define multiplier1	0		//Type MultiplierID#define multTransform		0		//Type MultiplierMode#define multBlend		1#define multTransformThenBlend	2#define multBlendThenTransform	3#define mult2D8BitFilter	4#define mult2D16BitFilter	5#define mult16BitFrameAccumulator	6#define multTransformThenTransform	7#define multDependent	0		//Type MultiplierMultiplexMode#define multIndependent	1#define blendInputSigns		0	//Type MultSignType#define transformInputSigns	1#define multiplierOutputSigns	2#define partialSumOutputSign	3#define evenIndex	0		//Type OddEven#define oddIndex	1#define both	2#define isNotSigned	0		//Type Sign#define isSigned	1#define nonSyncNoise	0		//Type NoiseSync#define frameSyncNoise	1//INTERNAL COLOR LOOK UP TABLES REGISTERS#define CLUT1	0		//Type CLUTID#define CLUT2	1//the following CLUT modes may be used by extended driver call//or by the SetLineCommand structure.  The line command mechanisim//cannot set Matrix modes or CLUT2's compressed state#define normalNormalCLUT	0		//Type CLUTmode#define normalCompressedCLUT	1#define normalMatrixCLUT	2#define mixedNormalCLUT		3#define mixedCompressedCLUT	4#define mixedMatrixCLUT		5#define pairedNormalCLUTs	6		//CLUT 1 and 2 colaborating on 384 colors#define pairedCompressedCLUT	7		//CLUT 1 and 2 colaborating on 512 colors#define CCC2BitNormal		8		//second CCC color is one of 128 at 24 bits#define CCC2BitCompressedCLUT	9		//second CCC color is one of 256 at 16 bits#define matrixNormalCLUT	10		//CLUT1 is Matrix, CLUT2 is Normal#define matrixCompressedCLUT	11#define matrixMatrixCLUT	12//The following are used by the driver for the CLUTModes,//CLUT1Source, and CLUT2Source registers#define normalCLUTs	(%00)#define mixedCLUT1	(%01)#define combinedCLUTs	(%10)#define CCCCLUTs	(%11)#define matrixMode	(%110)#define matrixSize16	0		//Type CLUTmatrixSize#define matrixSize32	1//RANGE THRESHOLDER#define thresholder1	0		//Type ThresholderID#define transitionInactive	0	//Type TransitionMode#define transitionInside	1#define transitionOutside	2#define transitionInsideAndOutside	3//RECTANGLE CONTROLS#define rectangle1	0		//Type RectangleID#define rectangle2	1#define rectangle3	2#define rectangle4	3#define normalYNormalXInside	0	//Type RectangleControl#define normalYNormalXOutside	1#define normalYInvertedXInside	2#define normalYInvertedXOutside	3#define invertedYNormalXInside	4#define invertedYNormalXOutside	5#define invertedYInvertedXInside	6#define invertedYInvertedXOutside	7//LINE CONTROL#define lineControlOff		0	//Type LineControlMode#define activeLineControl	1#define preScanLineControl	2#define activeAndPreScanLineControl	3//PIXEL CONTROL#define pixelIs8BitICF		0	//Type PixelControlMode#define pixelIs4BitDisplayChannel4BitPriority	1#define pixelIs7BitICF1BitChoiceControl	2#define pixelIs8BitChoiceControl	3#define pixelIsCaptureAndShiftControl	4#define ICFSourceFromPixelControl	0	//Type ICFSource#define ICFSourceFromNoise	1#define ICFscaleFactorFromRegister	0	//Type ICFScaleFactorSource#define ICFscaleFactorFromPixelControl	1#define ICFscaleFactorFromNoise	2#define pixel0Select	0		//Type PixelSelectChoice#define pixel1Select	1//@@Ron, how about a "bothPixelSelect" since often the caller may//@@want to affect the register pair////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////#endif