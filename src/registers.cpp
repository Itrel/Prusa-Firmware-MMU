#ifndef UNITTEST
#include <avr/pgmspace.h>
#else
#define PROGMEM /* */
#endif

#include "registers.h"
#include "application.h"
#include "version.hpp"

#include "modules/finda.h"
#include "modules/fsensor.h"
#include "modules/globals.h"
#include "modules/idler.h"
#include "modules/motion.h"
#include "modules/pulley.h"
#include "modules/selector.h"
#include "modules/permanent_storage.h"
#include "modules/voltage.h"

/** @defgroup register_table Register Table
 *

  ---------------------------------------------------------------------------------
  Register 8-bit Empty value = 0xFFh 255

  Register 16-bit Empty value = 0xFFFFh 65535

  _Italic = unused or default_

  __Bold = Status__

  ---------------------------------------------------------------------------------
  Access type:
  - Read: the register can be only read
  - Write: the register can be read and written to. The written change is not persistent (applies only until reset of the MMU)
  - Write Persistent: the register can be read and written to and the written values is stored in EEPROM (persistent across restarts)

  ---------------------------------------------------------------------------------
  How can you use the M707/M708 gcodes?
  - Serial terminal like Putty.

  ### !!! Gcodes are case sensitive so please don't use upper case A or X in the address you want to read !!!

  #### Useful tools/links:
  To convert hex to ascii https://www.rapidtables.com/convert/number/hex-to-ascii.html

  To convert hex to dec   https://www.rapidtables.com/convert/number/hex-to-decimal.html

  Version: 0.0.1

  ---------------------------------------------------------------------------------


| Address  | Bit/Type | Name                       | Valid values | Default     | Description                              | Read / Write | Gcode Read | Gcode Write
| :--      | :--      | :--                        | :--:         | :--:        | :--                                      | :--:         | :--:       | :--:
| 0x00h 00 | uint8    | project_major              | 00h 0        | ffh 255     | Project Major Version                    | Read only    | M707 A0x00 | N/A
| 0x01h 01 | uint8    | project_minor              | 00h 0        | ffh 255     | Project Minor Version                    | Read only    | M707 A0x01 | N/A
| 0x02h 02 | uint8    | project_revision           | 00h 0        | ffh 255     | Project Revision                         | Read only    | M707 A0x02 | N/A
| 0x03h 03 | uint8    | project_build_number       | 00h 0        | ffh 255     | Project Build Number                     | Read only    | M707 A0x03 | N/A
| 0x04h 04 | uint16   | MMU_errors                 | 0000h 0      | ffffh 65535 | MMU Errors                               | Read / Write Persistent | M707 A0x04 | M708 A0x04 Xnnnn
| 0x05h 05 | uint8    | Current_Progress_Code      | ffh 255      | ffh 255     | Emtpy                                    | Read only    | M707 A0x05 | N/A
| ^        | ^        | ^                          | 00h 0        | ^           | OK                                       | ^            | ^          | ^
| ^        | ^        | ^                          | 01h 1        | ^           | EngagingIdler                            | ^            | ^          | ^
| ^        | ^        | ^                          | 02h 2        | ^           | DisengagingIdler                         | ^            | ^          | ^
| ^        | ^        | ^                          | 03h 3        | ^           | UnloadingToFinda                         | ^            | ^          | ^
| ^        | ^        | ^                          | 04h 4        | ^           | UnloadingToPulley                        | ^            | ^          | ^
| ^        | ^        | ^                          | 05h 5        | ^           | FeedingToFinda                           | ^            | ^          | ^
| ^        | ^        | ^                          | 06h 6        | ^           | FeedingToBondtech                        | ^            | ^          | ^
| ^        | ^        | ^                          | 07h 7        | ^           | FeedingToNozzle                          | ^            | ^          | ^
| ^        | ^        | ^                          | 08h 8        | ^           | AvoidingGrind                            | ^            | ^          | ^
| ^        | ^        | ^                          | 09h 9        | ^           | FinishingMoves                           | ^            | ^          | ^
| ^        | ^        | ^                          | 0ah 10       | ^           | ERRDisengagingIdler                      | ^            | ^          | ^
| ^        | ^        | ^                          | 0bh 11       | ^           | ERREngagingIdler                         | ^            | ^          | ^
| ^        | ^        | ^                          | 0ch 12       | ^           | ERRWaitingForUser                        | ^            | ^          | ^
| ^        | ^        | ^                          | 0dh 13       | ^           | ERRInternal                              | ^            | ^          | ^
| ^        | ^        | ^                          | 0eh 14       | ^           | ERRHelpingFilament                       | ^            | ^          | ^
| ^        | ^        | ^                          | 0fh 15       | ^           | ERRTMCFailed                             | ^            | ^          | ^
| ^        | ^        | ^                          | 10h 16       | ^           | UnloadingFilament                        | ^            | ^          | ^
| ^        | ^        | ^                          | 11h 17       | ^           | LoadingFilament                          | ^            | ^          | ^
| ^        | ^        | ^                          | 11h 18       | ^           | SelectingFilamentSlot                    | ^            | ^          | ^
| ^        | ^        | ^                          | 12h 19       | ^           | PreparingBlade                           | ^            | ^          | ^
| ^        | ^        | ^                          | 13h 20       | ^           | PushingFilament                          | ^            | ^          | ^
| ^        | ^        | ^                          | 14h 21       | ^           | PerformingCut                            | ^            | ^          | ^
| ^        | ^        | ^                          | 15h 22       | ^           | ReturningSelector                        | ^            | ^          | ^
| ^        | ^        | ^                          | 16h 23       | ^           | ParkingSelector                          | ^            | ^          | ^
| ^        | ^        | ^                          | 17h 24       | ^           | EjectingFilament                         | ^            | ^          | ^
| ^        | ^        | ^                          | 18h 25       | ^           | RetractingFromFinda                      | ^            | ^          | ^
| ^        | ^        | ^                          | 19h 26       | ^           | Homing                                   | ^            | ^          | ^
| ^        | ^        | ^                          | 1ah 27       | ^           | MovingSelector                           | ^            | ^          | ^
| ^        | ^        | ^                          | 1bh 28       | ^           | FeedingToFSensor                         | ^            | ^          | ^
| 0x06h 06 | uint16   | Current_Error_Code         | 0000h 0      | ffffh 65535 | RUNNING                                  | Read only    | M707 A0x06 | N/A
| ^        | ^        | ^                          | 0001h 1      | ^           | OK                                       | ^            | ^          | ^
| ^        | ^        | ^                          | 8001h 32769  | ^           | FSENSOR_DIDNT_SWITCH_ON                  | ^            | ^          | ^
| ^        | ^        | ^                          | 8002h 32770  | ^           | FINDA_DIDNT_SWITCH_OFF                   | ^            | ^          | ^
| ^        | ^        | ^                          | 8003h 32771  | ^           | FSENSOR_DIDNT_SWITCH_ON                  | ^            | ^          | ^
| ^        | ^        | ^                          | 8004h 32772  | ^           | FSENSOR_DIDNT_SWITCH_OFF                 | ^            | ^          | ^
| ^        | ^        | ^                          | 8005h 32773  | ^           | FILAMENT_ALREADY_LOADED                  | ^            | ^          | ^
| ^        | ^        | ^                          | 8006h 32774  | ^           | INVALID_TOOL                             | ^            | ^          | ^
| ^        | ^        | ^                          | 8007h 32775  | ^           | Homing_FAILED                            | ^            | ^          | ^
| ^        | ^        | ^                          | 8008h 32776  | ^           | FINDA_VS_EEPROM_DISREPANCY               | ^            | ^          | ^
| ^        | ^        | ^                          | 8009h 32777  | ^           | FSENSOR_TOO_EARLY                        | ^            | ^          | ^
| ^        | ^        | ^                          | 802bh 32811  | ^           | QUEUE_FULL                               | ^            | ^          | ^
| ^        | ^        | ^                          | 802ch 32812  | ^           | VERSION_MISMATCH                         | ^            | ^          | ^
| ^        | ^        | ^                          | 802dh 32813  | ^           | PROTOCOL_ERROR                           | ^            | ^          | ^
| ^        | ^        | ^                          | 802eh 32814  | ^           | MMU_NOT_RESPONDING                       | ^            | ^          | ^
| ^        | ^        | ^                          | 802fh 32815  | ^           | INTERNAL                                 | ^            | ^          | ^
| ^        | ^        | ^                          | 8200h 33280  | ^           | TMC_IOIN_MISMATCH                        | ^            | ^          | ^
| ^        | ^        | ^                          | 8240h 33344  | ^           | TMC_IOIN_MISMATCH PULLEY                 | ^            | ^          | ^
| ^        | ^        | ^                          | 8280h 33408  | ^           | TMC_IOIN_MISMATCH SELECTOR               | ^            | ^          | ^
| ^        | ^        | ^                          | 8300h 33536  | ^           | TMC_IOIN_MISMATCH IDLER                  | ^            | ^          | ^
| ^        | ^        | ^                          | 83C0h 33728  | ^           | TMC_IOIN_MISMATCH All 3                  | ^            | ^          | ^
| ^        | ^        | ^                          | 8400h 33792  | ^           | TMC_RESET                                | ^            | ^          | ^
| ^        | ^        | ^                          | 8440h 33856  | ^           | TMC_RESET PULLEY                         | ^            | ^          | ^
| ^        | ^        | ^                          | 8480h 33920  | ^           | TMC_RESET SELECTOR                       | ^            | ^          | ^
| ^        | ^        | ^                          | 8500h 34048  | ^           | TMC_RESET IDLER                          | ^            | ^          | ^
| ^        | ^        | ^                          | 85C0h 34240  | ^           | TMC_RESET All 3                          | ^            | ^          | ^
| ^        | ^        | ^                          | 8800h 34816  | ^           | TMC_UNDERVOLTAGE_ON_CHARGE_PUMP          | ^            | ^          | ^
| ^        | ^        | ^                          | 8840h 34880  | ^           | TMC_UNDERVOLTAGE_ON_CHARGE_PUMP PULLEY   | ^            | ^          | ^
| ^        | ^        | ^                          | 8880h 34944  | ^           | TMC_UNDERVOLTAGE_ON_CHARGE_PUMP SELECTOR | ^            | ^          | ^
| ^        | ^        | ^                          | 8900h 35072  | ^           | TMC_UNDERVOLTAGE_ON_CHARGE_PUMP IDLER    | ^            | ^          | ^
| ^        | ^        | ^                          | 89C0h 35264  | ^           | TMC_UNDERVOLTAGE_ON_CHARGE_PUMP All 3    | ^            | ^          | ^
| ^        | ^        | ^                          | 9000h 36864  | ^           | TMC_SHORT_TO_GROUND                      | ^            | ^          | ^
| ^        | ^        | ^                          | 9040h 36928  | ^           | TMC_SHORT_TO_GROUND PULLEY               | ^            | ^          | ^
| ^        | ^        | ^                          | 9080h 36992  | ^           | TMC_SHORT_TO_GROUND SELECTOR             | ^            | ^          | ^
| ^        | ^        | ^                          | 9100h 37120  | ^           | TMC_SHORT_TO_GROUND IDLER                | ^            | ^          | ^
| ^        | ^        | ^                          | 91C0h 37312  | ^           | TMC_SHORT_TO_GROUND All 3                | ^            | ^          | ^
| ^        | ^        | ^                          | A000h 40960  | ^           | TMC_OVER_TEMPERATURE_WARN                | ^            | ^          | ^
| ^        | ^        | ^                          | A040h 41024  | ^           | TMC_OVER_TEMPERATURE_WARN PULLEY         | ^            | ^          | ^
| ^        | ^        | ^                          | A080h 41088  | ^           | TMC_OVER_TEMPERATURE_WARN SELECTOR       | ^            | ^          | ^
| ^        | ^        | ^                          | A100h 41216  | ^           | TMC_OVER_TEMPERATURE_WARN IDLER          | ^            | ^          | ^
| ^        | ^        | ^                          | A1C0h 41408  | ^           | TMC_OVER_TEMPERATURE_WARN All 3          | ^            | ^          | ^
| ^        | ^        | ^                          | C000h 49152  | ^           | TMC_OVER_TEMPERATURE_ERROR               | ^            | ^          | ^
| ^        | ^        | ^                          | C040h 49216  | ^           | TMC_OVER_TEMPERATURE_ERROR PULLEY        | ^            | ^          | ^
| ^        | ^        | ^                          | C080h 49280  | ^           | TMC_OVER_TEMPERATURE_ERROR SELECTOR      | ^            | ^          | ^
| ^        | ^        | ^                          | C100h 49408  | ^           | TMC_OVER_TEMPERATURE_ERROR IDLER         | ^            | ^          | ^
| ^        | ^        | ^                          | C1C0h 49600  | ^           | TMC_OVER_TEMPERATURE_ERROR All 3         | ^            | ^          | ^
| 0x07h 07 | uint8    | Filament_State             | 00h 0        | ffh 255     | Filament State                           | Read / Write | M707 A0x07 | M708 A0x07 Xnn
| 0x08h 08 | uint8    | FINDA_State                | 00h 0        | ffh 255     | not triggered                            | Read only    | M707 A0x08 | N/A
| ^        | ^        | ^                          | 01h 1        | ^           | triggered                                | ^            | ^          | ^
| 0x09h 09 | uint8    | FSensor_State              | 00h 0        | ffh 255     | not triggered                            | Read / Write | M707 A0x09 | M708 A0x09 Xnn
| ^        | ^        | ^                          | 01h 1        | ^           | triggered                                | ^            | ^          | ^
| 0x0ah 10 | uint8    | Motor_Mode                 | 00h 0        | 00h 0       | normal                                   | Read only    | M707 A0x0a | N/A
| ^        | ^        | ^                          | 01h 1        | ^           | stealth                                  | ^            | ^          | ^
| 0x0bh 11 | uint8    | extra_load_distance        | 00h 0        | 1eh 30      | unit mm                                  | Read / Write | M707 A0x0b | M708 A0x0b Xnn
| 0x0ch 12 | uint8    | FSensor_unload_check_dist. | 00h 0        | 28h 30      | unit mm                                  | Read / Write | M707 A0x0c | M708 A0x0c Xnn
| 0x0dh 13 | uint16   | Pulley_unload_feedrate     | 0000h 0      | 0078h 120   | unit mm/s                                | Read / Write | M707 A0x0d | M708 A0x0d Xnnnn
| 0x0eh 14 | uint16   | Pulley_acceleration        | 0000h 0      | 320h 800.0  | unit mm/s²                               | Read (Write) | M707 A0x0e | (M708 A0x0e Xnnnn)
| 0x0fh 15 | uint16   | Selector_acceleration      | 0000h 0      | 00c8h 200.0 | unit mm/s²                               | Read (Write) | M707 A0x0f | (M708 A0x0f Xnnnn)
| 0x10h 16 | uint16   | Idler_acceleration         | 0000h 0      | 01f4h 500.0 | unit deg/s²                              | Read (Write) | M707 A0x10 | (M708 A0x10 Xnnnn)
| 0x11h 17 | uint16   | Pulley_load_feedrate       | 0000h 0      | 0050h 80    | unit mm/s                                | Read / Write | M707 A0x11 | M708 A0x11 Xnnnn
| 0x12h 18 | uint16   | Selector_nominal_feedrate  | 0000h 0      | 002dh 45    | unit mm/s                                | Read / Write | M707 A0x12 | M708 A0x12 Xnnnn
| 0x13h 19 | uint16   | Idler_nominal_feedrate     | 0000h 0      | 012ch 300   | unit deg/s                               | Read / Write | M707 A0x13 | M708 A0x13 Xnnnn
| 0x14h 20 | uint16   | Pulley_slow_feedrate       | 0000h 0      | 0014h 20    | unit mm/s                                | Read / Write | M707 A0x14 | M708 A0x14 Xnnnn
| 0x15h 21 | uint16   | Selector_homing_feedrate   | 0000h 0      | 001eh 30    | unit mm/s                                | Read / Write | M707 A0x15 | (M708 A0x15 Xnnnn)
| 0x16h 22 | uint16   | Idler_homing_feedrate      | 0000h 0      | 0109h 265   | unit deg/s                               | Read / Write | M707 A0x16 | (M708 A0x16 Xnnnn)
| 0x17h 23 | uint8    | Pulley_sg_thrs__R          | 00h 0        | 08h 8       |                                          | Read / Write Persistent | M707 A0x17 | M708 A0x17 Xnn
| 0x18h 24 | uint8    | Selector_sg_thrs_R         | 00h 0        | 03h 3       |                                          | Read / Write Persistent | M707 A0x18 | M708 A0x18 Xnn
| 0x19h 25 | uint8    | Idler_sg_thrs_R            | 00h 0        | 06h 6       |                                          | Read / Write Persistent | M707 A0x19 | M708 A0x19 Xnn
| 0x1ah 26 | uint16   | Get Pulley position        | 0000h 0      | ffffh 65535 | unit mm                                  | Read only    | M707 A0x1a | N/A
| 0x1bh 27 | uint16   | Set/Get_Selector_slot      | 0000h 0      | ffffh 65535 | unit slot [0-4/5] 5=park pos             | Read / Write | M707 A0x1b | M708 A0x1b Xn
| 0x1ch 28 | uint16   | Set/Get_Idler_slot         | 0000h 0      | ffffh 65535 | unit slot [0-4/5] 5=disengaged           | Read / Write | M707 A0x1c | M708 A0x1c Xn
| 0x1dh 29 | uint8    | Set/Get Selector cut iRun current | 0 to 63 (aka 0-1024mA)| 31 (530mA) |                           | Read / Write | M707 A0x1d | M708 A0x1d Xn
| 0x1eh 30 | uint16   | Set/Get Pulley iRun current| 0-31         | 14h 20      | 20->350mA: see TMC2130 current conversion| Read / Write | M707 A0x1e | M708 A0x1e Xn
| 0x1fh 31 | uint16  |Set/Get Selector iRun current| 0-31         | 1fh 31      | 31->530mA: see TMC2130 current conversion| Read / Write | M707 A0x1f | M708 A0x1f Xn
| 0x20h 32 | uint16   | Set/Get Idler iRun current | 0-31         | 1fh 31      | 31->530mA: see TMC2130 current conversion| Read / Write | M707 A0x20 | M708 A0x20 Xn
| 0x21h 33 | uint16   | Current VCC voltage level  | 225-281 | | 225->5V, 281->4V, higher values mean lower voltage and the board would probably die sooner than reporting anything | Read only | M707 A0x21 | N/A
*/

