#pragma once
#include <wingdi.h>
#include <WinUser.h>
class DisplayOrientation
{
public:
    static DWORD GetOrientation() {
        DEVMODE dm;
        memset(&dm, 0, sizeof(DEVMODE));
        dm.dmSize = sizeof(DEVMODE);
        EnumDisplaySettingsEx(NULL,
            ENUM_CURRENT_SETTINGS, &dm, 0);
        return dm.dmDisplayOrientation;
    };
};