# dxFeed Graal CXX API Samples

## Import options

* [cmake-sub-project-sample](cmake-sub-project-sample/README.md) - demonstrates how to
  add [dxfeed-graal-cxx-api](https://github.com/dxFeed/dxfeed-graal-cxx-api) as a **CMake** subproject.
* [vs-project-sample](vs-project-sample/README.md) - demonstrates how to
  add [dxfeed-graal-cxx-api](https://github.com/dxFeed/dxfeed-graal-cxx-api) to **Visual Studio** solution.
* [dll-sample](dll-sample/README.md) - demonstrates how to add [dxfeed-graal-cxx-api](https://github.com/dxFeed/dxfeed-graal-cxx-api) to DLL plugin.


## Usage

You can download ready-to-run samples from
the [Release](https://github.com/dxFeed/dxfeed-graal-cxx-api-samples/releases) section with executable files.

Run sample from the build folder.

Expected result:

```
...\out\build\x64-Release>dxFeedGraalCxxApiSampleVS.exe AAPL
I 230607 134153.435 [main] QD - DXEndpoint is loading properties from dxfeed.properties
I 230607 134153.435 [main] QD - Using QDS-3.316+file-UNKNOWN+mars-UNKNOWN+monitoring-UNKNOWN+tools-UNKNOWN, (C) Devexperts
I 230607 134153.442 [main] QD - Using scheme com.dxfeed.api.impl.DXFeedScheme Ao7i0mLrB7RbnGZ43PGWcWWLGeKJ79lOVlbtAxAaXTI
I 230607 134153.580 [main] QD - qd with collectors [Ticker, Stream, History]
I 230607 134153.581 [main] QD - qd DXEndpoint with dxfeed.address=demo.dxfeed.com:7300
I 230607 134153.582 [main] QD - qd DXEndpoint with dxfeed.properties=dxfeed.properties
I 230607 134153.584 [main] ClientSocket-Distributor - Starting ClientSocketConnector to demo.dxfeed.com:7300
I 230607 134153.584 [demo.dxfeed.com:7300-Reader] ClientSocketConnector - Resolving IPs for demo.dxfeed.com
I 230607 134153.590 [demo.dxfeed.com:7300-Reader] ClientSocketConnector - Connecting to 208.93.103.170:7300
I 230607 134153.725 [demo.dxfeed.com:7300-Reader] ClientSocketConnector - Connected to 208.93.103.170:7300
D 230607 134153.861 [demo.dxfeed.com:7300-Reader] QD - Distributor received protocol descriptor multiplexor@CDSti [type=qtp, version=QDS-3.306, opt=hs, mars.root=mdd.demo-amazon.multiplexor-demo1] sending [TICKER, STREAM, HISTORY, DATA] from 208.93.103.170
Q: Quote{AAPL, eventTime=700101-030000.000+0300, time=230607-132647.000+0300, timeNanoPart=0, sequence=0, bidTime=230607-132645+0300, bidExchange=K, bidPrice=179.17, bidSize=15, askTime=230607-132647+0300, askExchange=Q, askPrice=179.2, askSize=3}
T: Trade{AAPL, eventTime=700101-030000.000+0300, time=230606-230000.348+0300, timeNanoPart=0, sequence=1824, exchange=Q, price=179.21, change=0, size=3952086, day=20230607, dayVolume=38259, dayTurnover=6844505.81, direction=ZERO_UP, ETH=true}
Mid = 179.185000
```
