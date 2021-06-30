//-----------------------------------------------------------------------------
// Maxime Bosca and EATM-CERT @EUROCONTROL, 2021
//
// This code is licensed to you under the terms of the GNU GPL, version 2 or,
// at your option, any later version. See the LICENSE.txt file for the text of
// the license.
//-----------------------------------------------------------------------------
// main code for general card data collection by MaximeBosca
//-----------------------------------------------------------------------------
#include "standalone.h" // standalone definitions
#include "proxmark3_arm.h"
#include "appmain.h"
#include "fpgaloader.h"
#include "util.h"
#include "dbprint.h"

void ModInfo(void) {
    DbpString("Card Data collection mode a.k.a collection");
}

void RunMod(void) {
    StandAloneMode();
    Dbprintf("[=] Card Data Collection code a.k.a collection started");
    FpgaDownloadAndGo(FPGA_BITSTREAM_LF);

    // the main loop for your standalone mode
    for (;;) {
        WDT_HIT();

        // exit from RunMod,   send a usbcommand.
        if (data_available()) break;

        // Was our button held down or pressed?
        int button_pressed = BUTTON_HELD(1000);

        Dbprintf("button %d", button_pressed);

        if (button_pressed != BUTTON_NO_CLICK)
            break;
    }

    DbpString("[=] exiting");
    LEDsoff();
}
