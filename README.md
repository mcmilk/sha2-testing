
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
sha256-cifra                298     302     302     303     301     300     298
sha256-sbase                315     315     315     316     315     315     315
sha256-tomcrypt             303     304     304     300     301     301     301
sha256-lzma                 417     416     410     411     415     416     415
sha256-openssl              396     398     398     396     397     398     398
sha256-bsd                  395     396     397     397     396     397     397
sha256-cppcrypto            460     463     464     464     463     463     463
sha256-cppcrypto-shani     2267    2280    2284    2287    2288    2285    2284

sha512_256-sbase            492     490     496     496     496     496     496
sha512_256-bsd              601     607     602     607     604     606     606
sha512_256-cppcrypto        734     739     737     736     737     737     737

sha512-cifra                474     476     476     479     474     476     472
sha512-sbase                493     496     492     492     495     496     495
sha512-openssl              598     605     607     607     607     607     607
sha512-bsd                  595     603     607     606     609     606     605
sha512-cppcrypto            733     738     739     736     737     736     738
```

```
Linux 5.10.0-13-amd64 #1 SMP Debian 5.10.106-1 (2022-03-17) x86_64 GNU/Linux
Architecture: x86_64 - Intel(R) Core(TM) i3-1005G1 CPU @ 1.20GHz
CC=gcc CFLAGS=-Os
implementation               1k      4k     16k     64k    256k      1m      4m
sha256-cifra                217     219     219     218     219     219     219
sha256-sbase                219     217     218     217     217     218     218
sha256-tomcrypt             225     225     224     226     225     225     226
sha256-lzma                 280     281     282     282     283     280     280
sha256-openssl              279     284     285     284     286     285     284
sha256-bsd                  277     280     280     281     278     280     280
sha256-cppcrypto            278     281     282     288     288     285     284
sha256-cppcrypto-shani     1194    1227    1236    1237    1237    1238    1238

sha512_256-sbase            344     350     351     350     351     351     351
sha512_256-bsd              405     411     414     415     415     412     414
sha512_256-cppcrypto        435     449     458     459     459     459     458

sha512-cifra                339     339     340     340     341     341     341
sha512-sbase                341     349     347     347     351     350     348
sha512-openssl              408     412     414     414     415     414     415
sha512-bsd                  405     413     415     414     415     415     415
sha512-cppcrypto            435     449     452     453     446     444     449
```

```
Linux 5.15.0-2-powerpc64 #1 SMP Debian 5.15.5-2 (2021-12-18) ppc64 GNU/Linux
Architecture: ppc64 - POWER8 Model 2.1 (pvr 004b 0201) - Big Endian
CC=gcc CFLAGS=-Os
implementation               1k      4k     16k     64k    256k      1m      4m
sha256-cifra                138     140     140     139     140     139     139
sha256-sbase                109     112     112     112     111     112     112
sha256-tomcrypt             111     111     111     111     112     111     111
sha256-lzma                 170     171     171     171     171     171     171
sha256-openssl              185     187     187     187     187     187     187
sha256-bsd                  185     187     187     187     187     187     187
sha256-cppcrypto            188     190     190     191     191     191     191

sha512_256-sbase            169     170     170     170     170     169     170
sha512_256-bsd              283     285     286     286     286     287     286
sha512_256-cppcrypto        291     294     295     295     295     295     295

sha512-cifra                226     227     227     228     228     228     228
sha512-sbase                169     170     170     170     170     170     170
sha512-openssl              282     285     286     286     282     287     287
sha512-bsd                  283     286     281     287     284     287     287
sha512-cppcrypto            290     294     295     295     295     295     294
```

```
Linux 3.10.0-1127.13.1.el7.ppc64le #1 SMP Tue Jun 23 16:24:35 UTC 2020 ppc64le GNU/Linux
Architecture: ppc64le - POWER8 (2.1 pvr 004b 0201)
CC=gcc CFLAGS=-Os
implementation               1k      4k     16k     64k    256k      1m      4m
sha256-cifra                112     107     107     107     107     107     113
sha256-sbase                 91      91      91      91      91      95      96
sha256-tomcrypt              92      92      92      93      93      98      98
sha256-lzma                 135     135     135     136     142     142     142
sha256-openssl              167     168     169     169     169     169     169
sha256-bsd                  167     168     169     169     169     168     169
sha256-cppcrypto            150     151     151     151     151     151     151

