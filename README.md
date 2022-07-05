
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
sha256-cifra                305     307     309     306     307     306     305
sha256-sbase                318     326     326     327     328     327     327
sha256-tomcrypt             304     303     304     304     302     304     304
sha256-lzma                 410     412     403     396     411     396     403
sha256-bsd                  394     397     397     397     394     398     399
sha256-cppcrypto            455     457     458     457     458     459     454
sha256-cppcrypto-shani     2247    2279    2283    2278    2285    2281    2281
sha256-cppcrypto-ssse3      497     499     498     499     499     499     499
sha256-cppcrypto-avx        302     303     303     303     304     304     303
sha256-cppcrypto-ni        2263    2280    2284    2275    2278    2285    2280
sha256-openssl             2262    2280    2283    2267    2278    2285    2280

sha512_256-sbase            489     497     494     493     492     490     493
sha512_256-bsd              595     602     602     598     603     600     603
sha512_256-cppcrypto        726     725     721     727     737     731     729

sha512-cifra                469     475     475     473     475     474     475
sha512-sbase                492     488     489     489     491     492     488
sha512-bsd                  590     600     603     596     601     599     600
sha512-cppcrypto            720     722     728     723     726     726     728
sha512-cppcrypto-ssse3      668     675     675     675     675     674     675
sha512-cppcrypto-avx2       955     961     963     957     961     964     962
sha512-cppcrypto-avx        472     492     493     494     492     492     492
sha512-openssl             1082    1080    1078    1075    1082    1079    1077
```

```
Linux 5.10.0-13-amd64 #1 SMP Debian 5.10.106-1 (2022-03-17) x86_64 GNU/Linux
Architecture: x86_64 - Intel(R) Core(TM) i3-1005G1 CPU @ 1.20GHz
CC=gcc CFLAGS=-Os
implementation               1k      4k     16k     64k    256k      1m      4m
sha256-cifra                217     219     219     218     218     218     218
sha256-sbase                204     213     211     214     208     218     219
sha256-tomcrypt             218     216     217     216     216     216     214
sha256-lzma                 277     278     279     280     279     280     279
sha256-bsd                  280     282     284     285     283     284     285
sha256-cppcrypto            282     286     285     286     278     286     288
sha256-cppcrypto-shani     1207    1259    1266    1269    1267    1267    1266
sha256-cppcrypto-ssse3      307     308     309     308     309     309     308
sha256-cppcrypto-avx        308     308     310     309     309     307     309
sha256-cppcrypto-ni        1203    1233    1240    1242    1235    1246    1240
sha256-openssl             1226    1231    1237    1238    1237    1238    1220

sha512_256-sbase            345     343     347     346     349     349     349
sha512_256-bsd              402     410     410     411     412     411     410
sha512_256-cppcrypto        438     441     455     450     448     452     453

sha512-cifra                337     340     340     341     340     341     340
sha512-sbase                348     349     348     350     349     347     349
sha512-bsd                  402     410     412     410     412     413     412
sha512-cppcrypto            434     438     450     450     449     446     446
sha512-cppcrypto-ssse3      476     481     482     482     483     483     483
sha512-cppcrypto-avx2       540     547     549     544     549     548     550
sha512-cppcrypto-avx        479     483     484     487     488     488     488
sha512-openssl              608     609     611     610     610     610     611
```

```
Linux 5.10.0-13-amd64 #1 SMP Debian 5.10.106-1 (2022-03-17) x86_64 GNU/Linux
Architecture: x86_64 - Intel(R) Core(TM) i7-3632QM CPU @ 2.20GHz
CC=gcc CFLAGS=-Os
implementation               1k      4k     16k     64k    256k      1m      4m
sha256-cifra                 52      51      53      53      74     137     138
sha256-sbase                150     150     151     142     147     150     151
sha256-tomcrypt             146     142     134     142     145     145     142
sha256-lzma                 183     182     183     177     174     185     185
sha256-bsd                  192     185     179     185     196     195     192
sha256-cppcrypto            192     197     197     195     188     196     197
sha256-cppcrypto-ssse3      264     257     249     244     263     253     263
sha256-cppcrypto-avx        263     263     259     242     262     259     263
sha256-openssl              298     299     299     275     298     299     257

sha512_256-sbase            219     231     230     219     218     232     229
sha512_256-bsd              297     300     298     287     295     299     291
sha512_256-cppcrypto        306     309     302     292     311     307     308

sha512-cifra                196     202     218     210     217     218     212
sha512-sbase                229     231     229     221     232     232     220
sha512-bsd                  290     300     299     285     299     293     289
sha512-cppcrypto            297     305     308     290     307     295     310
sha512-cppcrypto-ssse3      378     379     309     339     380     374     359
sha512-cppcrypto-avx        376     380     382     387     387     367     391
sha512-openssl              423     425     425     425     403     423     425
```

```
Linux 5.17.0-rc7-asahi-g4a4f4ec03834 #1 SMP PREEMPT Sat Mar 12 18:16:45 UTC 2022 GNU/Linux
Architecture: aarch64 - Apple M1 Little Endian
Flags:        fp asimd aes sha1 sha2 crc32 cpuid sha3 sha512 ...
CC=gcc CFLAGS=-Os
implementation               1k      4k     16k     64k    256k      1m      4m
sha256-cifra                 69      89      95     130     186     244     255
sha256-sbase                160     160     159     158     158     158     159
sha256-tomcrypt             160     160     158     159     158     158     159
sha256-lzma                 273     276     275     276     275     275     275
sha256-bsd                  292     292     291     291     292     291     292
sha256-cppcrypto            285     286     285     285     285     285     284
sha256-cppcrypto-armv8     1946    1957    1959    1959    1958    1956    1955
sha256-openssl             2180    2192    2195    2195    2195    2197    2196

