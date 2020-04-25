#include <PiDxe.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/RealTimeClockLib.h>
#include <Library/TimerLib.h>
#include <Library/TimeBaseLib.h>
#include <Library/UefiRuntimeLib.h>
#include <Library/ArmGenericTimerCounterLib.h>

EFI_STATUS
EFIAPI
LibGetTime (
    OUT EFI_TIME                *Time,
    OUT  EFI_TIME_CAPABILITIES  *Capabilities
) {
    UINTN DataSize;
    UINT64 Counter;
    EFI_STATUS Status;
    UINTN ElapsedSeconds;
    UINT32 Remainder;
    UINT32 Freq = ArmGenericTimerGetTimerFreq();
    if (Time == NULL)
        return EFI_INVALID_PARAMETER;
    ASSERT (Freq != 0);
    if (Freq == 0)
        return EFI_DEVICE_ERROR;
    if (Capabilities) {
        Capabilities->Accuracy = 0;
        Capabilities->Resolution = Freq;
        Capabilities->SetsToZero = FALSE;
    }
    DataSize = sizeof (UINTN);
    ElapsedSeconds = 0;
    Status = EfiGetVariable (L"RtcEpochSeconds",
                             &gEfiCallerIdGuid,
                             NULL,
                             &DataSize,
                             &ElapsedSeconds);
    if (EFI_ERROR (Status))
        ElapsedSeconds = PcdGet64(PcdRTCInf);
    Counter = GetPerformanceCounter ();
    ElapsedSeconds += DivU64x32Remainder (Counter, Freq, &Remainder);
    EpochToEfiTime (ElapsedSeconds, Time);
    //
    // Frequency < 0x100000000, so Remainder < 0x100000000, then (Remainder * 1,000,000,000)
    // will not overflow 64-bit.
    //
    Time->Nanosecond = DivU64x32 (MultU64x64 ((UINT64) Remainder,
                                  1000000000U), Freq);
    return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
LibSetTime (
    IN EFI_TIME *Time
) {
    UINTN Epoch;
    if (!IsTimeValid(Time))
        return EFI_INVALID_PARAMETER;
    Epoch = EfiTimeToEpoch(Time);
    return EfiSetVariable(L"RtcEpochSeconds", &gEfiCallerIdGuid,
                          EFI_VARIABLE_BOOTSERVICE_ACCESS |
                          EFI_VARIABLE_RUNTIME_ACCESS |
                          EFI_VARIABLE_NON_VOLATILE,
                          sizeof (Epoch),
                          &Epoch);
}

EFI_STATUS
EFIAPI
LibGetWakeupTime (
    OUT BOOLEAN     *Enabled,
    OUT BOOLEAN     *Pending,
    OUT EFI_TIME    *Time
) {
    return EFI_UNSUPPORTED;
}

EFI_STATUS
EFIAPI
LibSetWakeupTime (
    IN BOOLEAN      Enabled,
    OUT EFI_TIME    *Time
) {
    return EFI_UNSUPPORTED;
}

EFI_STATUS
EFIAPI
LibRtcInitialize (
    IN EFI_HANDLE                            ImageHandle,
    IN EFI_SYSTEM_TABLE                      *SystemTable
) {
    return EFI_SUCCESS;
}

VOID
EFIAPI
LibRtcVirtualNotifyEvent (
    IN EFI_EVENT        Event,
    IN VOID             *Context
) {
    return;
}