sha512_256-sbase            170     171     170     171     172     172     172
sha512_256-bsd              250     253     253     254     254     254     254
sha512_256-cppcrypto        276     279     280     280     280     280     280

sha512-cifra                208     210     209     210     210     210     210
sha512-sbase                170     171     171     172     172     172     172
sha512-openssl              250     253     254     253     254     254     254
sha512-bsd                  250     253     254     254     254     254     253
sha512-cppcrypto            276     279     280     280     278     280     280
```

```
Linux 3.10.0-862.14.4.el7.ppc64 #1 SMP Wed Sep 26 20:38:32 GMT 2018 GNU/Linux
Architecture: ppc64 - POWER7 (2.1 pvr 003f 0201)
CC=clang CFLAGS=-Os
implementation               1k      4k     16k     64k    256k      1m      4m
sha256-cifra                104     104     105     104     140     138     139
sha256-sbase                109     109     109     109     109     109     109
sha256-tomcrypt             125     125     125     125     125     125     125
sha256-lzma                 202     203     204     204     203     203     203
sha256-openssl              159     161     161     161     160     158     161
sha256-bsd                  157     158     159     158     159     161     159
sha256-cppcrypto            223     225     225     225     225     225     225

sha512_256-sbase            181     181     182     182     183     182     179
sha512_256-bsd              245     247     247     247     247     248     240
sha512_256-cppcrypto        338     347     348     348     348     348     348

sha512-cifra                213     215     215     216     215     215     216
sha512-sbase                181     182     183     183     183     183     183
sha512-openssl              244     244     246     246     247     246     247
sha512-bsd                  244     246     246     246     247     246     247
sha512-cppcrypto            343     347     348     348     348     348     349
```

```
Linux 5.17.0-rc7-asahi-g4a4f4ec03834 #1 SMP PREEMPT Sat Mar 12 18:16:45 UTC 2022 GNU/Linux
Architecture: aarch64 - Apple M1 Little Endian
Flags:        fp asimd aes sha1 sha2 crc32 cpuid sha3 sha512 ...
CC=gcc CFLAGS=-Os
implementation               1k      4k     16k     64k    256k      1m      4m
sha256-cifra                 69      69      89     147     178     243     255
sha256-sbase                160     160     160     160     160     160     160
sha256-tomcrypt             160     160     160     160     160     160     160
sha256-lzma                 276     276     276     276     276     276     276
sha256-openssl              292     292     292     291     292     292     292
sha256-bsd                  292     292     291     291     292     292     292
sha256-cppcrypto            285     286     286     286     286     286     286

sha512_256-sbase            273     273     273     273     273     273     272
sha512_256-bsd              469     469     470     469     469     469     469
sha512_256-cppcrypto        455     456     456     456     456     456     456

sha512-cifra                445     446     446     446     446     446     446
sha512-sbase                273     273     273     273     273     273     273
sha512-openssl              469     469     469     469     469     469     469
sha512-bsd                  468     469     469     469     469     469     469
sha512-cppcrypto            455     456     457     456     457     456     456
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
sha256-lzma                 135     136     136     135     135     135     135
sha256-openssl              158     159     159     159     159     159     159
sha256-bsd                  158     159     159     159     159     159     159
sha256-cppcrypto            152     152     152     152     152     152     152

sha512_256-sbase            167     167     168     168     168     168     168
sha512_256-bsd              247     249     249     249     249     249     249
sha512_256-cppcrypto        237     239     239     239     239     239     239

