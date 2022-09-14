
### SHA2 implementation testing and benchmarking ###

This is a collection of different SHA2 implementations.


### LICENSE ###

Please note, that each implementation has it's own LICENSE.


### TODO ###

- this is just some start
- in the end I would like to have some nice written and fast public domain code - I hope ;)


### Benchmarks ###

```
Linux 5.10.0-13-amd64 #1 SMP Debian 5.10.106-1 (2022-03-17) x86_64 GNU/Linux
Architecture: x86_64 - AMD Ryzen 7 5800X 8-Core Processor
CC=gcc CFLAGS=-Os
implementation               1k      4k     16k     64k    256k      1m      4m
sha256-cifra                297     300     301     300     300     299     300
sha256-sbase                311     314     315     313     314     314     315
sha256-tomcrypt             301     300     255     300     187     192     174
sha256-lzma                 243     233     408     412     408     413     411
sha256-bsd                  391     395     395     393     395     395     395
sha256-cppcrypto            456     458     461     458     459     460     459
sha256-intel-ssse3          495     500     497     500     499     497     497
sha256-intel-avx            303     304     305     305     305     305     303
sha256-intel-ni            2264    2276    2278    2286    2272    2282    2282
sha256-ossl-ssse3           627     631     629     628     629     630     628
sha256-ossl-avx             324     325     326     325     326     326     326
sha256-ossl-avx2            683     688     690     688     686     687     686
sha256-ossl-ni             2270    2282    2285    2280    2280    2287    2281
sha256-openssl             2270    2282    2285    2280    2279    2283    2281

sha512_256-sbase            493     496     494     492     492     491     491
sha512_256-bsd              596     600     599     600     603     597     599
sha512_256-cppcrypto        726     725     730     728     729     730     729
sha512_256-ossl-avx2       1072    1078    1084    1080    1084    1082    1083

sha512-cifra                472     476     469     468     473     472     471
sha512-sbase                489     488     491     490     491     490     492
sha512-bsd                  591     600     596     601     605     601     602
sha512-cppcrypto            722     729     729     728     730     729     731
sha512-intel-ssse3          679     679     681     678     678     679     678
sha512-intel-avx            493     492     494     494     495     494     494
sha512-intel-avx2           956     967     969     960     965     965     965
sha512-ossl-avx             492     496     498     498     498     498     498
sha512-ossl-avx2           1075    1079    1070    1081    1083    1080    1081
sha512-openssl             1073    1073    1081    1081    1082    1078    1081
```

```
FreeBSD freebsd 13.1-RELEASE releng/13.1-n250148-fc952ac2212
Architecture: x86_64 - AMD Ryzen 7 5800X 8-Core Processor
CC=clang CFLAGS=-Os
implementation               1k      4k     16k     64k    256k      1m      4m
sha256-cifra                314     314     313     314     313     312     312
sha256-sbase                304     306     306     305     298     306     306
sha256-tomcrypt             303     305     307     308     308     308     308
sha256-lzma                 392     392     393     392     392     393     393
sha256-bsd                  410     413     412     413     413     412     412
sha256-cppcrypto            430     430     429     429     425     415     415
sha256-intel-ssse3          494     498     497     498     499     499     498
sha256-intel-avx            301     302     303     305     304     305     304
sha256-intel-ni            2248    2263    2285    2285    2283    2283    2283
sha256-ossl-ssse3           625     623     621     622     623     621     625
sha256-ossl-avx             323     323     323     324     322     325     324
sha256-ossl-avx2            680     682     682     681     683     679     680
sha256-ossl-ni             2214    2257    2263    2264    2273    2277    2280
sha256-openssl             2269    2280    2283    2287    2288    2283    2284

sha512_256-sbase            485     483     485     486     485     485     485
sha512_256-bsd              642     640     642     643     643     643     641
sha512_256-cppcrypto        646     649     655     660     659     650     650
sha512_256-ossl-avx2       1072    1074    1081    1079    1080    1070    1078

sha512-cifra                472     472     473     474     474     473     472
sha512-sbase                482     485     484     484     486     485     484
sha512-bsd                  639     635     643     640     643     641     642
sha512-cppcrypto            649     644     647     651     650     649     651
sha512-intel-ssse3          674     672     672     673     673     674     673
sha512-intel-avx            490     489     489     492     490     491     491
sha512-intel-avx2           955     961     966     965     964     958     963
sha512-ossl-avx             490     491     493     492     496     493     494
sha512-ossl-avx2           1073    1075    1079    1077    1075    1079    1074
sha512-openssl             1060    1075    1078    1077    1079    1074    1077
```

