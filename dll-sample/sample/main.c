// Copyright (c) 2023 Devexperts LLC.
// SPDX-License-Identifier: MPL-2.0

#include <plugin-api.h>

#define UNICODE
#define WIN32_LEAN_AND_MEAN

#include "Windows.h"
#include <stdio.h>

void listener(dsp_event_t **events, size_t size, void *user_data) {
    if (size == 0 || events == NULL) {
        return;
    }

    for (size_t i = 0; i < size; i++) {
        if (events[i]->type == DSP_ET_QUOTE) {
            dsp_quote_t *q = (dsp_quote_t *) (events[i]);

            printf("Quote{bid_price = %.15g, bid_size = %.15g, ask_price = %.15g, ask_size = %.15g}\n", q->bid_price,
                   q->bid_size, q->ask_price, q->ask_size);
        } else if (events[i]->type == DSP_ET_TRADE) {
            dsp_trade_t *tr = (dsp_trade_t *) (events[i]);

            printf("Trade{price = %.15g, size = %.15g}\n", tr->price, tr->size);
        }
    }
}

int main() {
    HMODULE handle = LoadLibrary(L"dllsample-dxfeed-plugin.dll");

    if (handle == NULL) {
        return 1;
    }

    dsp_init_t dsp_init = (dsp_init_t) (GetProcAddress(handle, "dsp_init"));
    dsp_connect_t dsp_connect = (dsp_connect_t) (GetProcAddress(handle, "dsp_connect"));
    dsp_subscribe_t dsp_subscribe = (dsp_subscribe_t) (GetProcAddress(handle, "dsp_subscribe"));
    dsp_deinit_t dsp_deinit = (dsp_deinit_t) (GetProcAddress(handle, "dsp_deinit"));

    if (dsp_init == NULL || dsp_connect == NULL || dsp_subscribe == NULL || dsp_deinit == NULL) {
        return 2;
    }

    dsp_connect("demo.dxfeed.com:7300");
    dsp_subscribe("AAPL", listener, NULL);

    Sleep(10000);

    FreeLibrary(handle);

    return 0;

}