struct RegisterFlags {
    uint8_t writable : 1;
    uint8_t rwfuncs : 1; // 1: register needs special read and write functions
    uint8_t size : 2; // 0: 1 bit, 1: 1 byte, 2: 2 bytes
    constexpr RegisterFlags(bool writable, uint8_t size)
        : writable(writable)
        , rwfuncs(0)
        , size(size) {}
    constexpr RegisterFlags(bool writable, bool rwfuncs, uint8_t size)
        : writable(writable)
        , rwfuncs(rwfuncs)
        , size(size) {}
};

using TReadFunc = uint16_t (*)();
using TWriteFunc = void (*)(uint16_t);

// dummy zero register common to all empty registers
static constexpr uint16_t dummyZero = 0;

struct RegisterRec {
    RegisterFlags flags;
    union U1 {
        void *addr;
        TReadFunc readFunc;
        constexpr explicit U1(const TReadFunc &r)
            : readFunc(r) {}
        constexpr explicit U1(void *a)
            : addr(a) {}
    } A1;

    union U2 {
        void *addr;
        TWriteFunc writeFunc;
        constexpr explicit U2(const TWriteFunc &w)
            : writeFunc(w) {}
        constexpr explicit U2(void *a)
            : addr(a) {}
    } A2;

    template <typename T>
    constexpr RegisterRec(bool writable, T *address)
        : flags(RegisterFlags(writable, sizeof(T)))
        , A1((void *)address)
        , A2((void *)nullptr) {}
    constexpr RegisterRec(const TReadFunc &readFunc, uint8_t bytes)
        : flags(RegisterFlags(false, true, bytes))
        , A1(readFunc)
        , A2((void *)nullptr) {}