```
Linux 5.10.0-13-amd64 #1 SMP Debian 5.10.106-1 (2022-03-17) x86_64 GNU/Linux
Architecture: x86_64 - Intel(R) Core(TM) i3-1005G1 CPU @ 1.20GHz
CC=gcc CFLAGS=-Os
implementation               1k      4k     16k     64k    256k      1m      4m
sha256-cifra                215     214     217     219     219     219     218
sha256-sbase                217     218     217     217     218     218     219
sha256-tomcrypt             223     226     226     226     226     226     226
sha256-lzma                 280     282     283     245     276     278     283
sha256-bsd                  279     283     283     285     285     282     285
sha256-cppcrypto            279     288     291     287     287     286     291
sha256-intel-ssse3          305     308     308     308     308     308     308
sha256-intel-avx            306     308     307     309     310     309     309
sha256-intel-ni            1190    1224    1232    1235    1237    1230    1224
sha256-ossl-ssse3           351     356     356     356     357     357     357
sha256-ossl-avx             358     360     363     362     363     363     362
sha256-ossl-avx2            390     395     394     395     395     395     396
sha256-ossl-ni          ** 1193    1226    1232    1235    1237    1238    1234
sha256-openssl             1223    1162    1231    1108    1040    1208    1236

sha512_256-sbase            324     349     350     347     350     350     350
sha512_256-bsd              406     412     414     413     412     414     414
sha512_256-cppcrypto        440     451     456     457     457     453     456
sha512_256-ossl-avx2        598     607     610     610     610     611     611

sha512-cifra                337     339     340     341     341     340     341
sha512-sbase                342     350     350     350     350     350     350
sha512-bsd                  405     412     413     413     414     414     413
sha512-cppcrypto            430     448     450     456     457     459     460
sha512-intel-ssse3          472     481     482     482     483     483     483
sha512-intel-avx            477     485     487     484     488     487     487
sha512-intel-avx2           535     545     548     548     547     548     548
sha512-ossl-avx             549     559     561     562     562     562     562
sha512-ossl-avx2         ** 598     605     611     609     611     611     610
sha512-openssl              600     606     608     610     610     610     611
```

```
Linux 5.10.0-13-amd64 #1 SMP Debian 5.10.106-1 (2022-03-17) x86_64 GNU/Linux
Architecture: x86_64 - Intel(R) Core(TM) i7-3632QM CPU @ 2.20GHz
CC=gcc CFLAGS=-Os
implementation               1k      4k     16k     64k    256k      1m      4m
sha256-cifra                 92     100     102     126     135     138     135
sha256-sbase                140     142     147     139     149     148     146
sha256-tomcrypt             142     136     144     144     142     140     139
sha256-lzma                 179     185     187     186     128     145     180
sha256-bsd                  187     193     191     177     187     191     189
sha256-cppcrypto            182     176     172     192     185     191     190
sha256-intel-ssse3          255     264     248     261     258     252     254
sha256-intel-avx            244     262     250     260     264     253     251
sha256-ossl-ssse3           281     291     289     268     290     286     288
sha256-ossl-avx          ** 268     279     294     294     285     283     286
sha256-openssl              289     285     300     285     294     296     294

sha512_256-sbase            208     227     228     229     216     227     218
sha512_256-bsd              273     296     274     300     301     299     299
sha512_256-cppcrypto        279     283     310     303     312     298     310

sha512-cifra                198     205     209     201     212     205     210
sha512-sbase                208     224     231     224     227     221     218
sha512-bsd                  271     292     293     302     278     291     290
sha512-cppcrypto            278     286     297     302     308     292     299
sha512-intel-ssse3          367     326     354     370     363     379     364
sha512-intel-avx            353     389     373     380     379     372     384
sha512-ossl-avx          ** 404     415     419     425     381     406     418
sha512-openssl              411     416     398     423     402     421     402
```

