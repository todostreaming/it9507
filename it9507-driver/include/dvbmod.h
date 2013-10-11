/**
 *
 * Copyright (c) 2013 ITE Corporation. All rights reserved. 
 *
 * Module Name:
 *   iocontrol.h
 *
 * Abstract:
 *   The structure and IO code for IO control call.
 *
 */

#ifndef _DVBMOD_H_
#define _DVBMOD_H_

#include <linux/types.h>
#include <linux/dvb/frontend.h>

/**
 * The defination of ChannelInformation.
 */
typedef struct {
    __u32 frequency;                    /** Channel frequency in KHz.                                */
    fe_transmit_mode_t transmissionMode; /** Number of carriers used for OFDM signal                  */
    fe_modulation_t constellation;        /** Constellation scheme (FFT mode) in use                   */
    fe_guard_interval_t interval;                  /** Fraction of symbol length used as guard (Guard Interval) */
    fe_code_rate_t highCodeRate;              /** FEC coding ratio of high-priority stream                 */
} ChannelModulation;

typedef struct _TPS{
    __u16 cellid;
} TPS, *pTPS;

/* Use 'k' as magic number */
#define AFA_IOC_MAGIC  'k'

typedef struct {
    __u8				chip;
    fe_transmit_mode_t transmissionMode;
    fe_modulation_t constellation;
    fe_guard_interval_t interval;
    fe_code_rate_t highCodeRate;
    __u32				error;
    __u8				reserved[16];
} SetModuleRequest, *PSetModuleRequest;

typedef struct {
    __u8				chip;
    __u16				bandwidth;
    __u32				frequency;
    __u32				error;
    __u8				reserved[16];
} TxAcquireChannelRequest, *PTxAcquireChannelRequest;

typedef struct {
    __u8				OnOff;
    __u32				error;
    __u8				reserved[16];
} TxModeRequest, *PTxModeRequest;

typedef struct {
    int				GainValue;
    __u32				error;
} SetGainRequest, *PSetGainRequest;

typedef struct {
       __u8                      chip;
    __u32                        error;
    __u8                 reserved[16];
} StartTransferRequest, *PStartTransferRequest;

typedef struct {
       __u8                      chip;
    __u32                        error;
    __u8                 reserved[16];
} StopTransferRequest, *PStopTransferRequest;


typedef struct {
    __u32			error;
	__u32          frequency;
	__u16           bandwidth;    
	int*			maxGain;
	int*			minGain;
    __u8			reserved[16];	
} GetGainRangeRequest, *PGetGainRangeRequest;

typedef struct {
    __u32		   error;
    TPS           tps;
    __u8		   reserved[16];	
} SetTPSRequest, *PSetTPSRequest;

typedef struct {
    __u32		   error;
	int			  *gain;	 
    __u8		   reserved[16];	
} GetOutputGainRequest, *PGetOutputGainRequest;

/**
 * Demodulator API commands
 */
#define IOCTRL_ITE_GROUP_STANDARD           0x000
#define IOCTRL_ITE_GROUP_OTHER              0x500

#define IOCTL_ITE_DEMOD_SETMODULE_TX \
	_IOW(AFA_IOC_MAGIC, IOCTRL_ITE_GROUP_STANDARD + 0x21, SetModuleRequest)
	
#define IOCTL_ITE_DEMOD_ACQUIRECHANNEL_TX \
	_IOW(AFA_IOC_MAGIC, IOCTRL_ITE_GROUP_STANDARD + 0x22, TxAcquireChannelRequest)

#define IOCTL_ITE_DEMOD_ADJUSTOUTPUTGAIN_TX \
	_IOW(AFA_IOC_MAGIC, IOCTRL_ITE_GROUP_STANDARD + 0x2B, SetGainRequest)

#define IOCTL_ITE_DEMOD_GETGAINRANGE_TX \
	_IOW(AFA_IOC_MAGIC, IOCTRL_ITE_GROUP_STANDARD + 0x2C, GetGainRangeRequest)

#define IOCTL_ITE_DEMOD_GETOUTPUTGAIN_TX \
	_IOW(AFA_IOC_MAGIC, IOCTRL_ITE_GROUP_STANDARD + 0x2D, GetOutputGainRequest)

#define IOCTL_ITE_DEMOD_STARTTRANSFER_TX \
	_IOR(AFA_IOC_MAGIC, IOCTRL_ITE_GROUP_OTHER + 0x07, StartTransferRequest)
	
#define IOCTL_ITE_DEMOD_STOPTRANSFER_TX \
	_IOR(AFA_IOC_MAGIC, IOCTRL_ITE_GROUP_OTHER + 0x08, StopTransferRequest)
	
#define IOCTL_ITE_DEMOD_SETTPS_TX \
	_IOR(AFA_IOC_MAGIC, IOCTRL_ITE_GROUP_OTHER + 0x0E, SetTPSRequest)

__u32 DemodIOCTLFun(void *demodulator, __u32 IOCTLCode, unsigned long pIOBuffer);

#endif