    constexpr RegisterRec(const TReadFunc &readFunc, const TWriteFunc &writeFunc, uint8_t bytes)
        : flags(RegisterFlags(true, true, bytes))
        , A1(readFunc)
        , A2(writeFunc) {}

    constexpr RegisterRec()
        : flags(RegisterFlags(false, false, 1))
        , A1((void *)&dummyZero)
        , A2((void *)nullptr) {}
};

// @@TODO it is nice to see all the supported registers at one spot,
// however it requires including all bunch of dependencies
// which makes unit testing and separation of modules much harder.
// @@TODO clang complains that we are initializing this array with an uninitialized referenced variables (e.g. mg::globals)
// Imo that should be safe as long as we don't call anything from this array before the FW init is completed (which we don't).
// Otherwise all the addresses of global variables should be known at compile time and the registers array should be consistent.
//
// Note:
// The lambas seem to be pretty cheap:
//    void SetFSensorToNozzleFeedrate(uint8_t fs2NozzleFeedrate) { fsensorToNozzleFeedrate = fs2NozzleFeedrate; }
// compiles to:
// sts <modules::globals::globals+0x4>, r24
// ret
//
// @@TODO at the moment we are having problems compiling this array statically into PROGMEM.
// In this project that's really not an issue since we have half of the RAM empty:
// Data: 1531 bytes (59.8% Full)
// But it would be nice to fix that in the future - might be hard to push the compiler to such a construct
static const RegisterRec registers[] /*PROGMEM*/ = {
    // 0x00
    RegisterRec(false, &project_major),
    // 0x01
    RegisterRec(false, &project_minor),
    // 0x02
    RegisterRec(false, &project_revision),
    // 0x03
    RegisterRec(false, &project_build_number),
    // 0x04
    RegisterRec( // MMU errors
        []() -> uint16_t { return mg::globals.DriveErrors(); },
        // [](uint16_t) {}, // @@TODO think about setting/clearing the error counter from the outside
        2),
    // 0x05
    RegisterRec([]() -> uint16_t { return application.CurrentProgressCode(); }, 1),
    // 0x06
    RegisterRec([]() -> uint16_t { return application.CurrentErrorCode(); }, 2),
    // 0x07 filamentState
    RegisterRec(
        []() -> uint16_t { return mg::globals.FilamentLoaded(); },
        [](uint16_t v) { return mg::globals.SetFilamentLoaded(mg::globals.ActiveSlot(), static_cast<mg::FilamentLoadState>(v)); },
        1),
    // 0x08 FINDA
    RegisterRec(
        []() -> uint16_t { return static_cast<uint16_t>(mf::finda.Pressed()); },
        1),
    // 09 fsensor
    RegisterRec(
        []() -> uint16_t { return static_cast<uint16_t>(mfs::fsensor.Pressed()); },
        [](uint16_t v) { return mfs::fsensor.ProcessMessage(v != 0); },
        1),
    // 0xa motor mode (stealth = 1/normal = 0)
    RegisterRec([]() -> uint16_t { return static_cast<uint16_t>(mg::globals.MotorsStealth()); }, 1),
    // 0xb extra load distance after fsensor triggered (30mm default) [mm] RW
    RegisterRec(
        []() -> uint16_t { return mg::globals.FSensorToNozzle_mm().v; },
        [](uint16_t d) { mg::globals.SetFSensorToNozzle_mm(d); },
        1),
    // 0x0c fsensor unload check distance (40mm default) [mm] RW
    RegisterRec(
        []() -> uint16_t { return mg::globals.FSensorUnloadCheck_mm().v; },
        [](uint16_t d) { mg::globals.SetFSensorUnloadCheck_mm(d); },
        1),

    // 0xd 2 Pulley unload feedrate [mm/s] RW
    RegisterRec(
        []() -> uint16_t { return mg::globals.PulleyUnloadFeedrate_mm_s().v; },
        [](uint16_t d) { mg::globals.SetPulleyUnloadFeedrate_mm_s(d); },
        2),

    // 0xe Pulley acceleration [mm/s2] RW
    RegisterRec(
        []() -> uint16_t { return config::pulleyLimits.accel.v; },
        //@@TODO please update documentation as well
        2),
    // 0xf Selector acceleration [mm/s2] RW
    RegisterRec(
        []() -> uint16_t { return config::selectorLimits.accel.v; },
        //@@TODO please update documentation as well
        2),
    // 0x10 Idler acceleration [deg/s2] RW
    RegisterRec(
        []() -> uint16_t { return config::idlerLimits.accel.v; },
        //@@TODO please update documentation as well
        2),

    // 0x11 Pulley load feedrate [mm/s] RW
    RegisterRec(
        []() -> uint16_t { return mg::globals.PulleyLoadFeedrate_mm_s().v; },
        [](uint16_t d) { mg::globals.SetPulleyLoadFeedrate_mm_s(d); },
        2),
    // 0x12 Selector nominal feedrate [mm/s] RW
    RegisterRec(
        []() -> uint16_t { return mg::globals.SelectorFeedrate_mm_s().v; },
        [](uint16_t d) { mg::globals.SetSelectorFeedrate_mm_s(d); },
        2),
    // 0x13 Idler nominal feedrate [deg/s] RW
    RegisterRec(
        []() -> uint16_t { return mg::globals.IdlerFeedrate_deg_s().v; },
        [](uint16_t d) { mg::globals.SetIdlerFeedrate_deg_s(d); },
        2),

    // 0x14 Pulley slow load to fsensor feedrate [mm/s] RW
    RegisterRec(
        []() -> uint16_t { return mg::globals.PulleySlowFeedrate_mm_s().v; },
        [](uint16_t d) { mg::globals.SetPulleySlowFeedrate_mm_s(d); },
        2),
    // 0x15 Selector homing feedrate [mm/s] RW
    RegisterRec(
        []() -> uint16_t { return mg::globals.SelectorHomingFeedrate_mm_s().v; },
        [](uint16_t d) { mg::globals.SetSelectorHomingFeedrate_mm_s(d); },
        2),
    // 0x16 Idler homing feedrate [deg/s] RW
    RegisterRec(
        []() -> uint16_t { return mg::globals.IdlerHomingFeedrate_deg_s().v; },
        [](uint16_t d) { mg::globals.SetIdlerHomingFeedrate_deg_s(d); },
        2),

    // 0x17 Pulley sg_thrs threshold RW
    RegisterRec(
        []() -> uint16_t { return mg::globals.StallGuardThreshold(config::Pulley); },
        [](uint16_t d) { mg::globals.SetStallGuardThreshold(config::Pulley, d); },
        1),
    // 0x18 Selector sg_thrs RW
    RegisterRec(
        []() -> uint16_t { return mg::globals.StallGuardThreshold(mm::Axis::Selector); },
        [](uint16_t d) { mg::globals.SetStallGuardThreshold(mm::Axis::Selector, d); },
        1),
    // 0x19 Idler sg_thrs RW
    RegisterRec(
        []() -> uint16_t { return mg::globals.StallGuardThreshold(mm::Axis::Idler); },
        [](uint16_t d) { mg::globals.SetStallGuardThreshold(mm::Axis::Idler, d); },
        1),

    // 0x1a Get Pulley position [mm] R
    RegisterRec(
        []() -> uint16_t { return mpu::pulley.CurrentPosition_mm(); },
        2),
    // 0x1b Set/Get Selector slot RW
    RegisterRec(
        []() -> uint16_t { return ms::selector.Slot(); },
        [](uint16_t d) { ms::selector.MoveToSlot(d); },
        1),
    // 0x1c Set/Get Idler slot RW
    RegisterRec(
        []() -> uint16_t { return mi::idler.Slot(); },
        [](uint16_t d) { d >= config::toolCount ? mi::idler.Disengage() : mi::idler.Engage(d); },
        1),
    // 0x1d Set/Get Selector cut iRun current level RW
    RegisterRec(
        []() -> uint16_t { return mg::globals.CutIRunCurrent(); },
        [](uint16_t d) { mg::globals.SetCutIRunCurrent(d); },
        1),

    // 0x1e Get/Set Pulley iRun current RW
    RegisterRec(
        []() -> uint16_t { return mm::motion.CurrentsForAxis(config::Pulley).iRun; },
        [](uint16_t d) { mm::motion.SetIRunForAxis(config::Pulley, d); },
        1),
    // 0x1f Set/Get Selector iRun current RW
    RegisterRec(
        []() -> uint16_t { return mm::motion.CurrentsForAxis(config::Selector).iRun; },
        [](uint16_t d) { mm::motion.SetIRunForAxis(config::Selector, d); },
        1),
    // 0x20 Set/Get Idler iRun current RW
    RegisterRec(
        []() -> uint16_t { return mm::motion.CurrentsForAxis(config::Idler).iRun; },
        [](uint16_t d) { mm::motion.SetIRunForAxis(config::Idler, d); },
        1),
    // 0x21 Current VCC voltage level R
    RegisterRec(
        []() -> uint16_t { return mv::vcc.CurrentVCC(); },
        2),
};