sha512_256-sbase            273     273     265     267     266     267     269
sha512_256-bsd              468     469     469     468     468     468     468
sha512_256-cppcrypto        454     456     457     455     456     455     455

sha512-cifra                444     445     443     442     442     440     443
sha512-sbase                273     273     264     267     265     266     268
sha512-bsd                  469     470     469     466     468     468     469
sha512-cppcrypto            455     456     456     456     456     455     456
sha512-openssl             1280    1284    1285    1285    1285    1284    1282
```

```
Linux 5.15.0-2-powerpc64 #1 SMP Debian 5.15.5-2 (2021-12-18) ppc64 GNU/Linux
Architecture: ppc64 - POWER8 Model 2.1 (pvr 004b 0201) - Big Endian
CC=gcc CFLAGS=-Os
implementation               1k      4k     16k     64k    256k      1m      4m
sha256-cifra                142     141     142     141     140     142     142
sha256-sbase                111     112     104     112     112     112     112
sha256-tomcrypt             110     110     107     110     111     111     111
sha256-lzma                 171     171     170     171     171     171     171
sha256-bsd                  187     188     189     189     189     189     189
sha256-cppcrypto            187     189     190     189     190     188     190
sha256-openssl              360     363     364     365     364     365     365

sha512_256-sbase            168     169     169     169     170     169     169
sha512_256-bsd              285     286     289     289     289     289     289
sha512_256-cppcrypto        291     291     296     293     294     292     293

sha512-cifra                222     223     224     224     224     224     224
sha512-sbase                168     169     169     170     169     170     168
sha512-bsd                  285     288     289     289     289     289     288
sha512-cppcrypto            287     291     292     292     291     292     293
sha512-openssl              571     580     583     583     583     578     583
```

```
Linux 3.10.0-1127.13.1.el7.ppc64le #1 SMP Tue Jun 23 16:24:35 UTC 2020 ppc64le GNU/Linux
Architecture: ppc64le - POWER8 (2.1 pvr 004b 0201)
CC=gcc CFLAGS=-Os
implementation               1k      4k     16k     64k    256k      1m      4m
sha256-cifra                106     107     101     101     101     101     101
sha256-sbase                 81      81      81      85      85      85      91
sha256-tomcrypt              87      87      87      87      87      90      92
sha256-lzma                 126     127     127     127     127     135     135
sha256-bsd                  160     161     161     161     161     161     169
sha256-cppcrypto            148     149     149     149     149     149     149
sha256-openssl              221     224     225     225     225     225     225

sha512_256-sbase            171     172     172     172     172     172     172
sha512_256-bsd              254     257     258     258     258     258     258
sha512_256-cppcrypto        273     278     278     279     279     279     279

sha512-cifra                208     209     209     210     211     210     210
sha512-sbase                171     172     172     172     172     172     172
sha512-bsd                  254     257     258     258     257     257     258
sha512-cppcrypto            273     278     278     279     279     279     279
sha512-openssl              344     347     349     350     350     350     350
```

```
Linux 3.10.0-862.14.4.el7.ppc64 #1 SMP Wed Sep 26 20:38:32 GMT 2018 GNU/Linux
Architecture: ppc64 - POWER7 (2.1 pvr 003f 0201)
CC=gcc CFLAGS=-Os
implementation               1k      4k     16k     64k    256k      1m      4m
sha256-cifra                107     108     108     108      89     141     142
sha256-sbase                119     119     119     120     120     120     120
sha256-tomcrypt             107     107     107     107     107     107     108
sha256-lzma                 130     130     130     130     130     130     130
sha256-bsd                  183     184     181     184     185     185     185
sha256-cppcrypto            158     159     158     159     159     159     160
sha256-openssl              253     254     255     255     255     255     255

sha512_256-sbase            190     191     191     190     191     192     191
sha512_256-bsd              301     303     304     304     304     304     304
sha512_256-cppcrypto        272     274     275     276     275     275     273

sha512-cifra                223     224     223     224     224     224     224
sha512-sbase                190     191     191     191     191     192     191
sha512-bsd                  301     304     304     304     304     304     304
sha512-cppcrypto            271     274     275     275     275     276     275
sha512-openssl              400     405     406     406     406     406     406
```

```
Linux 4.18.0-348.2.1.el8_5.aarch64 #1 SMP Tue Nov 16 14:41:36 UTC 2021 aarch64 GNU/Linux
Architecture: aarch64 - X-Gene Little Endian (3300 MHz)
Flags:        fp asimd evtstrm aes pmull sha1 sha2 crc32 cpuid
CC=gcc CFLAGS=-Os
implementation               1k      4k     16k     64k    256k      1m      4m
sha256-cifra                 97      97      97      97      97      97      97
sha256-sbase                108     108     108     108     108     108     108
sha256-tomcrypt             108     108     108     108     108     108     108
sha256-lzma                 136     136     136     136     136     136     136
sha256-bsd                  156     156     157     157     157     157     157
sha256-cppcrypto            150     150     150     150     150     150     150
sha256-cppcrypto-armv8      677     686     688     689     689     689     689
sha256-openssl              671     676     677     677     676     677     678

sha512_256-sbase            163     164     164     164     164     164     164
sha512_256-bsd              249     250     251     251     251     251     251
sha512_256-cppcrypto        239     241     242     241     241     241     241

sha512-cifra                155     156     156     157     157     157     157
sha512-sbase                164     164     164     164     164     164     164
sha512-bsd                  249     251     251     250     251     251     251
sha512-cppcrypto            240     241     242     241     241     241     241
sha512-openssl              264     265     266     266     266     266     266
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