```
Linux 5.19.0-asahi-00002-g5528b48e9700 #1 SMP Fri Sep 2 10:36:11 CEST 2022 aarch64 GNU/Linux
Architecture: aarch64 - Apple M1 Little Endian
Flags:        fp asimd aes sha1 sha2 crc32 cpuid sha3 sha512 ...
CC=gcc CFLAGS=-Os
implementation               1k      4k     16k     64k    256k      1m      4m
sha256-cifra                 69      74      89     126     187     233     255
sha256-sbase                160     160     159     159     158     158     159
sha256-tomcrypt             160     160     159     159     158     158     159
sha256-lzma                 276     276     275     275     275     275     275
sha256-bsd                  297     296     296     296     295     296     296
sha256-cppcrypto            287     287     287     287     287     287     287
sha256-ossl-armv7           349     349     349     349     349     349     349
sha256-ossl-neon            356     357     357     357     357     357     357
sha256-ossl-armv8          2179    2188    2195    2196    2196    2196    2196
sha256-noloader-armv8      1927    1935    1937    1939    1940    1939    1939
sha256-openssl             2181    2192    2195    2196    2195    2196    2196

sha512_256-sbase            273     274     266     265     265     267     270
sha512_256-bsd              475     475     474     475     475     475     476
sha512_256-cppcrypto        459     460     460     460     460     460     460

sha512-cifra                446     446     444     442     441     441     444
sha512-sbase                273     274     265     264     265     266     269
sha512-bsd                  475     476     476     475     475     475     475
sha512-cppcrypto            459     460     456     460     460     459     460
sha512-ossl-armv7           555     556     555     555     555     555     555
sha512-ossl-armv8          1279    1284    1285    1285    1285    1286    1285
sha512-openssl             1280    1284    1286    1286    1285    1285    1285
```

```
Linux 4.18.0-80.7.2.el7.ppc64le #1 SMP ppc64le GNU/Linux
Architecture: ppc64 - POWER9 2.2 (pvr 004e 1202) - Little Endian

implementation               1k      4k     16k     64k    256k      1m      4m
sha256-cifra                161     160     162     159     162     162     162
sha256-sbase                126     127     126     126     126     126     127
sha256-tomcrypt             123     124     123     124     123     124     123
sha256-lzma                 164     168     169     167     168     168     168
sha256-bsd                  196     206     210     210     211     211     211
sha256-cppcrypto            183     184     181     179     184     184     184
sha256-ossl-ppc64           291     293     295     291     294     292     294
sha256-ossl-ppc64p8      ** 321     325     321     325     324     326     324
sha256-noloader-ppc64       244     247     247     248     249     247     248
sha256-openssl              290     292     289     293     292     293     294

sha512_256-sbase            208     210     210     210     210     209     209
sha512_256-bsd              317     321     322     319     320     320     322
sha512_256-cppcrypto        323     323     329     329     327     328     328

sha512-cifra                272     271     277     274     276     276     277
sha512-sbase                208     210     210     210     210     208     210
sha512-bsd                  317     321     322     320     321     323     323
sha512-cppcrypto            325     329     330     328     329     329     328
sha512-ossl-ppc64           457     465     460     467     467     468     466
sha512-ossl-ppc64p8      ** 501     518     521     522     517     523     521
sha512-noloader-ppc64       391     395     400     398     399     402     398
sha512-openssl              459     465     467     468     468     469     466
```