static constexpr uint8_t registersSize = sizeof(registers) / sizeof(RegisterRec);

bool ReadRegister(uint8_t address, uint16_t &value) {
    if (address >= registersSize) {
        return false;
    }
    value = 0;
    if (!registers[address].flags.rwfuncs) {
        switch (registers[address].flags.size) {
        case 0:
        case 1:
            value = *static_cast<uint8_t *>(registers[address].A1.addr);
            break;
        case 2:
            value = *static_cast<uint16_t *>(registers[address].A1.addr);
            break;
        default:
            return false;
        }
        return true;
    } else {
        switch (registers[address].flags.size) {
        case 0:
        case 1:
        case 2:
            value = registers[address].A1.readFunc();
            break;
        default:
            return false;
        }
        return true;
    }
}

bool WriteRegister(uint8_t address, uint16_t value) {
    if (address >= registersSize) {
        return false;
    }
    if (!registers[address].flags.writable) {
        return false;
    }
    if (!registers[address].flags.rwfuncs) {
        switch (registers[address].flags.size) {
        case 0:
        case 1:
            *static_cast<uint8_t *>(registers[address].A1.addr) = value;
            break;
        case 2:
            *static_cast<uint16_t *>(registers[address].A1.addr) = value;
            break;
        default:
            return false;
        }
        return true;
    } else {
        switch (registers[address].flags.size) {
        case 0:
        case 1:
        case 2:
            registers[address].A2.writeFunc(value);
            break;
        default:
            return false;
        }
        return true;
    }
}
