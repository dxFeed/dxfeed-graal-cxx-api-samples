#include <plugin-api.h>

#include <dxfeed_graal_cpp_api/api.hpp>

#include <memory>

using namespace dxfcpp;

struct Plugin {
    std::shared_ptr<DXEndpoint> endpoint = DXEndpoint::create();
    std::shared_ptr<DXFeedSubscription> subscription = endpoint->getFeed()->createSubscription(
            {Quote::TYPE, Trade::TYPE});
};

Plugin plugin{};

extern "C" {

DLLSAMPLE_API void dsp_init() {

}

DLLSAMPLE_API void dsp_connect(const char *address) {
    plugin.endpoint->connect(address);
}

DLLSAMPLE_API void dsp_subscribe(const char *symbol, dsp_events_listener events_listener, void *user_data) {
    plugin.subscription->addEventListener([user_data, events_listener](const auto &events) {
        auto size = events.size();

        if (size == 0) {
            return;
        }

        auto *eventsToListener = new dsp_event_t *[size];

        std::size_t index = 0;

        for (const auto &e: events) {
            if (const auto &q = e->template sharedAs<Quote>(); q) {
                eventsToListener[index++] = dxfcpp::bit_cast<dsp_event_t *>(
                        new dsp_quote_t{{DSP_ET_QUOTE}, q->getBidPrice(), q->getBidSize(), q->getAskPrice(),
                                        q->getAskSize()});
            } else if (const auto &tr = e->template sharedAs<Trade>(); tr) {
                eventsToListener[index++] = dxfcpp::bit_cast<dsp_event_t *>(
                        new dsp_trade_t{{DSP_ET_TRADE}, tr->getPrice(), tr->getSize()});
            }
        };

        events_listener(eventsToListener, index, user_data);

        for (std::size_t i = 0; i < index; i++) {
            if (eventsToListener[i]->type == DSP_ET_QUOTE) {
                delete dxfcpp::bit_cast<dsp_quote_t *>(eventsToListener[i]);
            } else if (eventsToListener[i]->type == DSP_ET_TRADE) {
                delete dxfcpp::bit_cast<dsp_trade_t *>(eventsToListener[i]);
            }
        }

        delete[] eventsToListener;
    });

    plugin.subscription->addSymbols(symbol);
}

DLLSAMPLE_API void dsp_deinit() {

}

}