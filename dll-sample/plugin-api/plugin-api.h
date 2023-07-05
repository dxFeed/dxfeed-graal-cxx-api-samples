#pragma once

#	ifdef DLLSAMPLE_EXPORTS
#		define DLLSAMPLE_API __declspec(dllexport)
#	elif DLLSAMPLE_IMPORTS
#		define DLLSAMPLE_API __declspec(dllimport)
#	elif __cplusplus
#		define DLLSAMPLE_API extern "C"
#	else
#		define DLLSAMPLE_API
#	endif

#ifdef __cplusplus
#    include <cstddef>
#    include <cstdint>

extern "C" {
#else

#    include <stddef.h>
#    include <stdint.h>

#endif

typedef enum dsp_event_type_t {
    DSP_ET_QUOTE,
    DSP_ET_TRADE,
} dsp_event_type_t;

#pragma pack(push, 1)

typedef struct dsp_event_t {
    dsp_event_type_t type;
} dsp_event_t;

typedef struct dsp_quote_t {
    dsp_event_t event;

    double bid_price;
    double bid_size;
    double ask_price;
    double ask_size;
} dsp_quote_t;

typedef struct dsp_trade_t {
    dsp_event_t event;

    double price;
    double size;
} dsp_trade_t;

#pragma pack(pop)

typedef void (*dsp_events_listener)(dsp_event_t **events, size_t size, void *user_data);

typedef void (*dsp_init_t)();

DLLSAMPLE_API void dsp_init();

typedef void (*dsp_connect_t)(const char *);

DLLSAMPLE_API void dsp_connect(const char *address);

typedef void (*dsp_subscribe_t)(const char *, dsp_events_listener, void *);

DLLSAMPLE_API void dsp_subscribe(const char *symbol, dsp_events_listener events_listener, void *user_data);

typedef void (*dsp_deinit_t)();

DLLSAMPLE_API void dsp_deinit();

#ifdef __cplusplus
}
#endif