sha512-cifra                155     156     156     156     156     156     155
sha512-sbase                167     168     168     168     168     168     168
sha512-openssl              247     249     249     249     249     249     249
sha512-bsd                  247     249     249     249     249     249     249
sha512-cppcrypto            237     239     239     239     239     239     239
```

```
Linux 3.13.0-170-generic #220-Ubuntu SMP Thu May 9 12:45:18 UTC 2019 aarch64 GNU/Linux
Architecture: aarch64 Little Endian
Features:     fp asimd evtstrm
CC=gcc CFLAGS=-Os
implementation               1k      4k     16k     64k    256k      1m      4m
sha256-cifra                 63      63      63      63      63      63      63
sha256-sbase                 69      69      70      69      69      69      69
sha256-tomcrypt              70      70      70      70      70      70      70
sha256-lzma                  66      66      66      66      66      65      66
sha256-openssl               98      98      98      98      98      98      98
sha256-bsd                   98      98      98      98      98      98      98
sha256-cppcrypto             80      80      80      80      80      80      80

sha512_256-sbase            106     106     106     106     106     106     106
sha512_256-bsd              135     136     136     135     135     135     135
sha512_256-cppcrypto        134     134     134     134     134     134     134

sha512-cifra                 95      96      96      95      95      95      95
sha512-sbase                106     106     106     106     106     106     106
sha512-openssl              135     136     136     135     135     135     135
sha512-bsd                  135     136     134     135     135     135     135
sha512-cppcrypto            134     134     134     134     134     134     134
```

```
Linux 5.10.63-v7l+ #1496 SMP Wed Dec 1 15:58:56 GMT 2021 armv7l GNU/Linux
Architecture: armv7l - Cortex-A72 Little Endian
Flags:        half thumb fastmult vfp edsp neon vfpv3 tls vfpv4 ... crc32
CC=gcc CFLAGS=-O2
implementation               1k      4k     16k     64k    256k      1m      4m
sha256-cifra                 73      73      73      73      73      73      73
sha256-sbase                 78      78      78      78      78      78      78
sha256-openssl              105     106     106     106     106     106     106
sha256-bsd                  105     106     106     106     106     106     106
sha256-cppcrypto             97      97      97      97      99      98      99

sha512_256-sbase             47      48      47      48      48      48      47
sha512_256-bsd               47      47      47      47      47      47      47
sha512_256-cppcrypto         50      50      50      50      50      50      50

sha512-cifra                 41      41      41      41      41      41      41
sha512-sbase                 47      47      47      48      47      48      47
sha512-openssl               47      47      47      47      47      47      47
sha512-bsd                   47      47      47      47      47      47      47
sha512-cppcrypto             50      50      50      50      50      50      50
```

```
SunOS gcc-solaris11 5.11 11.3 sun4u sparc SUNW,SPARC-Enterprise
Architecture: sparcv9 - SPARC64-VII (portid 1024 impl 0x7 ver 0x91 2520 MHz)
CC=gcc CFLAGS=-Os
implementation               1k      4k     16k     64k    256k      1m      4m
sha256-cifra                 39      39      39      39      39      39      39
sha256-sbase                 48      48      48      48      48      48      48
sha256-tomcrypt              47      47      47      47      47      47      47
sha256-lzma                  56      57      57      57      56      56      56
sha256-openssl               60      60      60      60      60      60      59
sha256-bsd                   60      60      60      60      60      60      57
sha256-cppcrypto             59      59      59      59      59      59      59

sha512_256-sbase             21      21      21      21      21      21      21
sha512_256-bsd               19      19      19      19      19      19      19
sha512_256-cppcrypto         18      18      18      18      18      18      18

sha512-cifra                 18      18      18      18      18      18      18
sha512-sbase                 21      21      21      21      21      21      21
sha512-openssl               19      19      19      19      19      19      19
sha512-bsd                   19      19      19      19      19      19      19
sha512-cppcrypto             18      18      18      18      18      18      18
```
