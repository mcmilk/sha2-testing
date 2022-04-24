
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
sha256-cifra                304     301     304     302     304     303     302
sha256-sbase                320     319     321     321     320     321     321
sha256-tomcrypt             301     302     302     302     303     302     303
sha256-lzma                 411     404     405     400     405     409     403
sha256-bsd                  393     395     397     396     397     397     396
sha256-cppcrypto            456     457     459     460     458     460     460
sha256-openssl             2259    2276    2280    2281    2281    2283    2284
sha256-cppcrypto-shani     2271    2281    2281    2282    2283    2284    2284

sha512_256-sbase            490     490     494     493     493     490     492
sha512_256-bsd              594     601     604     600     602     601     600
sha512_256-cppcrypto        722     728     725     730     729     730     730

sha512-cifra                475     477     476     475     475     477     478
sha512-sbase                482     487     490     489     488     490     490
sha512-bsd                  594     597     599     600     601     604     602
sha512-cppcrypto            720     729     730     726     731     729     729
sha512-openssl             1074    1080    1082    1082    1082    1079    1082
```

```
Linux 5.10.0-13-amd64 #1 SMP Debian 5.10.106-1 (2022-03-17) x86_64 GNU/Linux
Architecture: x86_64 - Intel(R) Core(TM) i3-1005G1 CPU @ 1.20GHz
CC=gcc CFLAGS=-Os
implementation               1k      4k     16k     64k    256k      1m      4m
sha256-cifra                214     218     218     219     219     219     219
sha256-sbase                223     218     219     218     219     218     219
sha256-tomcrypt             225     225     225     226     226     226     223
sha256-lzma                 283     283     283     284     282     283     282
sha256-bsd                  278     281     282     286     284     284     285
sha256-cppcrypto            283     289     291     292     292     292     292
sha256-openssl             1227    1235    1238    1239    1237    1237    1207
sha256-cppcrypto-shani     1192    1235    1244    1246    1247    1244    1245

sha512_256-sbase            329     331     331     331     334     352     352
sha512_256-bsd              411     413     414     415     414     415     415
sha512_256-cppcrypto        439     446     447     448     446     445     450

sha512-cifra                339     340     341     341     341     341     341
sha512-sbase                344     349     351     352     352     351     352
sha512-bsd                  409     413     415     416     415     414     414
sha512-cppcrypto            434     448     452     456     456     452     453
sha512-openssl              606     608     611     612     612     612     612
```

```
Linux 5.10.0-13-amd64 #1 SMP Debian 5.10.106-1 (2022-03-17) x86_64 GNU/Linux
Architecture: x86_64 - Intel(R) Core(TM) i7-3632QM CPU @ 2.20GHz
CC=gcc CFLAGS=-Os
implementation               1k      4k     16k     64k    256k      1m      4m
sha256-cifra                129     130     130     141     135     136     134
sha256-sbase                148     150     151     139     145     144     143
sha256-tomcrypt             142     135     145     136     140     141     141
sha256-lzma                 184     176     184     182     180     182     184
sha256-bsd                  173     188     197     192     198     193     194
sha256-cppcrypto            175     188     186     194     190     186     191
sha256-openssl              270     292     297     299     271     291     285

sha512_256-sbase            228     228     232     220     222     221     225
sha512_256-bsd              279     271     293     281     273     282     283
sha512_256-cppcrypto        299     306     298     290     302     304     302

sha512-cifra                217     200     216     221     213     219     217
sha512-sbase                223     228     225     206     227     220     216
sha512-bsd                  290     278     289     290     294     284     279
sha512-cppcrypto            300     309     306     293     303     301     306
sha512-openssl              424     425     420     378     424     406     423
```

```
Linux 5.17.0-rc7-asahi-g4a4f4ec03834 #1 SMP PREEMPT Sat Mar 12 18:16:45 UTC 2022 GNU/Linux
Architecture: aarch64 - Apple M1 Little Endian
Flags:        fp asimd aes sha1 sha2 crc32 cpuid sha3 sha512 ...
CC=gcc CFLAGS=-Os
implementation               1k      4k     16k     64k    256k      1m      4m
sha256-cifra                 69      76      90     147     180     244     255
sha256-sbase                160     160     160     160     160     160     160
sha256-tomcrypt             160     160     160     160     160     160     160
sha256-lzma                 276     275     276     275     276     276     276
sha256-bsd                  293     292     292     292     292     292     292
sha256-cppcrypto            285     286     286     286     286     286     286
sha256-openssl             2179    2193    2196    2195    2193    2196    2195

sha512_256-sbase            273     273     273     273     273     273     273
sha512_256-bsd              469     469     469     469     469     469     469
sha512_256-cppcrypto        455     456     457     457     456     456     456

sha512-cifra                446     446     446     446     446     446     446
sha512-sbase                273     273     273     273     273     273     273
sha512-bsd                  469     469     469     469     469     470     469
sha512-cppcrypto            455     456     457     457     456     456     456
sha512-openssl             1281    1285    1286    1286    1286    1286    1286
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
sha256-cifra                100     100     100     100     100     100     100
sha256-sbase                107     108     108     108     108     108     108
sha256-tomcrypt             104     104     104     104     104     105     105
sha256-lzma                 137     137     138     137     137     137     137
sha256-bsd                  158     159     159     159     159     159     159
sha256-cppcrypto            149     150     150     150     150     150     150
sha256-openssl              671     676     676     677     676     677     677

sha512_256-sbase            167     168     168     167     168     167     168
sha512_256-bsd              247     249     248     249     249     249     249
sha512_256-cppcrypto        239     241     241     241     241     241     241

sha512-cifra                155     156     156     156     156     156     156
sha512-sbase                167     168     167     168     168     168     168
sha512-bsd                  247     249     249     249     249     249     249
sha512-cppcrypto            239     241     241     241     241     241     241
sha512-openssl              264     266     266     266     266     266     266
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