```
Linux 5.15.0-2-powerpc64 #1 SMP Debian 5.15.5-2 (2021-12-18) ppc64 GNU/Linux
Architecture: ppc64 - POWER8 (2.1 pvr 004b 0201) - Big Endian
CC=gcc CFLAGS=-Os
implementation               1k      4k     16k     64k    256k      1m      4m
sha256-cifra                105     138     140     140     140     141     140
sha256-sbase                111     112     112     112     112     112     112
sha256-tomcrypt             111     111     111     112     112     112     112
sha256-lzma                 180     180     180     180     180     180     180
sha256-bsd                  187     188     189     189     189     189     189
sha256-cppcrypto            183     184     187     184     186     186     184
sha256-ossl-ppc64           222     224     225     226     226     225     226
sha256-ossl-ppc64p8      ** 358     363     363     364     365     365     365
sha256-noloader-ppc64       293     296     297     297     297     297     297
sha256-openssl              359     363     364     364     364     365     363

sha512_256-sbase            170     171     171     171     171     172     171
sha512_256-bsd              284     287     289     283     289     288     288
sha512_256-cppcrypto        291     294     295     295     295     295     295

sha512-cifra                222     223     223     225     224     224     224
sha512-sbase                170     171     171     171     172     171     171
sha512-bsd                  284     287     288     289     289     288     289
sha512-cppcrypto            290     295     295     295     295     295     295
sha512-ossl-ppc64           350     352     356     357     357     357     356
sha512-ossl-ppc64p8      ** 567     579     581     583     583     582     583
sha512-noloader-ppc64       466     476     478     478     477     478     478
sha512-openssl              570     580     582     583     583     583     583
```

```
Linux 3.10.0-862.14.4.el7.ppc64 #1 SMP Wed Sep 26 20:38:32 GMT 2018 GNU/Linux
Architecture: ppc64 - POWER7 (2.1 pvr 003f 0201) - Big Endian
CC=gcc CFLAGS=-Os
implementation               1k      4k     16k     64k    256k      1m      4m
sha256-cifra                106     106      78      78     141     142     142
sha256-sbase                120     121     120     120     120     121     120
sha256-tomcrypt             107     108     108     108     108     108     108
sha256-lzma                 132     133     133     133     133     133     133
sha256-bsd                  182     184     183     184     183     184     184
sha256-cppcrypto            153     153     154     154      92     131     155
sha256-ossl-ppc64        ** 193     195     195     222     255     255     255
sha256-openssl              253     254     255     255     255     228     255

sha512_256-sbase            185     184     186     186     186     187     187
sha512_256-bsd              302     304     305     306     305     305     305
sha512_256-cppcrypto        274     277     277     277     277     276     276

sha512-cifra                229     230     125     228     228     230     230
sha512-sbase                186     186     185     187     186     187     186
sha512-bsd                  289     300     305     305     305     305     306
sha512-cppcrypto            274     277     277     277     278     276     276
sha512-ossl-ppc64        ** 400     405     406     406     407     406     406
sha512-openssl              391     405     406     406     405     406     406
```

```
Linux 4.18.0-348.2.1.el8_5.aarch64 #1 SMP Tue Nov 16 14:41:36 UTC 2021 aarch64 GNU/Linux
Architecture: aarch64 - X-Gene Little Endian (3300 MHz)
Flags:        fp asimd evtstrm aes pmull sha1 sha2 crc32 cpuid
CC=gcc CFLAGS=-Os
implementation               1k      4k     16k     64k    256k      1m      4m
sha256-cifra                100     100     100     100     100     100     100
sha256-sbase                107     108     108     108     108     108     108
sha256-tomcrypt             111     111     111     111     111     111     111
sha256-lzma                 136     136     136     136     136     136     136
sha256-bsd                  157     157     157     157     157     157     157
sha256-cppcrypto            150     151     151     151     151     151     151
sha256-ossl-armv7           168     168     169     169     169     169     169
sha256-ossl-neon            209     211     211     211     211     211     211
sha256-ossl-armv8           670     674     677     677     678     678     678
sha256-noloader-armv8       661     672     674     675     675     675     675
sha256-openssl              671     676     677     677     677     676     678

sha512_256-sbase            161     162     162     162     162     162     162
sha512_256-bsd              246     248     248     248     248     248     248
sha512_256-cppcrypto        238     240     240     240     240     240     240

sha512-cifra                156     156     156     157     157     156     156
sha512-sbase                162     161     162     162     162     162     162
sha512-bsd                  246     248     248     248     248     248     248
sha512-cppcrypto            238     240     240     240     240     240     240
sha512-ossl-armv7           265     266     267     267     267     267     267
sha512-openssl              265     266     266     266     266     266     266
```

