#ifndef MIDI_DRV_H
#define MIDI_DRV_H

#define MIDI_DRV_NUM_PORTS  8
#define MIDI_DRV_DEFAULT_SYSEX_SIZE 2048

#define MIDI_DRV_RET_OK                 0
#define MIDI_DRV_RET_PARSE_ERROR        1
#define MIDI_DRV_RET_FILE_NOT_FOUND     2
#define MIDI_DRV_RET_FATAL_ERROR        3
#define MIDI_DRV_RET_IO_ERROR           4
#define MIDI_DRV_RET_SIGNAL             5

typedef ULONG (* ASM midi_drv_tx_func_t)(REG(a2, APTR) userdata);
typedef void (* ASM midi_drv_rx_func_t)(REG(d0, UWORD input), REG(a2, APTR userdata));

SAVEDS BOOL ASM midi_drv_init(REG(a6, APTR sysbase));
SAVEDS void ASM midi_drv_expunge(void);
SAVEDS ASM struct MidiPortData *midi_drv_open_port(
        REG(a3, struct MidiDeviceData *data),
        REG(d0, LONG portnum),
        REG(a0, midi_drv_tx_func_t tx_func),
        REG(a1, midi_drv_rx_func_t rx_func),
        REG(a2, APTR userdata)
        );
SAVEDS ASM void midi_drv_close_port(
        REG(a3, struct MidiDeviceData *data),
        REG(d0, LONG portnum)
        );

/* config option */
extern ULONG midi_drv_sysex_max_size;

struct midi_drv_config_param;
typedef int (*midi_config_func_t)(struct midi_drv_config_param *cfg);

extern int midi_drv_config(char *cfg_file, char *arg_template,
                           struct midi_drv_config_param *param,
                           midi_config_func_t func);

/* external API */
extern void midi_drv_api_tx_msg(int port, midi_msg_t msg);
extern void midi_drv_api_tx_sysex(int port, midi_msg_t msg, UBYTE *data, ULONG size);

extern int  midi_drv_api_rx_msg(int *port, midi_msg_t *msg);
extern void midi_drv_api_rx_sysex(int port, UBYTE **data, ULONG *size);
extern int  midi_drv_api_rx_wait(ULONG *wait_got_mask);

extern int  midi_drv_api_init(struct ExecBase *sysBase);
extern void midi_drv_api_config(void);
extern void midi_drv_api_exit(void);

#endif