```
Linux 3.13.0-170-generic #220-Ubuntu SMP Thu May 9 12:45:18 UTC 2019 aarch64 GNU/Linux
Architecture: aarch64 Little Endian (Raspberry Pi 400)
Features:     fp asimd evtstrm
CC=gcc CFLAGS=-Os
implementation               1k      4k     16k     64k    256k      1m      4m
sha256-cifra                 27      58      63      75      82      82      82
sha256-sbase                 82      82      82      82      82      82      82
sha256-tomcrypt              80      81      81      81      81      81      81
sha256-lzma                 110     110     110     110     110     110     110
sha256-bsd                  121     122     122     122     122     122     122
sha256-cppcrypto            123     124     124     124     124     124     127
sha256-openssl              162     164     163     163     164     165     164

sha512_256-sbase            126     127     127     127     127     127     127
sha512_256-bsd              192     192     193     193     193     193     193
sha512_256-cppcrypto        200     202     202     203     202     203     203

sha512-cifra                128     129     129     129     129     129     129
sha512-sbase                126     127     127     127     127     127     127
sha512-bsd                  192     193     193     193     193     193     193
sha512-cppcrypto            200     202     202     202     203     202     206
sha512-openssl              235     237     237     238     238     238     238
```

```
Linux 5.10.63-v7l+ #1496 SMP Wed Dec 1 15:58:56 GMT 2021 armv7l GNU/Linux
Architecture: armv7l - Cortex-A72 Little Endian (Raspberry Pi 400)
Flags:        half thumb fastmult vfp edsp neon vfpv3 tls vfpv4 ... crc32
CC=gcc CFLAGS=-Os
implementation               1k      4k     16k     64k    256k      1m      4m
sha256-cifra                 73      73      73      73      73      73      73
sha256-sbase                 78      77      78      78      78      78      78
sha256-tomcrypt              75      75      76      75      76      76      76
sha256-lzma                  91      91      91      91      91      91      90
sha256-bsd                  104     105     105     106     106     106     106
sha256-cppcrypto             97      99      99      99      98      99      99
sha256-openssl              145     145     145     145     145     145     145

sha512_256-sbase             47      48      48      48      48      48      48
sha512_256-bsd               47      47      47      47      47      47      47
sha512_256-cppcrypto         49      50      50      50      50      50      50

sha512-cifra                 41      41      41      41      41      41      41
sha512-sbase                 47      47      47      48      48      48      48
sha512-bsd                   47      47      47      47      47      47      47
sha512-cppcrypto             50      50      50      50      50      50      50
sha512-openssl               49      49      49      49      49      49      49
```

```
SunOS gcc-solaris11 5.11 11.3 sun4u sparc SUNW,SPARC-Enterprise
Architecture: sparcv9 - SPARC64-VII (portid 1024 impl 0x7 ver 0x91 2520 MHz)
CC=gcc CFLAGS=-Os
implementation               1k      4k     16k     64k    256k      1m      4m
sha256-cifra                 39      39      39      39      39      39      39
sha256-sbase                 48      48      48      48      48      48      48
sha256-tomcrypt              47      47      47      47      47      47      47
sha256-lzma                  55      56      56      56      56      55      55
sha256-bsd                   60      60      60      60      60      59      57
sha256-cppcrypto             59      59      59      59      58      58      58
sha256-openssl               59      59      59      59      59      58      56

sha512_256-sbase             21      21      21      21      21      21      21
sha512_256-bsd               19      18      19      19      19      19      19
sha512_256-cppcrypto         18      18      18      18      18      17      18

sha512-cifra                 18      18      18      18      18      18      18
sha512-sbase                 21      21      21      21      21      21      21
sha512-bsd                   19      19      18      19      19      19      19
sha512-cppcrypto             18      18      18      18      18      18      18
sha512-openssl               86      86      86      86      86      86      86
```
